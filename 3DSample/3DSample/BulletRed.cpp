//====================================================================
//
// 赤弾[BulletRed.cpp]
// 作成者:伊地田真衣
// 
// 更新日:2022/01/08	作成
//====================================================================

//*******************************************************************************
// インクルード部
//*******************************************************************************
#include "BulletRed.h"
#include "MyVector.h"
#include "Texture.h"

//========================= グローバル変数定義 ===========================
DrawBuffer* BulletRed::m_pBuffer = NULL;
FBXPlayer* BulletRed::m_pFBX = NULL;


//==============================================================
//
//	BulletRed::コンストラクタ
// 
//==============================================================
BulletRed::BulletRed()
{
	//----- 変数初期化 -----
	LoadTextureFromFile("Assets/Texture/flowerred.png", &m_pBulletRedTex);
	SetRBFlg(true);	// 赤弾
}

//==============================================================
//
//	BulletRed::デストラクタ
// 
//==============================================================
BulletRed::~BulletRed()
{
	Uninit();
}

//==============================================================
//
//	BulletRed::初期化
// 
//==============================================================
bool BulletRed::Init()
{
	/* 以下はモデルが来たら使用 */
	if (m_pBuffer == NULL) {
		BulletRed::LoadBullet("Assets/Model/flowerred.fbx");
	}

	GameObject::Init();
	return true;

}

//==============================================================
//
//	BulletRed::終了処理
// 
//==============================================================
void BulletRed::Unint()
{
	SAFE_RELEASE(m_pBulletRedTex);
	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pFBX;
		m_pFBX = NULL;
	}

	GameObject::Uninit();

}

//==============================================================
//
//	BulletRed::描画
// 
//==============================================================
void BulletRed::Draw()
{
	// 弾のテクスチャ
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			//* DirectX::XMMatrixRotationY(-m_DwarfAngle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pBulletRedTex);
		/*
		SHADER->SetTexture(m_fbx.GetTexture(i));
		*/

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

}


//====================================================================
//
//		テクスチャ読み込み
//
//====================================================================
bool BulletRed::LoadBullet(const char* pFilePath)
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