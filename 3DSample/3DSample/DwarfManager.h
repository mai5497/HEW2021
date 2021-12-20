#ifndef __DWARFMANAGER_H__
#define __DWARFMANAGER_H__

//========================= インクルード部 ===========================
#include "DwarfBase.h"

//========================= クラス定義 ===========================
class DwarfManager 
{
public:
	//---関数
	DwarfManager();
	~DwarfManager();
	bool Init();
	void Uninit();
	void Update();
	void Draw();

	DwarfBase *GetDwarf(int index);
	int			GetDwarfNum();
	void		SetDwarfTarget(XMFLOAT3 pos);


	//---変数

private:
	//---関数

	//---変数
	DwarfBase **m_ppDwarf;
	int			 m_DwarfNum;
};

#endif