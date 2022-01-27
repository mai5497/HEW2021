//****************************************************
//
//	スコア
//	作成者：伊吹汰輝
//	ステージクリア時にスコアに応じて星を描画
// 
//  01/27 : ステージクリア時星１つを実装
//			コメント追記
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
//		終了処理
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


	// スコアの入手量で描画
	switch (m_nScore)
	{
	case 1:
		SHADER->SetTexture(m_pTexScore[1]);
		// クリア時星１つしか実装してないのでここに仮で描画
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
//		スコア設定
//
//====================================================================
void Score::SetScore(int score)
{
	m_nScore = score;
}
