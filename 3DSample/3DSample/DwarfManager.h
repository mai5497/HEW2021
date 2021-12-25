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
	void SetStageInfo(Stage *pStage);		// 床の情報を取得

	void DwarfFiledCollision();				// 小人と床の当たり判定


	//---変数

private:
	//---関数

	//---変数
	DwarfBase **m_ppDwarf;
	int			 m_DwarfNum;
	Stage *m_pStage;		// 当たり判定用ステージクラスポインタ

};

#endif