//====================================================================
//
// 弾管理
// 作成者:吉原飛鳥
// 
// 更新日:2021/12/26	作成
//====================================================================

/* -----------------インクルードガード------------------ */
#pragma once

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"BulletBase.h"
#include	"Player.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define	MAX_RED_BULLET		(5)									// 赤弾の最大値
#define	MAX_BLUE_BULLET		(5)									// 青弾の最大値
#define	MAX_BULLET			(MAX_RED_BULLET + MAX_BLUE_BULLET)	// 弾の最大値(赤弾 + 青弾)

//*******************************************************************************
// クラス宣言															
//*******************************************************************************
class BulletManager
{
public:
	BulletManager();
	~BulletManager();

	//---関数
	bool Init();
	void Uninit();
	void Update();
	void Draw();

	// ---バレット処理
	void CreateBullet(bool rbFlg);
	//virtual void CreateBullet(XMFLOAT3 Pos, bool rbFlg);	// 弾の生成
	//virtual void OnCollision(GameObject*);
	void DestroyBullet();									// 弾の破壊
	BulletBase* GetBullet(int index);						// 弾の情報を渡す

	// ---プレイヤー処理
	void SetPlayePos(XMFLOAT3 Pos);							// プレイヤーの座標を設定
	void SetPlayerAngle(XMFLOAT3 Angle);					// プレイヤーの角度を設定
private:
	BulletBase** m_ppBullets;					// 弾の情報を扱う(ベース)
	int m_BulletNum;							// 弾の数

	XMFLOAT3 m_PlayerPos;						// プレイヤーの情報を扱う(座標)
	XMFLOAT3 m_PlayerAngle;						// プレイヤーの情報を扱う(角度)


};