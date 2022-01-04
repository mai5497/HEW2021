#ifndef __CLEAR_H__
#define __CLEAR_H__

//================== インクルード部 ==================
#include "Scene.h"

//================== 定数定義 ==================
enum SCENESTATE
{
	NEXTSTAGE = 0,
	GO_SELECT
};


//================== プロトタイプ宣言 ==================
void	InitClear();	// 初期化
void	UninitClear();	// 終了
int		UpdateClear();	// 更新
void	DrawClear();	// 描画



#endif