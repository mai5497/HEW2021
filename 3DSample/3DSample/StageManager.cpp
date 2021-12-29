#include "StageManager.h"

StageManager::StageManager():m_ppStages(NULL),m_nStageNum(0)
{

}
StageManager::~StageManager()
{
	Uninit();
}

bool StageManager::Init()
{
	struct StageSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};

	StageSetting settings[] =
	{
		//�傫����
		{ DirectX::XMFLOAT3( 0.0f,-0.5f, 0.0f),
		  DirectX::XMFLOAT3(50.0f, 1.0f,50.0f),
		},
		//���l�̃X�e�[�W
		{ DirectX::XMFLOAT3( 0.0f,0.5f, 0.0f),
		 DirectX::XMFLOAT3( 19.0f,1.0f,19.0f),
		},
		//�E�̕�
		{DirectX::XMFLOAT3(12.5f,0.0f,0.0f),
		DirectX::XMFLOAT3(2.0f,3.0f,27.0f)
		},
		//���̕�
		{DirectX::XMFLOAT3(-12.5f,0.0f,0.0f),
		DirectX::XMFLOAT3(2.0f,3.0f,27.0f)
		},
		//���̕�
		{DirectX::XMFLOAT3(0.0f,0.0f,12.5f),
		DirectX::XMFLOAT3(27.0f,3.0f,2.0f)
		},
		//��O�̕�
		{DirectX::XMFLOAT3(0.0f,0.0f,-12.5f),
		DirectX::XMFLOAT3(27.0f,3.0f,2.0f)
		}

	};

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
void StageManager::Update()
{
	for (int i = 0; i < m_nStageNum; ++i)
	{
		m_ppStages[i]->Update();
	}
}
void StageManager::Draw()
{
	for (int i = 0; i < m_nStageNum; ++i)
	{
		m_ppStages[i]->Draw();
	}
}

Stage *StageManager::GetStage(int index)
{
	if (index < m_nStageNum)
	{
		return m_ppStages[index];
	}
	return NULL;
}

int StageManager::GetStageNum()
{
	return m_nStageNum;
}

