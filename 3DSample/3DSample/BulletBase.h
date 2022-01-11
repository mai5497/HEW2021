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

private:
	//---�֐�

	//---�ϐ�
	int m_sleep;
	int m_sleep2;
	float m_BulletAngle;						// �p�x
	XMFLOAT3 m_dir;							// ����
	int m_AliveTime;							// �e�̐�������

	bool m_rbFlg;									// true�@���@��			false�@���@��
	bool m_ColFlg;								// true�@���@�ڂ��Ă���		false �� �ڂ��Ă��Ȃ�


};
