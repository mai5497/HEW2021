//====================================================================
//
// �X�e�[�W�I�u�W�F�N�g
// �쐬��:�g����
// 
// �X�V��:20212/01/18	�쐬
//====================================================================

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"StageObjectManager.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define MAX_STAGEOBJECT			(10)

typedef enum
{
	STAGE_1 =1,
	STAGE_2,
	STAGE_3,

	MAX_STAGE
}STAGE_NUMBER;
//==============================================================
//
//	StageObjectManager::�R���X�g���N�^
// 
//==============================================================
StageObjectManager::StageObjectManager()
{

}

//==============================================================
//
//	StageObjectManager::�f�X�g���N�^
// 
//==============================================================
StageObjectManager::~StageObjectManager()
{

}

//==============================================================
//
//	StageObjectManager::������
// 
//==============================================================
bool StageObjectManager::Init(int SelectStageNum)
{
	//---�X�e�[�W�I�u�W�F�N�g�̏��
	typedef struct {
		XMFLOAT3 pos;				// ���W
		XMFLOAT3 size;				// �傫��
		LPCSTR TexPath;			// �e�N�X�`���p�X
		LPCSTR ModelPath;			// ���f���p�X
	}StageObjectInfo;
	
	StageObjectInfo StageObjectSet[] =
	{
		//---(��)
		{
			XMFLOAT3(0.0f,1.5f,0.0f),
			XMFLOAT3(0.95f,0.7f,0.95f),
			LPCSTR("Assets/Model/fence.png"),
			LPCSTR("Assets/Model/fenceall.fbx"),
		},
 
		//---(�u���h�[�U�[)
		//{
		//	XMFLOAT3(1.0f,5.0f,3.0f),
		//	XMFLOAT3(1.0f,1.0f,1.0f),
		//	LPCSTR("Assets/Model/bulldozer.png"),
		//	LPCSTR("Assets/Model/bulldozer.fbx"),
		//},
	};

	//switch (m_SelectStageNm)
	//{

	//case STAGE_1:				// �X�e�[�W�P
	//	break;

	//case STAGE_2:				// �X�e�[�W2
	//	break;

	//case STAGE_3:				// �X�e�[�W3

	//	break;

	//default:					// ��O����
	//	break;

	//}


	//---�ő吔���擾
	m_StageObjectNum = sizeof(StageObjectSet) / sizeof(StageObjectSet[0]);

	//---�I�u�W�F�N�g�x�[�X�̃������m��
	m_ppStageObject = new  StageObjectBase *[m_StageObjectNum];

	// �I�u�W�F�N�g�̍ő吔�������m��
	for (int i = 0; i < m_StageObjectNum; i++) {
		m_ppStageObject[i] = new StageObjectBase;
		m_ppStageObject[i]->Init();
		m_ppStageObject[i]->CreateStageObject(StageObjectSet[i].pos, StageObjectSet[i].size, StageObjectSet[i].TexPath, StageObjectSet[i].ModelPath);
	}

	return true;

}

//==============================================================
//
//	StageObjectManager::�I������
// 
//==============================================================
void StageObjectManager::Uninit() 
{
	// �������J��
	for (int i = 0; i < m_StageObjectNum; i++)
	{
		m_ppStageObject[i]->Uninit();
		delete m_ppStageObject[i];
		m_ppStageObject[i] = nullptr;
	}
	delete[] m_ppStageObject;
	m_ppStageObject = nullptr;

}

//==============================================================
//
//	StageObjectManager::�X�V����
// 
//==============================================================
void StageObjectManager::Update()
{
	//---�Ƃ肠���������������Ǝv������(���������ǂ�)
}

//==============================================================
//
//	StageObjectManager::�X�V����
// 
//==============================================================
void StageObjectManager::Draw()
{
	// �X�e�[�W�I�u�W�F�N�g�̕`��
	for (int i = 0; i < m_StageObjectNum; i++){
		m_ppStageObject[i]->Draw();
	}

}

//==============================================================
//
//	ObjectBase�N���X::�I�u�W�F�N�g����
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
//void StageObjectManager::CreateStageObject(int index, XMFLOAT3 pos, XMFLOAT3 size, LPCSTR TexPath, LPCSTR ModelPath)
//{
//	---���W�E�T�C�Y�̎w��
//	m_pos= pos;					
//	m_size = size;
//	m_ppStageObject[index]->SetPos(pos);
//	m_ppStageObject[index]->SetSize(size);
//	m_ppStageObject[index]->GetPos() = pos;
//	m_ppStageObject[index]->GetSize() = size;
//
//	---�e�N�X�`���E���f���̓ǂݍ���
//	LoadTextureFromFile(TexPath, &m_ppStageObject[index]->m_pStageObjectTex);			// �e�N�X�`��
//	m_ppStageObject[index]->LoadStageObject(ModelPath);											// ���f��
//
//	Init();
//}
