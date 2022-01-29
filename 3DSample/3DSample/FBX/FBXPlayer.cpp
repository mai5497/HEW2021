#include "FBXPlayer.h"
#include <vector>
#include <map>
#include "FBXLoader.h"
#include <DirectXMath.h>
#include "../Texture.h"
#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#define SAFE_DELETE(p) do{if(p){delete p;}}while(0)
#define SAFE_DELETE_ARRAY(p) do{if(p){delete[] p;}}while(0)

const int MAX_FBX_ANIME = 10;

struct FBXVertex
{
	float pos[3];
	float color[4];
	float uv[2];
	float normal[3];
	float weight[4];
	long index[4];
};

class FBXResourceManager
{
public:
	struct FBXFile
	{
		ggfbx::MeshList mesh;
		ggfbx::BoneListInfo bone;
		ggfbx::MaterialList material;
		ggfbx::AnimationInfo anime;
		FBXVertex** ppVtx;
		bool* pUseIndex;
		int* pAnimeBoneIndex;

		DirectX::XMMATRIX** ppMeshBoneMatrix;
		struct MeshBoneInfo
		{
			int boneIdx;
			DirectX::XMMATRIX inv;
		};
		MeshBoneInfo** ppMeshBone;
	};
private:
	typedef std::pair<std::string, FBXFile*> ModelKey;
	typedef std::vector<ModelKey> ModelLibrary;
	typedef std::map<std::string, ID3D11ShaderResourceView*> TextureMap;
public:
	FBXResourceManager()
	{
	}
	~FBXResourceManager()
	{
		ModelLibrary::iterator it = m_modelLibrary.begin();
		while (it != m_modelLibrary.end())
		{
			auto mesh = it->second->mesh;
			auto meshIt = mesh.begin();
			while (meshIt != mesh.end())
			{
				int idx = meshIt - mesh.begin();
				SAFE_DELETE_ARRAY(it->second->ppVtx[idx]);
				SAFE_DELETE_ARRAY(it->second->ppMeshBoneMatrix[idx]);
				SAFE_DELETE_ARRAY(it->second->ppMeshBone[idx]);
				++meshIt;
			}
			SAFE_DELETE_ARRAY(it->second->ppMeshBoneMatrix);
			SAFE_DELETE_ARRAY(it->second->ppMeshBone);
			SAFE_DELETE_ARRAY(it->second->pAnimeBoneIndex);
			SAFE_DELETE_ARRAY(it->second->pUseIndex);
			SAFE_DELETE_ARRAY(it->second->ppVtx);

			ggfbx::Cleanup(&it->second->mesh, &it->second->bone, &it->second->material, &it->second->anime);
			SAFE_DELETE(it->second);
			++it;
		}
		m_modelLibrary.clear();

		TextureMap::iterator texIt = m_textureMap.begin();
		while (texIt != m_textureMap.end())
		{
			texIt->second->Release();
			++texIt;
		}
		m_textureMap.clear();
	}

