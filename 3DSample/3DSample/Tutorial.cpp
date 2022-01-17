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
	LoadTextureFromFile("Assets/Texture/Tutorial000.jpg", &m_pTexTutorial);
	m_pObjectTutorial = new GameObject;
	m_pObjectTutorial->Init();
	m_pObjectTutorial->SetPos(DirectX::XMFLOAT3(0.2f, -0.2f, 1));
	m_pObjectTutorial->SetSize(DirectX::XMFLOAT3(0.2f, 0.1f, 1));
	m_pCameraTutorial = new Camera;
	m_pCameraTutorial->Init();

	g_nCnt = 3;

}
//====================================================================
//
//		�I������
//
//====================================================================
void Tutorial::Uninit()
{
	SAFE_RELEASE(m_pTexTutorial);
	m_pCameraTutorial->Uninit();
	delete m_pCameraTutorial;
	m_pObjectTutorial->Uninit();
	delete m_pObjectTutorial;
}
//====================================================================
//
//		�X�V
//
//====================================================================
void Tutorial::Update()
{
	// �������ꂽ�������萔���s���鎖�Ő������폜
	if (IsTrigger('Z')) {	
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

	SHADER->SetTexture(m_pTexTutorial);

	if(g_nCnt > 0)
		m_pObjectTutorial->Draw();


	SHADER->SetTexture(NULL);
}