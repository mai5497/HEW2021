#ifndef __DWARFBASE_H__
#define __DWARFBASE_H__

//========================= インクルード部 ===========================
#include "CharacterBase.h"
#include "Collision.h"
#include "StageManager.h"

//=========================  定数・マクロ定義===========================
#define DWARF_SIZE			(2.0f)
#define TARGETSET_TIME		(300)
#define	RATE_ROTATE_DWARF	(0.20f)		// 回転慣性係数
#define GRAVITY				(0.3f)		// 重力
#define LIFTPOWER			(0.15f)		// 浮く力
#define COLLECTOR_POS_Y		(20.0f)		// ゆーふぉーの高さ



//↓みことみことみことみことみことみことみことみことみことみことみことみことみことみことみことみことみことみこと
#define MAX_RED_DWARF_1		(0)									// ステージ１赤小人最大値
#define MAX_BLUE_DWARF_1	(6)									// ステージ１青小人最大値
#define MAX_DWARF_1			(MAX_RED_DWARF_1 + MAX_BLUE_DWARF_1)// ステージ１小人最大数合計

#define MAX_RED_DWARF_2		(8)									// ステージ１赤小人最大値
#define MAX_BLUE_DWARF_2	(8)									// ステージ１青小人最大値
#define MAX_DWARF_2			(MAX_RED_DWARF_2 + MAX_BLUE_DWARF_2)// ステージ１小人最大数合計

#define MAX_RED_DWARF_3		(12)									// ステージ１赤小人最大値
#define MAX_BLUE_DWARF_3	(12)									// ステージ１青小人最大値
#define MAX_DWARF_3			(MAX_RED_DWARF_3 + MAX_BLUE_DWARF_3)// ステージ１小人最大数合計

#define DWARF_HITBOX_X		(1.0f)								// 小人のヒットボックス（正確には境界球）
#define DWARF_HITBOX_Y		(1.0f)
#define DWARF_HITBOX_Z		(1.0f)

#define DWARF_DEFAULT_SPEED	(4.0f)								// 普段のスピード
#define DWARF_RUN_SPEED		(3.0f)								// 弾から逃げるスピード
#define DWARF_FOLLOW_SPEED	(12.0f)								// 弾を追いかけるときのスピード
#define DWARF_REVERSE_SPEED (4.0f)								// ぶつかって反転するときのスピード
//↑みことみことみことみことみことみことみことみことみことみことみことみことみことみことみことみことみことみこと





//========================= クラス定義 ===========================
class DwarfBase : public CharacterBase 
{
public:
	//---関数
	DwarfBase();
	virtual ~DwarfBase();
	virtual void Update();
	virtual void Draw();

	virtual void TargetPos(XMFLOAT3 pos);	// 追跡相手の座標をセット
	void SetRBFlg(bool flg);				// 赤青フラグのセット(true：赤、false：青)
	bool GetRBFlg();
	void SetAliveFlg(bool flg);				// 生存フラグのセットtrueが生falseが死
	bool GetAliveFlg();
	void SetrunFlg(bool flg);				// 離れるフラグのセットtureで離れる
	bool GetrunFlg();
	void SetFollowFlg(bool flg);			// 追跡フラグのセットtrueで追跡
	bool GetFollowFlg();
	void SetMoveFlg(bool flg);				// 移動許可フラグのセットtrueで移動可
	bool GetMoveFlg();
	void SetColFlg(bool flg);				// 当たり判定フラグセットtureで当たり
	bool GetColFlg();
	XMFLOAT3 GetOldPos();					// 過去の座標取得
	XMFLOAT3 GetCurrentPos();				// 現在の座標取得
	void SetCollectionFlg(bool flg);		// 回収フラグセットtrueで回収された
	bool GetCollectionFlg();				
	void SetCircumferenceFlg(bool flg);		// 周回フラグセット
	bool GetCircumferenceFlg();				// 周回フラグゲット
	void SetLiftFlg(bool flg);
	bool GetLiftFlg();
	void SetBulletAliveTimer(int time);		// 弾の生存時間のセット

	//---変数

private:
	//---関数

	//---変数
	bool m_rbFlg;				// 赤小人青小人判定　true：赤、false：青
	bool m_aliveFlg;			// 生死
	bool m_runFlg;				// 弾から逃げる
	bool m_FollowFlg;			// 弾に追跡
	bool m_MoveFlg;				// 移動許可フラグ
	bool m_colFlg;				// 当たり判定フラグ
	bool m_CollectionFlg;		// 回収フラグ　true：回収された
	bool m_CircumferenceFlg;	// 周回フラグ
	bool m_liftFlg;				// 浮くフラグ

protected:
	//---関数

	//---変数
	XMFLOAT3	m_currentPos;	// 現在の座標
	XMFLOAT3	m_oldPos;		// 過去の座標
	XMFLOAT3	m_targetPos;	// ターゲット座標
	int m_CircumferenceTimer;	// 周回タイマー
	int m_BulletAliveTimer;		// 弾の生存時間
};


#endif