	int Load(const char* model, bool isAnimeOnly)
	{
		ModelLibrary::iterator it = m_modelLibrary.begin();
		while (it != m_modelLibrary.end())
		{
			if (it->first == model)
			{
				return static_cast<int>(it - m_modelLibrary.begin());
			}
			++it;
		}

		// 新規追加
		ModelKey key(model, new FBXFile);
		bool isLoad = false;
		if (isAnimeOnly)
		{
			isLoad = ggfbx::Load(model, NULL, &key.second->bone, NULL, &key.second->anime);
		}
		else
		{
			isLoad = ggfbx::Load(model, &key.second->mesh, &key.second->bone, &key.second->material, NULL);
		}

		if(isLoad)
		{
			key.second->ppMeshBone = nullptr;
			key.second->ppMeshBoneMatrix = nullptr;
			key.second->pAnimeBoneIndex = nullptr;
			key.second->pUseIndex = nullptr;
			key.second->ppVtx = nullptr;
			if (isAnimeOnly)
			{
				auto& anime = key.second->anime;
				auto& bone = key.second->bone.list;

				key.second->pAnimeBoneIndex = new int[anime.curveList.size()];
				auto animeIt = anime.curveList.begin();
				while (animeIt != anime.curveList.end())
				{
					auto boneIt = bone.begin();
					while (boneIt != bone.end())
					{
						if (animeIt->name == boneIt->name)
						{
							key.second->pAnimeBoneIndex[animeIt - anime.curveList.begin()] = boneIt - bone.begin();
							break;
						}
						++boneIt;
					}
					++animeIt;
				}
			}
			else
			{
				// 頂点データ作成
				MakeVertexData(
					&key.second->ppVtx,
					&key.second->pUseIndex,
					key.second->mesh);
				// テクスチャ読み込み
				auto matIt = key.second->material.begin();
				while (matIt != key.second->material.end())
				{
					auto texIt = matIt->textureList.begin();
					while (texIt != matIt->textureList.end())
					{
						if (m_textureMap.find(texIt->c_str()) == m_textureMap.end())
						{

							// フォルダ確認
							std::string path;
							if (!PathFileExists(texIt->c_str())) {
								// 見つからなかった
								char modelDir[MAX_PATH];
								char fileName[MAX_PATH];
								char fileExt[MAX_PATH];
								_splitpath(texIt->c_str(), nullptr, nullptr, fileName, fileExt);
								_splitpath(model, nullptr, modelDir, nullptr, nullptr);
								std::string path = modelDir;
								path += fileName;
								path += fileExt;
							}
							else
							{
								path = texIt->c_str();
							}

							if (path.length() > 0)
							{
								ID3D11ShaderResourceView* pTexture;
								if (SUCCEEDED(LoadTextureFromFile(path.c_str(), &pTexture)))
								{
									m_textureMap.insert(std::pair<std::string, ID3D11ShaderResourceView*>(
										path.c_str(), pTexture));
								}
							}
						}
						texIt++;
					}
					++matIt;
				}
				// アニメーション行列
				auto& mesh = key.second->mesh;
				key.second->ppMeshBoneMatrix = new DirectX::XMMATRIX*[mesh.size()];
				key.second->ppMeshBone = new FBXFile::MeshBoneInfo*[mesh.size()];
				auto meshIt = mesh.begin();
				while (meshIt != mesh.end())
				{
					int idx = meshIt - mesh.begin();
					key.second->ppMeshBoneMatrix[idx] = nullptr;
					key.second->ppMeshBone[idx] = nullptr;
					if (meshIt->skinInfo.boneList.size() > 0)
					{
						auto& meshBone = meshIt->skinInfo.boneList;
						int meshBoneNum = meshBone.size();
						key.second->ppMeshBoneMatrix[idx] = new DirectX::XMMATRIX[meshBoneNum];
						key.second->ppMeshBone[idx] = new FBXFile::MeshBoneInfo[meshBoneNum];
						auto meshBoneIt = meshBone.begin();
						while (meshBoneIt != meshBone.end())
						{
							int meshBoneIdx = meshBoneIt - meshBone.begin();
							key.second->ppMeshBoneMatrix[idx][meshBoneIdx] = DirectX::XMMatrixIdentity();
							auto& bone = key.second->bone.list;
							auto boneIt = bone.begin();
							while (boneIt != bone.end())
							{
								if (boneIt->name == meshBoneIt->name)
								{
									key.second->ppMeshBone[idx][meshBoneIdx].boneIdx = boneIt - bone.begin();
									DirectX::XMFLOAT4X4* pOffset = reinterpret_cast<DirectX::XMFLOAT4X4*>(meshBoneIt->offset);
									key.second->ppMeshBone[idx][meshBoneIdx].inv =
										DirectX::XMMatrixInverse(nullptr, DirectX::XMLoadFloat4x4(pOffset));
									break;
								}
								++boneIt;
							}
							++meshBoneIt;
						}
					}
					++meshIt;
				}
			}

			m_modelLibrary.push_back(key);
			return m_modelLibrary.size() - 1;
		}
		else
		{
			delete key.second;
		}
		return -1;
	}

