//****************************************************
//
//	�X�e�[�W�I�u�W�F�N�g[StageObject.h]
//	�쐬�ҁF�g����
//	
//	2022/01/18 :�쐬 
//
//****************************************************

/* -----------------�C���N���[�h�K�[�h------------------ */
#pragma once

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************
#include	"StageObjectBase.h"

#include	"FBX/FBXPlayer.h"
#include	"Texture.h"

//*******************************************************************************
// �N���X�錾
//*******************************************************************************
class StageObject : public StageObjectBase
{
public:
	StageObject();
	~StageObject();

	//---�֐�
	bool Init();
	void Uninit();
	void Draw();

	//---�ϐ�
	//ID3D11ShaderResourceView	*m_pObjectStageTex;

private:

	//---�֐�
	//bool LoadStageObject(const char *pFilePath);

	//---�ϐ�
	//static DrawBuffer* m_pBuffer;
	//static FBXPlayer* m_pFBX;				// FBX�t�@�C������N���X
};

