/**
 * @file EnemyBase.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 *		 2021/12/10 �U���t���O��ǉ�
 *					�U���t���O�Z�b�g�̊֐���ǉ�
 *					�U���t���O�擾�̊֐���ǉ�
 * @brief �G�̍��W�Ɋւ��鏈��
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
//		�U���t���O���Z�b�g
//		����	: �Z�b�g�������t���O
//		�߂�l	: void 
//
//=============================================
void EnemyBase::SetAttackFlg(bool flg) 
{
	m_AttackFlg = flg;
}


//=============================================
//
//		�U���t���O���擾
//		����	: void
//		�߂�l	: ���݂̃t���O 
//
//=============================================
bool EnemyBase::GetAttackFlg() 
{
	return m_AttackFlg;
}
