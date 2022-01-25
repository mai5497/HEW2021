#pragma once

//========================= �C���N���[�h�� ===========================
#include "GameObject.h"


//========================= �萔��` ===========================
enum COLOR {
	RED = 0,
	BLUE,
	REDBLUE,
	MAX_COLOR
};


//========================= �N���X��` ===========================
class CollectionPoint : public GameObject
{
public:
	//---�֐�
	CollectionPoint();
	~CollectionPoint();

	bool Init(int stagenum);
	void Uninit();
	void Update();
	void Draw();

	void SetNowCollectFlg(bool flg);
	void SetnowCollectTimer(int time);

	XMFLOAT3 GetTargetPos();
	int GetColorNum();

private:
	int m_PosSetTime;
	bool m_nowCollectFlg;
	int m_nowCollectTimer;
	bool m_TimerStart;
	XMFLOAT4 m_ColorVal[MAX_COLOR];
	int m_colorNum;
	int m_stageNum;
	int m_colorInfo[MAX_COLOR];
};

