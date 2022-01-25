//====================================================================
//
// �e�̗����n�_[BulletTarget.h]
// �쐬��:�g����
// 
// �X�V��:2022/01/15	�쐬
//====================================================================

/* -----------------�C���N���[�h�K�[�h------------------ */
#pragma once

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"GameObject.h"
#include	"MyVector.h"
#include	"TPScamera.h"


//---���f���`��p
#include	"Texture.h"
#include	"FBX/FBXPlayer.h"
#include	"DrawBuffer.h"

 //*******************************************************************************
 // �N���X�錾
 //*******************************************************************************
class BulletTarget : public GameObject
{
public:
	BulletTarget();
	~BulletTarget();

	//---�֐�
	bool Init();
	void Uninit();
	virtual void Update();
	void Draw();

	void SetBulletTargetPos(XMFLOAT3 pos);	// �^�[�Q�b�g���W�̐ݒ�
	XMFLOAT3 GetBulletTargetPos();			// �^�[�Q�b�g���W�̎擾

	//---�Ă�������ǂݍ���
	ID3D11ShaderResourceView	*m_pBulletTargetTex;

private:

	//---���f���ǂݍ���
	static DrawBuffer* m_pBTBuffer;		// �o�b�t�@��񑀍�
	static FBXPlayer* m_pBTFBX;			// FBX�t�@�C������N���X

	Camera *m_pCamera;					// �J�������
	float m_DrawAngle;						// �`��p�x
	float m_MoveSpeed;								// �ړ����x
};



