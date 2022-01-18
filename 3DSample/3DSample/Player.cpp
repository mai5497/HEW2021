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
#define PLAYER_SIZE		(0.25f)

//*******************************************************************************
// グローバル宣言
//*******************************************************************************
XMFLOAT3 pOldCameraPos;
DrawBuffer *Player::m_pBuffer = NULL;
FBXPlayer *Player::m_pFBX = NULL;
Camera *g_pPlayerCamera;


//==============================================================
//
//	Playerクラス::コンストラクタ
//	作成者	： 園田翔大
//	戻り値	： void
//	引数	： void
//
//==============================================================
Player::Player():m_pControllCamera(nullptr)
{
	//----- 変数初期化 -----
	LoadTextureFromFile("Assets/Model/princess.png", &m_pPlayerTex);

	// ---変数初期化
	m_pos.x = 0.0f;
	m_pos.y = 3.0f;
	m_pos.z = -13.0f;
	m_Angle = XMFLOAT3(0, 0, 0);
	m_DrawAngle = 0.0f;

	m_size = XMFLOAT3(PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE);


	g_pPlayerCamera = new Camera;
	g_pPlayerCamera->Init();

	m_collisionType = COLLISION_DYNAMIC;

	//g_pPlayerCamera = new Camera;
	//g_pPlayerCamera->Init();

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
	//g_pPlayerCamera->Uninit();
	//delete g_pPlayerCamera;

	m_pControllCamera = nullptr;
	SAFE_RELEASE(m_pPlayerTex);

	g_pPlayerCamera->Uninit();
	delete g_pPlayerCamera;
	g_pPlayerCamera = nullptr;
	
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
	GameObject::Init();	// プレイヤー用初期化？
	if (m_pBuffer == NULL) {
		Player::LoadPlayer("Assets/Model/princess.fbx");
	}


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

	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;

		delete m_pFBX;
		m_pFBX = NULL;
	}
	SAFE_RELEASE(m_pPlayerTex);

	GameObject::Uninit();
}

//==============================================================
//
//	Playerクラス::Update
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
void Player::Update()
{
	//----- 変数初期化 -----
	XMFLOAT2 Axis = LeftThumbPosition();
	bool moveFlg = false;

	//bool keyL = IsPress('A');
	//bool keyR = IsPress('D');
	//bool keyU = IsPress('W');
	//bool keyD = IsPress('S');
	//bool keyJ = IsTrigger(VK_SPACE);

	//１秒間（60FPS）で2M進ことを表す。
	//const float Move = (10.0f / 60) * 2;

	m_move = XMFLOAT3(Axis.x, m_move.y, Axis.y);

	//float CameraRad = m_pControllCamera->GetxzAngle() * 3.14159265359f / 180.0f;
	
	//プレイヤー移動
	//m_move.y -= 0.01f;	// 重力
	//if (m_pos.z == -13.0f) {
	//	if (keyL ) {
	//		moveFlg = true;
	//		m_move.x -= Move;
	//		if (m_Angle.y >= -CameraRad - 90.0f * 3.1415926f / 180.0f) {
	//			m_Angle.y -= 0.1f;
	//		}
	//	}

	//	if (keyR) {
	//		moveFlg = true;
	//		m_move.x += Move;
	//		if (m_Angle.y <= -CameraRad + 90.0f * 3.1415926f / 180.0f) {
	//			m_Angle.y += 0.1f;
	//		}
	//	}
	//} else if (m_pos.z < -13.0f) {
	//	m_pos.z = -13.0f;
	//}

	//if (m_pos.x == 12.5f) {
	//	if (keyU) {
	//		moveFlg = true;
	//		m_move.z += Move;
	//		if (m_Angle.y <= -CameraRad) {
	//			m_Angle.y += 0.1f;
	//		}
	//		if (m_Angle.y >= -CameraRad) {
	//			m_Angle.y -= 0.1f;
	//		}
	//	}
	//	if (keyD) {
	//		m_move.z -= Move;
	//	}
	//} else if (m_pos.x > 12.5f) {
	//	m_pos.x = 12.5f;
	//}

	//if (keyJ) { m_move.y += 0.2f; }			// ジャンプ

	//if (IsPress(VK_UP)) {	// 弾の飛ばす位置伸ばす
	//	/*todo 弾の飛距離伸ばす*/
	//}
	//if (IsPress(VK_DOWN)) {	// 弾の飛ばす位置短く
	//	/*todo 弾の飛距離落とす*/
	//}

	//MyVector2 direction(0, 0);

	// 極座標を使ったTPS視点
	//direction.x = m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//direction.y = m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);
	//direction = direction.GetNormalize();

	////座標を更新
	//m_pos.x += m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//m_pos.y += m_move.y;
	//m_pos.z += m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);

	//描画用角度設定
	if (moveFlg == true) {
		m_DrawAngle = atan2(m_move.z, m_move.x);
		m_DrawAngle -= XM_PI * 0.5f;
	}

	//m_move.x = direction.x * Move;
	//m_move.z = direction.y * Move;

	//m_pos.x += m_move.x;
	//m_pos.y = 1.5f;
	//m_pos.z += m_move.z;
	
	// カメラ更新
	//g_pPlayerCamera->Update();
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
	//SHADER->Bind(VS_WORLD, PS_PHONG);
	//g_pPlayerCamera->Bind();


	DirectX::XMFLOAT3 pPos = m_pos;
	DirectX::XMFLOAT3 pSize = m_size;


	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixRotationY(-m_DrawAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pPlayerTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	//CharacterBase::Draw();
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
