#ifndef __DWARFMANAGER_H__
#define __DWARFMANAGER_H__

//========================= �C���N���[�h�� ===========================
#include "DwarfBase.h"
#include "BulletManager.h"


class BulletManager;

//========================= �N���X��` ===========================
class DwarfManager 
{
public:
	//---�֐�
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
	void SubRedSum();
	void SubBlueSum();
	int GetRedSum();
	int GetBlueSum();

	//---�ϐ�

private:
	//---�֐�

	//---�ϐ�
	DwarfBase **m_ppDwarf;
	int m_DwarfNum;
	BulletManager *m_pBullet;
	int m_collectionSum;
	int m_redSum;
	int m_blueSum;
};

#endif