#ifndef __PIKMINMANAGER_H__
#define __PIKMINMANAGER_H__

//========================= インクルード部 ===========================
#include "PikminBase.h"

//========================= クラス定義 ===========================
class PikminManager 
{
public:
	//---関数
	PikminManager();
	~PikminManager();
	bool Init();
	void Uninit();
	void Update();
	void Draw();

	PikminBase *GetPikmin(int index);
	int			GetPikminNum();
	void		SetPikminTarget(XMFLOAT3 pos);


	//---変数

private:
	//---関数

	//---変数
	PikminBase **m_ppPikmin;
	int			 m_pikminNum;
};

#endif