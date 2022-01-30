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
#define BULLET_GRAVITY				(0.1f / FPS)
#define BULLET_DESTOROY_CNT			(300)							// �e��������܂ł̎���
#define BULLET_THROW_CNT			(30)

enum BULLETCOLOR {
	RED_BULLET = 0,
	BLUE_BULLET,

	MAX_BULLET_COLOR
};

 //*******************************************************************************
 // �N���X��`
 //*******************************************************************************
class BulletBase : public CharacterBase
{
public:
			BulletBase();
	virtual ~BulletBase();

	//---�֐�
	virtual bool Init() {return true;}
	virtual void Update();  
	virtual void Draw();
	bool LoadModel(const char* pFilePath,int index);

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
			int GetAliveTime();
protected:
	//---�֐�

	//---�ϐ�
	static DrawBuffer* m_pBuffer[MAX_BULLET_COLOR];
	static FBXPlayer* m_pBulletModel[MAX_BULLET_COLOR];		// FBX�t�@�C������N���X
	ID3D11ShaderResourceView* m_pBulletTex[MAX_BULLET_COLOR];

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
