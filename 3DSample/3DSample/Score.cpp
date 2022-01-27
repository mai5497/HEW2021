//****************************************************
//
//	�X�R�A
//	�쐬�ҁF�ɐ����P
//	�X�e�[�W�N���A���ɃX�R�A�ɉ����Đ���`��
// 
//  01/27 : �X�e�[�W�N���A�����P������
//			�R�����g�ǋL
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
	LoadTextureFromFile("Assets/Texture/UI/star/star_0.png", &m_pTexScore[0]);
	LoadTextureFromFile("Assets/Texture/UI/star/star_1.png", &m_pTexScore[1]);
	LoadTextureFromFile("Assets/Texture/UI/star/star_2.png", &m_pTexScore[2]);
	LoadTextureFromFile("Assets/Texture/UI/star/star_3.png", &m_pTexScore[3]);

	m_pObjectScore = new GameObject;
	m_pObjectScore->Init();
	m_pObjectScore->SetPos(DirectX::XMFLOAT3(0.0f, 0.15f, 1));
	m_pObjectScore->SetSize(DirectX::XMFLOAT3(0.3f, 0.2f, 1));

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
	for (int i = 0; i < 4; i++)
	{
		SAFE_RELEASE(m_pTexScore[i]);
	}
	
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
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	m_pCameraScore->Bind2D();


	// �X�R�A�̓���ʂŕ`��
	switch (m_nScore)
	{
	case 1:
		SHADER->SetTexture(m_pTexScore[1]);
		// �N���A�����P�����������ĂȂ��̂ł����ɉ��ŕ`��
		m_pObjectScore->Draw();					
		break;
	default:
		SHADER->SetTexture(m_pTexScore[0]);
		break;
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
