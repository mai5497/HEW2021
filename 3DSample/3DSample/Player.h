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
	// ---コンストラクタ/デストラクタ
	Player();
	virtual ~Player();

	// ---4大処理
	bool Init();
	void Uninit();
	virtual void Update();
	void Draw();

	// ---エネミー追跡処理
	virtual void PlayerToEnemy(GameObject*);

	// ---カメラ関連
	void SetControllCamera(Camera *pCamera);
	void GetCameraPos(TPSCamera*);

	// ---バレット関連
	Bullet *GetBullet(int index);
	int GetBulletNum();
	//void CreateBullet(TPSCamera*);
	void CreateBullet(bool rbFlg);
	void CreateBullet(Camera *pCamera,bool rbFlg);
	void DestroyBullet();
	void BulletFiledCollision();						// 弾と床の当たり判定

	// ---小人関連
	void SetDwarfInfo(DwarfManager *pDwarfManager);
	void SetStageInfo(Stage *pStage);

	// ---プレイヤー関連


private:

	Camera * m_pControllCamera;

	Bullet **m_ppBullets;
	int m_nBulletNum;

	DrawBuffer m_Buffer;

	DwarfManager *m_pDwarfManager;
	Stage *m_pStage;
};

#endif // !_PLAYER_H_
