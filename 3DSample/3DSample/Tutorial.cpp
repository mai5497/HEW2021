//****************************************************
//
//	チュートリアル
//	作成者：伊吹汰輝
//	操作説明などを描画
//	
//	01/26 : 素材差し替え
//  01/26 : オブジェクト追加
//	01\31 : クリアガイド追加
// 
//****************************************************

//========================= インクルード部 ===========================
#include "Tutorial.h"
#include "Input.h"

//*******************************************************************************
// グローバル宣言
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
//		初期化
//
//====================================================================
void Tutorial::Init()
{
	LoadTextureFromFile("Assets/Texture/UI/Tutorial.png", &m_pTexTutorial[0]);
	LoadTextureFromFile("Assets/Texture/UI/flower.png", &m_pTexTutorial[1]);
	LoadTextureFromFile("Assets/Texture/UI/dwarf.png", &m_pTexTutorial[2]);
	LoadTextureFromFile("Assets/Texture/UI/Gide_BG.png", &m_pTexTutorial[3]);

	// コントローラー説明
	m_pObjectTutorial[0] = new GameObject;
	m_pObjectTutorial[0]->Init();
	m_pObjectTutorial[0]->SetPos(DirectX::XMFLOAT3(0.3f, -0.15f, 1));
	m_pObjectTutorial[0]->SetSize(DirectX::XMFLOAT3(0.3f, 0.25f, 1));
	// 花
	m_pObjectTutorial[1] = new GameObject;
	m_pObjectTutorial[1]->Init();
	m_pObjectTutorial[1]->SetPos(DirectX::XMFLOAT3(0.35f, -0.25f, 1));
	m_pObjectTutorial[1]->SetSize(DirectX::XMFLOAT3(0.13f, 0.11f, 1));
	// 小人
	m_pObjectTutorial[2] = new GameObject;
	m_pObjectTutorial[2]->Init();
	m_pObjectTutorial[2]->SetPos(DirectX::XMFLOAT3(-0.18f, 0.23, 1));
	m_pObjectTutorial[2]->SetSize(DirectX::XMFLOAT3(0.13f, 0.115f, 1));
	// クリア説明
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
//		終了処理
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
//		更新
//
//====================================================================
void Tutorial::Update()
{
	// 説明された操作を一定数実行する事で説明を削除
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
//		描画
//
//====================================================================
void Tutorial::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	m_pCameraTutorial->Bind2D();

	// コントローラー説明
	SHADER->SetTexture(m_pTexTutorial[0]);
	if (g_nCnt > 0)
	{
		//m_pObjectTutorial[0]->Draw();
	}

	// 花
	SHADER->SetTexture(m_pTexTutorial[1]);
	m_pObjectTutorial[1]->Draw();

	// 何のUIなのか分からなかったので仮でコメントアウト
	// 小人
	//SHADER->SetTexture(m_pTexTutorial[2]);
	//m_pObjectTutorial[2]->Draw();

	// クリアガイド
	SHADER->SetTexture(m_pTexTutorial[3]);
	m_pObjectTutorial[3]->Draw();

	SHADER->SetTexture(NULL);
}