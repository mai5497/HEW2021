//****************************************************
//
//	�s�N�~���Ǘ�
//	�쐬�ҁF�ɒn�c�^��
//	
//	2021/12/06 : �쐬
//
//****************************************************


//========================= �C���N���[�h�� ===========================
#include <time.h>
#include "PikminManager.h"
#include "AttackPikmin.h"
#include "GameObject.h"


//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
PikminManager::PikminManager() : m_ppPikmin(nullptr),m_pikminNum(MAX_PIKMIN)
{


}

//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
PikminManager::~PikminManager() 
{

}


//====================================================================
//
//		������
//
//====================================================================
bool PikminManager::Init() 
{
	struct PikminSetting 
	{
		XMFLOAT3 pos;
	};

	// �L�����N�^�[��ݒu
	PikminSetting AtattckPikminSet[MAX_PIKMIN];

	XMFLOAT3 basePos = XMFLOAT3(0.0f, 0.0f, 0.0f);		// �w�肵���ʒu�t�߂ɔz�u�ł���
	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 0.0f, 0.0f);	// �����_��

	srand(time(NULL));

	// �|�C���^���i�[����z����쐬
	m_ppPikmin = new PikminBase*[MAX_PIKMIN];

	for (int i = 0; i < MAX_PIKMIN; i++) 
	{
		// �s�N�~���������_���ŏ����z�u
		randomPos.x = (float)rand() / RAND_MAX - 2.0f; //-2.0 ~ 2.0�̊Ԃ̗���
		randomPos.z = (float)rand() / RAND_MAX - 2.0f;
		// �����_���ŎZ�o�����l����ʒu�ɉ��Z���đ��
		AtattckPikminSet[i].pos = XMFLOAT3(basePos.x + randomPos.x, 0.5f, basePos.z + randomPos.z);
		// ���ꂼ��̔z��Ƀs�N�~�����������m��
		m_ppPikmin[i] = new AttackPikmin;
		m_ppPikmin[i]->TargetPos(AtattckPikminSet[i].pos);
		m_ppPikmin[i]->SetPos(AtattckPikminSet[i].pos);
		m_ppPikmin[i]->SetSize(XMFLOAT3(1.0f / 2, 1.0f / 2, 1.0f / 2));
		m_ppPikmin[i]->Init();
	}
	return true;
}


//====================================================================
//
//		�I������
//
//====================================================================
void PikminManager::Uninit() 
{
	for (int i = 0; i < MAX_PIKMIN; i++)
	{
		delete m_ppPikmin[i];
		m_ppPikmin[i] = NULL;
	}
	delete[] m_ppPikmin;
	m_ppPikmin = NULL;

}


//====================================================================
//
//		�X�V����
//
//====================================================================
void PikminManager::Update() 
{
	for (int i = 0; i < MAX_PIKMIN; i++) 
	{
		m_ppPikmin[i]->Update();
	}
}


//====================================================================
//
//		�`�揈��
//
//====================================================================
void PikminManager::Draw() 
{
	for (int i = 0; i < MAX_PIKMIN; i++)
	{
		m_ppPikmin[i]->Draw();
	}

}


//====================================================================
//
//		�s�N�~�����擾
//
//====================================================================
PikminBase* PikminManager::GetPikmin(int index) 
{
	if (index < MAX_PIKMIN) {
		return m_ppPikmin[index];
	}
	return NULL;
}

//====================================================================
//
//		�s�N�~�����擾
//
//====================================================================
int PikminManager::GetPikminNum() 	
{
	return m_pikminNum;
}

//====================================================================
//
//		�s�N�~�����擾
//
//====================================================================
void PikminManager::SetPikminTarget(XMFLOAT3 pos) 
{
	for (int i = 0; i < m_pikminNum; i++) 
	{
		m_ppPikmin[i]->TargetPos(pos);
	}
}


