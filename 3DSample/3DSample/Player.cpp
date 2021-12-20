/**
 * @file Player.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 *		 2021/12/19 赤青弾をわけて打てるように
 * @brief プレイヤーに関する処理
 */
#include "Player.h"
#include "Input.h"
#include "TPSCamera.h"
#include "MyVector.h"
#include "Collision.h"
#include <math.h>
#include "Controller.h"
#include "MyMath.h"

#define FPS 60

DirectX::XMFLOAT3 pOldCameraPos;

Player::Player()
	:m_pControllCamera(nullptr)
	, m_ppBullets(NULL)
	, m_nBulletNum(0)
{
	m_pos.y = 1.0f;
	m_Angle = DirectX::XMFLOAT3(0, 0, 0);
	m_collisionType = COLLISION_DYNAMIC;
}
Player::~Player()
{
	m_pControllCamera = nullptr;
	Uninit();
}

bool Player::Init()
{
	struct BulletSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};


	BulletSetting settings[] = {
		{ DirectX::XMFLOAT3(m_pos),
		DirectX::XMFLOAT3(30,1,30), },
	{ DirectX::XMFLOAT3(m_pos),
	DirectX::XMFLOAT3(30,1,30), },
	{ DirectX::XMFLOAT3(m_pos),
	DirectX::XMFLOAT3(30,1,30), },
	{ DirectX::XMFLOAT3(m_pos),
	DirectX::XMFLOAT3(30,1,30), },
	{ DirectX::XMFLOAT3(m_pos),
	DirectX::XMFLOAT3(30,1,30), },
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

void Player::Update()
{
	//----- 変数初期化 -----
	XMFLOAT2 Axis = LeftThumbPosition();
	bool rbFlg = true;

	bool keyL = IsPress('A');
	bool keyR = IsPress('D');
	bool keyU = IsPress('W');
	bool keyD = IsPress('S');
	bool keyBlue = IsPress('E');
	bool keyRed = IsPress('Q');
	bool keyJ = IsTrigger(VK_SPACE);

	//１秒間（60FPS）で2M進ことを表す。
	const float Move = 10.0f / 60;
	m_move = DirectX::XMFLOAT3(Axis.x, m_move.y, Axis.y);
	float CameraRad = m_pControllCamera->GetxzAngle() * 3.14159265359f / 180.0f;
	
	//プレイヤー移動
	m_move.y -= 0.01f;
	if (keyL) 
	{
		m_move.x -= Move;
		if (m_Angle.y >= -CameraRad - 90.0f * 3.1415926f / 180.0f)
		{
			m_Angle.y -= 0.1f;
		}
	}

	if (keyR) 
	{ 
		m_move.x += Move;

		if (m_Angle.y <= -CameraRad + 90.0f * 3.1415926f / 180.0f)
		{
			m_Angle.y += 0.1f;
		}
	}
	if (keyU)
	{
		m_move.z += Move;
		if (m_Angle.y <= -CameraRad)
			m_Angle.y += 0.1f;
		if (m_Angle.y >= -CameraRad)
			m_Angle.y -= 0.1f;
	}

	if (keyRed) {
		rbFlg = true;	// 赤
	}

	if (keyBlue) {
		rbFlg = false;	// 青
	}

	if (keyD) { m_move.z -= Move; }
	if (keyJ) { m_move.y += 0.2f; }

	if (IsTrigger('Z'))
	{
		CreateBullet(m_pControllCamera,rbFlg);
		//for (int i = 0; i < g_pPikminManager->GetPikminNum(); i++) {
		//	g_pPikminManager->GetPikmin(i)->SetFollowFlg(true);
		//}

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
	//m_pos.x += m_move.x;
	//m_pos.y += m_move.y;
	//m_pos.z += m_move.z;

	//m_pos.x += m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//m_pos.y += m_move.y;
	//m_pos.z += m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);

	//当たり判定
	m_move.x = direction.x * Move;
	m_move.z = direction.y * Move;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (!m_ppBullets[i]->use)
		{
			continue;
		}
		m_ppBullets[i]->Update();
	}
}

void Player::Draw()
{
	DirectX::XMFLOAT3 pPos = m_pos;
	DirectX::XMFLOAT3 pSize = m_size;

	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (!m_ppBullets[i]->use)
		{
			continue;
		}
		m_ppBullets[i]->Draw();
	}

	CharacterBase::Draw();
}

Bullet *Player::GetBullet(int index)
{
	if (index < m_nBulletNum)
	{ 
		return m_ppBullets[index];
	}
	return NULL;
}

int Player::GetBulletNum()
{
	return m_nBulletNum;
}

void Player::SetControllCamera(Camera *pCamera)
{
	m_pControllCamera = pCamera;
}

// PlayerにEnemyが近づいてくる関数
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

void Player::GetCameraPos(TPSCamera* pCamera)
{
	pOldCameraPos = pCamera->GetCameraPos();
}

// 手裏剣を生成する関数
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
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));	// 赤をセット
		} else {
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));	// 青をセット
		}
		m_ppBullets[i]->
		m_ppBullets[i]->SetPos(m_pos);
		DirectX::XMFLOAT3 dir;

		float dirY;
		dirY = pCameraPos.y - pOldCameraPos.y;
		
		dir.x = m_pos.x - pCameraPos.x;
		dir.y = m_pos.y - dirY;
		dir.z = m_pos.z - pCameraPos.z;

		//ベクトルの大きさ
		float L;
		L = sqrtf((dir.x * dir.x) +
			(dir.y * dir.y) +
			(dir.z * dir.z));

		//// dir の長さを1にする(正規化)
		dir.x = dir.x / L;
		dir.y = dir.y / L;
		dir.z = dir.z / L;

		// 長さが1になったベクトルに移動させたい速度をかける(手裏剣の速度)
		dir.x = dir.x * 0.2;
		dir.y = dir.y * 0.2;
		dir.z = dir.z * 0.2;

		m_ppBullets[i]->SetMove(dir);
		break;
	}
}

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