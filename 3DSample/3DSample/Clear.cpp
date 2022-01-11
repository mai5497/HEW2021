//============== インクルード部 ======================
#include "clear.h"
#include "GameObject.h"
#include "Texture.h"
#include "Input.h"
#include "Camera.h"
#include "Defines.h"



//============== 定数定義 ======================
#define CLEAR_CNT			(600)

//============== グローバル変数定義 ======================
static int g_nTimer;					// タイマー
ID3D11ShaderResourceView* g_pClearTex;	// テクスチャ
static DrawBuffer g_pBuffer;			// 頂点バッファ
GameObject* g_pClearObject;				// ゲームオブジェクト
Camera* g_pClearCamera;


//=========================================================
//
//	初期化
//
//=========================================================
void InitClear() {
	// タイマー初期化
	g_nTimer = CLEAR_CNT;

	LoadTextureFromFile("Assets/Texture/Clear.png", &g_pClearTex);
	g_pClearObject = new GameObject;
	g_pClearObject->Init();
	g_pClearObject->SetPos(DirectX::XMFLOAT3(0, 0, 300));
	g_pClearObject->SetSize(DirectX::XMFLOAT3(1, (float)SCREEN_HEIGHT / SCREEN_WIDTH, 1));
	g_pClearCamera = new Camera;
	g_pClearCamera->Init();
	//g_pClearObject->SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));	// 半透明
}

//===========================================================
//
//	終了処理
//
//===========================================================
void UninitClear() {
	SAFE_RELEASE(g_pClearTex);
	g_pClearCamera->Uninit();
	delete g_pClearCamera;
	g_pClearObject->Uninit();
	delete g_pClearObject;
}

//===========================================================
//
//	更新
//	戻り値：次のステージに行くのか選択のシーンに戻るかを数字で返す
//
//===========================================================
int	UpdateClear() {
	// タイマーカウントダウン
	g_nTimer--;
	if (g_nTimer < 0) {
		return GO_SELECT;	// 一定時間たったらステージ選択へ戻る
	}

	// とりあえず１で次のステージ
	if (IsTrigger('1')) {
		return NEXTSTAGE;
	}
	// ２でステージ選択
	if (IsTrigger('2')) {
		return GO_SELECT;
	}
	//g_pClearObject->Update();
}

//===================
//
//	描画
//
//===================
void DrawClear() {
	SHADER->Bind(VS_WORLD, PS_PHONG);

	g_pClearCamera->Bind2D();

	SHADER->SetTexture(g_pClearTex);

	g_pClearObject->Draw();

	SHADER->SetTexture(NULL);
}

