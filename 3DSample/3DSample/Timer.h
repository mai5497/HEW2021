#pragma once

//========================= �C���N���[�h�� ===========================
#include "Texture.h"

//========================= �N���X��` ===========================
class Timer
{
	//---�֐�
public:
	Timer();
	~Timer();

	void Init();
	void Uninit();
	bool Update();
	void Draw();
	
	//---�ϐ�
private:
	int m_nCount;

};