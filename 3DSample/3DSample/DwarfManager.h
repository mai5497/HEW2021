#ifndef __DWARFMANAGER_H__
#define __DWARFMANAGER_H__

//========================= インクルード部 ===========================
#include "DwarfBase.h"
#include "BulletManager.h"


class BulletManager;

//========================= クラス定義 ===========================
class DwarfManager 
{
public:
	//---関数
	DwarfManager();
	~DwarfManager();
	bool Init(int stagenum);
	void Uninit();
	void Update();
	void Draw();

	DwarfBase *GetDwarf(int index);
	int			GetDwarfNum();
	void		SetAllDwarfTarget(XMFLOAT3 pos);
	void SetBulletInfo(BulletManager *pBullet);
	void AddCollectionSum();
	void SubCollectionSum();
	int GetCollectionSum();
	//---変数

private:
	//---関数

	//---変数
	DwarfBase **m_ppDwarf;
	int m_DwarfNum;
	BulletManager *m_pBullet;
	 int m_collectionSum;
};

#endif