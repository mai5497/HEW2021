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

//���݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂���

/* ���t�@�����X(�����̎d��)
	
	�E���W		... X�� �� ��	�c�}�C�i�X	�E�E	�c�v���X
						Y�� �� ��	�c�v���X		�E��	�c�v���X
						Z�� �� ��O	�c�}�C�i�X	�E��	�c�v���X

	�E�傫��		... ���_(0,0,0)����e���W�̎��̗����ɐL�т�
						��)(8,8,8)�ɐݒ�,�e�����+��-�̕����ɂS���L�т�
							������8�̑傫���ɂȂ�
	�E�p�x		... �l�����̂܂܊p�x�̑傫���ɂȂ�
						��)(180.0f,0.0f,0.0f)��������
							X����180�x�����
						���S����0.0f�ɂ͐ݒ�ł��Ȃ��I�I

#define �I�u�W�F�N�g�̖��O				XMFLAOT3(x,y,z),\		���W��������
									XMFLOAT3(x,y,z),\		�傫����������
									XMFLAOT3(x,y,z),\		�p�x��������
									LPCSTR(),\				�e�N�X�`���̃p�X(�G��Ȃ��đ��v)
									LPCSTR(),\				���f���̃p�X(�G��Ȃ��đ��v)
*/

//---��
#define	FENCE						XMFLOAT3(0.0f,1.5f,0.0f),\
									XMFLOAT3(1.45f, 0.7f, 1.45f),\
									XMFLOAT3(0.0f,180.0f,0.0f),\
									LPCSTR("Assets/Model/fence.png"),\
									LPCSTR("Assets/Model/fenceall.fbx")\

