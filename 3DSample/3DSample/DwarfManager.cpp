//****************************************************
//
//	���l�Ǘ�
//	�쐬�ҁF�ɒn�c�^��
//	
//	2021/12/06 : �쐬
//	2021/12/21 : ���l��ǉ�
//
//****************************************************


//========================= �C���N���[�h�� ===========================
#include <time.h>
#include "DwarfManager.h"
#include "GameObject.h"
#include "RedDwarf.h"
#include "BlueDwarf.h"


//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
DwarfManager::DwarfManager() : 
	m_ppDwarf(nullptr),
	m_DwarfNum(0)
{
	m_collectionSum = 0;
}

//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
DwarfManager::~DwarfManager() 
{

}


//====================================================================
//
//		������
//
//====================================================================
bool DwarfManager::Init(int stagenum) {
	//----- ���[�J���ϐ������� -----
	int rednum;
	int bluenum;

	if (stagenum == 1) {
		rednum = MAX_RED_DWARF_1;
		bluenum = MAX_BLUE_DWARF_1;
		m_DwarfNum = MAX_DWARF_1;
	} else if (stagenum == 2) {
		rednum = MAX_RED_DWARF_2;
		bluenum = MAX_BLUE_DWARF_2;
		m_DwarfNum = MAX_DWARF_2;
	} else if (stagenum == 3) {
		rednum = MAX_RED_DWARF_3;
		bluenum = MAX_BLUE_DWARF_3;
		m_DwarfNum = MAX_DWARF_3;
	}


	XMFLOAT3 basePos = XMFLOAT3(0.0f, 0.0f, 0.0f);		// �w�肵���ʒu�t�߂ɔz�u�ł���
	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 0.0f, 0.0f);	// �����_��

	srand(time(NULL));

	// �|�C���^���i�[����z����쐬
		
	m_ppDwarf = new DwarfBase*[m_DwarfNum];

	for (int i = 0; i < m_DwarfNum; i++){
		// ���l�������_���ŏ����z�u
		randomPos.x = (float)(rand() % 30 - 15.0f);	//-10.0 ~ 10.0�̊Ԃ̗���
		randomPos.z = (float)(rand() % 30 - 15.0f);

		// �����_���ŎZ�o�����l����ʒu�ɉ��Z���đ��
		XMFLOAT3(basePos.x + randomPos.x, 5.0f, basePos.z + randomPos.z);
		// ���ꂼ��̔z��ɏ��l���������m��
		if (i < rednum) {
			m_ppDwarf[i] = new RedDwarf;
		} else {
			m_ppDwarf[i] = new BlueDwarf;
		}

		m_ppDwarf[i]->TargetPos(XMFLOAT3(basePos.x + randomPos.x, 5.0f, basePos.z + randomPos.z));
		m_ppDwarf[i]->SetPos(XMFLOAT3(basePos.x + randomPos.x, 5.0f, basePos.z + randomPos.z));
		m_ppDwarf[i]->SetSize(XMFLOAT3(DWARF_SIZE, DWARF_SIZE, DWARF_SIZE));
		m_ppDwarf[i]->Init();
	}

	return true;
}


//====================================================================
//
//		�I������
//
//====================================================================
void DwarfManager::Uninit() 
{
	for (int i = 0; i < m_DwarfNum; i++)
	{
		m_ppDwarf[i]->Uninit();
		delete m_ppDwarf[i];
		m_ppDwarf[i] = NULL;
	}
	delete[] m_ppDwarf;
	m_ppDwarf = NULL;

}


