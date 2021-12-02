/**
 * @file Bullet.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 * @brief プレイヤーから発射される弾に関する処理
 */
#include "Bullet.h"
#include <math.h>

//---定数定義
#define FPS (60)					//フレーム数
#define WAIT_TIME (1.0 * FPS)		//遅延のための時間
#define WAIT_TIME2 (0.8f * FPS)		//遅延のための時間

Bullet::Bullet(DirectX::XMFLOAT3 size)
{
	m_pos.y = 1000.0f;				//初期座標x
	m_pos.z = 1000.0f;				//初期座標y
	m_pos.x = 1000.0f;				//初期座標z
	m_size.x = 0.25f;				
	m_size.y = 0.25f;
	m_size.z = 0.25f;
	m_sleep = 0;
	m_sleep2 = 0;

}
Bullet::~Bullet()
{

}

void Bullet::Update()
{
	//毎フレーム初期化
//	m_move = DirectX::XMFLOAT3(0, m_move.y, 0);

	//一定時間後に重力をかける
	if (m_sleep > WAIT_TIME)
	{
		//このコメントアウト↓外すと一定時間後に弾がゆっくり落下します
		//m_move.y -= 0.3f / FPS;
		m_move.x = 0;
		m_move.y = 0;
		m_move.z = 0;
		m_sleep = 0;
	}
	
	if (m_sleep2 > WAIT_TIME2)
	{
		if (m_pos.y > 0.1f)
			m_move.y -= 0.01f / FPS;

		m_sleep2 = 0;
	}

	m_sleep++;
	m_sleep2++;
	//座標更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;


	
}


//弾の当たり判定
void Bullet::OnCollision(GameObject* pObj)
{
	// 弾が使われてないときは終了する
	if (use == false) { return; }

	DirectX::XMFLOAT3 m_Enemypos = pObj->GetPos();		//敵の座標取得
	DirectX::XMFLOAT3 Target = m_pos;					//弾の座標を取得（敵との当たり判定でつかう

	DirectX::XMFLOAT3 dir;
	dir.x = m_pos.x - m_Enemypos.x;
	dir.y = m_pos.y - m_Enemypos.y;
	dir.z = m_pos.z - m_Enemypos.z;

	float l;
	l = sqrtf(powf(dir.x, 2) + powf(dir.y, 2) + powf(dir.z, 2));
	dir.x = dir.x / l;
	dir.y = dir.y / l;
	dir.z = dir.z / l;

	dir.x = dir.x * 0.025f;
	dir.y = dir.y * 0.025f;
	dir.z = dir.z * 0.025f;

	pObj->SetMove(dir);
}

