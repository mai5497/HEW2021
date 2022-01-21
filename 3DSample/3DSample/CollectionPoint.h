#pragma once

//========================= �C���N���[�h�� ===========================
#include "GameObject.h"


//========================= �N���X��` ===========================
class CollectionPoint : public GameObject
{
public:
	//---�֐�
	CollectionPoint();
	~CollectionPoint();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

	void SetNowCollectFlg(bool flg);
	void SetnowCollectTimer(int time);

private:
	int m_PosSetTime;
	bool m_nowCollectFlg;
	int m_nowCollectTimer;
};

