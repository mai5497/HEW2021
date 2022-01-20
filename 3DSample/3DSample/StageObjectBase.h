//****************************************************
//
//	�I�u�W�F�N�g�x�[�X[ObjectBase.h]
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
#include	"GameObject.h"

#include	"Texture.h"
#include	"FBX/FBXPlayer.h"
#include	"MyVector.h"

//*******************************************************************************
// �N���X�錾
//*******************************************************************************
class StageObjectBase : public GameObject
{	
public:
	StageObjectBase();
	virtual ~StageObjectBase();

	//---�֐�
	bool Init();
	void Uninit();
	virtual void Update();
	virtual void Draw();

	//---settet
	//void SetPos(XMFLOAT3 pos);
	//void SetSize(XMFLOAT3 size);
	void SetTexPath(LPCSTR pTexPath);
	void SetModelPath(LPCSTR pModelPath);

	//---getter
	//virtual XMFLOAT3 GerPos();
	//virtual XMFLOAT3 GetSize();
	LPCSTR GetTexPath();
	LPCSTR GetModelPath();

	//---�֐�
	bool LoadStageObject(const char *pFilePath);			//���f���ǂݍ���

	//---����
	void CreateStageObject(XMFLOAT3 pos, XMFLOAT3 size, LPCSTR TexPath, LPCSTR ModelPath);

	//---�ϐ�
	ID3D11ShaderResourceView *m_pStageObjectTex;

private:

	//---�ϐ�
	DrawBuffer *m_pBuffer;
	FBXPlayer *m_pFBX;


	LPCSTR m_TexPath;
	LPCSTR m_ModelPath;

};