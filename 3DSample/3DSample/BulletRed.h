//====================================================================
//
// �Ԓe[BulletRed.h]
// �쐬��:�ɒn�c�^��
// 
// �X�V��:2022/01/08	�쐬
//====================================================================

/* -----------------�C���N���[�h�K�[�h------------------ */
#ifndef __BULLETRED_H__
#define __BULLETRED_H__

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************
#include "BulletBase.h"
#include "FBX/FBXPlayer.h"

//*******************************************************************************
// �N���X�錾															
//*******************************************************************************
class BulletRed : public BulletBase
{
public:
	//---�֐�
	BulletRed();
	virtual ~BulletRed();
	bool Init();
	virtual void Unint();
	void Draw();

	//---�ϐ�
	ID3D11ShaderResourceView* m_pBulletRedTex;

private:
	//---�֐�
	bool LoadBullet(const char* pFilePath);

	//---�ϐ�
	static DrawBuffer* m_pBuffer;
	static FBXPlayer* m_pFBX;		// FBX�t�@�C������N���X
};
#endif