	const FBXFile* Get(int index)
	{
		if (m_modelLibrary.size() <= index) { return nullptr; }
		return m_modelLibrary[index].second;
	}
	ID3D11ShaderResourceView* GetTexture(const char* name)
	{
		auto it = m_textureMap.find(name);
		if (it != m_textureMap.end())
		{
			return it->second;
		}
		return nullptr;
	}

private:
	void MakeVertexData(FBXVertex*** pppVtx, bool** ppUseIndex, ggfbx::MeshList& mesh)
	{
		*pppVtx = new FBXVertex*[mesh.size()];
		*ppUseIndex = new bool[mesh.size()];
		auto meshIt = mesh.begin();
		while (meshIt != mesh.end())
		{
			// インデックスバッファを利用して描画するか検証
			bool& isIdxDraw = (*ppUseIndex)[meshIt - mesh.begin()];
			isIdxDraw = true;
			if (meshIt->normalInfo.mapping == ggfbx::MAPPING_INDEX)
			{
				isIdxDraw = false;
			}
			if (meshIt->uvList.size() > 0 && meshIt->uvList[0].mapping == ggfbx::MAPPING_INDEX)
			{
				// 単一uvのみに対応
				isIdxDraw = false;
			}

			// 頂点バッファ作成
			int vtxNum = isIdxDraw ? meshIt->vertexList.size() : meshIt->indexList.size();
			FBXVertex* pVtx = (*pppVtx)[meshIt - mesh.begin()] = new FBXVertex[vtxNum];
			for (int i = 0; i < vtxNum; ++i)
			{
				// それぞれのインデックスを取得
				int vtxIdx = i;
				int normIdx = i;
				int uvIdx = i;
				if (!isIdxDraw)
				{
					vtxIdx = meshIt->indexList[i];
					if (meshIt->normalInfo.mapping == ggfbx::MAPPING_VERTEX)
					{
						normIdx = vtxIdx;
					}
					if (meshIt->uvList.size() > 0 && meshIt->uvList[0].mapping == ggfbx::MAPPING_VERTEX)
					{
						uvIdx = vtxIdx;
					}
				}
				// 頂点
				DirectX::XMVECTOR vec = DirectX::XMVector3TransformCoord(
					DirectX::XMVectorSet(
						meshIt->vertexList[vtxIdx].x,
						meshIt->vertexList[vtxIdx].y,
						meshIt->vertexList[vtxIdx].z, 0),
					DirectX::XMMatrixSet(
						meshIt->transform._11, meshIt->transform._12, meshIt->transform._13, meshIt->transform._14,
						meshIt->transform._21, meshIt->transform._22, meshIt->transform._23, meshIt->transform._24,
						meshIt->transform._31, meshIt->transform._32, meshIt->transform._33, meshIt->transform._34,
						meshIt->transform._41, meshIt->transform._42, meshIt->transform._43, meshIt->transform._44)
				);
				DirectX::XMFLOAT3 pos;
				DirectX::XMStoreFloat3(&pos, vec);
				pVtx->pos[0] = pos.x;
				pVtx->pos[1] = pos.y;
				pVtx->pos[2] = pos.z;
				// カラー
				pVtx->color[0] = pVtx->color[1] = pVtx->color[2] = pVtx->color[3] = 1.0f;
				// UV
				if (meshIt->uvList.size() > 0)
				{
					pVtx->uv[0] = meshIt->uvList[0].list[uvIdx].x;
					pVtx->uv[1] = 1 - meshIt->uvList[0].list[uvIdx].y;
				}
				else
				{
					pVtx->uv[0] = pVtx->uv[1] = 0.0f;
				}
				// 法線
				if (meshIt->normalInfo.list.size() > 0)
				{
					pVtx->normal[0] = meshIt->normalInfo.list[normIdx].x;
					pVtx->normal[1] = meshIt->normalInfo.list[normIdx].y;
					pVtx->normal[2] = meshIt->normalInfo.list[normIdx].z;
				}
				else
				{
					pVtx->normal[0] = pVtx->normal[1] = 0.0f;
					pVtx->normal[2] = 1.0f;
				}
				// ウェイト
				if (meshIt->skinInfo.weightList.size() > 0)
				{
					for (int i = 0; i < ggfbx::MeshInfo::SkinInfo::WeightInfo::WEIGHT_NUM_MAX; ++i)
					{
						auto value = meshIt->skinInfo.weightList[vtxIdx].value[i];
						pVtx->weight[i] = value.weight;
						pVtx->index[i] = value.index;
					}
				}
				else
				{
					for (int i = 0; i < ggfbx::MeshInfo::SkinInfo::WeightInfo::WEIGHT_NUM_MAX; ++i)
					{
						pVtx->weight[i] = 0.0f;
						pVtx->index[i] = 0;
					}
					pVtx->weight[0] = 1.0f;
				}

				++pVtx;
			}

			++meshIt;
		}
	}

private:
	ModelLibrary m_modelLibrary;
	TextureMap m_textureMap;
};

