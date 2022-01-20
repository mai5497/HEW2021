//====================================================================
//
// �e[Shadow.h]
// �쐬��:�g����
// 
// �X�V��:2022/01/18	�쐬
//====================================================================

/* -----------------�C���N���[�h�K�[�h------------------ */
#pragma once

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"GameObject.h"
#include	"Camera.h"

//---���f���`��
#include	"Texture.h"
#include	"FBX/FBXPlayer.h"
#include	"DrawBuffer.h"

 //*******************************************************************************
 // �N���X�錾
 //*******************************************************************************
class Shadow : public GameObject
{
public:
	Shadow();
	~Shadow();

	//---�֐�
	bool Init();
	void Uninit();
	void Update();
	void Draw();

	XMFLOAT3 GetShadowPos();									// �e�̍��W�擾
	void CreateShadow(XMFLOAT3 pos,float radius);	// �e�̐���										// �e�̐���

	//---�e�N�X�`���ǂݍ���
	ID3D11ShaderResourceView *m_pShadowTex;		// �e�N�X�`��

private:
	//---���f���ǂݍ���

	Camera* m_pCamera;							// �J�������

};
