#define _CRTDBG_MAP_ALLOC
#include <windows.h>
#include "Defines.h"
#include "Main.h"
#include "Input.h"
#include <stdio.h>
//メモリリーク検出のヘッダファイル
#include <crtdbg.h>

int g_nMouseWheelDelta;

// timeGetTime周りの使用
#pragma comment(lib, "winmm.lib")

//--- プロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


// エントリポイント
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//プログラム終了時にメモリリークの有無を確認
	_CrtSetDbgFlag(
		_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);

	
	   //--- 変数宣言
	   // ウィンドウクラス情報を
	   // 設定する構造体
	WNDCLASSEX wcex;
	// 作成したウィンドウのハンドル
	HWND hWnd;
	MSG message;

	// ---ウィンドクラス情報の設定
	ZeroMemory(&wcex, sizeof(wcex));
	// ウィンドウと紐づけ
	wcex.hInstance = hInstance;
	// ウィンドウクラス情報を識別する名前
	wcex.lpszClassName = "Class Name";
	// ウィンドウプロシージャの指定
	wcex.lpfnWndProc = WndProc;
	// ウィンドウのスタイル(特徴)を指定
	wcex.style = CS_CLASSDC;
	// 構造体のサイズを指定
	wcex.cbSize = sizeof(WNDCLASSEX);
	// タスクバーに表示するアイコンを指定
	wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	// 16x16サイズのアイコン
	wcex.hIconSm = wcex.hIcon;
	// カーソル
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	// 背景の指定
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	// ウィンドウクラス情報の登録
	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, "Failed to RegisterClassEx", "Error", MB_OK);
		return 0;
	}

	// ---ウィンドウの作成
	hWnd = CreateWindowEx(
		// 追加でウィンドウの
		// スタイル(特徴)を指定
		WS_EX_OVERLAPPEDWINDOW,
		// ウィンドウを作成するための
		// ウィンドウクラスを指定
		wcex.lpszClassName,
		// キャプション部分(上)に
		// 表示する名前
		"タイトル",
		// 基本のウィンドウスタイル
		WS_CAPTION | WS_SYSMENU,
		// ウィンドウの表示位置X
		CW_USEDEFAULT,
		// ウィンドウの表示位置Y
		CW_USEDEFAULT,
		// ウィンドウの横幅
		SCREEN_WIDTH,
		// ウィンドウの縦幅
		SCREEN_HEIGHT,
		// 親のウィンドウの指定
		HWND_DESKTOP,
		// メニューの指定
		NULL,
		// ウィンドウを紐づける
		// アプリケーション
		hInstance,
		// 不要
		NULL
	);

	// ---ウィンドウの表示
	ShowWindow(
		// 表示するウィンドウ
		hWnd,
		// 表示方法
		nCmdShow
	);
	// ウィンドウの中身をリフレッシュ
	UpdateWindow(hWnd);

	// 初期化処理
	Init(hWnd, SCREEN_WIDTH, SCREEN_HEIGHT);
	// 時間計測の精度を指定
	timeBeginPeriod(1); // 1ミリ秒間隔

						//--- FPS制御の初期化
	int fpsCount = 0; // 一秒間の処理回数
					  // 計測の開始時間
	DWORD countStartTime = timeGetTime();
	// 前回の実行時間
	DWORD preExecTime = countStartTime;
	DWORD frameCount = 0;

	//--- ウィンドウの管理
	while (1)
	{
		// OSで発生したメッセージを
		// このプログラムのキューに受け取る
		if (PeekMessage(
			&message, NULL, 0, 0,
			PM_NOREMOVE))
		{
			// キューに溜まったメッセージを
			// 取り出してくる
			if (!GetMessage(&message,
				NULL, 0, 0))
			{
				break;
			}
			else
			{
				// 受け取ったメッセージを
				// ウィンドウプロシージャに送信
				TranslateMessage(&message);
				DispatchMessage(&message);
			}
		}
		else
		{
			// FPSの制御
			DWORD nowTime = timeGetTime(); // 現在時刻
										   // 1秒(1000ミリ秒)経過したか判定
			if (nowTime - countStartTime >= 1000)
			{
				// タイトル部分にFPSを表示
				char fpsText[20];
				sprintf(fpsText, "FPS:%d", fpsCount);
				SetWindowText(hWnd, fpsText);
				// 次の１秒間の計測準備
				countStartTime = nowTime;
				fpsCount = 0;
			}

			// ゲームの処理
			// 60FPS(16ミリ秒)経過するまでは処理をしない
			if (nowTime - preExecTime >= 1000 / 60)
			{
				UpdateInput(hWnd, g_nMouseWheelDelta);
				g_nMouseWheelDelta = 0;
				Update();
				Draw();
				//fpsCount++; // ゲームの処理が一回行われた
				preExecTime = nowTime;
			}
		}
	}


	//--- 終了時
	timeEndPeriod(1); // 時間計測の精度を戻す
	Uninit();
	// ウィンドウクラス情報の登録解除
	UnregisterClass(
		wcex.lpszClassName,
		hInstance
	);

	return 0;
}

// ウィンドウプロシージャ
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// 受け取ったメッセージごとに処理
	switch (message)
	{
	case WM_MOUSEWHEEL:
		g_nMouseWheelDelta += GET_WHEEL_DELTA_WPARAM(wParam) / WHEEL_DELTA;
		break;
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			ShowCursor(TRUE);
			int res = MessageBox(NULL, TEXT("終了しますか？"),
				TEXT(""), MB_OKCANCEL | MB_ICONQUESTION);
			if (res != IDCANCEL) {
				PostQuitMessage(0);
			}
		}
		break;
		// ウィンドウを閉じた
	case WM_DESTROY:
		// WM_QUITメッセージの発行
		// プログラムを完全終了させる命令
		PostQuitMessage(0);
		break;
	}

	// ほかのメッセージは
	// 基本の処理を行わせる
	return DefWindowProc(hWnd, message, wParam, lParam);
}