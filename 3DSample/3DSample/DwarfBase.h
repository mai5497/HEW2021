#ifndef __DWARFBASE_H__
#define __DWARFBASE_H__

//========================= インクルード部 ===========================
#include "CharacterBase.h"
#include "Collision.h"
#include "Stage.h"

//=========================  定数・マクロ定義===========================
#define MAX_RED_DWARF	(6)									// 赤小人最大値
#define MAX_BLUE_DWARF	(6)									// 青小人最大値
#define MAX_DWARF		(MAX_RED_DWARF + MAX_BLUE_DWARF)	// 小人最大数合計

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
	void SetAttackFlg(bool flg);			// 攻撃フラグのセット（セットしたい方）
	bool GetAttackFlg();
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

protected:
	//---関数

	//---変数
	XMFLOAT3	m_currentPos;	// 現在の座標
	XMFLOAT3	m_oldPos;		// 過去の座標
	XMFLOAT3	m_targetPos;	// ターゲット座標

	bool m_AttackFlg;


};


#endif