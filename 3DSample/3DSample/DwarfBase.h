#ifndef __DWARFBASE_H__
#define __DWARFBASE_H__

//========================= �C���N���[�h�� ===========================
#include "CharacterBase.h"
#include "Collision.h"
#include "StageManager.h"

//=========================  �萔�E�}�N����`===========================
#define MAX_RED_DWARF	(6)									// �ԏ��l�ő�l
#define MAX_BLUE_DWARF	(6)									// ���l�ő�l
#define MAX_DWARF		(MAX_RED_DWARF + MAX_BLUE_DWARF)	// ���l�ő吔���v

#define DWARF_SIZE		(2.0f)
#define TARGETSET_TIME	(300)
#define	RATE_ROTATE_DWARF	(0.20f)		// ��]�����W��



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
	bool m_CollectionFlg;		// ����@true�F������ꂽ
	bool m_CircumferenceFlg;	// ����t���O

protected:
	//---�֐�

	//---�ϐ�
	XMFLOAT3	m_currentPos;	// ���݂̍��W
	XMFLOAT3	m_oldPos;		// �ߋ��̍��W
	XMFLOAT3	m_targetPos;	// �^�[�Q�b�g���W

};


#endif