//****************************************************
//
//	赤小人
//	作成者：伊地田真衣
//	
//	2021/12/04 : 作成(伊地田)
//	2021/12/09 : 仮素材導入(伊地田)
//	2021/12/21 : 新素材
//
//
//****************************************************


//========================= インクルード部 ===========================
#include "RedDwarf.h"
#include "MyVector.h"
#include "Collision.h"
#include "Player.h"
#include "Texture.h"
#include "GameScene.h"
#include "FBX//FBXPlayer.h"
#include "DrawBuffer.h"




//========================= 定数定義 ===========================
#define DWARF_SIZE	(0.7f)
#define GRAVITY		(0.3f)

//========================= グローバル変数定義 ===========================
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
	LoadTextureFromFile("Assets/Model/kobitored.png", &m_pRedDwarfTex);

	m_move = XMFLOAT3(0.0f,0.0f,0.0f);

	m_size = XMFLOAT3(DWARF_SIZE, DWARF_SIZE, DWARF_SIZE);

	m_Radius = XMFLOAT3(2.0f, 1.0f, 2.0f);

	SetRBFlg(true);	// 赤小人
	use = true;
}


//====================================================================
//
//		デストラクタ
//
//====================================================================
RedDwarf:: ~RedDwarf()
{
	Uninit();
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
		RedDwarf::LoadDwarf("Assets/Model/kobitored.fbx");
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
	SAFE_RELEASE(m_pRedDwarfTex);
	if (m_pBuffer != NULL) {
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
void RedDwarf::Update()
{	
	//----- 変数初期化 -----
	//static bool jumpFlg;
	float Differ;		// 小人と弾の距離の差
	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);

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
	if (GetFollowFlg()) {		// 追跡フラグが立っているとき
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * 5);
	} else if (GetrunFlg()) {	// 弾から逃げるとき
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * -1.5);
	} else {
		vDirection = XMVectorScale(vDirection, (1.0f / 60));
	}
	// Float3型に変換
	XMStoreFloat3(&m_move, vDirection);



	// アークタンジェント(逆正接)
	m_DwarfAngle = atan2(m_move.z, m_move.x);
	m_DwarfAngle -= DirectX::XM_PI * 0.5f;


	//if (jumpFlg) {
	//	m_move.y -= 0.21f;
	//}

	Differ = fabsf(m_targetPos.x - m_pos.x) + fabsf(m_targetPos.z - m_pos.z);
	if (GetrunFlg() || Differ > 0.3f) {	// なんとなく離れたとき。マジックナンバーでごめん。
		//SetMoveFlg(false);		// 移動許可おろす
		SetrunFlg(false);
	}

	// 重力をかける
	m_move.y -= GRAVITY;

	// 移動
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	if (m_pos.y < 0.5f) {
		RedDwarf::SetAliveFlg(false);
	}

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

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixRotationY(-m_DwarfAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pRedDwarfTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
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