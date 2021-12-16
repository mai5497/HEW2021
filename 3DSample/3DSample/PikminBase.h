#ifndef __PIKMINBASE_H__
#define __PIKMINBASE_H__

//========================= �C���N���[�h�� ===========================
#include "CharacterBase.h"
using namespace DirectX;

//=========================  �萔�E�}�N����`===========================
#define MAX_PIKMIN	(5)		// �s�N�~���ő�l

//========================= �N���X��` ===========================
class PikminBase : public CharacterBase 
{
public:
	//---�֐�
	PikminBase();
	virtual ~PikminBase();
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