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
#include "Texture.h"

#define STAGE_SIZE (0.007f)

ID3D11ShaderResourceView *m_pStageTex[3];

DrawBuffer *StageManager::m_pBuffer = NULL;
FBXPlayer *StageManager::m_pfbx = NULL;


//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
StageManager::StageManager():m_ppStages(NULL),m_nStageNum(0)
{
	//LoadTextureFromFile("Assets/Model/woodground.jpg", &m_pStageTex[0]);
	LoadTextureFromFile("Assets/Model/base1.jpg", &m_pStageTex[0]);
	LoadTextureFromFile("Assets/Model/ground.png", &m_pStageTex[1]);
	LoadTextureFromFile("Assets/Model/base2.jpg", &m_pStageTex[2]);
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

bool StageManager::LoadStage(const char* pFilePath) {
	HRESULT hr;
	m_pfbx = new FBXPlayer;
	hr = m_pfbx->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
	int meshNum = m_pfbx->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
		//���b�V�����Ƃɒ��_�o�b�t�@�쐬
		m_pBuffer[i].CreateVertexBuffer(
			m_pfbx->GetVertexData(i),
			m_pfbx->GetVertexSize(i),
			m_pfbx->GetVertexCount(i)
		);
		//�C���f�b�N�X�o�b�t�@�쐬
		m_pBuffer[i].CreateIndexBuffer(
			m_pfbx->GetIndexData(i),
			m_pfbx->GetIndexCount(i)
		);

	}
	return true;
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
	if (m_pBuffer == NULL) {
		LoadStage("Assets/Model/ground2.fbx");
	}



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
		  XMFLOAT3(0.8f,1.0f,0.8f),
		},
		////�E�̕�
		//{ XMFLOAT3(12.5f,0.0f,0.0f),
		// XMFLOAT3(2.0f,3.0f,27.0f)
		//},
		////���̕�
		//{ XMFLOAT3(-12.5f,0.0f,0.0f),
		//  XMFLOAT3(2.0f,3.0f,27.0f)
		//},
		////���̕�
		//{ XMFLOAT3(0.0f,0.0f,12.5f),
		//  XMFLOAT3(27.0f,3.0f,2.0f)
		//},
		////��O�̕�
		//{ XMFLOAT3(0.0f,0.0f,-12.5f),
		//  XMFLOAT3(27.0f,3.0f,2.0f)
		//},
		//�傫���ǉE
		{ XMFLOAT3(25,0.0f,0),
		  XMFLOAT3(1,30,50),
		},

		//�傫���Ǎ�
		{ XMFLOAT3(-25,0.0f,0),
		  XMFLOAT3(1,30,50),
		},

		//�傫���ǉ�
		{ XMFLOAT3(0,0.0f,25),
		  XMFLOAT3(50,30,1),
		},

	};


	//switch (m_SelectStageNum) {
	//	case 1:
	//		settings[1] =
	//		{
	//			//���l�̃X�e�[�W
	//			XMFLOAT3(0.0f,0.5f, 0.0f),
	//			XMFLOAT3(0.8f,0.8f,0.8f),
	//		};
	//		break;
	//	case 2:
	//		settings[1] =
	//		{
	//			//���l�̃X�e�[�W
	//			XMFLOAT3(0.0f,0.5f, 0.0f),
	//			XMFLOAT3(0.5f,0.5f,0.5f),
	//		};
	//		break;
	//	case 3:
	//		settings[1] =
	//		{
	//			//���l�̃X�e�[�W
	//			XMFLOAT3(0.0f,0.5f, 0.0f),
	//			XMFLOAT3(0.6f,0.6f,0.6f),
	//		};
	//		break;
	//	default:
	//		break;
	//}
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
	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pfbx;
		m_pfbx = NULL;
	}

	for (int i = 0; i < m_nStageNum; i++) {
		SAFE_RELEASE(m_pStageTex[i]);
	}

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
	int meshNum = m_pfbx->GetMeshNum();

	SHADER->SetTexture(m_pStageTex[0]);
	m_ppStages[0]->Draw();

	// ���l�̃X�e�[�W
	for (int j = 0; j < meshNum; ++j) {
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(m_ppStages[1]->GetSize().x, m_ppStages[1]->GetSize().y, m_ppStages[1]->GetSize().z)
			*DirectX::XMMatrixRotationY(XM_PI)
			*DirectX::XMMatrixTranslation(m_ppStages[1]->GetPos().x, m_ppStages[1]->GetPos().y, m_ppStages[1]->GetPos().z));

		SHADER->SetTexture(m_pStageTex[1]);
		m_pBuffer[j].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	SHADER->SetTexture(m_pStageTex[2]);
	m_ppStages[2]->Draw();
	m_ppStages[3]->Draw();
	m_ppStages[4]->Draw();


	SHADER->SetTexture(NULL);




	//for (int i = 0; i < m_nStageNum; ++i)
	//{
	//	m_ppStages[i]->Draw();
	//}
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