//====================================================================
//
//		�X�V����
//
//====================================================================
void DwarfManager::Update() {
	static int Timer;
	Timer--;

	for (int i = 0; i < m_DwarfNum; i++) {
		if (!m_ppDwarf[i]->GetAliveFlg()) {
			return; // ��̂ł����񂾂�Q�[���I�[�o�[�̈�
		}
		if (m_ppDwarf[i]->GetCollectionFlg()) {
			continue;
		}

		for (int j = 0; j < MAX_BULLET; j++) {
			if (!m_pBullet->GetBullet(j)->use) {
				continue;
			}
			if (!CollisionSphere(m_ppDwarf[i], m_pBullet->GetBullet(j))) {		// �߂��ɂ��Ȃ������牺�̏��������Ȃ�
				continue;
			}

			if (m_pBullet->GetBullet(j)->GetRBFlg() == m_ppDwarf[i]->GetRBFlg()) {	// �������e�Ə��l�̐F��������������
				if (m_ppDwarf[i]->GetLiftFlg()) {
					continue;
				}
				//m_ppDwarf[i]->SetMoveFlg(true);		// �ړ�����
				m_ppDwarf[i]->SetFollowFlg(true);	// �ǐՂ��n�߂�
				m_ppDwarf[i]->SetrunFlg(false);		// �e���痣��Ȃ�
			} else {
				if (m_ppDwarf[i]->GetLiftFlg()) {
					continue;
				}
				//m_ppDwarf[i]->SetMoveFlg(false);	// �ړ������Ȃ�
				m_ppDwarf[i]->SetFollowFlg(false);	// �ǐՂ��Ȃ�
				m_ppDwarf[i]->SetrunFlg(true);		// �e���痣���
			}
		}

		for (int k = i + 1; k < m_DwarfNum; k++) {
			if (CollisionSphere(m_ppDwarf[i], m_ppDwarf[k])) {
				m_ppDwarf[i]->SetColFlg(true);
				m_ppDwarf[k]->SetColFlg(true);
			}
		}

		//if (Timer < 0) {
		//	if (!m_ppDwarf[i]->GetrunFlg() && !m_ppDwarf[i]->GetFollowFlg()) {
		//		m_ppDwarf[i]->SetCircumferenceFlg(true);
		//	}
		//	m_ppDwarf[i]->SetColFlg(false);
		//}
		m_ppDwarf[i]->Update();
	}

	//if (Timer < 0) {
	//	Timer = TARGETSET_TIME;
	//}

}


//====================================================================
//
//		�`�揈��
//
//====================================================================
void DwarfManager::Draw() 
{
	for (int i = 0; i < m_DwarfNum; i++)
	{
		if (!m_ppDwarf[i]->GetAliveFlg()) {
			return; // ��̂ł����񂾂�Q�[���I�[�o�[�̈�
		}
		if (m_ppDwarf[i]->GetCollectionFlg()) {
			continue;
		}
		m_ppDwarf[i]->Draw();
	}

}


//====================================================================
//
//		���l���擾
//
//====================================================================
DwarfBase* DwarfManager::GetDwarf(int index) 
{
	if (index < m_DwarfNum) {
		return m_ppDwarf[index];
	}
	return NULL;
}

//====================================================================
//
//		���l���擾
//
//====================================================================
int DwarfManager::GetDwarfNum() 	
{
	return m_DwarfNum;
}

//====================================================================
//
//		�^�[�Q�b�g�Z�b�g
//
//====================================================================
void DwarfManager::SetAllDwarfTarget(XMFLOAT3 pos) 
{
	for (int i = 0; i < m_DwarfNum; i++) 
	{
		m_ppDwarf[i]->TargetPos(pos);
	}
}

//==============================================================
//
//	�e�̏��̎擾
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: void
//	����	: �e�Ǘ��N���X�̃|�C���^
//
//==============================================================
void DwarfManager::SetBulletInfo(BulletManager *pBullet)
{
	m_pBullet = pBullet;
}

//==============================================================
//
//	������J�E���g�A�b�v
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: void
//	����	: void
//
//==============================================================
void DwarfManager::AddCollectionSum() 
{
	m_collectionSum++;
}

//==============================================================
//
//	������J�E���g�_�E��
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: void
//	����	: void
//
//==============================================================
void DwarfManager::SubCollectionSum() {
	m_collectionSum--;
}


//==============================================================
//
//	������̎擾
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: void
//	����	: void
//
//==============================================================
int DwarfManager::GetCollectionSum()
{
	return m_collectionSum;
}
