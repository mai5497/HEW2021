#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "CharacterBase.h"
#include "Camera.h"
#include "Bullet.h"
#include "DrawBuffer.h"
#include "TPSCamera.h"

class Player : public CharacterBase
{
public:
	Player();
	virtual ~Player();

	bool Init();
	void Uninit();
	virtual void Update();
	void Draw();
	virtual void PlayerToEnemy(GameObject*);

	void SetControllCamera(Camera *pCamera);

	Bullet *GetBullet(int index);
	int GetBulletNum();

	//void CreateBullet(TPSCamera*);
	void CreateBullet(Camera *pCamera,bool rbFlg);
	void GetCameraPos(TPSCamera*);
	void DestroyBullet();

private:
	Camera * m_pControllCamera;

	Bullet **m_ppBullets;
	int m_nBulletNum;

	DrawBuffer m_Buffer;
};

#endif // !_PLAYER_H_
