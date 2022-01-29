#include "SceneManager.h"
#include "Main.h"
#include "DirectX.h"
#include "Texture.h"
#include "Input.h"
#include "Shader.h"
#include "Defines.h"
#include "FBX/FBXLoader.h"
#include "DrawBuffer.h"
#include "Sound.h"


using namespace DirectX;


//---グローバル変数
DrawBuffer g_buffer;
SceneManager* g_pSceneManager;



HRESULT ErrorBox(HRESULT hr, const char* message)
{
	MessageBox(NULL, message, "Error", MB_OK);
	return hr;
}

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	//fbxsdkの初期化
	ggfbx::Initialize();
	// DirectX
	hr = InitDX(hWnd, width, height, false);
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to DirectX."); }
	// キーボード
	//hr = InitKeyboard();
	//if (FAILED(hr)) { return ErrorBox(hr, "Failed to Keyboard."); }
	// シェーダ
	hr = SHADER->Init();
	if (FAILED(hr)) { return ErrorBox(hr, "Failed to Shader."); }

	CSound::Init();

	g_pSceneManager = new SceneManager();
	g_pSceneManager->Init();

	//---ゲームで使うオブジェクトの初期化
	//頂点の情報を持った構造体
	struct Vertex
	{
		float pos[3];		//x,y,z
		float color[4];		//r,g,b,a
		float uv[2];		//u,v
	};

	//頂点情報を定義
	//DirectXは左手座標系
	//左手座標系の回転方向は時計回り
	//親指を自分に向けて手を握ったとき
	//握り方向がそのまま回転の向きを表す

	//三角形を描画するための頂点の順序は
	//それぞれの座標系の回転方向に合わせる
	//→回転方向に合わせることで
	//  三角形の表面と裏面を判別できるから

	Vertex vtx[] = {
		//手前の面
		{ { -1, 1,-1 },{ 1,1,1,1 },{ 0,0 } },//左上
		{ {  1, 1,-1 },{ 1,1,1,1 },{ 1,0 } },//右上
		{ { -1,-1,-1 },{ 1,1,1,1 },{ 0,1 } },//左下

		{ {  1, 1,-1 },{ 1,1,1,1 },{ 1,0 } },//右上
		{ {  1,-1,-1 },{ 1,1,1,1 },{ 1,1 } },//右下
		{ { -1,-1,-1 },{ 1,1,1,1 },{ 0,1 } },//左下

		//右の面
		{ { 1, 1,-1 },{ 1,1,1,1 },{ 0,0 } },//左上
		{ { 1, 1, 1 },{ 1,1,1,1 },{ 1,0 } },//右上
		{ { 1,-1,-1 },{ 1,1,1,1 },{ 0,1 } },//左下
	
		{ { 1, 1, 1 },{ 1,1,1,1 },{ 1,0 } },//右上
		{ { 1,-1, 1 },{ 1,1,1,1 },{ 1,1 } },//右下
		{ { 1,-1,-1 },{ 1,1,1,1 },{ 0,1 } },//左下

		//奥の面
		{ {  1, 1,1 },{ 1,1,1,1 },{ 1,1 } },//左上
		{ { -1, 1,1 },{ 1,1,1,1 },{ 0,1 } },//右上
		{ {  1,-1,1 },{ 1,1,1,1 },{ 1,0 } },//左下

		{ { -1, 1,1 },{ 1,1,1,1 },{ 0,1 } },//右上
		{ { -1,-1,1 },{ 1,1,1,1 },{ 0,0 } },//右下
		{ {  1,-1,1 },{ 1,1,1,1 },{ 1,0 } },//左下

		//左の面
		{ { -1, 1, 1 },{ 1,1,1,1 },{ 0,0 } },//左上
		{ { -1, 1,-1 },{ 1,1,1,1 },{ 1,0 } },//右上
		{ { -1,-1, 1 },{ 1,1,1,1 },{ 0,1 } },//左下

		{ { -1, 1,-1 },{ 1,1,1,1 },{ 1,0 } },//右上
		{ { -1,-1,-1 },{ 1,1,1,1 },{ 1,1 } },//右下
		{ { -1,-1, 1 },{ 1,1,1,1 },{ 0,1 } },//左下

		//上の面
		{ { -1, 1, 1 },{ 1,1,1,1 },{ 0,0 } },//左上
		{ {  1, 1, 1 },{ 1,1,1,1 },{ 1,0 } },//右上
		{ { -1, 1,-1 },{ 1,1,1,1 },{ 0,1 } },//左下

		{ {  1, 1, 1 },{ 1,1,1,1 },{ 1,0 } },//右上
		{ {  1, 1,-1 },{ 1,1,1,1 },{ 1,1 } },//右下
		{ { -1, 1,-1 },{ 1,1,1,1 },{ 0,1 } },//左下

	};
	//頂点バッファの作成
	g_buffer.CreateVertexBuffer(
		vtx, sizeof(Vertex),
		sizeof(vtx) / sizeof(Vertex)
	);

	
	return hr;
}

void Uninit()
{
	g_pSceneManager->Uninit();
	delete g_pSceneManager;
	CSound::Fin();
	SHADER->Uninit();
	UninitDX();
	ggfbx::Terminate();
}

void Update()
{
	CSound::Update();
	g_pSceneManager->Update();
}

void Draw()
{
	BeginDrawDX();
	
	//最終的に画面に描画されるまでに
	//GPUで
	//①頂点が実際に画面に描画される位置の計算
	//②描画される画面の色の計算
	//が行われる
	//この処理をシェーダーと呼ぶ(①は頂点シェーダ、
	//②はピクセルシェーダ
	//頂点バッファをGPUに渡すだけでは画面に描画されず
	//どの計算で画面に表示するのか
	//(シェーダ)を設定する必要がある。

	//シェーダの処理はここで行ってね↓
	g_pSceneManager->Draw();
	

	EndDrawDX();
}

// EOF