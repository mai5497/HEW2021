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
	LoadTextureFromFile("Assets/Model/Tutorial000.jpg", &m_pTexTutorial);
	m_pObjectTutorial = new GameObject;
	m_pObjectTutorial->Init();
	m_pObjectTutorial->SetPos(DirectX::XMFLOAT3(4, 8, -18));
	m_pObjectTutorial->SetSize(DirectX::XMFLOAT3(2, 1, 0));
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
	SHADER->Bind(VS_WORLD, PS_PHONG);



	SHADER->SetTexture(m_pTexTutorial);

	if(g_nCnt > 0)
		m_pObjectTutorial->Draw();


	SHADER->SetTexture(NULL);
}