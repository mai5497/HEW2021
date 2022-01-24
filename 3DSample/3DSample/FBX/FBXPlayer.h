#ifndef __FBX_PLAYER_H__
#define __FBX_PLAYER_H__

#include <d3d11.h>
#include <DirectXMath.h>

const int BLEND_NUM = 2;
const int PARAMETRIC_NUM = 2;

typedef int ANIME_INDEX;

struct FBXPlayAnimeValue
{
	float value[9];
};
struct FBXPlayBoneInfo
{
	DirectX::XMMATRIX matrix;
	DirectX::XMMATRIX preMat;
	FBXPlayAnimeValue keyFrame;
	DirectX::XMFLOAT3 start;
	DirectX::XMFLOAT3 end;
};
struct FBXPlayInfo
{
	int index;
	float frame;
	float total;
	float speed;
	bool loop;
	FBXPlayAnimeValue* pPlayAnime;
};

class FBXPlayer
{
public:
	FBXPlayer();
	~FBXPlayer();

	// モデルの読み込み(一体のみ
	HRESULT LoadModel(const char* model);
	// アニメーションの読み込み(10アニメーションまで
	ANIME_INDEX LoadAnimation(const char* anime);

	//--- アニメーション
	// アニメーション更新
	void Step(float speed = 1.0f);
	// すぐに再生
	void Play(ANIME_INDEX anime, bool loop = false, float speed = 1.0f);
	// 遷移しながら再生
	void PlayBlend(ANIME_INDEX anime, bool loop = false, float blend = 0.2f, float start = 0.0f, float speed = 1.0f);
	// 混ぜ合わせながら再生
	void PlayParametric(ANIME_INDEX a, ANIME_INDEX b, bool loop = false, float blend = 0.2f, float start = 0.0f, float speed = 1.0f);
	// 混ぜる割合
	void SetParametric(float rate);
	// 再生中か判定
	bool IsPlay();

	//--- 各種情報
	// メッシュ
	int GetMeshNum();
	void* GetVertexData(int mesh);
	UINT GetVertexSize(int mesh);
	UINT GetVertexCount(int mesh);
	const long* GetIndexData(int mesh);
	UINT GetIndexCount(int mesh);
	ID3D11ShaderResourceView* GetTexture(int mesh);
	// メッシュごとのアニメーション
	DirectX::XMMATRIX* GetAnimeMatrix(int mesh);
	UINT GetAnimeMatrixNum(int mesh);
	// ボーン
	int GetBoneNum();
	const FBXPlayBoneInfo* GetBoneInfo(int bone);
private:

	void InitPlayInfo(FBXPlayInfo* pInfo);
	void CopyPlayInfo(FBXPlayInfo* pA, FBXPlayInfo* pB);
	void UpdatePlayInfo(FBXPlayInfo* pInfo, float speed);
	void CalcPlayInfo(FBXPlayInfo* pInfo);
	void CalcBone(int index, DirectX::XMMATRIX mat, DirectX::XMVECTOR pos);
private:
	int m_modelID;
	int *m_pAnimes;

	FBXPlayBoneInfo* m_pBones;

	float m_blendTime;
	float m_totalBlendTime;
	float m_parametricBlend;
	FBXPlayInfo m_blendSet[BLEND_NUM];
	FBXPlayInfo m_parametricSet[PARAMETRIC_NUM];
};




#endif // __FBX_PLAYER_H__