#ifndef __PIKMINMANAGER_H__
#define __PIKMINMANAGER_H__

//========================= �C���N���[�h�� ===========================
#include "PikminBase.h"

//========================= �N���X��` ===========================
class PikminManager 
{
public:
	//---�֐�
	PikminManager();
	~PikminManager();
	bool Init();
	void Uninit();
	void Update();
	void Draw();

	PikminBase *GetPikmin(int index);
	int			GetPikminNum();
	void		SetPikminTarget(XMFLOAT3 pos);


	//---�ϐ�

private:
	//---�֐�

	//---�ϐ�
	PikminBase **m_ppPikmin;
	int			 m_pikminNum;
};

#endif