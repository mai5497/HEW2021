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
	void SetStageInfo(StageManager *pStage);

	// ---�v���C���[�֘A
	ID3D11ShaderResourceView *m_pPlayerTex;


private:
	bool LoadPlayer(const char *pFilePath);


	Camera * m_pControllCamera;				// �J�������W����

	Bullet **m_ppBullets;					// �e�̏��
	int m_nBulletNum;						// �o���b�g�����擾

	static DrawBuffer *m_pBuffer;			// �o�b�t�@��񑀍�
	static FBXPlayer *m_pFBX;				// FBX�t�@�C������N���X

	float m_DrawAngle;


	DwarfManager *m_pDwarfManager;
	StageManager *m_pStage;


};

#endif // !_PLAYER_H_
