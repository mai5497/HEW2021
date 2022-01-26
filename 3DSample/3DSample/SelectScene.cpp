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


typedef enum
{

	SELECT_BG = 0,
	SELECT_LOGO,
	
	SELECT_TITLE_1,
	SELECT_TITLE_2,
	SELECT_TITLE_3,
	
	SELECT_BLOCK_1,
	SELECT_BLOCK_2,
	SELECT_BLOCK_3,
	
	SELECT_ARROW,

	SELECT_MAX,
}Selct;


//========================= グローバル変数定義 ===========================
ID3D11ShaderResourceView* g_pSelectTex[SELECT_MAX];
Camera* g_pSelectCamera;
GameObject g_pSelectObject[SELECT_MAX];

const char* g_pTexFName[SELECT_MAX] = {
	"Assets/Texture/SceneTexture/Select_BG.png",
	"Assets/Texture/SceneTexture/Select_Logo.png",
	"Assets/Texture/SceneTexture/Stage_1.png",
	"Assets/Texture/SceneTexture/Stage_2.png",
	"Assets/Texture/SceneTexture/Stage_3.png",
	"Assets/Texture/SceneTexture/1box/1box_0.png",
	"Assets/Texture/SceneTexture/2box/2box_0.png",
	"Assets/Texture/SceneTexture/3box/3box_0.png",
	"Assets/Texture/SceneTexture/arrow_down.png",
};

float g_arrowPosX;
XMFLOAT3 g_pos;

//====================================================================
//
//		コンストラクタ
//
//====================================================================
SelectScene::SelectScene(void) {

}


//====================================================================
//
//		デストラクタ
//
//====================================================================
SelectScene::~SelectScene(void) {

}


//====================================================================
//
//		初期化
//
//====================================================================
void SelectScene::Init()
{
	for (int i = 0; i < SELECT_MAX; ++i)
	{
		LoadTextureFromFile(g_pTexFName[i], &g_pSelectTex[i]);
		g_pSelectObject[i].Init();
	}

	g_pSelectObject[SELECT_BG].SetSize(DirectX::XMFLOAT3(1.0f, 0.6f, 1));
	g_pSelectObject[SELECT_BG].SetPos (DirectX::XMFLOAT3(0, 0, 3));

	g_pSelectObject[SELECT_LOGO].SetSize(DirectX::XMFLOAT3(0.35f, 0.25f, 1));
	g_pSelectObject[SELECT_LOGO].SetPos (DirectX::XMFLOAT3(0.0f, 0.18f, 2));

	g_pSelectObject[SELECT_TITLE_1].SetSize(DirectX::XMFLOAT3( 0.15f, 0.1f, 1));
	g_pSelectObject[SELECT_TITLE_1].SetPos (DirectX::XMFLOAT3(-0.3f,  0.02f, 1));
	g_pSelectObject[SELECT_TITLE_2].SetSize(DirectX::XMFLOAT3( 0.15f, 0.1f, 1));
	g_pSelectObject[SELECT_TITLE_2].SetPos (DirectX::XMFLOAT3( 0.0f,  0.02f, 1));
	g_pSelectObject[SELECT_TITLE_3].SetSize(DirectX::XMFLOAT3( 0.15f, 0.1f, 1));
	g_pSelectObject[SELECT_TITLE_3].SetPos (DirectX::XMFLOAT3( 0.3f,  0.02f, 1));

	g_pSelectObject[SELECT_BLOCK_1].SetSize(DirectX::XMFLOAT3( 0.12f, 0.12f, 1));
	g_pSelectObject[SELECT_BLOCK_1].SetPos (DirectX::XMFLOAT3(-0.3f, -0.15f, 1));
	g_pSelectObject[SELECT_BLOCK_2].SetSize(DirectX::XMFLOAT3( 0.12f, 0.12f, 1));
	g_pSelectObject[SELECT_BLOCK_2].SetPos (DirectX::XMFLOAT3( 0.0f, -0.15f, 1));
	g_pSelectObject[SELECT_BLOCK_3].SetSize(DirectX::XMFLOAT3( 0.12f, 0.12f, 1));
	g_pSelectObject[SELECT_BLOCK_3].SetPos (DirectX::XMFLOAT3( 0.3f, -0.15f, 1));

	g_pSelectObject[SELECT_ARROW].SetPos (DirectX::XMFLOAT3(-0.3f, -0.02f, 1));
	g_pSelectObject[SELECT_ARROW].SetSize(DirectX::XMFLOAT3(0.05f, 0.05f, 1));

	g_pSelectCamera = new Camera;
	g_pSelectCamera->Init();


	g_arrowPosX = -0.3f;
	m_StageNum = 1;
	CSound::Play(SELECT_BGM);

}


//====================================================================
//
//		終了処理
//
//====================================================================
void SelectScene::Uninit()
{
	for (int i = 0; i < SELECT_MAX; ++i)
	{
		SAFE_RELEASE(g_pSelectTex[i]);
		g_pSelectObject[i].Uninit();
	}
	g_pSelectCamera->Uninit();

	delete g_pSelectCamera;

	CSound::Stop(SELECT_BGM);


}


//====================================================================
//
//		更新処理
//
//====================================================================
SCENE SelectScene::Update()
{


	if (IsTrigger(VK_RIGHT) || IsRelease(JPadButton::DPAD_RIGHT)) {
		CSound::Play(SE_SELECT_1);
		m_StageNum++;
		g_arrowPosX += 0.3f;
		if (m_StageNum > 3) {
			m_StageNum = 3;
			g_arrowPosX = 0.3f;
			//g_pSelectObject[SELECT_TITLE_1].SetCollor(XMFLOAT4(0.0f,0.0f,1.0f,1.0f));

		}
	}
	if (IsRelease(VK_LEFT) || IsRelease(JPadButton::DPAD_LEFT)) {
		CSound::Play(SE_SELECT_1);
		m_StageNum--;
		g_arrowPosX -= 0.3f;

		if (m_StageNum < 1) {
			m_StageNum = 0;
			g_arrowPosX = -0.3f;
		}
	}
	// 選択されたステージに矢印を移動
	g_pSelectObject[SELECT_ARROW].SetPos(DirectX::XMFLOAT3(g_arrowPosX, -0.05f, 1));

	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {
		CSound::Play(SE_ENTER_1);

		switch (m_StageNum) {
		case 1:
			return SCENE_GAME;
		case 2:
			return SCENE_GAME;
		case 3:
			return SCENE_GAME;
		default:
			break;
		}
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
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	g_pSelectCamera->Bind2D();

	for (int i = 0; i < SELECT_MAX; ++i)
	{
		SHADER->SetTexture(g_pSelectTex[i]);
		g_pSelectObject[i].Draw();
	}

	SHADER->SetTexture(NULL);

}


//====================================================================
//
//		シーン番号取得
//
//====================================================================
int SelectScene::GetStageNum() {
	return m_StageNum;
}