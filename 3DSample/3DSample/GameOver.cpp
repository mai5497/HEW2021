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
#define	MAX_GAMEOVER_TEX			(4)					// テクスチャの数

#define LOGO_POS_X					(0.0f)				// X座標
#define LOGO_POS_Y					(0.1f)				// Y座標
#define LOGO_POS_Z					(300.0f)			// Z座標

#define	LOGO_SIZE_X					(1.0f)				// 横
#define	LOGO_SIZE_Y					(0.1f)				// 縦
#define	LOGO_SIZE_Z					(0.1f)				// 奥行

//*******************************************************************************
// グローバル変数
//*******************************************************************************
static int g_nTimer;										// タイマー

ID3D11ShaderResourceView* g_pGameOverTex[MAX_GAMEOVER_TEX];	// テクスチャ
static DrawBuffer g_pBuffer;								// 頂点バッファ

GameObject g_pGameOverObject[MAX_GAMEOVER_TEX];				// ゲームオブジェクト
Camera* g_pGameOverCamera;									// ゲームカメラ

const char* g_pGameOverTexFName[MAX_GAMEOVER_TEX] = {		// テクスチャデータ
	"Assets/Texture/SceneTexture/GameOver.png",
	"Assets/Texture/SceneTexture/Retry.png",
	"Assets/Texture/SceneTexture/StageSelect.png",
	"Assets/Texture/SceneTexture/SelectObj_Block_Pencel.png",
};

float	g_GO_ArrowPosY;										// カーソル移動
int		g_GO_SelectState;									// シーンの値


//=========================================================
//	初期化
//=========================================================
void InitGameOver()
{
	//---タイマー初期化
	g_nTimer = CHANGE_STATE_CNT;

	//---オブジェクト・テクスチャ読み込み
	for (int i = 0; i < MAX_GAMEOVER_TEX; i++){
		LoadTextureFromFile(g_pGameOverTexFName[i],&g_pGameOverTex[i]);
		g_pGameOverObject[i].Init();
	}

	//---ゲームオーバー
	g_pGameOverObject[0].SetPos(XMFLOAT3(0.0f, 0.2f, 1.0f));
	g_pGameOverObject[0].SetSize(XMFLOAT3(0.7f, 0.1f, 0.0f));

	//---リトライ
	g_pGameOverObject[1].SetPos(XMFLOAT3(0.0f, 0.0f, 1.0f));
	g_pGameOverObject[1].SetSize(XMFLOAT3(0.4f, 0.08f, 0.0f));

	//---ステージセレクト
	g_pGameOverObject[2].SetPos(XMFLOAT3(0.0f, -0.15f, 1.0f));
	g_pGameOverObject[2].SetSize(XMFLOAT3(0.4f, 0.1f, 0.0f));

	//---カーソル
	g_pGameOverObject[3].SetPos(XMFLOAT3(-0.35f, 0.0f, 0.9f));
	g_pGameOverObject[3].SetSize(XMFLOAT3(0.2f, 0.1f, 0.0f));


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
	g_nTimer--;
	if (g_nTimer < 0) {
		return STATE_SELECT;					// 一定時間後にステージ選択へ
	}

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
			g_GO_ArrowPosY = 0.15f;
			g_GO_SelectState = STATE_SELECT;
		}
	}

	//---カーソルのオブジェクト再表示
	g_pGameOverObject[3].SetPos(XMFLOAT3(-0.35f, g_GO_ArrowPosY, 0.9f));

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