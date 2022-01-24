//****************************************************
//
//	����n�_
//	�쐬�ҁF�ɐ����P
//	
//	2021/12/22 : �쐬
//	2021/12/26 : �R�����g�ǋL
//
//****************************************************

//========================= �C���N���[�h�� ===========================
#include "CollectionPoint.h"

#define POSSETTIME	(90)	// ����I���ォ��v���X�̎���


//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
CollectionPoint::CollectionPoint()
{
	m_size	= XMFLOAT3(5.0f, 0.0f, 5.0f);


	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 2.0f, 0.0f);	// �����_��
	//----- �����ō��W��ݒ� -----
	randomPos.x = (float)(rand() % 18 - 9.0f);	//-9.0 ~ 9.0�̊Ԃ̗���
	randomPos.z = (float)(rand() % 20 - 10.0f);	//-10.0 ~ 10.0�̊Ԃ̗���

	m_pos = randomPos;

	m_Radius = XMFLOAT3(2.0f, 0.1f, 2.0f);
	m_Angle	= XMFLOAT3(0, 0, 0);
	m_PosSetTime = POSSETTIME;	
	m_TimerStart = false;

	m_collisionType = COLLISION_STATIC;
}


//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
CollectionPoint::~CollectionPoint()
{
	Uninit();

}
//====================================================================
//
//		������
//
//====================================================================
bool CollectionPoint::Init()
{
	GameObject::Init();
	return true;
}


//====================================================================
//
//		�I������
//
//====================================================================
void CollectionPoint::Uninit()
{
	GameObject::Uninit();

}


//====================================================================
//
//		�X�V����
//
//====================================================================
void CollectionPoint::Update()
{
	if (m_nowCollectTimer < 1 && !m_TimerStart) {
		m_TimerStart = true;
	}

	if (m_TimerStart) {
		m_PosSetTime--;
	}

	if(m_PosSetTime < 0){
		XMFLOAT3 randomPos = XMFLOAT3(0.0f, 2.0f, 0.0f);	// �����_��
		//----- �����ō��W��ݒ� -----
		randomPos.x = (float)(rand() % 18 - 9.0f);	//-9.0 ~ 9.0�̊Ԃ̗���
		randomPos.z = (float)(rand() % 20 - 10.0f);	//-9.0 ~ 9.0�̊Ԃ̗���

		m_pos = randomPos;
		m_TimerStart = false;
		m_PosSetTime = POSSETTIME;
	}
}


//====================================================================
//
//		�`�揈��
//
//====================================================================
void CollectionPoint::Draw()
{
	//���[���h���W�ϊ�
	SHADER->SetWorld(
		XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* XMMatrixRotationY(m_Angle.y)
		* XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	m_pCube->Draw();
}


//====================================================================
//
//		������t���O�Z�b�g
//
//====================================================================
void CollectionPoint::SetNowCollectFlg(bool flg) {
	m_nowCollectFlg = flg;
}


//====================================================================
//
//		������^�C�}�[�Z�b�g
//
//====================================================================
void CollectionPoint::SetnowCollectTimer(int time) {
	m_nowCollectTimer = time;
}



//====================================================================
//
//		�^�[�Q�b�g�̍��W�̎擾
//
//====================================================================
XMFLOAT3 CollectionPoint::GetTargetPos() {
	return m_pos;
}

