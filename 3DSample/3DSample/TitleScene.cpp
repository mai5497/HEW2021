

//*******************************************************************************
// インクルード部
//*******************************************************************************
#include "TitleScene.h"
#include "Input.h"
#include "Texture.h"
#include "DrawBuffer.h"
#include "GameObject.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "Defines.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
typedef enum
{
	TITLE_BG = 0,
	TITLE_LOGO,

	TITLE_START,
	TITLE_END,

	TITLE_BUTTON,

	TITLE_MAX,
}Title;

#define MAX_TITLE_TEX			(TITLE_MAX)			// 使用するテクスチャの数
#define TITLE_SELECT_SIZE	(1.3f)					// 選択中は1.3倍に

//*******************************************************************************
// グローバル変数
//*******************************************************************************
const char* g_pTitleTexFName[MAX_TITLE_TEX] = {
	"Assets/Texture/Scene/Select_BG.png",			// 背景
	"Assets/Texture/Scene/Title_Logo.png",			// タイトルロゴ
	"Assets/Texture/Title/GameStart.png",				// ゲームをはじめる
	"Assets/Texture/Title/GameEnd.png",				// げーむおわる
	"Assets/Texture/Scene/Press_A.png",				// Press A
};

ID3D11ShaderResourceView* g_pTitleTex[MAX_TITLE_TEX];
Camera* g_pTitleCamera;
GameObject	g_pTitleObject[TITLE_MAX];


TitleScene::TitleScene(void)
{

}

TitleScene::~TitleScene(void)
{

}

void TitleScene::Init()
{

	//---てくすちゃ・おぶじぇくと読み込み
	for (int i = 0; i < MAX_TITLE_TEX; i++) {
		LoadTextureFromFile(g_pTitleTexFName[i], &g_pTitleTex[i]);
		g_pTitleObject[i].Init();
	}

	//---背景
	g_pTitleObject[TITLE_BG].SetPos(XMFLOAT3(0.0f,0.0f,1.5f));
	g_pTitleObject[TITLE_BG].SetSize(XMFLOAT3(1.0f,0.6f,0.0f));
	
	//---たいとるろご
	g_pTitleObject[TITLE_LOGO].SetPos(XMFLOAT3(0.0f,0.1f,1.1f));
	g_pTitleObject[TITLE_LOGO].SetSize(XMFLOAT3(0.45f,0.3f,0.0f));

	//--げーむはじめる
	g_pTitleObject[TITLE_START].SetPos(XMFLOAT3(0.0f, -0.1f, 1.2f));
	g_pTitleObject[TITLE_START].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));

	//---げーむおわる
	g_pTitleObject[TITLE_END].SetPos(XMFLOAT3(0.0f, -0.2f, 1.13f));
	g_pTitleObject[TITLE_END].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));

	//---PressA
	g_pTitleObject[TITLE_BUTTON].SetPos(XMFLOAT3(0.0f,-0.5f,1.0f));
	g_pTitleObject[TITLE_BUTTON].SetSize(XMFLOAT3(0.5f,0.1f,0.0f));

	//---かめらいんすたんす
	g_pTitleCamera = new Camera;
	g_pTitleCamera->Init();

	//---変数初期化
	m_SelectState = SCENE_SELECT;

	// BGM再生
	CSound::Play(TITLE_BGM);
}

void TitleScene::Uninit()
{
	for (int i = 0; i < MAX_TITLE_TEX; i++) {
		SAFE_RELEASE(g_pTitleTex[i]);
		g_pTitleObject[i].Uninit();
	}
	g_pTitleCamera->Uninit();
	delete g_pTitleCamera;

	CSound::Stop(TITLE_BGM);
}

SCENE TitleScene::Update()
{
	//---カーソル移動
	if (IsRelease(VK_DOWN) || IsRelease(JPadButton::DPAD_DOWN)) {			// 下移動
		CSound::Play(SE_SELECT_1);
		m_SelectState += 3;

		if (m_SelectState > 5) {
			m_SelectState = SCENE_END;
		}
	}
	if (IsRelease(VK_UP) || IsRelease(JPadButton::DPAD_UP)) {					// 上移動
		CSound::Play(SE_SELECT_1);
		m_SelectState -= 3;

		if (m_SelectState < 2) {
			m_SelectState = SCENE_SELECT;
		}
	}

	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {					// 決定きー
		CSound::Play(SE_ENTER_1);

		if (m_SelectState == 2) {
			return SCENE_SELECT;
		}
		if(m_SelectState == 5) {
			PostQuitMessage(0);
		}
	}

	switch (m_SelectState)
	{
	case 2:
		g_pTitleObject[TITLE_START].SetSize(XMFLOAT3(0.45f * TITLE_SELECT_SIZE, 0.3f * TITLE_SELECT_SIZE, 0.0f));
		g_pTitleObject[TITLE_END].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));
		break;

	case 5:
		g_pTitleObject[TITLE_END].SetSize(XMFLOAT3(0.45f * TITLE_SELECT_SIZE, 0.3f * TITLE_SELECT_SIZE, 0.0f));
		g_pTitleObject[TITLE_START].SetSize(XMFLOAT3(0.45f, 0.3f, 0.0f));
		break;

	default:
		break;
	}
	//return SCENE_SELECT;

#ifdef _DEBUG
		if (IsRelease(JPadButton::L_SHOULDER) && IsRelease(JPadButton::R_SHOULDER)) {
			CSound::Play(SE_ENTER_1);
			return SCENE_GAME;
		}

#endif // _DEBUG

		return SCENE_TITLE;

}
void TitleScene::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	g_pTitleCamera->Bind2D();
	
	for (int i = 0; i < MAX_TITLE_TEX; i++) {
		SHADER->SetTexture(g_pTitleTex[i]);
		g_pTitleObject[i].Draw();
	}

	SHADER->SetTexture(NULL);
}	