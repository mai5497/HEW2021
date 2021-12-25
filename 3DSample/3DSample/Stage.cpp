//========================= �C���N���[�h�� ===========================
#include "Stage.h"
#include "Texture.h"


//========================= �O���[�o���ϐ���` ===========================
//DrawBuffer *Stage::m_pBuffer = NULL;
//FBXPlayer *Stage::m_pFBX = NULL;

static LPCSTR g_TexName[MODEL_MAX] = {
	"Assets/Model/base1.png",
	"Assets/Model/ground.png",
	"Assets/Model/ground.png",
	"Assets/Model/ground.png",
	"Assets/Model/ground.png",
	"Assets/Model/ground.png",
};

static LPCSTR g_ModelName[MODEL_MAX] = {
	"Assets/Model/base1.fbx",
	"Assets/Model/ground.fbx",
	"Assets/Model/ground.fbx",
	"Assets/Model/ground.fbx",
	"Assets/Model/ground.fbx",
	"Assets/Model/ground.fbx",
};



Stage::Stage():m_ppFields(NULL),m_nFieldNum(0)
{
	for (int i = 0; i < MODEL_MAX; i++) {
		LoadTextureFromFile(g_TexName[i], &m_pStageTex[i]);
	}
}
Stage::~Stage()
{
	Uninit();
}

bool Stage::Init()
{

	struct FieldSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};

	FieldSetting settings[] =
	{
		//�傫����
		{ DirectX::XMFLOAT3(0,-0.5f,0),
		  DirectX::XMFLOAT3(50,1,50),
		},
		//���l�̃X�e�[�W
		{ DirectX::XMFLOAT3(0,0.5f,0),
		 DirectX::XMFLOAT3(13,1,13),
		},
		//�E�̕�
		{DirectX::XMFLOAT3(10,-0.5f,0),
		DirectX::XMFLOAT3(2.5f,3,20)},
		//���̕�
		{DirectX::XMFLOAT3(-10,-0.5f,0),
		DirectX::XMFLOAT3(2.5f,3,20) },
		//���̕�
		{DirectX::XMFLOAT3(0,-0.5f,10),
		DirectX::XMFLOAT3(22.5,3,2.5f)},
		//��O�̕�
		{DirectX::XMFLOAT3(0,-0.5f,-10),
		DirectX::XMFLOAT3(22.5,3,2.5f)}
	};

	//�����f�[�^����t�B�[���h�̐����v�Z
	m_nFieldNum = sizeof(settings) / sizeof(settings[0]);

	//�|�C���^���i�[����z����쐬
	m_ppFields = new FieldManager *[m_nFieldNum];

	//���ꂼ��̔z��Ƀt�B�[���h���������m��
	for (int i = 0; i < m_nFieldNum; i++)
	{
		Stage::LoadStage(g_ModelName[i], i);
		m_ppFields[i] = new FieldManager(settings[i].size);
		m_ppFields[i]->SetPos(settings[i].pos);
		m_ppFields[i]->Init();
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


void Stage::Uninit()
{
	delete[] m_pBuffer;
	m_pBuffer = NULL;
	for (int i = 0; i < MODEL_MAX; i++) {
		delete[] m_pFBX;
	}
	m_pFBX = NULL;


	if (m_ppFields != NULL){
		for (int i = 0; i < m_nFieldNum; i++){
			//�ʂɍ폜
			delete m_ppFields[i];
		}
		//�z����폜
		delete[] m_ppFields;
		m_ppFields = NULL;
	}
}


void Stage::Update()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Update();
	}
}


void Stage::Draw()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Draw();
	}
}


FieldManager *Stage::GetField(int index)
{
	if (index < m_nFieldNum)
	{
		return m_ppFields[index];
	}
	return NULL;
}


int Stage::GetFieldNum()
{
	return m_nFieldNum;
}


//====================================================================
//
//		�e�N�X�`���ǂݍ���
//
//====================================================================
bool Stage::LoadStage(const char* pFilePath,int num) {
	/* �ȉ��̓��f����������g�p */
	HRESULT hr;
	m_pFBX[num] = new FBXPlayer;
	hr = m_pFBX[num]->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
	int meshNum = m_pFBX[num]->GetMeshNum();
	m_pBuffer[num] = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
		//���b�V�����Ƃɒ��_�o�b�t�@�쐬
		m_pBuffer[num][i].CreateVertexBuffer(
			m_pFBX[num]->GetVertexData(i),
			m_pFBX[num]->GetVertexSize(i),
			m_pFBX[num]->GetVertexCount(i)
		);
		//�C���f�b�N�X�o�b�t�@�쐬
		m_pBuffer[num][i].CreateIndexBuffer(
			m_pFBX[num]->GetIndexData(i),
			m_pFBX[num]->GetIndexCount(i)
		);

	}
	return true;
}
