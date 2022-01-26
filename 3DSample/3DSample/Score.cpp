//****************************************************
//
//	スコア
//	作成者：伊吹汰輝
//	
//
//****************************************************

//========================= インクルード部 ===========================
#include "Score.h"




Score::Score()
{

}
Score::~Score()
{

}

//====================================================================
//
//		初期化
//
//====================================================================
void Score::Init()
{
	LoadTextureFromFile("Assets/Texture/SceneTexture/star/star_3.png", &m_pTexScore);
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
//		終了処理
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
//		更新
//
//====================================================================
void Score::Update()
{
	
}

//====================================================================
//
//		描画
//
//====================================================================
void Score::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	m_pCameraScore->Bind2D();

	SHADER->SetTexture(m_pTexScore);

	// スコア入手で描画
	switch (m_nScore)
	{
	case 5:
		break;
		m_pObjectScore->Draw();

	default:
		break;
	}
	

	SHADER->SetTexture(NULL);
}

//====================================================================
//
//		スコア設定
//
//====================================================================
void Score::SetScore(int score)
{
	m_nScore = score;
}
