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
#include "Player.h"
#include "Input.h"
#include "TPSCamera.h"
#include "MyVector.h"
#include "Collision.h"
#include <math.h>
#include "Controller.h"
#include "MyMath.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define FPS		(60)
#define BULLET_SPEED	(0.1f)

//*******************************************************************************
// グローバル宣言
//*******************************************************************************
DirectX::XMFLOAT3 pOldCameraPos;

//==============================================================
//
//	Playerクラス::コンストラクタ
//	作成者	： 園田翔大
//	戻り値	： void
//	引数	： void
//
//==============================================================
Player::Player():m_pControllCamera(nullptr),m_ppBullets(NULL),m_nBulletNum(0)
{
	m_pos.x = -10.0f;
	m_pos.y = 3.0f;
	m_pos.z = -10.0f;
	m_Angle = XMFLOAT3(0, 0, 0);
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
	Uninit();
}

//==============================================================
//
//	Playerクラス::初期化処理
//	作成者	： 園田翔大
//	戻り値	： bool型
//	引数		： void
//
//==============================================================
bool Player::Init()
{
	struct BulletSetting
	{
		XMFLOAT3 pos;
		XMFLOAT3 size;
	};


	BulletSetting settings[] = 
	{
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
		{XMFLOAT3(m_pos),XMFLOAT3(30,1,30), },
	};

	//初期データから弾数を計算
	m_nBulletNum = sizeof(settings) / sizeof(settings[0]);

	//ポインタを格納する配列を作成
	m_ppBullets = new Bullet *[m_nBulletNum];

	//それぞれの配列に弾をメモリ確保
	for (int i = 0; i < m_nBulletNum; i++)
	{
		m_ppBullets[i] = new Bullet(settings[i].size);
		m_ppBullets[i]->SetPos(settings[i].pos);
		m_ppBullets[i]->Init();	// 弾用初期化
	}
	GameObject::Init();	// プレイヤー用初期化？
	return true;
}

//==============================================================
//
//	Playerクラス::終了処理
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
void Player::Uninit()
{
	if (m_ppBullets != NULL)
	{
		for (int i = 0; i < m_nBulletNum; i++)
		{
			//個別に削除
			delete m_ppBullets[i];
		}
		//配列を削除
		delete[] m_ppBullets;
		m_ppBullets = NULL;
	}
	GameObject::Uninit();
}

//==============================================================
//
//	Playerクラス::更新処理
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
void Player::Update()
{
	//----- 変数初期化 -----
	XMFLOAT2 Axis = LeftThumbPosition();
	static bool rbFlg = true;


	bool keyL = IsPress('A');
	bool keyR = IsPress('D');
	bool keyU = IsPress('W');
	bool keyD = IsPress('S');
	bool keyBlue = IsPress('E');
	bool keyRed = IsPress('Q');
	bool keyJ = IsTrigger(VK_SPACE);

	//１秒間（60FPS）で2M進ことを表す。
	const float Move = (10.0f / 60) * 2;

	m_move = XMFLOAT3(Axis.x, m_move.y, Axis.y);

	float CameraRad = m_pControllCamera->GetxzAngle() * 3.14159265359f / 180.0f;
	
	//プレイヤー移動
	m_move.y -= 0.01f;
	if (keyL){
		m_move.x -= Move;
		if (m_Angle.y >= -CameraRad - 90.0f * 3.1415926f / 180.0f){
			m_Angle.y -= 0.1f;
		}
	}

	if (keyR){ 
		m_move.x += Move;
		if (m_Angle.y <= -CameraRad + 90.0f * 3.1415926f / 180.0f){
			m_Angle.y += 0.1f;
		}
	}

	if (keyU){
		m_move.z += Move;
		if (m_Angle.y <= -CameraRad) {
			m_Angle.y += 0.1f;
		}
		if (m_Angle.y >= -CameraRad) {
			m_Angle.y -= 0.1f;
		}
	}

	if (keyRed) {	// 赤に切り替え
		rbFlg = true;	// 赤
	}

	if (keyBlue) {	// 青に切り替え
		rbFlg = false;	// 青
	}

	if (keyD) { m_move.z -= Move; }
	if (keyJ) { m_move.y += 0.2f; }			// ジャンプ

	if (IsPress(VK_UP)) {	// 弾の飛ばす位置伸ばす
		/*todo 弾の飛距離伸ばす*/
	}
	if (IsPress(VK_DOWN)) {	// 弾の飛ばす位置短く
		/*todo 弾の飛距離落とす*/
	}

	if (IsTrigger('Z')){	// 弾飛ばす
		CreateBullet(m_pControllCamera,rbFlg);
	}


	//if (Input::instance().getControllerConnection())
	//{

	//}

	MyVector2 direction(0, 0);

	// 極座標を使ったTPS視点
	direction.x = m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	direction.y = m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);
	direction = direction.GetNormalize();

	////座標を更新
	//m_pos.x += m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//m_pos.y += m_move.y;
	//m_pos.z += m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);

	//当たり判定
	m_move.x = direction.x * Move;
	m_move.z = direction.y * Move;

	for (int i = 0; i < m_pDwarfManager->GetDwarfNum(); i++) {
		for (int j = 0; j < m_nBulletNum; j++) {
			if (!CollisionSphere(m_pDwarfManager->GetDwarf(i), m_ppBullets[j])) {	// 近くにいなかったら下の処理をしない
				continue;
			}

			if (m_ppBullets[j]->GetRB() == m_pDwarfManager->GetDwarf(i)->GetRBFlg()) {	// 投げた弾と小人の色が同じだったら
				m_pDwarfManager->GetDwarf(i)->SetMoveFlg(true);		// 移動許可
				m_pDwarfManager->GetDwarf(i)->SetFollowFlg(true);	// 追跡を始める
				m_pDwarfManager->GetDwarf(i)->SetrunFlg(false);		// 弾から離れるのをやめる
			} else {
				m_pDwarfManager->GetDwarf(i)->SetMoveFlg(false);	// 移動許可しない
				m_pDwarfManager->GetDwarf(i)->SetFollowFlg(false);	// 追跡しない
				m_pDwarfManager->GetDwarf(i)->SetrunFlg(true);		// 弾から離れる
			}
		}
	}

	BulletFiledCollision();


	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (!m_ppBullets[i]->use){
			continue;
		}
		m_ppBullets[i]->Update();
	}
}

