//====================================================================
//
// �e�̃x�[�X
// �쐬��:�g����
// 
// �X�V��:2021/12/26	�쐬
//====================================================================

/* -----------------�C���N���[�h�K�[�h------------------ */
#pragma once

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"CharacterBase.h"
#include	"Collision.h"
#include	"Stage.h"
#include	"BulletManager.h"
#include	"BulletTarget.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************


 //*******************************************************************************
 // �N���X��`
 //*******************************************************************************
class BulletBase : public CharacterBase
{
public:
			BulletBase();
	virtual ~BulletBase();

	//---�֐�
	virtual void Update();  
	virtual void Draw();

	//virtual void CreateBullet(XMFLOAT3 SPos, bool rbFlg);
	//		void CreateBullet(bool rbFlg);
	//		void DestroyBullet();

	//---setter/getter
			//---��F�̒e�̏���
			void SetRBFlg(bool flg);			// �������e���Ԃ����Z�b�g����
			bool GetRBFlg();

			void SetColFlg(bool flg);
			bool GetColFlg();
			bool GetLandingFlg();

			void SetBezierInfo(XMFLOAT3 startPos, XMFLOAT3 endPos, XMFLOAT3 centerPos,float ThrowTimer);		// �x�W�F�Ȑ��ɂ��Z�o���s�����߂̍��W���擾

private:
	//---�֐�

	//---�ϐ�
	int m_sleep;
	int m_sleep2;
	float m_BulletAngle;			// �p�x
	XMFLOAT3 m_dir;					// ����
	int m_AliveTime;				// �e�̐�������

	XMFLOAT3 m_StarPos;				// �J�n�n�_
	XMFLOAT3 m_EndPos;				// ���n�_
	XMFLOAT3 m_CenterPos;			// ����_
	float m_ThrowTimer;				// �����鎞��

	XMFLOAT3 m_BulletTargetPos;		// �^�[�Q�b�g�̍��W

	bool m_rbFlg;					// true�@���@��			false�@���@��
	bool m_ColFlg;					// true�@���@�n�ʂƐڂ��Ă���	false �� �n�ʂƐڂ��Ă��Ȃ�
	bool m_LandingFlg;				// ���n�t���O�i���n�����u�ԁj

};
