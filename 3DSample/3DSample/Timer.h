#pragma once

#include "Texture.h"

class Timer
{
public:

	Timer();
	~Timer();

	void Init();
	void Uninit();
	bool Update();
	void Draw();

private:
	int m_nCount;

};