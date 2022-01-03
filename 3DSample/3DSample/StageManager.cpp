//****************************************************
//
//	�X�e�[�W�Ǘ�
//	�쐬�ҁF���c�đ�
//	
//	2021/12/01 : �쐬
//	2022/01/02 : �R�����g�ǉ��i�ɒn�c�j
//				 �X�e�[�W�ԍ��̕ϐ���ǉ��i�ɒn�c�j
//
//****************************************************

//========================= �C���N���[�h�� ===========================
#include "StageManager.h"

//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
StageManager::StageManager():m_ppStages(NULL),m_nStageNum(0)
{

}


//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
StageManager::~StageManager()
{
	Uninit();
}


//====================================================================
//
//		������
//		�����@�F�I�����ꂽ�X�e�[�W
//		�߂�l�F�������ł������ǂ���
//
//====================================================================
bool StageManager::Init(int SelectStageNum)
{
	//----- �����o�ϐ������� -----
	m_SelectStageNum = SelectStageNum;


	//----- �X�e�[�W�ݒ� -----
	struct StageSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};

	StageSetting settings[] =
	{
		//�傫����
		{ XMFLOAT3(0.0f,-0.5f, 0.0f),
		  XMFLOAT3(50.0f, 1.0f,50.0f),
		},
		//���l�̃X�e�[�W
		{ XMFLOAT3(0.0f,0.5f, 0.0f),
		  XMFLOAT3(19.0f,1.0f,19.0f),
		},
		//�E�̕�
		{ XMFLOAT3(12.5f,0.0f,0.0f),
		 XMFLOAT3(2.0f,3.0f,27.0f)
		},
		//���̕�
		{ XMFLOAT3(-12.5f,0.0f,0.0f),
		  XMFLOAT3(2.0f,3.0f,27.0f)
		},
		//���̕�
		{ XMFLOAT3(0.0f,0.0f,12.5f),
		  XMFLOAT3(27.0f,3.0f,2.0f)
		},
		//��O�̕�
		{ XMFLOAT3(0.0f,0.0f,-12.5f),
		  XMFLOAT3(27.0f,3.0f,2.0f)
		}
	};


	switch (m_SelectStageNum) {
		case 1:
			settings[1] =
			{
				//���l�̃X�e�[�W
				XMFLOAT3(0.0f,0.5f, 0.0f),
				XMFLOAT3(20.0f,1.0f,20.0f),
			};
			break;
		case 2:
			settings[1] =
			{
				//���l�̃X�e�[�W
				XMFLOAT3(0.0f,0.5f, 0.0f),
				XMFLOAT3(20.0f,1.0f,20.0f),
			};
			break;
		case 3:
			settings[1] =
			{
				//���l�̃X�e�[�W
				XMFLOAT3(0.0f,0.5f, 0.0f),
				XMFLOAT3(19.0f,1.0f,19.0f),
			};
			break;
		default:
			break;
	}
	//�����f�[�^����t�B�[���h�̐����v�Z
	m_nStageNum = sizeof(settings) / sizeof(settings[0]);

	//�|�C���^���i�[����z����쐬
	m_ppStages = new Stage *[m_nStageNum];

	//���ꂼ��̔z��Ƀt�B�[���h���������m��
	for (int i = 0; i < m_nStageNum; i++)
	{
		m_ppStages[i] = new Stage(settings[i].size);
		m_ppStages[i]->SetPos(settings[i].pos);
		m_ppStages[i]->Init();
	}
	//���N���X��z��Ń������m�ۂ���ꍇ��
	//����̃R���X�g���N�^(�����̂Ȃ��R���X�g���N�^)
	//���K�v�B�ǂ����Ă������t���̃R���X�g���N�^��
	//�z��ŌĂяo�������Ƃ��́A�|�C���^���i�[����
	//�z����m�ۂ��A�z����̗v�f�Ƀ������m���
	//�s�����Ƃň����t���̃R���X�g���N�^��
	//�Ăяo������������B


	return true;
}


//====================================================================
//
//		�I������
//
//====================================================================
void StageManager::Uninit()
{
	if (m_ppStages != NULL){
		for (int i = 0; i < m_nStageNum; i++){
			//�ʂɍ폜
			delete m_ppStages[i];
		}
		//�z����폜
		delete[] m_ppStages;
		m_ppStages = NULL;
	}
}


//====================================================================
//
//		�X�V����
//
//====================================================================
void StageManager::Update()
{
	for (int i = 0; i < m_nStageNum; ++i)
	{
		m_ppStages[i]->Update();
	}
}


//====================================================================
//
//		�`�揈��
//
//====================================================================
void StageManager::Draw()
{
	for (int i = 0; i < m_nStageNum; ++i)
	{
		m_ppStages[i]->Draw();
	}
}


//====================================================================
//
//		�X�e�[�W�̎擾
//
//====================================================================
Stage *StageManager::GetStage(int index)
{
	if (index < m_nStageNum)
	{
		return m_ppStages[index];
	}
	return NULL;
}

//====================================================================
//
//		���ڂ̃X�e�[�W����Ԃ�
//
//====================================================================
int StageManager::GetStageNum()
{
	return m_nStageNum;
}