//==============================================================
//
//	Playerクラス::描画処理
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
void Player::Draw()
{
	DirectX::XMFLOAT3 pPos = m_pos;
	DirectX::XMFLOAT3 pSize = m_size;

	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (!m_ppBullets[i]->use){
			continue;
		}
		m_ppBullets[i]->Draw();
	}

	CharacterBase::Draw();
}

//==============================================================
//
//	Playerクラス::弾情報取得
//	作成者	： 園田翔大
//	戻り値	： Bullet型
//	引数		： int index	... 弾の数
//
//==============================================================
Bullet *Player::GetBullet(int index)
{
	if (index < m_nBulletNum){ 
		return m_ppBullets[index];
	}
	return NULL;
}

//==============================================================
//
//	Playerクラス::弾の数の情報取得
//	作成者	： 園田翔大
//	戻り値	： int型	... 弾の数(m_nBUlletNum)を返す
//	引数		： void
//
//==============================================================
int Player::GetBulletNum()
{
	return m_nBulletNum;
}

//==============================================================
//
//	Playerクラス::カメラをプレイヤーの位置にセット？
//	作成者	： 園田翔太
//	戻り値	： void
//	引数		： カメラクラス型
//
//==============================================================
void Player::SetControllCamera(Camera *pCamera)
{
	m_pControllCamera = pCamera;
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
	L = sqrtf((dir.x * dir.x) +
		(dir.y * dir.y) +
		(dir.z * dir.z));

	//// dir の長さを1にする(正規化)
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

//==============================================================
//
//	Playerクラス::弾を生成する処理
//	作成者	： 園田翔大
//	編集者	： 伊地田真衣
//	戻り値	： void
//	引数		： Camera型の位置,色判定
//
//==============================================================
void Player::CreateBullet(Camera* pCamera , bool rbFlg)
{
	DirectX::XMFLOAT3 pCameraPos = pCamera->GetCameraPos();
	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (m_ppBullets[i]->use){
			continue;
		}

		m_ppBullets[i]->use = true;
		m_ppBullets[i]->SetRB(rbFlg);
		if (m_ppBullets[i]->GetRB()) {	// trueが赤
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.5f));	// 赤をセット
		} else {
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 0.5f));	// 青をセット
		}

		m_ppBullets[i]->SetPos(m_pos);
		DirectX::XMFLOAT3 dir;

		float dirY;
		dirY = pCameraPos.y - pOldCameraPos.y;
		
		dir.x = m_pos.x - pCameraPos.x;
		dir.y = m_pos.y - dirY;
		dir.z = m_pos.z - pCameraPos.z;

		//ベクトルの大きさ
		float L;
		L = sqrtf((dir.x * dir.x)  + (dir.y * dir.y) +(dir.z * dir.z));

		//// dir の長さを1にする(正規化)
		dir.x = dir.x / L;
		dir.y = dir.y / L;
		dir.z = dir.z / L;

		// 長さが1になったベクトルに移動させたい速度をかける(手裏剣の速度)
		dir.x = dir.x * BULLET_SPEED;
		dir.y = dir.y * BULLET_SPEED;
		dir.z = dir.z * BULLET_SPEED;

		//m_ppBullets[i]->SetMove(dir);
		m_ppBullets[i]->SetMove(dir);
		break;
	}
}
void Player::CreateBullet(XMFLOAT3 pos, XMFLOAT3 dir)
{

}

//==============================================================
//
//	Playerクラス::弾を破壊する処理
//	作成者	: 園田翔大
//	戻り値	: void
//	引数		: void
//
//==============================================================
void Player::DestroyBullet()
{
	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (!m_ppBullets[i]->use)
		{
			continue;
		}
		m_ppBullets[i]->use = false;
		break;
	}
}

//==============================================================
//
//	Playerクラス::小人の情報の取得
//	作成者	: 伊地田真衣
//	戻り値	: void
//	引数	: 小人管理クラスのポインタ
//
//==============================================================
void Player::SetDwarfInfo(DwarfManager *pDwarfManager)
{
	m_pDwarfManager = pDwarfManager;
}

//==============================================================
//
//	Playerクラス::ステージの情報の取得
//	作成者	: 伊地田真衣
//	戻り値	: void
//	引数	: ステージ管理クラスのポインタ
//
//==============================================================
void Player::SetStageInfo(Stage *pStage) {
	m_pStage = pStage;
}


//=============================================================
//
//	弾がフィールドと接しているかの判定処理
//	作成者	： 吉原飛鳥
//	編集者	： 伊地田真衣
//	戻り値	： void
//　引数	： void
//
//=============================================================
void Player::BulletFiledCollision() {
	for (int i = 0; i < m_nBulletNum; i++) {
		if (!m_ppBullets[i]->use) {	// 弾なかったら下の処理やらん
			continue;
		}
		if (!CollisionSphere(m_ppBullets[i], m_pStage->GetField(0))) {	// 当たってなかったら下の処理やらん
			m_ppBullets[i]->SetColFlg(false);
			continue;
		}
		m_ppBullets[i]->SetColFlg(true);
	}
}