FBXResourceManager g_fbxManager;

FBXPlayer::FBXPlayer()
	: m_modelID(-1)
	, m_pBones(nullptr)
	, m_blendTime(0.0f)
	, m_totalBlendTime(0.0f)
	, m_parametricBlend(0.0f)
{
	m_pAnimes = new int[MAX_FBX_ANIME];
	for (int i = 0; i < MAX_FBX_ANIME; ++i)
	{
		m_pAnimes[i] = -1;
	}
	for (int i = 0; i < BLEND_NUM; ++i)
	{
		InitPlayInfo(&m_blendSet[i]);
		m_blendSet[i].pPlayAnime = nullptr;
	}
	for (int i = 0; i < PARAMETRIC_NUM; ++i)
	{
		InitPlayInfo(&m_parametricSet[i]);
		m_parametricSet[i].pPlayAnime = nullptr;
	}
}
FBXPlayer::~FBXPlayer()
{
	for (int i = 0; i < PARAMETRIC_NUM; ++i)
	{
		SAFE_DELETE_ARRAY(m_parametricSet[i].pPlayAnime);
	}
	for (int i = 0; i < BLEND_NUM; ++i)
	{
		SAFE_DELETE_ARRAY(m_blendSet[i].pPlayAnime);
	}
	SAFE_DELETE_ARRAY(m_pBones);
	SAFE_DELETE_ARRAY(m_pAnimes);
}


