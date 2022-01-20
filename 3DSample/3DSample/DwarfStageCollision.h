#ifndef __DWARFSTAGECOLLISION_H__
#define __DWARFSTAGECOLLISION_H__

#include "GameObject.h"

class DwarfStageCollision {
public:
	//---�֐�
	DwarfStageCollision();
	~DwarfStageCollision();
	void Init();
	void Uninit();
	//void Update();	// �����Ƀf�[�^�Ƃ��đ��݂��邾���Ȃ̂ōX�V����
	void Draw();		// �����Ƀf�[�^�Ƃ��đ��݂��邾���Ȃ̂ŕ`�斳���B�i�e�X�g�p�ɕ`��͂�������s���j
	GameObject* GetDwarfStageCollision(int num);
	int GetStageNum();

private:
	//---�ϐ�
	GameObject **m_ppDwarfStageCollision;	// �����蔻��Ƃ�p�̃I�u�W�F�N�g����
	int m_DawarfStageNum;
};



#endif // !__DWARFSTAGECOLLISION_H__
