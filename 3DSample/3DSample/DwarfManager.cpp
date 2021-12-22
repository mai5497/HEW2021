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
DwarfManager::DwarfManager() : m_ppDwarf(nullptr),m_DwarfNum(MAX_DWARF)
{


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
		randomPos.x = (float)(rand() % 80 - 40.0f);	//-40.0 ~ 40.0�̊Ԃ̗���
		randomPos.z = (float)(rand() % 80 - 40.0f);
		// �����_���ŎZ�o�����l����ʒu�ɉ��Z���đ��
		DwarfSet[i].pos = XMFLOAT3(basePos.x + randomPos.x, 0.5f, basePos.z + randomPos.z);
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
//		���l���擾
//
//====================================================================
void DwarfManager::SetDwarfTarget(XMFLOAT3 pos) 
{
	for (int i = 0; i < m_DwarfNum; i++) 
	{
		m_ppDwarf[i]->TargetPos(pos);
	}
}


