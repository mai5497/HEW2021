//============== インクルード部 ======================
#include "clear.h"
#include "GameObject.h"
#include "Texture.h"
#include "Input.h"
#include "Camera.h"
#include "Defines.h"

//============== 定数定義 ======================
#define CLEAR_CNT			(600)
#define MAX_CLAER_SCENE_TEX	(4)			// テクスチャの数

//============== グローバル変数定義 ======================
static DrawBuffer			g_pBuffer;								// 頂点バッファ
ID3D11ShaderResourceView*	g_pClearTex[MAX_CLAER_SCENE_TEX];		// テクスチャ

Camera*			g_pClearCamera;									// カメラ
GameObject		g_pClearObject[MAX_CLAER_SCENE_TEX];			// ゲームオブジェクト
float			g_ArrowPosY;									// カーソル座標
//static int		g_nTimer;										// タイマー
static int		g_SelectState;									// シーンの値


const char* g_pClearTexFName[MAX_CLAER_SCENE_TEX] = {
	"Assets/Texture/Scene/GameClear.png",
	"Assets/Texture/Scene/NextStage.png",
	"Assets/Texture/Scene/StageSelect.png",
	"Assets/Texture/Scene/SelectObj_Block_Pencel.png",
};


//=========================================================
//
//	初期化
//
//=========================================================
void InitClear() {
	// タイマー初期化
	//g_nTimer = CLEAR_CNT;

	// オブジェクト・テクスチャ読み込み
	for (int i = 0; i < MAX_CLAER_SCENE_TEX; i++){
		LoadTextureFromFile(g_pClearTexFName[i], &g_pClearTex[i]);
		g_pClearObject[i].Init();
	}

	//---ゲームクリアテクスチャ
	g_pClearObject[0].SetPos(XMFLOAT3(0.0f, 0.15f, 4));			// 座標
	g_pClearObject[0].SetSize(XMFLOAT3(0.45f, 0.3f, 1));			// サイズ
	//g_pClearObject[0].SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.2f));	// 半透明

	//---次のステージ
	g_pClearObject[1].SetPos(XMFLOAT3(0.0f, 0.0f, 3));
	g_pClearObject[1].SetSize(XMFLOAT3(0.4f, 0.3f, 1));

	//---ステージセレクト
	g_pClearObject[2].SetPos(XMFLOAT3(0.0f, -0.15f, 2));
	g_pClearObject[2].SetSize(XMFLOAT3(0.4f, 0.34f, 1));

	//---カーソル
	g_pClearObject[3].SetPos(XMFLOAT3(-0.35f, 0.0f, 1));
	g_pClearObject[3].SetSize(XMFLOAT3(0.2f, 0.1f, 1));

	//g_pClearObject = new GameObject;
	//g_pClearObject->Init();
	//g_pClearObject->SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f));	// 半透明

	g_pClearCamera = new Camera;
	g_pClearCamera->Init();

	// カーソルの初期位置
	g_ArrowPosY = 0.0f;

	// シーンの値初期
	g_SelectState = STATE_NEXT;
}

//===========================================================
//
//	終了処理
//
//===========================================================
void UninitClear() {

	// オブジェクト・テクスチャ解放
	for (int i = 0; i < MAX_CLAER_SCENE_TEX; i++)
	{
		SAFE_RELEASE(g_pClearTex[i]);
		g_pClearObject[i].Uninit();

	}

	// カメラインスタンス解放
	g_pClearCamera->Uninit();
	delete g_pClearCamera;

}

//===========================================================
//
//	更新
//	戻り値：次のステージに行くのか選択のシーンに戻るかを数字で返す
//
//===========================================================
int	UpdateClear() 
{
	// タイマーカウントダウン
	//g_nTimer--;
	//if (g_nTimer < 0) {
	//	return STATE_SELECT;	// 一定時間たったらステージ選択へ戻る
	//}


	//---カーソル移動
	if (IsTrigger(VK_UP) || IsRelease(JPadButton::DPAD_UP)) {
		CSound::Play(SE_SELECT_1);

		g_ArrowPosY += 0.15f;

		g_SelectState = STATE_NEXT;
		if (g_ArrowPosY > 0.0f) {
			g_ArrowPosY = 0.0f;
			g_SelectState = STATE_NEXT;
		}
	}

	if (IsTrigger(VK_DOWN) || IsRelease(JPadButton::DPAD_DOWN)) {
		CSound::Play(SE_SELECT_1);

		g_ArrowPosY -= 0.15f;

		g_SelectState = STATE_SELECT;
		if (g_ArrowPosY < -0.15f) {
			g_ArrowPosY = 0.15f;
			g_SelectState = STATE_SELECT;
		}
	}

	//---カーソルのオブジェクト再表示
	g_pClearObject[3].SetPos(XMFLOAT3(-0.35f, g_ArrowPosY, 0.9f));

	//---決定
	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {
		CSound::Play(SE_ENTER_1);
		return g_SelectState;
	}
	// とりあえず１で次のステージ
	//if (IsRelease('1') || IsRelease(JPadButton::Y)) {
	//	return STATE_NEXT;
	//}
	// ２でステージ選択
	//if (IsRelease('2') || IsRelease(JPadButton::A)) {
	//	return STATE_SELECT;
	//}
	//g_pClearObject->Update();

	return -1;
}

//===================
//
//	描画
//
//===================
void DrawClear() {
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	g_pClearCamera->Bind2D();

	for (int i = 0; i < MAX_CLAER_SCENE_TEX; i++)
	{
		SHADER->SetTexture(g_pClearTex[i]);
		g_pClearObject[i].Draw();

	}

	SHADER->SetTexture(NULL);
}

