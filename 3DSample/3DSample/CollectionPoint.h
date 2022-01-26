#pragma once

//========================= インクルード部 ===========================
#include "GameObject.h"


//========================= 定数定義 ===========================
enum COLOR {
	RED = 0,
	BLUE,
	REDBLUE,
	MAX_COLOR
};


//========================= クラス定義 ===========================
class CollectionPoint : public GameObject
{
public:
	//---関数
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

