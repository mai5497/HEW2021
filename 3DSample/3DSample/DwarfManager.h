#ifndef __DWARFMANAGER_H__
#define __DWARFMANAGER_H__

//========================= �C���N���[�h�� ===========================
#include "DwarfBase.h"

//========================= �N���X��` ===========================
class DwarfManager 
{
public:
	//---�֐�
	DwarfManager();
	~DwarfManager();
	bool Init();
	void Uninit();
	void Update();
	void Draw();

	DwarfBase *GetDwarf(int index);
	int			GetDwarfNum();
	void		SetDwarfTarget(XMFLOAT3 pos);


	//---�ϐ�

private:
	//---�֐�

	//---�ϐ�
	DwarfBase **m_ppDwarf;
	int			 m_DwarfNum;
};

#endif