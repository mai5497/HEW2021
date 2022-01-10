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

	// ---�v���C���[����
	void SetPlayePos(XMFLOAT3 Pos);							// �v���C���[�̍��W��ݒ�
	void SetPlayerAngle(XMFLOAT3 Angle);					// �v���C���[�̊p�x��ݒ�
private:
	BulletBase** m_ppBullets;					// �e�̏�������(�x�[�X)
	int m_BulletNum;							// �e�̐�

	XMFLOAT3 m_PlayerPos;						// �v���C���[�̏�������(���W)
	XMFLOAT3 m_PlayerAngle;						// �v���C���[�̏�������(�p�x)


};