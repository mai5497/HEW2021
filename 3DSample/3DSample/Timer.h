#pragma once

//========================= インクルード部 ===========================
#include "Texture.h"

//========================= クラス定義 ===========================
class Timer
{
	//---関数
public:
	Timer();
	~Timer();

	void Init();
	void Uninit();
	bool Update();
	void Draw();

	void SetColor(int nColor);

	//---変数
private:
	int m_nCount;

};