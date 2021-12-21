/**
 * @file CharacterBase.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 * @brief �v���C���[�̍��W�Ɋւ��鏈��
 */
#include "CharacterBase.h"

CharacterBase::CharacterBase()
{
	//�L�����N�^�[�͓����I�u�W�F�N�g
	m_collisionType = COLLISION_DYNAMIC;
}

CharacterBase::~CharacterBase()
{

}

void CharacterBase::Draw()
{
	//���[���h���W�ϊ�
	SHADER->SetWorld
	(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
	* XMMatrixRotationY(m_Angle.y) * XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	m_pCube->Draw();
}
