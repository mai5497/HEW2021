//****************************************************
//
//	青小人
//	作成者：伊地田真衣
//	
//	2021/12/21 : 赤をコピーして作成
//				 追跡追加
//				 モデル差し替え
//
//****************************************************


//========================= インクルード部 ===========================
#include "BlueDwarf.h"
#include "MyVector.h"
#include "Collision.h"
#include "Player.h"
#include "Texture.h"
#include "Bullet.h"
#include "GameScene.h"

//========================= 定数定義 ===========================
#define DWARF_SIZE (0.7f)

//========================= グローバル変数定義 ===========================
DrawBuffer *BlueDwarf::m_pBuffer = NULL;
FBXPlayer *BlueDwarf::m_pFBX = NULL;

//====================================================================
//
//		コンストラクタ
//
//====================================================================
BlueDwarf::BlueDwarf()
{
	//----- 変数初期化 -----
	LoadTextureFromFile("Assets/Texture/kobitoblue.png", &m_pBlueDwarfTex);

	m_move.x = 0.0f;
	m_move.y = 0.0f;
	m_move.z = 0.0f;
	m_size.x = DWARF_SIZE;
	m_size.y = DWARF_SIZE;
	m_size.z = DWARF_SIZE;

	
	SetRBFlg(false);	// 青小人
	use = true;
}


//====================================================================
//
//		デストラクタ
//
//====================================================================
BlueDwarf:: ~BlueDwarf()
{
	Uninit();
}


//====================================================================
//
//		初期化
//
//====================================================================
bool BlueDwarf::Init()
{
	/* 以下はモデルが来たら使用 */
	if (m_pBuffer == NULL) {
		BlueDwarf::LoadDwarf("Assets/Model/kobitoblue.fbx");
	}

	GameObject::Init();
	return true;
}


//====================================================================
//
//		終了処理
//
//====================================================================
void BlueDwarf::Uninit()
{
	if (m_pBuffer != NULL) 
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pFBX;
		m_pFBX = NULL;
	}
	GameObject::Uninit();
}


//====================================================================
//
//		更新処理
//
//====================================================================
void BlueDwarf::Update()
{	
	//----- 変数初期化 -----
	//static bool jumpFlg;
	float Differ;		// 小人と弾の距離の差


	// 追従するターゲットの座標
	XMVECTOR vTarget = XMLoadFloat3(&m_targetPos);

	// 小人の座標
	XMVECTOR vBlueDwarfPos = XMLoadFloat3(&m_pos);

	// 進行方向							　　↓ベクトルの引き算
	XMVECTOR vDirection = XMVectorSubtract(vTarget, vBlueDwarfPos);

	// 一定の速度にするために正規化
	// 速度を変えるならvDirectonに速度をかける。
	vDirection = XMVector3Normalize(vDirection);

	// かける関数								  ↓かける数
	vDirection = XMVectorScale(vDirection, 1.0f / 60);

	// Float3型に変換
	if (GetFollowFlg()) {	// 追跡フラグが立っているとき
		XMStoreFloat3(&m_move, vDirection * 5);
	}
	if (GetrunFlg()) {		// 弾から逃げるとき
		XMStoreFloat3(&m_move, -(vDirection * 5));
	}

	// アークタンジェント(逆正接)
	m_DwarfAngle = atan2(m_move.z, m_move.x);
	m_DwarfAngle -= DirectX::XM_PI * 0.5f;

	//if(m_AttackFlg) {
	//	m_move.y += 0.2f;
	//	jumpFlg = true;
	//} else {
	//	jumpFlg = false;
	//}

	//if (jumpFlg) {
	//	m_move.y -= 0.21f;
	//}

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
void BlueDwarf::Draw()
{

	// 小人のテクスチャ
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(
			DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixRotationY(-m_DwarfAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pBlueDwarfTex);
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
void BlueDwarf::Attack()
{


}


//====================================================================
//
//		テクスチャ読み込み
//
//====================================================================
bool BlueDwarf::LoadDwarf(const char* pFilePath)
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