//---�{�[��
#define	BALL						XMFLOAT3(35.0f,1.0f,-20.0f),\
									XMFLOAT3(3.0f,3.0f,3.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/ball.png"),\
									LPCSTR("Assets/Model/ball.fbx")\

//---�u���h�[�U�[
#define BULLDOZER					XMFLOAT3(-30.0f,2.0f,0.0f),\
									XMFLOAT3(2.0f,2.0f,2.0f),\
									XMFLOAT3(0.0f,210.0f,0.0f),\
									LPCSTR("Assets/Model/bulldozer.png"),\
									LPCSTR("Assets/Model/bulldozer.fbx")\

//---���Ă̍U���s�N�~��
#define RED_HELMET					XMFLOAT3(0.0f,3.0f,0.0f),\
									XMFLOAT3(5.0f, 5.0f,5.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/kougeki_lambert11_BaseColor.png"),\
									LPCSTR("Assets/Model/helmet.fbx")\

//---���Ă̔j��s�N�~��
#define BLUE_HELMET					XMFLOAT3(-10.0f,1.0f,10.0f),\
									XMFLOAT3(1.0f, 1.0f,1.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/hakai_lambert5_BaseColor.png"),\
									LPCSTR("Assets/Model/helmet2.fbx")\

//---�W�F���K
#define	JENGA						XMFLOAT3(-10.0f,1.0f,20.0f),\
									XMFLOAT3(1.0f, 1.0f,1.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/jenga1.png"),\
									LPCSTR("Assets/Model/jenga.fbx")\


//---�N������
#define KUREYON						XMFLOAT3(30.0f,1.0f,-8.0f),\
									XMFLOAT3(1.0f, 1.0f,1.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/kureyon.png"),\
									LPCSTR("Assets/Model/kureyon.fbx")\

//---�s���N�J�[
#define PINKCAR						XMFLOAT3(-30.0f,1.0f,0.0f),\
									XMFLOAT3(1.0f, 1.0f,1.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/pinkcar.png"),\
									LPCSTR("Assets/Model/pinkcar.fbx")\

//---���S
#define REGO						XMFLOAT3(0.0f,1.0f,-15.0f),\
									XMFLOAT3(5.0f, 5.0f,5.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/rego.png"),\
									LPCSTR("Assets/Model/rego.fbx")\

//---���[�r�b�N�L���[�u
#define RUBIKCUBE					XMFLOAT3(0.0f,1.0f,10.0f),\
									XMFLOAT3(1.0f, 1.0f,1.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/rubikcube.png"),\
									LPCSTR("Assets/Model/rubikcube.fbx")\

//---�X�^���h���C�g
#define STANDLIGHT					XMFLOAT3(0.0f,0.0f,0.0f),\
									XMFLOAT3(1.0f,1.0f,1.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/standlight.png"),\
									LPCSTR("Assets/Model/standlight.fbx")\

//---�d��
#define TRAIN						XMFLOAT3(10.0f,1.0f,10.0f),\
									XMFLOAT3(1.0f, 1.0f,1.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/train.png"),\
									LPCSTR("Assets/Model/train.fbx")\

//---�g�����v�^���[
#define TRUMPTOWER					XMFLOAT3(0.0f,1.0f,0.0f),\
									XMFLOAT3(1.0f,1.0f,1.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/trumptower.jpg"),\
									LPCSTR("Assets/Model/trumptower.fbx")\

//---�c�~�L�̏�
#define TUMIKICASTLE				XMFLOAT3(0.0f,-20.0f,60.0f),\
									XMFLOAT3(3.0f, 3.0f, 3.0f),\
									XMFLOAT3(1.0f,0.0f,0.0f),\
									LPCSTR("Assets/Model/tumikicastel.png"),\
									LPCSTR("Assets/Model/tumikicastel.fbx")\

//��݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂���

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
	m_SelectStageNm = SelectStageNum;

	//---�X�e�[�W�I�u�W�F�N�g�̏��
	typedef struct {
		XMFLOAT3 pos;				// ���W
		XMFLOAT3 size;				// �傫��
		XMFLOAT3 angle;			// �p�x
		LPCSTR TexPath;			// �e�N�X�`���p�X
		LPCSTR ModelPath;		// ���f���p�X
	}StageObjectInfo;
	
	//---�X�e�[�W1�ɔz�u����I�u�W�F�N�g
	StageObjectInfo Stage1ObjectSet[] =
	{
		//---(��)
		FENCE,
	};

	//---�X�e�[�W2�ɔz�u����
	StageObjectInfo Stage2ObjectSet[] =
	{
		
		BALL,
		BULLDOZER,
		RED_HELMET,
		BLUE_HELMET,


	};

	switch (m_SelectStageNm)
	{

	case STAGE_1:				// �X�e�[�W�P

	 	//---�ő吔���擾
		m_StageObjectNum = sizeof(Stage1ObjectSet) / sizeof(Stage1ObjectSet[0]);

		//---�I�u�W�F�N�g�x�[�X�̃������m��
		m_ppStageObject = new  StageObjectBase * [m_StageObjectNum];

		//�I�u�W�F�N�g�̍ő吔�������m��
		for (int i = 0; i < m_StageObjectNum; i++) {
			m_ppStageObject[i] = new StageObjectBase;
			m_ppStageObject[i]->Init();
			m_ppStageObject[i]->CreateStageObject(Stage1ObjectSet[i].pos, Stage1ObjectSet[i].size, Stage1ObjectSet[i].angle, Stage1ObjectSet[i].TexPath, Stage1ObjectSet[i].ModelPath);
		}
		break;

	case STAGE_2:				// �X�e�[�W2

		//---�ő吔���擾
		m_StageObjectNum = sizeof(Stage2ObjectSet) / sizeof(Stage2ObjectSet[0]);

		//---�I�u�W�F�N�g�x�[�X�̃������m��
		m_ppStageObject = new  StageObjectBase * [m_StageObjectNum];

		//�I�u�W�F�N�g�̍ő吔�������m��
		for (int i = 0; i < m_StageObjectNum; i++) {
			m_ppStageObject[i] = new StageObjectBase;
			m_ppStageObject[i]->Init();
			m_ppStageObject[i]->CreateStageObject(Stage2ObjectSet[i].pos, Stage2ObjectSet[i].size, Stage2ObjectSet[i].angle,Stage2ObjectSet[i].TexPath, Stage2ObjectSet[i].ModelPath);
		}
		break;

	case STAGE_3:				// �X�e�[�W3

		break;

	default:					// ��O����
		break;

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
	switch (m_SelectStageNm)
	{
	case STAGE_1:
		// �������J��
		for (int i = 0; i < m_StageObjectNum; i++)
		{
			m_ppStageObject[i]->Uninit();
			delete m_ppStageObject[i];
			m_ppStageObject[i] = nullptr;
		}
		delete[] m_ppStageObject;
		m_ppStageObject = nullptr;
		break;

	case STAGE_2:
		// �������J��
		for (int i = 0; i < m_StageObjectNum; i++)
		{
			m_ppStageObject[i]->Uninit();
			delete m_ppStageObject[i];
			m_ppStageObject[i] = nullptr;
		}
		delete[] m_ppStageObject;
		m_ppStageObject = nullptr;
		break;

	case STAGE_3:
		break;


	default:
		break;
	}


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

	switch (m_SelectStageNm)
	{
	case STAGE_1:
		// �X�e�[�W�I�u�W�F�N�g�̕`��
		for (int i = 0; i < m_StageObjectNum; i++) {
			m_ppStageObject[i]->Draw();
		}
		break;

	case STAGE_2:
		// �X�e�[�W�I�u�W�F�N�g�̕`��
		for (int i = 0; i < m_StageObjectNum; i++) {
			m_ppStageObject[i]->Draw();
		}
		break;

	case STAGE_3:
		break;


	default:
		break;
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
