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
	m_size	= XMFLOAT3(7.0f, 0.0f, 7.0f);


	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 2.0f, 0.0f);	// �����_��
	//----- �����ō��W��ݒ� -----
	randomPos.x = (float)(rand() % 18 - 9.0f);	//-9.0 ~ 9.0�̊Ԃ̗���
	randomPos.z = (float)(rand() % 20 - 10.0f);	//-10.0 ~ 10.0�̊Ԃ̗���

	m_pos = randomPos;

	m_Radius = XMFLOAT3(3.0f, 0.1f, 3.0f);
	m_Angle	= XMFLOAT3(0, 0, 0);
	m_PosSetTime = POSSETTIME;	
	m_TimerStart = false;

	m_ColorVal[RED] = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
	m_ColorVal[BLUE] = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
	m_ColorVal[REDBLUE] = XMFLOAT4(0.5f, 0.0f, 0.5f, 1.0f);
	m_colorNum = 0;	// �J���[�̏����Ƃ�z��̔ԍ�

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
bool CollectionPoint::Init(int stagenum)
{
	GameObject::Init();

	if (stagenum == 1) {
		m_colorInfo[0] = BLUE;
		m_colorInfo[1] = MAX_COLOR;
	}
	if (stagenum == 2) {
		m_colorInfo[0] = RED;
		m_colorInfo[1] = BLUE;
		m_colorInfo[2] = REDBLUE;
		m_colorInfo[3] = MAX_COLOR;
	}
	if (stagenum == 3) {
		m_colorInfo[0] = RED;
		m_colorInfo[1] = BLUE;
		m_colorInfo[2] = REDBLUE;
		m_colorInfo[3] = MAX_COLOR;
	}

	m_Color = m_ColorVal[m_colorInfo[m_colorNum]];

	GameObject::Update();

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
	//----- �����_���Ŕz�u -----
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
		randomPos.z = (float)(rand() % 20 - 10.0f);	//-10.0 ~ 10.0�̊Ԃ̗���


		m_pos = randomPos;
		m_TimerStart = false;
		m_PosSetTime = POSSETTIME;
		m_colorNum++;
		if (m_colorInfo[m_colorNum] == MAX_COLOR) {
			m_colorNum = 0;
		}
		m_Color = m_ColorVal[m_colorInfo[m_colorNum]];
	}



	GameObject::Update();
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


//====================================================================
//
//		���݂̐F�ԍ��̎擾
//
//====================================================================
int CollectionPoint::GetColorNum() {
	return m_colorInfo[m_colorNum];
}
//====================================================================
//
//		�w�肳�ꂽ�F�ԍ��̎擾
//
//====================================================================
int CollectionPoint::GetColorNum(int index) {
	return m_colorInfo[index];
}


//====================================================================
//
//		�z��̒��g���������܂��ɉ����o��
//		�����F�����v�f�ԍ�
//		�߂�l�F�Ȃ�
//
//====================================================================
void CollectionPoint::SqueezeFront(int index) {
	int i;
	for (i = index + 1; m_colorInfo[i] < MAX_COLOR; i++) {
		m_colorInfo[i-1] = m_colorInfo[i];
	}
	m_colorInfo[i-1] = MAX_COLOR;
}
