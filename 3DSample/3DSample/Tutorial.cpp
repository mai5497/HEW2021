//****************************************************
//
//	�`���[�g���A��
//	�쐬�ҁF�ɐ����P
//	��������Ȃǂ�`��
//	
//	01/26 : �f�ލ����ւ�
//  01/26 : �I�u�W�F�N�g�ǉ�
//	01\31 : �N���A�K�C�h�ǉ�
// 
//****************************************************

//========================= �C���N���[�h�� ===========================
#include "Tutorial.h"
#include "Input.h"

//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
int g_nCnt;

Tutorial::Tutorial()
{

}
Tutorial::~Tutorial()
{

}

//====================================================================
//
//		������
//
//====================================================================
void Tutorial::Init()
{
	LoadTextureFromFile("Assets/Texture/UI/Tutorial.png", &m_pTexTutorial[0]);
	LoadTextureFromFile("Assets/Texture/UI/flower.png", &m_pTexTutorial[1]);
	LoadTextureFromFile("Assets/Texture/UI/dwarf.png", &m_pTexTutorial[2]);
	LoadTextureFromFile("Assets/Texture/UI/Gide_BG.png", &m_pTexTutorial[3]);

	// �R���g���[���[����
	m_pObjectTutorial[0] = new GameObject;
	m_pObjectTutorial[0]->Init();
	m_pObjectTutorial[0]->SetPos(DirectX::XMFLOAT3(0.3f, -0.15f, 1));
	m_pObjectTutorial[0]->SetSize(DirectX::XMFLOAT3(0.3f, 0.25f, 1));
	// ��
	m_pObjectTutorial[1] = new GameObject;
	m_pObjectTutorial[1]->Init();
	m_pObjectTutorial[1]->SetPos(DirectX::XMFLOAT3(0.35f, -0.25f, 1));
	m_pObjectTutorial[1]->SetSize(DirectX::XMFLOAT3(0.13f, 0.11f, 1));
	// ���l
	m_pObjectTutorial[2] = new GameObject;
	m_pObjectTutorial[2]->Init();
	m_pObjectTutorial[2]->SetPos(DirectX::XMFLOAT3(-0.18f, 0.23, 1));
	m_pObjectTutorial[2]->SetSize(DirectX::XMFLOAT3(0.13f, 0.115f, 1));
	// �N���A����
	m_pObjectTutorial[3] = new GameObject;
	m_pObjectTutorial[3]->Init();
	m_pObjectTutorial[3]->SetPos(DirectX::XMFLOAT3(-0.4f, 0.20, 1));
	m_pObjectTutorial[3]->SetSize(DirectX::XMFLOAT3(0.2f, 0.15f, 1));
	m_pObjectTutorial[3]->SetCollor(DirectX::XMFLOAT4(1.0f, 1.0f,1.0f,0.6f));


	m_pCameraTutorial = new Camera;
	m_pCameraTutorial->Init(XMFLOAT3(0.0f, 0.0f, -5.0f));

	g_nCnt = 3;

}

//====================================================================
//
//		�I������
//
//====================================================================
void Tutorial::Uninit()
{
	m_pCameraTutorial->Uninit();
	delete m_pCameraTutorial;

	for (int i = 0; i < 4; i++)
	{
		SAFE_RELEASE(m_pTexTutorial[i]);

		m_pObjectTutorial[i]->Uninit();
		delete m_pObjectTutorial[i];

	}
}
//====================================================================
//
//		�X�V
//
//====================================================================
void Tutorial::Update()
{
	// �������ꂽ�������萔���s���鎖�Ő������폜
	if (IsTrigger('Q') || IsTrigger('E')) {
		g_nCnt --;
	}
	for (int i = 0; i < 4; i++)
	{
		m_pObjectTutorial[i]->Update();
	}
}

//====================================================================
//
//		�`��
//
//====================================================================
void Tutorial::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	m_pCameraTutorial->Bind2D();

	// �R���g���[���[����
	SHADER->SetTexture(m_pTexTutorial[0]);
	if (g_nCnt > 0)
	{
		//m_pObjectTutorial[0]->Draw();
	}

	// ��
	SHADER->SetTexture(m_pTexTutorial[1]);
	m_pObjectTutorial[1]->Draw();

	// ����UI�Ȃ̂�������Ȃ������̂ŉ��ŃR�����g�A�E�g
	// ���l
	//SHADER->SetTexture(m_pTexTutorial[2]);
	//m_pObjectTutorial[2]->Draw();

	// �N���A�K�C�h
	SHADER->SetTexture(m_pTexTutorial[3]);
	m_pObjectTutorial[3]->Draw();

	SHADER->SetTexture(NULL);
}