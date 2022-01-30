//====================================================================
//
// ゲームオーバー[Pause.cpp]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/30	作成
//====================================================================

//*******************************************************************************
// インクルード部
//*******************************************************************************
#include	"Pause.h"
#include	"GameObject.h"
#include	"Texture.h"
#include	"Input.h"
#include	"Camera.h"
#include	"Defines.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
typedef enum {							// 描画するオブジェクト
	PASUE_BG = 0,
	PAUSE_TITLE,
	PAUSE_CONTINUE,
	PAUSE_RETRAY,
	PAUSE_SELECT,
	PAUSE_END,

	PAUSE_MAX
}PauseObject;

#define MAX_PAUSE_TEX	(PAUSE_MAX)		// 使用するテクスチャの数
#define SELECT_SIZE		(1.3f)			// 1.3倍にする(選ばれているとき)
//*******************************************************************************
// グローバル変数
//*******************************************************************************
const char* g_TexPath[MAX_PAUSE_TEX] = {		// テクスチャパス
	"Assets/Texture/Pause/Translucent.png",		// 半透明
	"Assets/Texture/Pause/Pause.png",			// ポーズタイトル
	"Assets/Texture/Pause/Continue.png",		// ゲームを続ける
	"Assets/Texture/Pause/Retry.png",			// リトライ
	"Assets/Texture/Pause/Select.png",			// セレクト
	"Assets/Texture/Pause/End.png",				// ゲーム終了

};

ID3D11ShaderResourceView* g_pPauseTex[MAX_PAUSE_TEX];	// テクスチャ
Camera* g_pPauseCamra;									// カメラインスタンス
GameObject g_PauseObject[PAUSE_MAX];					// オブジェクトインスタンス


//==============================================================
//
//	Pause::コンストラクタ
// 
//==============================================================
Pause::Pause()
{

}

//==============================================================
//
//	Pause::デストラクタ
// 
//==============================================================
Pause::~Pause()
{

}


//==============================================================
//
//	Pause::初期化
// 
//==============================================================
void Pause::Init()
{
	//---オブジェクト・テクスチャ読み込み
	for (int i = 0; i < MAX_PAUSE_TEX; i++) {
		LoadTextureFromFile(g_TexPath[i], &g_pPauseTex[i]);
		g_PauseObject[i].Init();
	}

	//---半透明背景
	g_PauseObject[PASUE_BG].SetPos(XMFLOAT3(0.0f, 0.0f, 12.0f));
	g_PauseObject[PASUE_BG].SetSize(XMFLOAT3(SCREEN_WIDTH, SCREEN_HEIGHT, 0));
	g_PauseObject[PASUE_BG].SetCollor(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.5f));

	//---ポーズ
	g_PauseObject[PAUSE_TITLE].SetPos(XMFLOAT3(0.0f, 0.23f,11.0f));
	g_PauseObject[PAUSE_TITLE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
 
	//---ゲームを続ける
	g_PauseObject[PAUSE_CONTINUE].SetPos(XMFLOAT3(0.0f, 0.1f,10.0f));
	g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	//---リトライ
	g_PauseObject[PAUSE_RETRAY].SetPos(XMFLOAT3(0.0f, 0.0f, 9.0f));
	g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	//---ステージセレクト
	g_PauseObject[PAUSE_SELECT].SetPos(XMFLOAT3(0.0f, -0.1f, 8.0f));
	g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	//---ゲーム終了
	g_PauseObject[PAUSE_END].SetPos(XMFLOAT3(0.0f, -0.2f, 7.0f));
	g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	//---カメラインスタンス
	g_pPauseCamra = new Camera;
	g_pPauseCamra->Init();

	m_SelectState = 1;
}

//=========================================================
//	終了
//=========================================================
void Pause::Uninit()
{
	//---オブジェクト・テクスチャ解放
	for (int i = 0; i < MAX_PAUSE_TEX; i++){
		SAFE_RELEASE(g_pPauseTex[i]);
		g_PauseObject[i].Uninit();
	}

	//---カメラ解放
	g_pPauseCamra->Uninit();
	delete  g_pPauseCamra;
}


//=========================================================
//	更新
//=========================================================
int Pause::Update()
{
	//---色の変更
	g_PauseObject->Update();

	//---カーソル移動

	if (IsRelease(VK_DOWN) || IsRelease(JPadButton::DPAD_DOWN)) {		// 下移動
		CSound::Play(SE_SELECT_1);

		m_SelectState++;

		if (m_SelectState > 4) {
			m_SelectState = 4;
		}
	}

	if (IsRelease(VK_UP) || IsRelease(JPadButton::DPAD_UP)) {			// 上移動
		CSound::Play(SE_SELECT_1);
		m_SelectState--;
		if (m_SelectState < 1) {
			m_SelectState = 1;
		}
	}

	if (IsRelease(VK_RETURN) || IsRelease(JPadButton::A)) {				// 決定きー
		CSound::Play(SE_ENTER_1);
		
		// 選ばれた値を返す
		return m_SelectState;
	
	}

	// 選択されているときにテクスチャのサイズを1.3倍にする
	switch (m_SelectState)
	{
	case 1:
		g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f * SELECT_SIZE, 0.3 * SELECT_SIZE, 0.0f));

		g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f, 0.3 , 0.0f));

		break;

	case 2:
		g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f * SELECT_SIZE, 0.3 * SELECT_SIZE, 0.0f));

		g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

		break;

	case 3:
		g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f * SELECT_SIZE, 0.3 * SELECT_SIZE, 0.0f));

		g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

		break;

	case 4:
		g_PauseObject[PAUSE_END].SetSize(XMFLOAT3(0.45f * SELECT_SIZE, 0.3 * SELECT_SIZE, 0.0f));

		g_PauseObject[PAUSE_CONTINUE].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_RETRAY].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));
		g_PauseObject[PAUSE_SELECT].SetSize(XMFLOAT3(0.45f, 0.3, 0.0f));

	default:
		break;
	}

}
//=========================================================
//	描画
//=========================================================
void Pause::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	g_pPauseCamra->Bind2D();

	for (int i = 0; i < MAX_PAUSE_TEX; i++){
		SHADER->SetTexture(g_pPauseTex[i]);
		g_PauseObject[i].Draw();
	}

	SHADER->SetTexture(NULL);
}
