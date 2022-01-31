//****************************************************
//
//	チュートリアル
//	作成者：園田翔太
//  UFOの到着、待機時間を描画
// 
//	01/25 : フレームを追加して描画
//	01/26 : 機能追加
//  01/27 : コメント追記
//  01/29 : 定数化
// 
//****************************************************

//========================= インクルード部 ===========================
#include "Timer.h"
#include "GameObject.h"
#include "Camera.h"
#include "DirectX.h"
#include <DirectXMath.h>
#include <d3dcompiler.h>

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define MAX_TEX_TIMER	(10)

// 現在のタイマー挙動
// 回収地点に到着時０になり、すぐに次の回収地点へ到着するまでの時間をセット
// その為、回収地点での待機時間( ADD_TIME )を追加している。

#define WAIT_TIME		(720)		// 基本待機時間
#define ADD_TIME		(180)		// 2回目以降の追加待機時間


typedef enum
{
	RED = 0,
	BLUE,
	PURPLE,

	MAX_COLOR

}COLOR;

//*******************************************************************************
// グローバル宣言
//*******************************************************************************
GameObject*		g_pTimerObj[4];
GameObject*		g_pTimerFlame;
Camera*			g_pTimerCamera;
ID3D11ShaderResourceView*	g_pTimerTex[MAX_TEX_TIMER];
ID3D11ShaderResourceView*	g_pTimerFlameTex[MAX_COLOR];

const unsigned char VTX_NUM = 4; // 頂点数

int g_nColor;

Timer::Timer()
{
	m_nCount = WAIT_TIME;
}
Timer::~Timer()
{

}

//====================================================================
//
//		初期化
//
//====================================================================
void Timer::Init()
{
	LoadTextureFromFile("Assets/Texture/UI/Number/0.png", &g_pTimerTex[0]);
	LoadTextureFromFile("Assets/Texture/UI/Number/1.png", &g_pTimerTex[1]);
	LoadTextureFromFile("Assets/Texture/UI/Number/2.png", &g_pTimerTex[2]);
	LoadTextureFromFile("Assets/Texture/UI/Number/3.png", &g_pTimerTex[3]);
	LoadTextureFromFile("Assets/Texture/UI/Number/4.png", &g_pTimerTex[4]);
	LoadTextureFromFile("Assets/Texture/UI/Number/5.png", &g_pTimerTex[5]);
	LoadTextureFromFile("Assets/Texture/UI/Number/6.png", &g_pTimerTex[6]);
	LoadTextureFromFile("Assets/Texture/UI/Number/7.png", &g_pTimerTex[7]);
	LoadTextureFromFile("Assets/Texture/UI/Number/8.png", &g_pTimerTex[8]);
	LoadTextureFromFile("Assets/Texture/UI/Number/9.png", &g_pTimerTex[9]);
	LoadTextureFromFile("Assets/Texture/UI/time_ufo1.png", &g_pTimerFlameTex[0]);
	LoadTextureFromFile("Assets/Texture/UI/time_ufo2.png", &g_pTimerFlameTex[1]);
	LoadTextureFromFile("Assets/Texture/UI/time_ufo3.png", &g_pTimerFlameTex[2]);

	// 秒
	g_pTimerObj[0] = new GameObject;
	g_pTimerObj[0]->Init();
	g_pTimerObj[0]->SetPos(DirectX::XMFLOAT3(0.385f, 0.19f, 4));
	g_pTimerObj[0]->SetSize(DirectX::XMFLOAT3(0.04f, 0.04f, 0.0f));
	g_pTimerObj[1] = new GameObject;
	g_pTimerObj[1]->Init();
	g_pTimerObj[1]->SetPos(DirectX::XMFLOAT3(0.36f, 0.19f, 5));
	g_pTimerObj[1]->SetSize(DirectX::XMFLOAT3(0.04f, 0.04f, 0.0f));
	
	// 分
	g_pTimerObj[2] = new GameObject;
	g_pTimerObj[2]->Init();
	g_pTimerObj[2]->SetPos(DirectX::XMFLOAT3(0.32f, 0.19f, 5));
	g_pTimerObj[2]->SetSize(DirectX::XMFLOAT3(0.04f, 0.04f, 0.0f));
	g_pTimerObj[3] = new GameObject;
	g_pTimerObj[3]->Init();
	g_pTimerObj[3]->SetPos(DirectX::XMFLOAT3(0.295f, 0.19f, 4));
	g_pTimerObj[3]->SetSize(DirectX::XMFLOAT3(0.04f, 0.04f, 0.0f));

	// フレーム
	g_pTimerFlame = new GameObject;
	g_pTimerFlame->Init();
	g_pTimerFlame->SetPos(DirectX::XMFLOAT3(0.34f, 0.2f, 6));
	g_pTimerFlame->SetSize(DirectX::XMFLOAT3(0.15f, 0.15f, 0.0f));

	g_nColor = 1;
}


//====================================================================
//
//		終了処理
//
//====================================================================
void Timer::Uninit()
{
	for (int i = 0; i < MAX_TEX_TIMER; i++)
	{
		SAFE_RELEASE(g_pTimerTex[i]);
	}
	for (int i = 0; i < MAX_COLOR; i++)
	{
		SAFE_RELEASE(g_pTimerFlameTex[i]);
	}
	for (int i = 0; i < 4; i++)
	{
		g_pTimerObj[i]->Uninit();
		delete g_pTimerObj[i];
	}
	
	g_pTimerFlame->Uninit();
	delete g_pTimerFlame;

}


//====================================================================
//
//		更新
//
//====================================================================
bool Timer::Update()
{
	if (m_nCount > 60)
	{
		m_nCount--;
	}
	else
	{
		m_nCount = WAIT_TIME + ADD_TIME;
		return true;
	}

	return false;
}


//====================================================================
//
//		描画
//
//====================================================================
void Timer::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	
	int number = m_nCount / 60;
	int i = 60;
	int j = 60;

	g_pTimerCamera->Bind2D();

	// フレーム
	switch (g_nColor)
	{
	case 1:
		SHADER->SetTexture(g_pTimerFlameTex[RED]);
		break;
	case 2:
		SHADER->SetTexture(g_pTimerFlameTex[BLUE]);
		break;
	case 3:
		SHADER->SetTexture(g_pTimerFlameTex[PURPLE]);
		break;
	default:
		break;
	}
	g_pTimerFlame->Draw();
	
	// 分
	SHADER->SetTexture(g_pTimerTex[0]);
	g_pTimerObj[2]->Draw();
	g_pTimerObj[3]->Draw();

	// 秒
	for (int b = 6; b >= 0; )
	{
		if (j < number)
		{
			SHADER->SetTexture(g_pTimerTex[b]);
			g_pTimerObj[1]->Draw();
		}
		j -= 10;
		b--;
	}
	for (int c = 0; c < 6; c++)
	{
		for (int a = 9; a >= 0;)
		{			
			i -= 1;
			if (i < number)
			{
				SHADER->SetTexture(g_pTimerTex[a]);
				g_pTimerObj[0]->Draw();
			}
			a--;
		}
  
	}
	
	SHADER->SetTexture(NULL);
}

//====================================================================
//
//		フレームカラー設定
//
//====================================================================
void Timer::SetColor(int nColor)
{
	g_nColor = nColor;
}
