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
	SELECT_ROGO,
	
	SELECT_TITLE_1,
	SELECT_TITLE_2,
	SELECT_TITLE_3,
	
	SELECT_BLOCK_0,
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
	"Assets/Texture/StageSelect_BG.png",
	"Assets/Texture/StageSelect.png",
	"Assets/Texture/Stage_1.png",
	"Assets/Texture/Stage_2.png",
	"Assets/Texture/Stage_3.png",
	"Assets/Texture/SelectObj_Block0.png",
	"Assets/Texture/SelectObj_Block1.png",
	"Assets/Texture/SelectObj_Block2.png",
	"Assets/Texture/SelectObj_Block3.png",
	"Assets/Texture/arrow_down.png",
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

	g_pSelectObject[SELECT_BG].SetSize(DirectX::XMFLOAT3(1.0f, 0.6f, 0.1f));
	g_pSelectObject[SELECT_BG].SetPos (DirectX::XMFLOAT3(0, 0, 1));

	g_pSelectObject[SELECT_ROGO].SetSize(DirectX::XMFLOAT3(0.35f, 0.15f, 1));
	g_pSelectObject[SELECT_ROGO].SetPos (DirectX::XMFLOAT3(0.0f, 0.18f, 1));

	g_pSelectObject[SELECT_TITLE_1].SetSize(DirectX::XMFLOAT3( 0.15f, 0.1f, 1));
	g_pSelectObject[SELECT_TITLE_1].SetPos (DirectX::XMFLOAT3(-0.3f,  0.02f, 1));
	g_pSelectObject[SELECT_TITLE_2].SetSize(DirectX::XMFLOAT3( 0.15f, 0.1f, 1));
	g_pSelectObject[SELECT_TITLE_2].SetPos (DirectX::XMFLOAT3( 0.0f,  0.02f, 1));
	g_pSelectObject[SELECT_TITLE_3].SetSize(DirectX::XMFLOAT3( 0.15f, 0.1f, 1));
	g_pSelectObject[SELECT_TITLE_3].SetPos (DirectX::XMFLOAT3( 0.3f,  0.02f, 1));

	g_pSelectObject[SELECT_BLOCK_0].SetSize(DirectX::XMFLOAT3(0.15f,  0.2f, 1));
	g_pSelectObject[SELECT_BLOCK_0].SetPos (DirectX::XMFLOAT3(-0.42f, -0.18f, 1));

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


	g_arrowPosX = -4;
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

	if (IsTrigger('1')) {	// ステージ１
		m_StageNum = 1;
		g_arrowPosX = -0.3f;

	}
	if (IsTrigger('2')) {	// ステージ２
		m_StageNum = 2;
		g_arrowPosX = 0.0f;

	}
	if (IsTrigger('3')) {	// ステージ３
		m_StageNum = 3;
		g_arrowPosX = 0.3f;

	}
	// 選択されたステージに矢印を移動
	g_pSelectObject[SELECT_ARROW].SetPos(DirectX::XMFLOAT3(g_arrowPosX, -0.05f, 1));

	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::B)) {
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