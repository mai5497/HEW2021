//====================================================================
//
// 弾のベース
// 作成者:吉原飛鳥
// 
// 更新日:2021/12/26	作成
//====================================================================

/* -----------------インクルードガード------------------ */
#pragma once

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"CharacterBase.h"
#include	"Collision.h"
#include	"Stage.h"
#include	"BulletManager.h"
#include	"BulletTarget.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************


 //*******************************************************************************
 // クラス定義
 //*******************************************************************************
class BulletBase : public CharacterBase
{
public:
			BulletBase();
	virtual ~BulletBase();

	//---関数
	virtual void Update();  
	virtual void Draw();

	//virtual void CreateBullet(XMFLOAT3 SPos, bool rbFlg);
	//		void CreateBullet(bool rbFlg);
	//		void DestroyBullet();

	//---setter/getter
			//---二色の弾の処理
			void SetRBFlg(bool flg);			// 投げた弾が赤か青かセットする
			bool GetRBFlg();

			void SetColFlg(bool flg);
			bool GetColFlg();
			bool GetLandingFlg();

			void SetBezierInfo(XMFLOAT3 startPos, XMFLOAT3 endPos, XMFLOAT3 centerPos,float ThrowTimer);		// ベジェ曲線による算出を行うための座標を取得

private:
	//---関数

	//---変数
	int m_sleep;
	int m_sleep2;
	float m_BulletAngle;			// 角度
	XMFLOAT3 m_dir;					// 向き
	int m_AliveTime;				// 弾の生存時間

	XMFLOAT3 m_StarPos;				// 開始地点
	XMFLOAT3 m_EndPos;				// 着地点
	XMFLOAT3 m_CenterPos;			// 制御点
	float m_ThrowTimer;				// 投げる時間

	XMFLOAT3 m_BulletTargetPos;		// ターゲットの座標

	bool m_rbFlg;					// true　→　赤			false　→　青
	bool m_ColFlg;					// true　→　地面と接している	false → 地面と接していない
	bool m_LandingFlg;				// 着地フラグ（着地した瞬間）

};
