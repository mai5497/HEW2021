//****************************************************
//
//	オブジェクトベース[StageObjectBase.cpp]
//	作成者：吉原飛鳥
//	
//	2022/01/18 :作成 
//
//****************************************************

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"StageObjectBase.h"

 //*******************************************************************************
 // グローバル変数
 //*******************************************************************************
DrawBuffer* StageObjectBase::m_pBuffer = NULL;
FBXPlayer* StageObjectBase::m_pFBX = NULL;

//==============================================================
//
//	ObjectBaseクラス::コンストラクタ
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
StageObjectBase::StageObjectBase()
{
	//---変数初期化
	/*m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;

	m_size.x = 1.0f;
	m_size.y = 1.0f;
	m_size.z = 1.0f;*/

	// テクスチャ読み込み
	//LoadTextureFromFile(m_TexPath, &m_pStageObjectTex);

	// モデル読み込み
	//LoadStageObject(m_ModelPath);

	m_collisionType = COLLISION_STATIC;
}

//==============================================================
//
//	ObjectBaseクラス::デストラクタ
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
StageObjectBase::~StageObjectBase()
{

}


//==============================================================
//
//	ObjectBaseクラス::更新
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void StageObjectBase::Update()
{

}
//==============================================================
//
//	ObjectBaseクラス::描画
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void StageObjectBase::Draw()
{
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			* DirectX::XMMatrixRotationY(XM_PI)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pStageObjectTex);
		/*
		SHADER->SetTexture(m_fbx.GetTexture(i));
		*/

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}

//==============================================================
//
//	ObjectBaseクラス::テクスチャパスを設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void StageObjectBase::SetTexPath(LPCSTR TexPath)
{
	m_TexPath = TexPath;
}

//==============================================================
//
//	ObjectBaseクラス::モデルパス設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void StageObjectBase::SetModelPath(LPCSTR ModelPath)
{
	m_ModelPath = ModelPath;
}

//==============================================================
//
//	ObjectBaseクラス::テクスチャパスを取得
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
LPCSTR StageObjectBase::GetTexPath()
{
	return m_TexPath;
}

//==============================================================
//
//	ObjectBaseクラス::モデルパスを取得
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
LPCSTR StageObjectBase::GetModelPath()
{
	return m_ModelPath;
}

//==============================================================
//
//	ObjectBaseクラス::オブジェクト生成
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void StageObjectBase::CreateStageObject(XMFLOAT3 pos, XMFLOAT3 size, LPCSTR TexPath, LPCSTR ModelPath)
{
	//---座標・サイズの指定
	m_pos= pos;					
	m_size = size;

	//---テクスチャ・モデルの読み込み
	if (m_pBuffer == NULL) {
		LoadTextureFromFile(TexPath, &m_pStageObjectTex);			// テクスチャ
	}
	if (m_pFBX == NULL) {
		LoadStageObject(ModelPath);												// モデル
	}

}

//==============================================================
//
//	ObjectBaseクラス::モデル読み込み
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
bool StageObjectBase::LoadStageObject(const char* pFilePath)
{
	/* 以下はモデルが来たら使用 */
	HRESULT hr;
	m_pFBX = new FBXPlayer;
	hr = m_pFBX->LoadModel(pFilePath);
	if (FAILED(hr))
	{
		return false;
	}

	//モデルのメッシュの数だけ頂点バッファ作成
	int meshNum = m_pFBX->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++)
	{
		//メッシュごとに頂点バッファ作成
		m_pBuffer[i].CreateVertexBuffer(
			m_pFBX->GetVertexData(i),
			m_pFBX->GetVertexSize(i),
			m_pFBX->GetVertexCount(i)
		);
		//インデックスバッファ作成
		m_pBuffer[i].CreateIndexBuffer(
			m_pFBX->GetIndexData(i),
			m_pFBX->GetIndexCount(i)
		);

	}

	return true;
}