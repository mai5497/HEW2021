//****************************************************
//
//	赤小人
//	作成者：伊地田真衣
//	
//	2021/12/04 : 作成
//	2021/12/09 : 仮素材導入
//
//****************************************************


//========================= インクルード部 ===========================
#include "RedDwarf.h"
#include "MyVector.h"
#include "Collision.h"
#include "Player.h"
#include "Texture.h"
#include "Bullet.h"
#include "GameScene.h"

#define DWARF_SIZE (1.0f)

DrawBuffer *RedDwarf::m_pBuffer = NULL;
FBXPlayer *RedDwarf::m_pFBX = NULL;


//====================================================================
//
//		コンストラクタ
//
//====================================================================
RedDwarf::RedDwarf() 
{
	//----- 変数初期化 -----
	LoadTextureFromFile("Assets/Model/kougeki.png", &m_pRedDwarfTex);

	m_move.x = 0.0f;
	m_move.y = 0.0f;
	m_move.z = 0.0f;

}


//====================================================================
//
//		デストラクタ
//
//====================================================================
RedDwarf:: ~RedDwarf()
{

}


//====================================================================
//
//		初期化
//
//====================================================================
bool RedDwarf::Init()
{
	/* 以下はモデルが来たら使用 */
	if (m_pBuffer == NULL) {
		RedDwarf::LoadDwarf("Assets/Model/kougeki.fbx");
	}

	GameObject::Init();
	return true;
}


//====================================================================
//
//		終了処理
//
//====================================================================
void RedDwarf::Uninit()
{
	if (m_pBuffer != NULL) 
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pFBX;
		m_pFBX = NULL;
	}
}


//====================================================================
//
//		更新処理
//
//====================================================================
void RedDwarf::Update()
{	
	//----- 変数初期化 -----
	static bool jumpFlg;

	// 追従するターゲットの座標
	XMVECTOR vTarget = XMLoadFloat3(&m_targetPos);

	// 小人の座標
	XMVECTOR vRedDwarfPos = XMLoadFloat3(&m_pos);

	// 進行方向							　　↓ベクトルの引き算
	XMVECTOR vDirection = XMVectorSubtract(vTarget, vRedDwarfPos);

	// 一定の速度にするために正規化
	// 速度を変えるならvDirectonに速度をかける。
	vDirection = XMVector3Normalize(vDirection);

	// かける関数								  ↓かける数
	vDirection = XMVectorScale(vDirection, 1.0f / 60);

	// Float3型に変換
	XMStoreFloat3(&m_move, vDirection * 5);

	// アークタンジェント(逆正接)
	m_DwarfAngle = atan2(m_move.z, m_move.x);
	m_DwarfAngle -= DirectX::XM_PI * 0.5f;

	if(m_AttackFlg) {
		m_move.y += 0.2f;
		jumpFlg = true;
	} else {
		jumpFlg = false;
	}

	if (jumpFlg) {
		m_move.y -= 0.21f;
	}

	// 移動
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	m_currentPos = m_pos;
}


//====================================================================
//
//		描画処理
//
//====================================================================
void RedDwarf::Draw()
{

	// 小人のテクスチャ
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(
			DirectX::XMMatrixScaling(DWARF_SIZE, DWARF_SIZE, DWARF_SIZE)
			*DirectX::XMMatrixRotationY(-m_DwarfAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pRedDwarfTex);
		/*SHADER->SetTexture(
		m_fbx.GetTexture(i)
		);*/

		m_pBuffer[i].Draw(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
	}
}


//====================================================================
//
//		攻撃
//
//====================================================================
void RedDwarf::Attack()
{


}


//====================================================================
//
//		テクスチャ読み込み
//
//====================================================================
bool RedDwarf::LoadDwarf(const char* pFilePath)
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