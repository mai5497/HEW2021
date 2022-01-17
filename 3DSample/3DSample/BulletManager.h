//====================================================================
//
// �e�Ǘ�
// �쐬��:�g����
// 
// �X�V��:2021/12/26	�쐬
//====================================================================

/* -----------------�C���N���[�h�K�[�h------------------ */
#pragma once

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"BulletBase.h"
#include	"Player.h"
#include	"BulletTarget.h"
#include	"TPScamera.h"

// �N���X�̑O����`
class Player;
class BulletTarget;
class Camera;

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define	MAX_RED_BULLET		(5)									// �Ԓe�̍ő�l
#define	MAX_BLUE_BULLET		(5)									// �e�̍ő�l
#define	MAX_BULLET			(MAX_RED_BULLET + MAX_BLUE_BULLET)	// �e�̍ő�l(�Ԓe + �e)

//*******************************************************************************
// �N���X�錾															
//*******************************************************************************
class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	//---�֐�
	bool Init();
	void Uninit();
	void Update();
	void Draw();

	// ---�o���b�g����
	void CreateBullet(bool rbFlg);
	//virtual void CreateBullet(XMFLOAT3 Pos, bool rbFlg);	// �e�̐���
	//virtual void OnCollision(GameObject*);
	void DestroyBullet();									// �e�̔j��
	BulletBase* GetBullet(int index);						// �e�̏���n��

	void SetTargetPos(XMFLOAT3 Pos);						// �e�̗����n�_��ݒ�


	// ---�v���C���[����
	void SetPlayePos(XMFLOAT3 Pos);							// �v���C���[�̍��W��ݒ�
	void SetPlayerAngle(XMFLOAT3 Angle);					// �v���C���[�̊p�x��ݒ�

private:
	BulletBase** m_ppBullets;					// �e�̏�������(�x�[�X)
	int m_BulletNum;							// �e�̐�

	XMFLOAT3 m_PlayerPos;						// �v���C���[�̏�������(���W)
	//XMFLOAT3 m_PlayerAngle;						// �v���C���[�̏�������(�p�x)
	XMFLOAT3 m_TargetPos;						// �^�[�Q�b�g���W
	//XMFLOAT3 m_CurrentPos;						// ���݂̍��W


	//Player *m_pPlayer;							// �v���C���[�C���X�^���X������
	//Camera* m_pCamera;							// �J�����C���X�^���X
	//BulletTarget *m_pTarget;					// �����n�_�̃C���X�^���X������

};