//====================================================================
//
// �e[BulletBlue.h]
// �쐬��:�g����
// 
// �X�V��:2022/01/09	�쐬
//====================================================================
/* -----------------�C���N���[�h�K�[�h------------------ */
#pragma once

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************
#include "BulletBase.h"
#include "FBX/FBXPlayer.h"

enum BULLETANIME {
	BLAST = 0,
};


//*******************************************************************************
// �N���X�錾															
//*******************************************************************************
class BulletBlue : public BulletBase
{
public:
	BulletBlue();
	~BulletBlue();

	//---�֐�
	bool Init();
	virtual void Unint();
	void Draw();
	void AnimUpdate();

	//---�ϐ�
	ID3D11ShaderResourceView* m_pBulletBlueTex;

private:
	//---�֐�
	bool LoadBullet(const char* pFilePath);

	//---�ϐ�
	static DrawBuffer* m_pBuffer;
	static FBXPlayer* m_pFBX;		// FBX�t�@�C������N���X
	ANIME_INDEX m_floweAnim[MAX_ANIME];

};