HRESULT FBXPlayer::LoadModel(const char* file)
{
	if (m_modelID != -1) { return E_FAIL; }

	m_modelID = g_fbxManager.Load(file, false);
	if (m_modelID == -1) { return E_FAIL; }

	auto model = g_fbxManager.Get(m_modelID);
	auto bone = model->bone.list;
	int size = bone.size();
	if (size == 0) { return S_OK; }

	m_pBones = new FBXPlayBoneInfo[size];
	for (int i = 0; i < BLEND_NUM; ++i)
	{
		m_blendSet[i].pPlayAnime = new FBXPlayAnimeValue[size];
	}
	for (int i = 0; i < PARAMETRIC_NUM; ++i)
	{
		m_parametricSet[i].pPlayAnime = new FBXPlayAnimeValue[size];
	}
	auto boneIt = bone.begin();
	while (boneIt != bone.end())
	{
		int idx = boneIt - bone.begin();
		m_pBones[idx].keyFrame.value[0] = boneIt->translate.x;
		m_pBones[idx].keyFrame.value[1] = boneIt->translate.y;
		m_pBones[idx].keyFrame.value[2] = boneIt->translate.z;
		m_pBones[idx].keyFrame.value[3] = boneIt->rotation.x;
		m_pBones[idx].keyFrame.value[4] = boneIt->rotation.y;
		m_pBones[idx].keyFrame.value[5] = boneIt->rotation.z;
		m_pBones[idx].keyFrame.value[6] = boneIt->scale.x;
		m_pBones[idx].keyFrame.value[7] = boneIt->scale.y;
		m_pBones[idx].keyFrame.value[8] = boneIt->scale.z;
		m_pBones[idx].preMat =
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(boneIt->preRotate.x)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(boneIt->preRotate.y)) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(boneIt->preRotate.z));
		for (int i = 0; i < BLEND_NUM; ++i)
		{
			m_blendSet[i].pPlayAnime[idx] = m_pBones[idx].keyFrame;
		}
		for (int i = 0; i < PARAMETRIC_NUM; ++i)
		{
			m_parametricSet[i].pPlayAnime[idx] = m_pBones[idx].keyFrame;
		}
		++boneIt;
	}
	CalcBone(model->bone.root, DirectX::XMMatrixIdentity(), DirectX::XMVectorSet(0, 0, 0, 0));



	return S_OK;
}
ANIME_INDEX FBXPlayer::LoadAnimation(const char* anime)
{
	for (int i = 0; i < MAX_FBX_ANIME; ++i)
	{
		if (m_pAnimes[i] == -1)
		{
			m_pAnimes[i] = g_fbxManager.Load(anime, true);
			return m_pAnimes[i] == -1 ? -1 : i;
		}
	}
	return -1;
}

void FBXPlayer::Step(float speed)
{
	auto model = g_fbxManager.Get(m_modelID);
	auto& bone = model->bone;
	auto boneIt = bone.list.begin();

	// ブレンドモーションの更新
	for (int i = 0; i < BLEND_NUM; ++i)
	{
		if (m_blendSet[i].index == -1)
		{
			// パラメトリックの更新
			if (m_blendSet[i].total <= 0) { continue; }

			float rate = m_blendSet[i].frame / m_blendSet[i].total;
			m_parametricSet[0].frame = m_parametricSet[0].total * rate;
			m_parametricSet[1].frame = m_parametricSet[1].total * rate;
			for (int j = 0; j < PARAMETRIC_NUM; ++j)
			{
				CalcPlayInfo(&m_parametricSet[j]);
			}
			boneIt = bone.list.begin();
			while (boneIt != bone.list.end())
			{
				int idx = boneIt - bone.list.begin();
				for (int j = 0; j < ggfbx::AnimationInfo::CurveInfo::CHANNEL_MAX; ++j)
				{
					float a = m_parametricSet[0].pPlayAnime[idx].value[j];
					float b = m_parametricSet[1].pPlayAnime[idx].value[j];
					m_blendSet[i].pPlayAnime[idx].value[j] = (b - a)* m_parametricBlend + a;
				}
				++boneIt;
			}
		}
		else
		{
			CalcPlayInfo(&m_blendSet[i]);
		}
	}

	// キーフレーム合成
	float blend = m_blendTime / max(0.0001f, m_totalBlendTime);
	boneIt = bone.list.begin();
	while (boneIt != bone.list.end())
	{
		int idx = boneIt - bone.list.begin();
		if (blend > 0)
		{
			for (int i = 0; i < ggfbx::AnimationInfo::CurveInfo::CHANNEL_MAX; ++i)
			{
				float a = m_blendSet[0].pPlayAnime[idx].value[i];
				float b = m_blendSet[1].pPlayAnime[idx].value[i];
				m_pBones[idx].keyFrame.value[i] = (a - b) * blend + b;
			}
		}
		else
		{
			m_pBones[idx].keyFrame = m_blendSet[0].pPlayAnime[idx];
		}
		++boneIt;
	}

	// 更新
	CalcBone(bone.root, DirectX::XMMatrixIdentity(), DirectX::XMVectorSet(0,0,0,0));

	// メッシュごとに割り当て
	auto& mesh = model->mesh;
	auto meshIt = mesh.begin();
	while (meshIt != mesh.end())
	{
		int meshIdx = meshIt - mesh.begin();
		auto& meshBone = meshIt->skinInfo.boneList;
		auto meshBoneIt = meshBone.begin();
		while (meshBoneIt != meshBone.end())
		{
			int meshBoneIdx = meshBoneIt - meshBone.begin();
			model->ppMeshBoneMatrix[meshIdx][meshBoneIdx] = 
				model->ppMeshBone[meshIdx][meshBoneIdx].inv *
				m_pBones[model->ppMeshBone[meshIdx][meshBoneIdx].boneIdx].matrix;
			++meshBoneIt;
		}
		++meshIt;
	}

	// フレームの更新
	if (m_blendTime > 0)
	{
		m_blendTime -= speed / 60.0f;
		if (m_blendTime < 0)
		{
			CopyPlayInfo(&m_blendSet[0], &m_blendSet[1]);
			InitPlayInfo(&m_blendSet[1]);
		}
	}
	for (int i = 0; i < BLEND_NUM; ++i)
	{
		UpdatePlayInfo(&m_blendSet[i], speed);
	}
}

