//====================================================================
//
// 青弾[BlueBullet.cpp]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/09	作成
//====================================================================
 
//*******************************************************************************
// インクルード部
//*******************************************************************************
#include	"BulletBlue.h"
#include	"MyVector.h"
#include	"Texture.h"

//========================= グローバル変数定義 ===========================
DrawBuffer* BulletBlue::m_pBuffer = NULL;
FBXPlayer* BulletBlue::m_pFBX = NULL;

//==============================================================
//
//	BlueBullet::コンストラクタ
// 
//==============================================================
BulletBlue::BulletBlue()
{
	/* テクスチャ読み込み */
	LoadTextureFromFile("Assets/Texture/flowerblue.png", &m_pBulletBlueTex);
	SetRBFlg(false);	// 青弾
	
}

//==============================================================
//
//	BlueBullet::デストラクタ
// 
//==============================================================
BulletBlue::~BulletBlue()
{
	Uninit();
}

//====================================================================
//
//	BlueBullet::初期化
//
//====================================================================
bool BulletBlue::Init()
{
	/* モデル読み込み */
	if (m_pBuffer == NULL) {
		LoadBullet("Assets/Model/flowerblue.fbx");
	}
	//m_floweAnim[0] = m_pFBX->LoadAnimation("Assets/Model/flowerblue_anime.fbx");

	return true;
}

//void BulletBlue::Update() {
//	m_pFBX->Play(0);
//	m_pFBX->Step();
//}

//==============================================================
//
//	BlueBullet::終了処理
// 
//==============================================================
void BulletBlue::Unint()
{
	SAFE_RELEASE(m_pBulletBlueTex);
	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pFBX;
		m_pFBX = NULL;
	}

}

//==============================================================
//
//	RedBullet::描画
// 
//==============================================================
void BulletBlue::Draw()
{
	//SHADER->Bind(VS_ANIMATION,PS_UNLIT);
	//m_pFBX->Step();

	// 弾のテクスチャ
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			//* DirectX::XMMatrixRotationY(-m_DwarfAngle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		SHADER->SetAnimation(m_pFBX->GetAnimeMatrix(i), m_pFBX->GetAnimeMatrixNum(i));
		SHADER->SetTexture(m_pBulletBlueTex);

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
bool BulletBlue::LoadBullet(const char* pFilePath)
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