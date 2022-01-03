//****************************************************
//
//	セレクトシーン
//	作成者：園田翔大
//	
//	2021/12/27 : 作成
//	2022/01/02 : コメント追加（伊地田）
//				 ステージ番号の変数を追加（伊地田）
//
//****************************************************

//========================= インクルード部 ===========================
#include "SelectScene.h"
#include "Input.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "GameObject.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "Defines.h"


//========================= グローバル変数定義 ===========================
ID3D11ShaderResourceView* g_pSelectTex;
//DrawBuffer g_pBuffer;
//TPSCamera* g_pSelectTPSCamera;
Camera* g_pSelectCamera;
GameObject* g_pSelectObject;

//====================================================================
//
//		コンストラクタ
//
//====================================================================
SelectScene::SelectScene(void)
{

}


//====================================================================
//
//		デストラクタ
//
//====================================================================
SelectScene::~SelectScene(void)
{

}


//====================================================================
//
//		初期化
//
//====================================================================
void SelectScene::Init()
{
	LoadTextureFromFile("Assets/Model/Select.png", &g_pSelectTex);

	//g_pSelectTPSCamera = new TPSCamera();
	//g_pSelectTPSCamera->Init();
	//g_pSelectTPSCamera->SetTargetObj(g_pSelectBG);
	g_pSelectObject = new GameObject;
	g_pSelectObject->Init();
	g_pSelectObject->SetPos(DirectX::XMFLOAT3(0, 0, 300));
	g_pSelectObject->SetSize(DirectX::XMFLOAT3(1, (float)SCREEN_HEIGHT / SCREEN_WIDTH, 1));

	g_pSelectCamera = new Camera;
	g_pSelectCamera->Init();

}


//====================================================================
//
//		終了処理
//
//====================================================================
void SelectScene::Uninit()
{
	SAFE_RELEASE(g_pSelectTex);
	g_pSelectCamera->Uninit();
	//delete g_pSelectTPSCamera;
	delete g_pSelectCamera;
	g_pSelectObject->Uninit();
	delete g_pSelectObject;


}


//====================================================================
//
//		更新処理
//
//====================================================================
SCENE SelectScene::Update()
{
	//g_pSelectTPSCamera->Update();

	if (IsTrigger('1')) {	// ステージ１
		m_StageNum = 1;
		return SCENE_GAME;
	}
	if (IsTrigger('2')) {	// ステージ２
		m_StageNum = 2;
		return SCENE_GAME;
	}
	if (IsTrigger('3')) {	// ステージ３
		m_StageNum = 3;
		return SCENE_GAME;
	}


	return SCENE_SELECT;
}


//====================================================================
//
//		描画処理
//
//====================================================================
void SelectScene::Draw()
{
	SHADER->Bind(VS_WORLD, PS_PHONG);

	g_pSelectCamera->Bind2D();

	SHADER->SetTexture(g_pSelectTex);

	//g_pBuffer.Draw(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	g_pSelectObject->Draw();

	SHADER->SetTexture(NULL);

}


//====================================================================
//
//		シーン番号取得
//
//====================================================================
int SelectScene::GetStageNum()
{
	return m_StageNum;
}