void FBXPlayer::Play(ANIME_INDEX anime, bool loop, float speed)
{
	if (anime < 0 || MAX_FBX_ANIME <= anime)
	{
		return;
	}

	for (int i = 0; i < BLEND_NUM; ++i)
	{
		InitPlayInfo(&m_blendSet[i]);
	}
	for (int i = 0; i < PARAMETRIC_NUM; ++i)
	{
		InitPlayInfo(&m_parametricSet[i]);
	}

	m_blendSet[0].index = m_pAnimes[anime];
	m_blendSet[0].loop = loop;
	m_blendSet[0].speed = speed;
	m_blendSet[0].total = g_fbxManager.Get(m_pAnimes[anime])->anime.totalFrame;
}
void FBXPlayer::PlayBlend(ANIME_INDEX anime, bool loop, float blend, float start, float speed)
{
	if (m_blendTime > 0.0f)
	{
		float processRate = m_blendTime / m_totalBlendTime;
		if (processRate > 0.55f)
		{
			CopyPlayInfo(&m_blendSet[0], &m_blendSet[1]);
		}
	}

	InitPlayInfo(&m_blendSet[1]);
	m_blendSet[1].index = m_pAnimes[anime];
	m_blendSet[1].loop = loop;
	m_blendSet[1].frame = start;
	m_blendSet[1].speed = speed;
	m_blendSet[1].total = g_fbxManager.Get(m_pAnimes[anime])->anime.totalFrame;

	m_blendTime = blend;
	m_totalBlendTime = blend;
}
void FBXPlayer::PlayParametric(ANIME_INDEX a, ANIME_INDEX b, bool loop, float blend, float start, float speed)
{
	if (m_blendTime > 0.0f)
	{
		float processRate = m_blendTime / m_totalBlendTime;
		if (processRate > 0.55f)
		{
			CopyPlayInfo(&m_blendSet[0], &m_blendSet[1]);
		}
	}
	InitPlayInfo(&m_blendSet[1]);
	m_blendSet[1].loop = loop;
	m_blendSet[1].frame = start;
	m_blendSet[1].speed = speed;
	m_blendSet[1].total = 1.0f;

	m_parametricSet[0].index = m_pAnimes[a];
	m_parametricSet[1].index = m_pAnimes[b];
	for (int i = 0; i < PARAMETRIC_NUM; ++i)
	{
		m_parametricSet[i].total = g_fbxManager.Get(m_parametricSet[i].index)->anime.totalFrame;
	}
	SetParametric(m_parametricBlend);

	m_blendTime = blend;
	m_totalBlendTime = blend;

}
void FBXPlayer::SetParametric(float rate)
{
	for (int i = 0; i < BLEND_NUM; ++i)
	{
		if (m_blendSet[i].index == -1 && m_blendSet[i].total > 0)
		{
			m_parametricBlend = rate;
			float a = m_parametricSet[0].total;
			float b = m_parametricSet[1].total;
			float totalTime = (b - a) * m_parametricBlend + a;
			m_blendSet[i].total = totalTime;
			if (m_blendSet[i].frame >= m_blendSet[i].total)
			{
				m_blendSet[i].frame -= m_blendSet[i].total;
			}
			break;
		}
	}
}
bool FBXPlayer::IsPlay()
{
	return m_blendSet[0].frame < m_blendSet[0].total
		|| m_blendSet[1].frame < m_blendSet[1].total;
}

