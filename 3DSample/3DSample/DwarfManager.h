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
	void SetStageInfo(Stage *pStage);		// ���̏����擾



	//---�ϐ�

private:
	//---�֐�
	void DwarfFiledCollision(int num);				// ���l�Ə��̓����蔻��

	//---�ϐ�
	DwarfBase **m_ppDwarf;
	int			 m_DwarfNum;
	Stage *m_pStage;		// �����蔻��p�X�e�[�W�N���X�|�C���^

};

#endif