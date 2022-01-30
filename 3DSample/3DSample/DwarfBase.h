#ifndef __DWARFBASE_H__
#define __DWARFBASE_H__

//========================= �C���N���[�h�� ===========================
#include "CharacterBase.h"
#include "Collision.h"
#include "StageManager.h"

//=========================  �萔�E�}�N����`===========================
#define DWARF_SIZE			(2.0f)
#define TARGETSET_TIME		(300)
#define	RATE_ROTATE_DWARF	(0.20f)		// ��]�����W��
#define GRAVITY				(0.3f)		// �d��
#define LIFTPOWER			(0.15f)		// ������
#define COLLECTOR_POS_Y		(20.0f)		// ��[�ӂ��[�̍���



//���݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂���
#define MAX_RED_DWARF_1		(0)									// �X�e�[�W�P�ԏ��l�ő�l
#define MAX_BLUE_DWARF_1	(6)									// �X�e�[�W�P���l�ő�l
#define MAX_DWARF_1			(MAX_RED_DWARF_1 + MAX_BLUE_DWARF_1)// �X�e�[�W�P���l�ő吔���v

#define MAX_RED_DWARF_2		(8)									// �X�e�[�W�P�ԏ��l�ő�l
#define MAX_BLUE_DWARF_2	(8)									// �X�e�[�W�P���l�ő�l
#define MAX_DWARF_2			(MAX_RED_DWARF_2 + MAX_BLUE_DWARF_2)// �X�e�[�W�P���l�ő吔���v

#define MAX_RED_DWARF_3		(12)									// �X�e�[�W�P�ԏ��l�ő�l
#define MAX_BLUE_DWARF_3	(12)									// �X�e�[�W�P���l�ő�l
#define MAX_DWARF_3			(MAX_RED_DWARF_3 + MAX_BLUE_DWARF_3)// �X�e�[�W�P���l�ő吔���v

#define DWARF_HITBOX_X		(1.0f)								// ���l�̃q�b�g�{�b�N�X�i���m�ɂ͋��E���j
#define DWARF_HITBOX_Y		(1.0f)
#define DWARF_HITBOX_Z		(1.0f)

#define DWARF_DEFAULT_SPEED	(4.0f)								// ���i�̃X�s�[�h
#define DWARF_RUN_SPEED		(3.0f)								// �e���瓦����X�s�[�h
#define DWARF_FOLLOW_SPEED	(12.0f)								// �e��ǂ�������Ƃ��̃X�s�[�h
#define DWARF_REVERSE_SPEED (4.0f)								// �Ԃ����Ĕ��]����Ƃ��̃X�s�[�h
//���݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂��Ƃ݂���





//========================= �N���X��` ===========================
class DwarfBase : public CharacterBase 
{
public:
	//---�֐�
	DwarfBase();
	virtual ~DwarfBase();
	virtual void Update();
	virtual void Draw();

	virtual void TargetPos(XMFLOAT3 pos);	// �ǐՑ���̍��W���Z�b�g
	void SetRBFlg(bool flg);				// �Ԑt���O�̃Z�b�g(true�F�ԁAfalse�F��)
	bool GetRBFlg();
	void SetAliveFlg(bool flg);				// �����t���O�̃Z�b�gtrue����false����
	bool GetAliveFlg();
	void SetrunFlg(bool flg);				// �����t���O�̃Z�b�gture�ŗ����
	bool GetrunFlg();
	void SetFollowFlg(bool flg);			// �ǐՃt���O�̃Z�b�gtrue�Œǐ�
	bool GetFollowFlg();
	void SetMoveFlg(bool flg);				// �ړ����t���O�̃Z�b�gtrue�ňړ���
	bool GetMoveFlg();
	void SetColFlg(bool flg);				// �����蔻��t���O�Z�b�gture�œ�����
	bool GetColFlg();
	XMFLOAT3 GetOldPos();					// �ߋ��̍��W�擾
	XMFLOAT3 GetCurrentPos();				// ���݂̍��W�擾
	void SetCollectionFlg(bool flg);		// ����t���O�Z�b�gtrue�ŉ�����ꂽ
	bool GetCollectionFlg();				
	void SetCircumferenceFlg(bool flg);		// ����t���O�Z�b�g
	bool GetCircumferenceFlg();				// ����t���O�Q�b�g
	void SetLiftFlg(bool flg);
	bool GetLiftFlg();
	void SetBulletAliveTimer(int time);		// �e�̐������Ԃ̃Z�b�g

	//---�ϐ�

private:
	//---�֐�

	//---�ϐ�
	bool m_rbFlg;				// �ԏ��l���l����@true�F�ԁAfalse�F��
	bool m_aliveFlg;			// ����
	bool m_runFlg;				// �e���瓦����
	bool m_FollowFlg;			// �e�ɒǐ�
	bool m_MoveFlg;				// �ړ����t���O
	bool m_colFlg;				// �����蔻��t���O
	bool m_CollectionFlg;		// ����t���O�@true�F������ꂽ
	bool m_CircumferenceFlg;	// ����t���O
	bool m_liftFlg;				// �����t���O

protected:
	//---�֐�

	//---�ϐ�
	XMFLOAT3	m_currentPos;	// ���݂̍��W
	XMFLOAT3	m_oldPos;		// �ߋ��̍��W
	XMFLOAT3	m_targetPos;	// �^�[�Q�b�g���W
	int m_CircumferenceTimer;	// ����^�C�}�[
	int m_BulletAliveTimer;		// �e�̐�������
};


#endif