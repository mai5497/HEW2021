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

private:
	//---関数

	//---変数
	int m_sleep;
	int m_sleep2;
	float m_BulletAngle;						// 角度
	XMFLOAT3 m_dir;							// 向き
	int m_AliveTime;							// 弾の生存時間

	bool m_rbFlg;									// true　→　赤			false　→　青
	bool m_ColFlg;								// true　→　接している		false → 接していない


};
