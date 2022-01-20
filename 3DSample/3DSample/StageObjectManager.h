//====================================================================
//
// �X�e�[�W�I�u�W�F�N�g
// �쐬��:�g����
// 
// �X�V��:20212/01/18	�쐬
//====================================================================
/* -----------------�C���N���[�h�K�[�h------------------ */
#pragma once

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"StageObjectBase.h"

 //*******************************************************************************
 // �N���X�錾
 //*******************************************************************************
class StageObjectManager
{
public:
	StageObjectManager();
	~StageObjectManager();

	//---�֐�
	bool Init();
	void Uninit();
	void Update();
	void Draw();

	//void CreateStageObject(int index, XMFLOAT3 pos, XMFLOAT3 size, LPCSTR TexPath, LPCSTR ModelPath);

private:
	StageObjectBase	**m_ppStageObject;		// �X�e�[�W�̃I�u�W�F�N�g
	int m_StageObjectNum;								// �X�e�[�W�̃I�u�W�F�N�g�̍ő吔
};

