//****************************************************
//
//	�`���[�g���A��
//	�쐬�ҁF�ɐ����P
//	��������p�̉摜��`��
//
//****************************************************

#include "Tutorial.h"
#include "Input.h"

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
	LoadTextureFromFile("Assets/Texture/Tutorial.png", &m_pTexTutorial[0]);
	LoadTextureFromFile("Assets/Texture/flower.png", &m_pTexTutorial[1]);
	LoadTextureFromFile("Assets/Texture/dwarf.png", &m_pTexTutorial[2]);
	m_pObjectTutorial[0] = new GameObject;
	m_pObjectTutorial[0]->Init();
	m_pObjectTutorial[0]->SetPos(DirectX::XMFLOAT3(0.3f, -0.15f, 1));
	m_pObjectTutorial[0]->SetSize(DirectX::XMFLOAT3(0.3f, 0.25f, 1));
	m_pObjectTutorial[1] = new GameObject;
	m_pObjectTutorial[1]->Init();
	m_pObjectTutorial[1]->SetPos(DirectX::XMFLOAT3(-0.34f, 0.23f, 1));
	m_pObjectTutorial[1]->SetSize(DirectX::XMFLOAT3(0.13f, 0.11f, 1));
	m_pObjectTutorial[2] = new GameObject;
	m_pObjectTutorial[2]->Init();
	m_pObjectTutorial[2]->SetPos(DirectX::XMFLOAT3(-0.18f, 0.23, 1));
	m_pObjectTutorial[2]->SetSize(DirectX::XMFLOAT3(0.13f, 0.115f, 1));
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
	for (int i = 0; i < 3; i++)
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

	SHADER->SetTexture(m_pTexTutorial[0]);
	if (g_nCnt > 0)
	{
		m_pObjectTutorial[0]->Draw();
	}

	SHADER->SetTexture(m_pTexTutorial[1]);
	m_pObjectTutorial[1]->Draw();

	SHADER->SetTexture(m_pTexTutorial[2]);
	//m_pObjectTutorial[2]->Draw();



	SHADER->SetTexture(NULL);
}