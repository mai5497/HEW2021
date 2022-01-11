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
	m_DwarfNum(MAX_DWARF)
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
bool DwarfManager::Init() 
{
	struct DwarfSetting 
	{
		XMFLOAT3 pos;
	};

	// �L�����N�^�[��ݒu
	DwarfSetting DwarfSet[MAX_DWARF];

	XMFLOAT3 basePos = XMFLOAT3(0.0f, 0.0f, 0.0f);		// �w�肵���ʒu�t�߂ɔz�u�ł���
	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 0.0f, 0.0f);	// �����_��

	srand(time(NULL));

	// �|�C���^���i�[����z����쐬
	m_ppDwarf = new DwarfBase*[MAX_DWARF];

	for (int i = 0; i < MAX_DWARF; i++){
		// ���l�������_���ŏ����z�u
		randomPos.x = (float)(rand() % 20 - 10.0f);	//-10.0 ~ 10.0�̊Ԃ̗���
		randomPos.z = (float)(rand() % 20 - 10.0f);
		// �����_���ŎZ�o�����l����ʒu�ɉ��Z���đ��
		DwarfSet[i].pos = XMFLOAT3(basePos.x + randomPos.x, 2.0f, basePos.z + randomPos.z);
		// ���ꂼ��̔z��ɏ��l���������m��
		if (i < MAX_RED_DWARF) {
			m_ppDwarf[i] = new RedDwarf;
		} else {
			m_ppDwarf[i] = new BlueDwarf;
		}

		m_ppDwarf[i]->TargetPos(DwarfSet[i].pos);
		m_ppDwarf[i]->SetPos(DwarfSet[i].pos);
		m_ppDwarf[i]->SetSize(XMFLOAT3(1.0f / 2, 1.0f / 2, 1.0f / 2));
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
	for (int i = 0; i < MAX_DWARF; i++)
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
void DwarfManager::Update() 
{
	for (int i = 0; i < MAX_DWARF; i++) 
	{
		if (!m_ppDwarf[i]->GetAliveFlg()) {
			continue;
			//return // ��̂ł����񂾂�Q�[���I�[�o�[�̈�
		}
		if (m_ppDwarf[i]->GetCollectionFlg()) {
			continue;
		}
	
		for (int j = 0; j < MAX_BULLET; j++) 
		{
			if (!CollisionSphere(m_ppDwarf[i], m_pBullet->GetBullet(j))) {		// �߂��ɂ��Ȃ������牺�̏��������Ȃ�
				continue;
			}

			if (m_pBullet->GetBullet(j)->GetRBFlg() == m_ppDwarf[i]->GetRBFlg()) {	// �������e�Ə��l�̐F��������������
				//m_ppDwarf[i]->SetMoveFlg(true);		// �ړ�����
				m_ppDwarf[i]->SetFollowFlg(true);	// �ǐՂ��n�߂�
				m_ppDwarf[i]->SetrunFlg(false);		// �e���痣��Ȃ�
			} else {
				//m_ppDwarf[i]->SetMoveFlg(false);	// �ړ������Ȃ�
				m_ppDwarf[i]->SetFollowFlg(false);	// �ǐՂ��Ȃ�
				m_ppDwarf[i]->SetrunFlg(true);		// �e���痣���
			}
		}

		m_ppDwarf[i]->Update();
	}

}


//====================================================================
//
//		�`�揈��
//
//====================================================================
void DwarfManager::Draw() 
{
	for (int i = 0; i < MAX_DWARF; i++)
	{
		if (!m_ppDwarf[i]->GetAliveFlg()) {
			continue;
			//return // ��̂ł����񂾂�Q�[���I�[�o�[�̈�
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
	if (index < MAX_DWARF) {
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
//	�e�̏��̎擾
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: void
//	����	: �e�Ǘ��N���X�̃|�C���^
//
//==============================================================
void DwarfManager::AddCollectionSum() 
{
	m_collectionSum++;
}


