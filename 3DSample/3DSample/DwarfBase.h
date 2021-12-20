#ifndef __DWARFBASE_H__
#define __DWARFBASE_H__

//========================= �C���N���[�h�� ===========================
#include "CharacterBase.h"
using namespace DirectX;

//=========================  �萔�E�}�N����`===========================
#define MAX_DWARF	(5)		// �s�N�~���ő�l

//========================= �N���X��` ===========================
class DwarfBase : public CharacterBase 
{
public:
	//---�֐�
	DwarfBase();
	virtual ~DwarfBase();
	void Update();
	virtual void Draw();

	virtual void TargetPos(XMFLOAT3 pos);
	void SetAttackFlg(bool flg);	// �t���O�̃Z�b�g�i�Z�b�g���������j
	bool GetAttackFlg();
	//---�ϐ�

private:
	//---�֐�

	//---�ϐ�

protected:
	//---�֐�

	//---�ϐ�
	int			m_hp;			// HP
	int			m_energy;		// ������i�U���͌��h��́j
	XMFLOAT3	m_currentPos;	// ���݂̍��W
	XMFLOAT3	m_oldPos;		// �ߋ��̍��W
	XMFLOAT3	m_targetPos;	// �^�[�Q�b�g���W

	bool m_AttackFlg;

};


#endif