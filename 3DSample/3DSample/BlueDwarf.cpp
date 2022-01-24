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
#include "GameScene.h"

//========================= 定数定義 ===========================


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
	LoadTextureFromFile("Assets/Model/kobitoblue.png", &m_pBlueDwarfTex);

	m_DwarfAngle = 0.0f;


	SetRBFlg(false);	// 青小人

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
	if (m_pBuffer == NULL) {
		LoadDwarf("Assets/Model/kobitoblue.fbx");
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

	SAFE_RELEASE(m_pBlueDwarfTex);
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
	float vAngle;		// 目的位置の角度

	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);


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
	if (GetFollowFlg()) {		// 追跡フラグが立っているとき
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * DWARF_FOLLOW_SPEED);
		SetMoveFlg(true);
	} else if (GetrunFlg()) {	// 弾から逃げるとき
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * -DWARF_RUN_SPEED);
		SetMoveFlg(true);
	} else {	// 徘徊時
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * DWARF_DEFAULT_SPEED);
		SetMoveFlg(true);
	}

	// Float3型に変換
	XMStoreFloat3(&m_move, vDirection);

	// アークタンジェント(逆正接)
	vAngle = XMConvertToDegrees(atan2(m_move.z, m_move.x));
	float DiffAngle = vAngle - m_DwarfAngle;
	if (DiffAngle >= 180.0f) {
		DiffAngle -= 360.0f;
	}
	if (DiffAngle < -180.0f) {
		DiffAngle += 360.0f;
	}
	m_DwarfAngle += DiffAngle * RATE_ROTATE_DWARF;
	if (m_DwarfAngle >= 180.0f) {
		m_DwarfAngle -= 360.0f;
	}
	if (m_DwarfAngle < -180.0f) {
		m_DwarfAngle += 360.0f;
	}


	//if (jumpFlg) {
	//	m_move.y -= 0.21f;
	//}

	Differ = fabsf(m_targetPos.x - m_pos.x) + fabsf(m_targetPos.z - m_pos.z);
	if (GetrunFlg() && Differ > 15.0f) {	// なんとなく離れたとき。マジックナンバーでごめん。
		SetrunFlg(false);
		SetMoveFlg(false);
	}
	if (Differ < 0.025f && GetFollowFlg()) {	// なんとなく近くにいるとき。マジックナンバーでごめん。
		SetFollowFlg(false);
		SetMoveFlg(false);
	}

	if (!GetLiftFlg()) {
		// 重力をかける
		m_move.y -= GRAVITY;
	} else {
		// 浮く
		m_move.y += LIFTPOWER;
		if (m_pos.y > COLLECTOR_POS_Y) {
			SetLiftFlg(false);
		}
	}




	// 移動
	if (GetMoveFlg()) {
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
		m_pos.z += m_move.z;
		if (GetLiftFlg()) {
			m_pos.x += 0.0f;
			m_pos.y += m_move.y;
			m_pos.z += 0.0f;
		}
	} else {
		if (GetLiftFlg()) {
			m_pos.x += 0.0f;
			m_pos.y += m_move.y;
			m_pos.z += 0.0f;
		}
	}
	
	if (m_pos.y < 0.5f) {
		/* todo: ゲームオーバーの瞬間にその小人にカメラ寄る */
		BlueDwarf::SetAliveFlg(false);
	}

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
			*DirectX::XMMatrixRotationY(-XMConvertToRadians(m_DwarfAngle) + (XM_PI * 0.5f))
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pBlueDwarfTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}




//====================================================================
//
//		テクスチャ読み込み
//
//====================================================================
bool BlueDwarf::LoadDwarf(const char* pFilePath)
{
	HRESULT hr;
	m_pFBX = new FBXPlayer;
	hr = m_pFBX->LoadModel(pFilePath);
	if (FAILED(hr)){
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