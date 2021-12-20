/**
 * @file Bullet.cpp
 * @Author	園田翔大
 * @Edit	吉原(2021/12/19)
 * @date 2021/11/29 作成
 *		 2021/12/19 赤青玉を判別する変数を追加
 *					赤青玉判別変数のゲッターセッターを追加
					フィールドと弾の当たり判定の処理を追加(吉原)
 * @brief プレイヤーから発射される弾に関する処理
 */
#include "Bullet.h"
#include <math.h>

//---定数定義
#define FPS (60)					//フレーム数
#define WAIT_TIME (1.0 * FPS)		//遅延のための時間
#define WAIT_TIME2 (0.8f * FPS)		//遅延のための時間

Bullet::Bullet(DirectX::XMFLOAT3 size):
	m_rbFlg(true)
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

	GameObject::Update();
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


//=============================================================
//
//	投げた弾が赤か青かセットする
//	作成者	： 伊地田真衣
//	戻り値	： void
//　引数	： 赤か青かセットtrueが赤falseが青
//
//=============================================================
void Bullet::SetRB(bool flg) 
{
	m_rbFlg = flg;
}


//=============================================================
//
//	弾が赤か青か取得
//	作成者	： 伊地田真衣
//	戻り値	： 赤か青かtrueが赤falseが青
//　引数	： void
//
//=============================================================
bool Bullet::GetRB()
{
	return m_rbFlg;
}

//=============================================================
//
//	弾がフィールドと接しているかの判定処理
//	作成者	： 吉原飛鳥
//	戻り値	： void
//　引数		： フィールドと接している(true)/接していない(false)
//
//=============================================================
void Bullet::BulletCollision(bool SetFlg)
{

	m_ColFlg = SetFlg;
}
