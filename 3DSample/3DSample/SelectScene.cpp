//****************************************************
//
//	セレクトシーン
//	作成者：園田翔大
//	
//	2021/12/27 : 作成
//	2022/01/02 : コメント追加（伊地田）
//				 ステージ番号の変数を追加（伊地田）
//  2022/01/26 : 素材差し替え、各種数値調整
//  2022/01/27 : スコアに応じた星の獲得を追加
//				 コメント追記
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
#include "Timer.h"


//============== 定数定義 ======================
#define SELECT_MAX_TEX 14

typedef enum
{

	SELECT_BG = 0,
	SELECT_LOGO,
	
	SELECT_BLOCK_1,
	SELECT_BLOCK_2,
	SELECT_BLOCK_3,
	

	SELECT_MAX,
}Selct;


//========================= グローバル変数定義 ===========================
ID3D11ShaderResourceView*	g_pSelectTex[SELECT_MAX_TEX];
Camera*		g_pSelectCamera;
GameObject	g_pSelectObject[SELECT_MAX];


const char* g_pTexFName[SELECT_MAX_TEX] = {
	"Assets/Texture/Scene/Select_BG.png",
	"Assets/Texture/Scene/Select_Logo.png",
	"Assets/Texture/Scene/1box/1box_0.png",
	"Assets/Texture/Scene/1box/1box_1.png",
	"Assets/Texture/Scene/1box/1box_2.png",
	"Assets/Texture/Scene/1box/1box_3.png",
	"Assets/Texture/Scene/2box/2box_0.png",
	"Assets/Texture/Scene/2box/2box_1.png",
	"Assets/Texture/Scene/2box/2box_2.png",
	"Assets/Texture/Scene/2box/2box_3.png",
	"Assets/Texture/Scene/3box/3box_0.png",
	"Assets/Texture/Scene/3box/3box_1.png",
	"Assets/Texture/Scene/3box/3box_2.png",
	"Assets/Texture/Scene/3box/3box_3.png",

};

int		g_nScore[3] = { 0, 0, 0 };


