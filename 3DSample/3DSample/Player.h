#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "CharacterBase.h"
#include "Camera.h"
#include "Bullet.h"
#include "DrawBuffer.h"
#include "TPSCamera.h"
#include "DwarfManager.h"
#include "Collision.h"
#include "Stage.h"

class Player : public CharacterBase
{
public:
	// ---�R���X�g���N�^/�f�X�g���N�^
	Player();
	virtual ~Player();

	// ---4�又��
	bool Init();
	void Uninit();
	virtual void Update();
	void Draw();

	// ---�G�l�~�[�ǐՏ���
	virtual void PlayerToEnemy(GameObject*);

	// ---�J�����֘A
	void SetControllCamera(Camera *pCamera);
	void GetCameraPos(TPSCamera*);

	// ---�o���b�g�֘A
	Bullet *GetBullet(int index);
	int GetBulletNum();
	//void CreateBullet(TPSCamera*);
	void CreateBullet(bool rbFlg);
	void CreateBullet(Camera *pCamera,bool rbFlg);
	void DestroyBullet();
	void BulletFiledCollision();						// �e�Ə��̓����蔻��

	// ---���l�֘A
	void SetDwarfInfo(DwarfManager *pDwarfManager);
	void SetStageInfo(Stage *pStage);

	// ---�v���C���[�֘A


private:

	Camera * m_pControllCamera;

	Bullet **m_ppBullets;
	int m_nBulletNum;

	DrawBuffer m_Buffer;

	DwarfManager *m_pDwarfManager;
	Stage *m_pStage;
};

#endif // !_PLAYER_H_
