/**
 * @file Player.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 *		 2021/12/19 赤青弾をわけて打てるように(伊地田)
 * @brief プレイヤーに関する処理
 */

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"Player.h"
#include	"Input.h"
#include	"TPSCamera.h"
#include	"MyVector.h"
#include	<math.h>
#include	"Controller.h"
#include	"MyMath.h"
#include	"Camera.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define FPS				(60)
#define PLAYER_SIZE_X	(0.8)
#define PLAYER_SIZE_Y	(0.8f)
#define PLAYER_SIZE_Z	(0.8f)

//*******************************************************************************
// グローバル宣言
//*******************************************************************************
XMFLOAT3 pOldCameraPos;


//==============================================================
//
//	Playerクラス::コンストラクタ
//	作成者	： 園田翔大
//	戻り値	： void
//	引数	： void
//
//==============================================================
Player::Player():
	m_pControllCamera(nullptr),
	m_throwFlg(false)
{
	//----- 変数初期化 -----
	LoadTextureFromFile("Assets/Model/player.png", &m_pPlayerTex);

	// ---変数初期化
	m_pos.x = 0.0f;
	m_pos.y = 2.0f;
	m_pos.z = -25.0f;
	m_Angle = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_DrawAngle = XM_PI;
	m_size = XMFLOAT3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z);

	m_pBuffer = nullptr;
	m_pFBX = nullptr;

	m_collisionType = COLLISION_DYNAMIC;
}

//==============================================================
//
//	Playerクラス::デストラクタ
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
Player::~Player()
{
	m_pControllCamera = nullptr;
	SAFE_RELEASE(m_pPlayerTex);
	
	Uninit();
}

//==============================================================
//
//	Playerクラス::Init
//	作成者	： 園田翔大
//	戻り値	： bool型
//	引数		： void
//
//==============================================================
bool Player::Init()
{
	//----- プレイヤー処理 -----
	if (m_pBuffer == nullptr) {
		LoadPlayer("Assets/Model/player.fbx");
	}
	m_playerAnim[STAND] = m_pFBX->LoadAnimation("Assets/Model/player_standby.fbx");
	m_playerAnim[THROW] = m_pFBX->LoadAnimation("Assets/Model/player_throw.fbx");

	return true;
}

//==============================================================
//
//	Playerクラス::Uninit
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
void Player::Uninit()
{

	if (m_pBuffer != nullptr) {
		delete[] m_pBuffer;
		m_pBuffer = nullptr;

		delete m_pFBX;
		m_pFBX = nullptr;
	}
	SAFE_RELEASE(m_pPlayerTex);
}

//==============================================================
//
//	Playerクラス::Update
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
void Player::Update() {
	//----- 変数初期化 -----
	//XMFLOAT2 Axis = LeftThumbPosition();
	//bool moveFlg = false;

	m_move = XMFLOAT3(m_BulletTargetPos.x, m_BulletTargetPos.y, m_BulletTargetPos.z - m_pos.z);
	
	if (IsRelease('E') || IsRelease('Q')) {
		m_pFBX->Play(m_playerAnim[THROW]);
	} 
	//m_pFBX->Play(m_playerAnim[STAND]);



	//描画用角度設定
	m_DrawAngle = atan2(m_move.z, m_move.x);
	m_DrawAngle -= XM_PI * 0.5f;
	if (m_pFBX->IsPlay()) {
		m_pFBX->Step();
	}
}

//==============================================================
//
//	Playerクラス::Draw
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
void Player::Draw()
{
	SHADER->Bind(VS_ANIMATION,PS_UNLIT);


	XMFLOAT3 pPos = m_pos;
	XMFLOAT3 pSize = m_size;


	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixRotationY(-m_DrawAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		SHADER->SetAnimation(m_pFBX->GetAnimeMatrix(i), m_pFBX->GetAnimeMatrixNum(i));
		SHADER->SetTexture(m_pPlayerTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}


}

//==============================================================
//
//	Playerクラス::プレイヤーに追跡する処理(エネミーが)
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： ゲームオブジェクト型
//
//==============================================================
void Player::PlayerToEnemy(GameObject* pObj)
{
	//敵の位置
	DirectX::XMFLOAT3 EnemyNear = pObj->GetPos();

	//プレイヤーの位置
	DirectX::XMFLOAT3 PlayerNear = m_pos;

	// 敵の移動方向(移動速度)をプレイヤーの方へ向ける
	DirectX::XMFLOAT3 dir;
	dir.x = m_pos.x - pObj->GetPos().x;
	dir.y = m_pos.y - pObj->GetPos().y;
	dir.z = m_pos.z - pObj->GetPos().z;

	//ベクトルの大きさ
	float L;
	L = sqrtf((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));			// 平方根で値算出

	// dir の長さを1にする(正規化)
	// 正規化 ... ベクトルの方向は維持したまま、大きさは1の値にすること
	dir.x = dir.x / L;
	dir.y = dir.y / L;
	dir.z = dir.z / L;

	// 長さが1になったベクトルに移動させたい速度をかける(敵の速度)
	dir.x = dir.x * 0.08f;
	dir.y = dir.y * 0.08f;
	dir.z = dir.z * 0.08f;

	pObj->SetMove(dir);

}


//==============================================================
//
//	Playerクラス::カメラをプレイヤーの位置にセット？
//	作成者	： 園田翔太
//	戻り値	： void
//	引数		： カメラクラス型
//
//==============================================================
void Player::SetControllCamera(Camera* pCamera)
{
	m_pControllCamera = pCamera;
}


//==============================================================
//
//	Playerクラス::カメラ位置を取得
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： TPSCamera型のポジション
//
//==============================================================
void Player::GetCameraPos(TPSCamera* pCamera)
{
	pOldCameraPos = pCamera->GetCameraPos();
}

//====================================================================
//
//		テクスチャ読み込み
//
//====================================================================
bool Player::LoadPlayer(const char* pFilePath) {
	HRESULT hr;
	m_pFBX = new FBXPlayer;
	hr = m_pFBX->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//モデルのメッシュの数だけ頂点バッファ作成
	int meshNum = m_pFBX->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
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

//==============================================================
//
//	Playerクラス::プレイヤーの座標を取得
//	作成者	: 吉原飛鳥
//	戻り値	: XMFLOAT3
//	引数		: なし 
//==============================================================
XMFLOAT3 Player::GetPlayerPos()
{
	return m_pos;
}

//==============================================================
//
//	Playerクラス::プレイヤーの角度を取得
//	作成者	: 吉原飛鳥
//	戻り値	: XMFLOAT3
//	引数		: なし 
//==============================================================
XMFLOAT3 Player::GetPlayerAngle()
{
	return m_Angle;
}

//==============================================================
//
//	Playerクラス::プレイヤーの描画角度を取得
//	作成者	: 吉原飛鳥
//	戻り値	: float
//	引数		: なし 
//==============================================================
float Player::GetPlayerDrawAngle()
{
	return m_DrawAngle;
}


//==============================================================
//
//	Playerクラス::弾のターゲットの座標の取得
//	作成者	: 伊地田真衣
//	戻り値	: なし
//	引数		: 弾のターゲットの座標 
//==============================================================
void Player::SetBulletTargetPos(XMFLOAT3 pos) {
	m_BulletTargetPos = pos;
}


//==============================================================
//
//	Playerクラス::投げているフラグセット
//	作成者	: 伊地田真衣
//	戻り値	: なし
//	引数		: 弾のターゲットの座標 
//==============================================================
void Player::SetThrowFlg(bool flg) {
	m_throwFlg = flg;
}