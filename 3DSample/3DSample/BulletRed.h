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
	void Update();

private:
	//---�֐�
	bool LoadBullet(const char* pFilePath);

	//---�ϐ�
	ANIME_INDEX m_floweAnim[MAX_ANIME];
	FBXPlayer *m_pRedModel;
	DrawBuffer *m_pRedBuffer;

};
#endif