//====================================================================
//
// ゲームオーバー[GameOver.cpp]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/10	作成
//====================================================================

//*******************************************************************************
// インクルード部
//*******************************************************************************
#include	"GameOver.h"
#include	"GameObject.h"
#include	"Texture.h"
#include	"Input.h"
#include	"Camera.h"
#include	"Defines.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define	CHANGE_STATE_CNT			(600)				// シーン切り替えまでのタイマー
#define	MAX_GAMEOVER_TEX			(5)					// テクスチャの数

#define LOGO_POS_X					(0.0f)				// X座標
#define LOGO_POS_Y					(0.1f)				// Y座標
#define LOGO_POS_Z					(300.0f)			// Z座標

#define	LOGO_SIZE_X					(1.0f)				// 横
#define	LOGO_SIZE_Y					(0.1f)				// 縦
#define	LOGO_SIZE_Z					(0.1f)				// 奥行

//*******************************************************************************
// グローバル変数
//*******************************************************************************

ID3D11ShaderResourceView*	g_pGameOverTex[MAX_GAMEOVER_TEX];		// テクスチャ
static DrawBuffer			g_pBuffer;								// 頂点バッファ

GameObject		g_pGameOverObject[MAX_GAMEOVER_TEX];				// ゲームオブジェクト
Camera*			g_pGameOverCamera;									// ゲームカメラ

//static int g_nTimer;				// タイマー

const char* g_pGameOverTexFName[MAX_GAMEOVER_TEX] = {		// テクスチャデータ
	"Assets/Texture/Scene/SeceneBG.png",
	"Assets/Texture/Scene/GameOver.png",
	"Assets/Texture/Scene/Retry.png",
	"Assets/Texture/Scene/StageSelect.png",
	"Assets/Texture/Scene/SelectObj_Block_Pencel.png",
};

float	g_GO_ArrowPosY;										// カーソル移動
int		g_GO_SelectState;									// シーンの値


//=========================================================
//	初期化
//=========================================================
void InitGameOver()
{
	//---タイマー初期化
	//g_nTimer = CHANGE_STATE_CNT;

	//---オブジェクト・テクスチャ読み込み
	for (int i = 0; i < MAX_GAMEOVER_TEX; i++){
		LoadTextureFromFile(g_pGameOverTexFName[i],&g_pGameOverTex[i]);
		g_pGameOverObject[i].Init();
	}

	//---半透明背景
	g_pGameOverObject[0].SetPos(XMFLOAT3(0.0f, 0.15f, 8));
	g_pGameOverObject[0].SetSize(XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 1));
	g_pGameOverObject[0].SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));

	//---ゲームオーバー
	g_pGameOverObject[1].SetPos(XMFLOAT3(0.0f, 0.15f, 4));
	g_pGameOverObject[1].SetSize(XMFLOAT3(0.45f, 0.3f, 1));

	//---リトライ
	g_pGameOverObject[2].SetPos(XMFLOAT3(0.0f, 0.0f, 3));
	g_pGameOverObject[2].SetSize(XMFLOAT3(0.4f, 0.3f, 1));

	//---ステージセレクト
	g_pGameOverObject[3].SetPos(XMFLOAT3(0.0f, -0.15f, 2));
	g_pGameOverObject[3].SetSize(XMFLOAT3(0.4f, 0.34f, 1));

	//---カーソル
	g_pGameOverObject[4].SetPos(XMFLOAT3(-0.35f, 0.0f, 1));
	g_pGameOverObject[4].SetSize(XMFLOAT3(0.2f, 0.1f, 1));


	//---クラスメモリ確保
	g_pGameOverCamera = new Camera;
	g_pGameOverCamera->Init();

	// カーソルの位置
	g_GO_ArrowPosY = 0.0f;

	//---シーンの値
	g_GO_SelectState = STATE_RETRY;
}

//=========================================================
//	終了処理
//=========================================================
void UninitGameOver()
{
	//---オブジェクト・テクスチャ解放
	for (int i = 0; i < MAX_GAMEOVER_TEX; i++){
		SAFE_RELEASE(g_pGameOverTex[i]);
		g_pGameOverObject[i].Uninit();

	}
	//---メモリ開放
	g_pGameOverCamera->Uninit();
	delete g_pGameOverCamera;

}

//=========================================================
//	更新処理
//=========================================================
int UpdateGameOver()
{
	//---タイマーカウントダウン
	//g_nTimer--;
	//if (g_nTimer < 0) {
	//	return STATE_SELECT;					// 一定時間後にステージ選択へ
	//}

	//---カーソル移動
	if (IsTrigger(VK_UP) || IsRelease(JPadButton::DPAD_UP)) {
		CSound::Play(SE_SELECT_1);

		g_GO_ArrowPosY += 0.15f;
		g_GO_SelectState = STATE_RETRY;

		if (g_GO_ArrowPosY > 0.0f) {
			g_GO_ArrowPosY = 0.0f;
			g_GO_SelectState = STATE_RETRY;
		}
	}

	if (IsTrigger(VK_DOWN) || IsRelease(JPadButton::DPAD_DOWN)) {
		CSound::Play(SE_SELECT_1);

		g_GO_ArrowPosY -= 0.15f;
		g_GO_SelectState = STATE_SELECT;

		if (g_GO_ArrowPosY < -0.15f) {
			g_GO_ArrowPosY = 0.0f;
			g_GO_SelectState = STATE_SELECT;
		}
	}

	//---カーソルのオブジェクト再表示
	g_pGameOverObject[4].SetPos(XMFLOAT3(-0.35f, g_GO_ArrowPosY, 0.9f));

	//---決定
	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {
		CSound::Play(SE_ENTER_1);
		return g_GO_SelectState;
	}


	//// 1ボタンでリトライ
	//if (IsRelease('1') || IsRelease(JPadButton::Y)) {
	//	return STATE_RETRY;						
	//}

	//// 2ボタンでステージ選択
	//if (IsRelease('2') || IsRelease(JPadButton::A)) {
	//	return STATE_SELECT;
	//}

	// 色の変更のためオブジェクトの更新処理を記述
	g_pGameOverObject->Update();
	return -1;
}

//=========================================================
//	描画処理
//=========================================================
void DrawGameOver()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	g_pGameOverCamera->Bind2D();

	for (int i = 0; i < MAX_GAMEOVER_TEX; i++){
		SHADER->SetTexture(g_pGameOverTex[i]);
		g_pGameOverObject[i].Draw();
	}
	SHADER->SetTexture(NULL);
}