int FBXPlayer::GetMeshNum()
{
	auto model = g_fbxManager.Get(m_modelID);
	if (model == nullptr) { return 0; }
	return model->mesh.size();
}
void* FBXPlayer::GetVertexData(int mesh)
{
	auto model = g_fbxManager.Get(m_modelID);
	if (model == nullptr) { return nullptr; }
	return model->ppVtx[mesh];
}
UINT FBXPlayer::GetVertexSize(int mesh)
{
	return sizeof(FBXVertex);
}
UINT FBXPlayer::GetVertexCount(int mesh)
{
	auto model = g_fbxManager.Get(m_modelID);
	if (model == nullptr) { return 0; }
	if (model->pUseIndex[mesh])
	{
		return model->mesh[mesh].vertexList.size();
	}
	else
	{
		return model->mesh[mesh].indexList.size();
	}
}

const long* FBXPlayer::GetIndexData(int mesh)
{
	auto model = g_fbxManager.Get(m_modelID);
	if (model == nullptr) { return nullptr; }
	return model->mesh[mesh].indexList.data();
}
UINT FBXPlayer::GetIndexCount(int mesh)
{
	auto model = g_fbxManager.Get(m_modelID);
	if (model == nullptr) { return 0; }
	if (model->pUseIndex[mesh])
	{
		return model->mesh[mesh].indexList.size();
	}
	return 0;
}
ID3D11ShaderResourceView* FBXPlayer::GetTexture(int mesh)
{
	auto model = g_fbxManager.Get(m_modelID);
	if (model == nullptr) { return nullptr; }
	auto matIt = model->material.begin();
	while (matIt != model->material.end())
	{
		if (!matIt->textureList.empty())
		{
			if (matIt->name == model->mesh[mesh].materialName)
			{
				return g_fbxManager.GetTexture(matIt->textureList[0].c_str());
			}
		}
		++matIt;
	}
	return nullptr;
}
DirectX::XMMATRIX* FBXPlayer::GetAnimeMatrix(int mesh)
{
	auto model = g_fbxManager.Get(m_modelID);
	if (model == nullptr) { return 0; }
	return model->ppMeshBoneMatrix[mesh];
}
UINT FBXPlayer::GetAnimeMatrixNum(int mesh)
{
	auto model = g_fbxManager.Get(m_modelID);
	if (model == nullptr) { return 0; }
	return model->mesh[mesh].skinInfo.boneList.size();
}
int FBXPlayer::GetBoneNum()
{
	auto model = g_fbxManager.Get(m_modelID);
	if (model == nullptr) { return 0; }
	return model->bone.list.size();	
}
const FBXPlayBoneInfo* FBXPlayer::GetBoneInfo(int bone)
{
	if (bone < 0 || GetBoneNum() <= bone)
	{
		return nullptr;
	}
	return &m_pBones[bone];
}


