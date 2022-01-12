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

#define LOGO_POS_X						(0.0f)				// X座標
#define LOGO_POS_Y						(0.1f)				// Y座標
#define LOGO_POS_Z						(300.0f)				// Z座標

#define	LOGO_SIZE_X					(1.0f)				// 横
#define	LOGO_SIZE_Y					(0.1f)				// 縦
#define	LOGO_SIZE_Z					(0.1f)				// 奥行
//*******************************************************************************
// グローバル変数
//*******************************************************************************
static int g_nTimer;												// タイマー
ID3D11ShaderResourceView* g_pGameOverTex;		// テクスチャ
static DrawBuffer g_pBuffer;									// 頂点バッファ
GameObject* g_pGameOverObject;							// ゲームオブジェクト
Camera* g_pGameOverCamera;								// ゲームカメラ

//=========================================================
//	初期化
//=========================================================
void InitGameOver()
{
	//---タイマー初期化
	g_nTimer = CHANGE_STATE_CNT;

	//---テクスチャ読み込み
	LoadTextureFromFile("Assets/Texture/GameOver.png", &g_pGameOverTex);

	//---クラスメモリ確保
	g_pGameOverObject = new GameObject;
	g_pGameOverObject->Init();
	g_pGameOverObject->SetPos(XMFLOAT3(LOGO_POS_X, LOGO_POS_Y, LOGO_POS_Z));
	g_pGameOverObject->SetSize(XMFLOAT3(LOGO_SIZE_X, LOGO_SIZE_Y, LOGO_SIZE_Z));

	g_pGameOverCamera = new Camera;
	g_pGameOverCamera->Init();
}

//=========================================================
//	終了処理
//=========================================================
void UninitGameOver()
{
	//---テクスチャ解放
	SAFE_RELEASE(g_pGameOverTex);

	//---メモリ開放
	g_pGameOverCamera->Uninit();
	delete g_pGameOverCamera;

	g_pGameOverObject->Uninit();
	delete g_pGameOverObject;
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

	// 1ボタンでリトライ
	if (IsRelease('1')) {
		return STATE_RETRY;						
	}

	// 2ボタンでステージ選択
	if (IsRelease('2')) {
		return STATE_SELECT;
	}

}

//=========================================================
//	描画処理
//=========================================================
void DrawGameOver()
{

	SHADER->Bind(VS_WORLD, PS_PHONG);
	g_pGameOverCamera->Bind2D();

	SHADER->SetTexture(g_pGameOverTex);

	g_pGameOverObject->Draw();

	SHADER->SetTexture(NULL);
}