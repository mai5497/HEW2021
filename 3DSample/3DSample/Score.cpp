//****************************************************
//
//	�X�R�A
//	�쐬�ҁF�ɐ����P
//	
//
//****************************************************

//========================= �C���N���[�h�� ===========================
#include "Score.h"




Score::Score()
{

}
Score::~Score()
{

}

//====================================================================
//
//		������
//
//====================================================================
void Score::Init()
{
	LoadTextureFromFile("Assets/Model/good.png", &m_pTexScore);
	m_pObjectScore = new GameObject;
	m_pObjectScore->Init();
	m_pObjectScore->SetPos(DirectX::XMFLOAT3(0, 10, -10));
	m_pObjectScore->SetSize(DirectX::XMFLOAT3(8, 6, 1));
	m_pCameraScore = new Camera;
	m_pCameraScore->Init(XMFLOAT3(0.0f, 0.0f, -5.0f));;

	m_nScore = 0;
}

//====================================================================
//
//		�I������
//
//====================================================================
void Score::Uninit()
{
	SAFE_RELEASE(m_pTexScore);
	m_pCameraScore->Uninit();
	delete m_pCameraScore;
	m_pObjectScore->Uninit();
	delete m_pObjectScore;
}

//====================================================================
//
//		�X�V
//
//====================================================================
void Score::Update()
{
	
}

//====================================================================
//
//		�`��
//
//====================================================================
void Score::Draw()
{
	SHADER->Bind(VS_WORLD, PS_PHONG);



	SHADER->SetTexture(m_pTexScore);

	// �X�R�A����ŕ`��
	if (m_nScore > 5){
		m_pObjectScore->Draw();
	}

	SHADER->SetTexture(NULL);
}

//====================================================================
//
//		�X�R�A�ݒ�
//
//====================================================================
void Score::SetScore(int score)
{
	m_nScore = score;
}
