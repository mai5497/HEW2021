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
	SHADER->Bind(VS_WORLD, PS_PHONG);



	SHADER->SetTexture(m_pTexScore);

	// スコア入手で描画
	if (m_nScore > 5){
		m_pObjectScore->Draw();
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
