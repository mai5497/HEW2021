/**
 * @file Bullet.cpp
 * @Author	���c�đ�
 * @Edit	�g��(2021/12/19)
 * @date 2021/11/29 �쐬
 *		 2021/12/19 �Ԑʂ𔻕ʂ���ϐ���ǉ�
 *					�Ԑʔ��ʕϐ��̃Q�b�^�[�Z�b�^�[��ǉ�
					�t�B�[���h�ƒe�̓����蔻��̏�����ǉ�(�g��)
 * @brief �v���C���[���甭�˂����e�Ɋւ��鏈��
 */
#include "Bullet.h"
#include <math.h>

//---�萔��`
#define FPS (60)					//�t���[����
#define WAIT_TIME (1.0 * FPS)		//�x���̂��߂̎���
#define WAIT_TIME2 (0.8f * FPS)		//�x���̂��߂̎���

Bullet::Bullet(DirectX::XMFLOAT3 size):
	m_rbFlg(true)
{
	m_pos.y = 1000.0f;				//�������Wx
	m_pos.z = 1000.0f;				//�������Wy
	m_pos.x = 1000.0f;				//�������Wz
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
	//���t���[��������
//	m_move = DirectX::XMFLOAT3(0, m_move.y, 0);

	//��莞�Ԍ�ɏd�͂�������
	if (m_sleep > WAIT_TIME)
	{
		//���̃R�����g�A�E�g���O���ƈ�莞�Ԍ�ɒe��������藎�����܂�
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

	//���W�X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	GameObject::Update();
}


//�e�̓����蔻��
void Bullet::OnCollision(GameObject* pObj)
{
	// �e���g���ĂȂ��Ƃ��͏I������
	if (use == false) { return; }

	DirectX::XMFLOAT3 m_Enemypos = pObj->GetPos();		//�G�̍��W�擾
	DirectX::XMFLOAT3 Target = m_pos;					//�e�̍��W���擾�i�G�Ƃ̓����蔻��ł���

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
//	�������e���Ԃ����Z�b�g����
//	�쐬��	�F �ɒn�c�^��
//	�߂�l	�F void
//�@����	�F �Ԃ����Z�b�gtrue����false����
//
//=============================================================
void Bullet::SetRB(bool flg) 
{
	m_rbFlg = flg;
}


//=============================================================
//
//	�e���Ԃ����擾
//	�쐬��	�F �ɒn�c�^��
//	�߂�l	�F �Ԃ���true����false����
//�@����	�F void
//
//=============================================================
bool Bullet::GetRB()
{
	return m_rbFlg;
}

//=============================================================
//
//	�e���t�B�[���h�Ɛڂ��Ă��邩�̔��菈��
//	�쐬��	�F �g����
//	�߂�l	�F void
//�@����		�F �t�B�[���h�Ɛڂ��Ă���(true)/�ڂ��Ă��Ȃ�(false)
//
//=============================================================
void Bullet::BulletCollision(bool SetFlg)
{

	m_ColFlg = SetFlg;
}
