/**
 * @file EnemyBase.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 *		 2021/12/10 攻撃フラグを追加
 *					攻撃フラグセットの関数を追加
 *					攻撃フラグ取得の関数を追加
 * @brief 敵の座標に関する処理
 */
#include "EnemyBase.h"

EnemyBase::EnemyBase()
	:m_targetPos(0, 0, 0)
	,m_AttackFlg(false)
{
	m_collisionType = COLLISION_ENEMY;
}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Draw()
{
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(
			m_size.x, m_size.y, m_size.z)
		* DirectX::XMMatrixTranslation(
			m_pos.x, m_pos.y, m_pos.z));

	m_pCube->Draw();
}

void EnemyBase::TargetPos(DirectX::XMFLOAT3 pos)
{
	m_targetPos = pos;
}


void EnemyBase::EnemyStop()
{

}


//=============================================
//
//		攻撃フラグをセット
//		引数	: セットしたいフラグ
//		戻り値	: void 
//
//=============================================
void EnemyBase::SetAttackFlg(bool flg) 
{
	m_AttackFlg = flg;
}


//=============================================
//
//		攻撃フラグを取得
//		引数	: void
//		戻り値	: 現在のフラグ 
//
//=============================================
bool EnemyBase::GetAttackFlg() 
{
	return m_AttackFlg;
}
