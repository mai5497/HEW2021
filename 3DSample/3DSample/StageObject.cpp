//****************************************************
//
//	ステージオブジェクト[ObjectStage.cpp]
//	作成者：吉原飛鳥
//	
//	2022/01/18 :作成 
//
//****************************************************
// 
 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"StageObject.h"

 //*******************************************************************************
 // 定数・マクロ定義
 //*******************************************************************************
#define	OBJECT_SIZE		(XMFLOAT3(0.5f,0.5f,0.5f))

 //*******************************************************************************
 // グローバル変数
 //*******************************************************************************
//DrawBuffer* StageObject::m_pBuffer = NULL;
//FBXPlayer* StageObject::m_pFBX = NULL;

//==============================================================
//
//	BlueBullet::コンストラクタ
// 
//==============================================================
StageObject::StageObject()
{

}

//==============================================================
//
//	BlueBullet::デストラクタ
// 
//==============================================================
StageObject::~StageObject()
{

}

//==============================================================
//
//	BlueBullet::初期化
// 
//==============================================================
bool StageObject::Init()
{
	//---変数初期化
	//m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//m_size = (OBJECT_SIZE);

	GameObject::Init();

	return true;
}

//==============================================================
//
//	BlueBullet::終了
// 
//==============================================================
void StageObject::Uninit()
{
	////---テクスチャ解放
	//SAFE_RELEASE(m_pObjectStageTex);

	//if (m_pBuffer != NULL) {
	//	delete[] m_pBuffer;
	//	m_pBuffer = NULL;
	//	delete m_pFBX;
	//	 m_pFBX  = NULL;
 //	}

	GameObject::Uninit();
}

//==============================================================
//
//	BlueBullet::描画
// 
//==============================================================
void StageObject::Draw()
{
	////モデル描画
	//int meshNum = m_pFBX->GetMeshNum();
	//for (int i = 0; i < meshNum; ++i) {
	//	SHADER->SetWorld(
	//		XMMatrixScaling(m_size.x, m_size.y, m_size.z) *
	//		XMMatrixRotationY(-m_Angle.y) *
	//		XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

	//	SHADER->SetTexture(m_pObjectStageTex);

	//	m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//}

	StageObjectBase::Draw();
}

////====================================================================
////
////		テクスチャ読み込み
////
////====================================================================
//bool StageObject::LoadStageObject(const char* pFilePath)
//{
//	/* 以下はモデルが来たら使用 */
//	HRESULT hr;
//	m_pFBX = new FBXPlayer;
//	hr = m_pFBX->LoadModel(pFilePath);
//	if (FAILED(hr))
//	{
//		return false;
//	}
//
//	//モデルのメッシュの数だけ頂点バッファ作成
//	int meshNum = m_pFBX->GetMeshNum();
//	m_pBuffer = new DrawBuffer[meshNum];
//	for (int i = 0; i < meshNum; i++)
//	{
//		//メッシュごとに頂点バッファ作成
//		m_pBuffer[i].CreateVertexBuffer(
//			m_pFBX->GetVertexData(i),
//			m_pFBX->GetVertexSize(i),
//			m_pFBX->GetVertexCount(i)
//		);
//		//インデックスバッファ作成
//		m_pBuffer[i].CreateIndexBuffer(
//			m_pFBX->GetIndexData(i),
//			m_pFBX->GetIndexCount(i)
//		);
//
//	}
//	return true;
//
//}
