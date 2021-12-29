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
	void SetStageInfo(StageManager *pStage);

	// ---プレイヤー関連
	ID3D11ShaderResourceView *m_pPlayerTex;


private:
	bool LoadPlayer(const char *pFilePath);


	Camera * m_pControllCamera;				// カメラ座標操作

	Bullet **m_ppBullets;					// 弾の情報
	int m_nBulletNum;						// バレット数を取得

	static DrawBuffer *m_pBuffer;			// バッファ情報操作
	static FBXPlayer *m_pFBX;				// FBXファイル操作クラス

	float m_DrawAngle;


	DwarfManager *m_pDwarfManager;
	StageManager *m_pStage;


};

#endif // !_PLAYER_H_