//====================================================================
//
//		コンストラクタ
//
//====================================================================
SelectScene::SelectScene(void) {
	m_StageNum = 1;

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
	for (int i = 0; i < SELECT_MAX_TEX; ++i)
	{
		LoadTextureFromFile(g_pTexFName[i], &g_pSelectTex[i]);
	}

	g_pSelectObject[SELECT_BG].Init();
	g_pSelectObject[SELECT_BG].SetSize(DirectX::XMFLOAT3(1.0f, 0.6f, 1));
	g_pSelectObject[SELECT_BG].SetPos (DirectX::XMFLOAT3(0, 0, 3));

	g_pSelectObject[SELECT_LOGO].Init();
	g_pSelectObject[SELECT_LOGO].SetSize(DirectX::XMFLOAT3(0.5f, 0.4f, 1));
	g_pSelectObject[SELECT_LOGO].SetPos (DirectX::XMFLOAT3(0.0f, 0.18f, 2));

	g_pSelectObject[SELECT_BLOCK_1].Init();
	g_pSelectObject[SELECT_BLOCK_1].SetSize(DirectX::XMFLOAT3( 0.2f, 0.2f, 1));
	g_pSelectObject[SELECT_BLOCK_1].SetPos (DirectX::XMFLOAT3(-0.3f, -0.08f, 1));
	g_pSelectObject[SELECT_BLOCK_2].Init();
	g_pSelectObject[SELECT_BLOCK_2].SetSize(DirectX::XMFLOAT3( 0.2f, 0.2f, 1));
	g_pSelectObject[SELECT_BLOCK_2].SetPos (DirectX::XMFLOAT3( 0.0f, -0.05f, 1));
	g_pSelectObject[SELECT_BLOCK_3].Init();
	g_pSelectObject[SELECT_BLOCK_3].SetSize(DirectX::XMFLOAT3( 0.2f, 0.2f, 1));
	g_pSelectObject[SELECT_BLOCK_3].SetPos (DirectX::XMFLOAT3( 0.3f, -0.1f, 1));

	g_pSelectCamera = new Camera;
	g_pSelectCamera->Init();
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
	for (int i = 0; i < SELECT_MAX_TEX; ++i)
	{
		SAFE_RELEASE(g_pSelectTex[i]);
	}
	for (int i = 0; i < SELECT_MAX; ++i)
	{
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

		if (m_StageNum > 3) {
			m_StageNum = 3;
		}
	}
	if (IsRelease(VK_LEFT) || IsRelease(JPadButton::DPAD_LEFT)) {
		CSound::Play(SE_SELECT_1);
		m_StageNum--;
		if (m_StageNum < 1) {
			m_StageNum = 0;
		}
	}

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

	// ---力技のセレクト動かした(2021/01/28時点)
	switch (m_StageNum)
	{
	case 1:
		g_pSelectObject[SELECT_BLOCK_1].SetPos(XMFLOAT3(-0.3f, 0.0f, 1.0f));
		g_pSelectObject[SELECT_BLOCK_2].SetPos(DirectX::XMFLOAT3(0.0f, -0.05f, 1));
		g_pSelectObject[SELECT_BLOCK_3].SetPos(DirectX::XMFLOAT3(0.3f, -0.1f, 1));

		break;
	case 2:
		g_pSelectObject[SELECT_BLOCK_2].SetPos(DirectX::XMFLOAT3(0.0f, 0.00f, 1));
		g_pSelectObject[SELECT_BLOCK_1].SetPos(DirectX::XMFLOAT3(-0.3f, -0.08f, 1));
		g_pSelectObject[SELECT_BLOCK_3].SetPos(DirectX::XMFLOAT3(0.3f, -0.1f, 1));


		break;
	case 3:
		g_pSelectObject[SELECT_BLOCK_3].SetPos(DirectX::XMFLOAT3(0.3f, 0.0f, 1));
		g_pSelectObject[SELECT_BLOCK_1].SetPos(DirectX::XMFLOAT3(-0.3f, -0.08f, 1));
		g_pSelectObject[SELECT_BLOCK_2].SetPos(DirectX::XMFLOAT3(0.0f, -0.05f, 1));

		break;

	default: 
		break;
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

	// 背景とロゴ
	for (int i = 0; i < 2; ++i)
	{
		SHADER->SetTexture(g_pSelectTex[i]);
		g_pSelectObject[i].Draw();
	}

	// スコア入手で描画
	// ステージ１
	switch (g_nScore[0])
	{
		case 0:
			SHADER->SetTexture(g_pSelectTex[2]);
			break;
		case 1:
			SHADER->SetTexture(g_pSelectTex[3]);
			break;
		case 2:
			SHADER->SetTexture(g_pSelectTex[4]);
			break;
		case 3:
			SHADER->SetTexture(g_pSelectTex[5]);
			break;
		default:
			break;
	}
	g_pSelectObject[SELECT_BLOCK_1].Draw();

	// ステージ２
	switch (g_nScore[1])
	{
		case 0:
			SHADER->SetTexture(g_pSelectTex[6]);
			break;
		case 1:
			SHADER->SetTexture(g_pSelectTex[7]);
			break;
		case 2:
			SHADER->SetTexture(g_pSelectTex[8]);
			break;
		case 3:
			SHADER->SetTexture(g_pSelectTex[9]);
			break;
		default:
			break;
	}
	g_pSelectObject[SELECT_BLOCK_2].Draw();

	// ステージ３
	switch (g_nScore[2])
	{
		case 0:
			SHADER->SetTexture(g_pSelectTex[10]);
			break;
		case 1:
			SHADER->SetTexture(g_pSelectTex[11]);
			break;
		case 2:
			SHADER->SetTexture(g_pSelectTex[12]);
			break;
		case 3:
			SHADER->SetTexture(g_pSelectTex[13]);
			break;
		default:
			break;
	}
	g_pSelectObject[SELECT_BLOCK_3].Draw();

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

//====================================================================
//
//		スコア設定
//
//====================================================================
void SelectScene::SetScore(int stageNum, int score)
{
	int nScore = score;

	// 設定されたステージにスコア追加
	switch (stageNum)
	{
	case 1:
		g_nScore[0] = nScore;
		break;
	case 2:
		g_nScore[1] = nScore;
		break;
	case 3:
		g_nScore[2] = nScore;
		break;
	default:
		break;
	}
}

