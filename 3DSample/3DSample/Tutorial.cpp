//****************************************************
//
//	チュートリアル
//	作成者：伊吹汰輝
//	操作説明用の画像を描画
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
//		初期化
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
	SAFE_RELEASE(m_pTexTutorial);
	m_pCameraTutorial->Uninit();
	delete m_pCameraTutorial;
	m_pObjectTutorial->Uninit();
	delete m_pObjectTutorial;
}
//====================================================================
//
//		更新
//
//====================================================================
void Tutorial::Update()
{
	// 説明された操作を一定数実行する事で説明を削除
	if (IsTrigger('Z')) {	
		g_nCnt --;
	}
}
//====================================================================
//
//		描画
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