void FBXPlayer::InitPlayInfo(FBXPlayInfo* pInfo)
{
	pInfo->index = -1;
	pInfo->total = 0.f;
	pInfo->speed = 1.f;
	pInfo->frame = 0;
	pInfo->loop = false;
}
void FBXPlayer::CopyPlayInfo(FBXPlayInfo* pA, FBXPlayInfo* pB)
{
	pA->index = pB->index;
	pA->loop = pB->loop;
	pA->frame = pB->frame;
	pA->speed = pB->speed;
	pA->total = pB->total;
}
void FBXPlayer::UpdatePlayInfo(FBXPlayInfo* pInfo, float speed)
{
	if (pInfo->frame < pInfo->total)
	{
		pInfo->frame += pInfo->speed * speed;
		if (pInfo->frame >= pInfo->total)
		{
			if (pInfo->loop)
			{
				pInfo->frame -= pInfo->total;
			}
			else
			{
				pInfo->frame = pInfo->total;
			}
		}
	}
}

void FBXPlayer::CalcPlayInfo(FBXPlayInfo* pInfo)
{
	if (pInfo->index == -1) { return; }
	auto model = g_fbxManager.Get(pInfo->index);
	auto& anime = model->anime;
	auto& curve = anime.curveList;
	auto curveIt = curve.begin();
	int index = 0;
	while (curveIt != curve.end())
	{
		auto& defValue = model->bone.list[model->pAnimeBoneIndex[index]];
		float value[ggfbx::AnimationInfo::CurveInfo::CHANNEL_MAX] = {
			defValue.translate.x, defValue.translate.y, defValue.translate.z,
			defValue.rotation.x, defValue.rotation.y, defValue.rotation.z,
			defValue.scale.x, defValue.scale.y, defValue.scale.z,
		};
		for (int i = 0; i < ggfbx::AnimationInfo::CurveInfo::CHANNEL_MAX; ++i)
		{
			auto& key = curve[index].keyList[i];
			switch (key.size())
			{
			case 0:
				pInfo->pPlayAnime[model->pAnimeBoneIndex[index]].value[i] = value[i];
				break;
			case 1:
				pInfo->pPlayAnime[model->pAnimeBoneIndex[index]].value[i] = key[0].value;
				break;
			default:
			{
				auto keyIt = key.begin();
				auto preKeyIt = keyIt;
				while (keyIt != key.end())
				{
					if (preKeyIt->frame <= pInfo->frame && pInfo->frame < keyIt->frame)
					{
						float rate = (pInfo->frame - preKeyIt->frame) / (keyIt->frame - preKeyIt->frame);
						pInfo->pPlayAnime[model->pAnimeBoneIndex[index]].value[i] =
							(keyIt->value - preKeyIt->value) * rate + preKeyIt->value;
						break;
					}
					preKeyIt = keyIt;
					++keyIt;
				}
				if (keyIt == key.end())
				{
					pInfo->pPlayAnime[model->pAnimeBoneIndex[index]].value[i] = preKeyIt->value;
				}
			}
				break;
			}
		}
		
		++curveIt;
		++index;
	}
}
void FBXPlayer::CalcBone(int index, DirectX::XMMATRIX mat, DirectX::XMVECTOR pos)
{
	auto model = g_fbxManager.Get(m_modelID);
	auto& bone = model->bone.list[index];
	float* pValue = m_pBones[index].keyFrame.value;
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(pValue[0], pValue[1], pValue[2]);
	DirectX::XMMATRIX rotX = DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(pValue[3]));
	DirectX::XMMATRIX rotY = DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(pValue[4]));
	DirectX::XMMATRIX rotZ = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(pValue[5]));
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(pValue[6], pValue[7], pValue[8]);
	DirectX::XMMATRIX R = rotX * rotY * rotZ;

	mat = S * R * m_pBones[index].preMat * T * mat;
	m_pBones[index].matrix = mat;
	DirectX::XMStoreFloat3(&m_pBones[index].start, pos);
	pos = DirectX::XMVector3TransformCoord(DirectX::XMVectorSet(0, 0, 0, 0), mat);
	DirectX::XMStoreFloat3(&m_pBones[index].end, pos);

	for (int i = 0; i < bone.children.size(); ++i)
	{
		CalcBone(bone.children[i], mat, pos);
	}
}