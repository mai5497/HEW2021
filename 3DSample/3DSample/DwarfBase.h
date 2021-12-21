#ifndef __DWARFBASE_H__
#define __DWARFBASE_H__

//========================= インクルード部 ===========================
#include "CharacterBase.h"
using namespace DirectX;

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

	virtual void TargetPos(XMFLOAT3 pos);
	void SetAttackFlg(bool flg);	// フラグのセット（セットしたい方）
	bool GetAttackFlg();
	void SetRBFlg(bool flg);		// フラグのセット(true：赤、false：青)
	bool GetRBFlg();
	//---変数

private:
	//---関数

	//---変数
	bool m_rbFlg;				// 赤小人青小人判定　true：赤、false：青

protected:
	//---関数

	//---変数
	XMFLOAT3	m_currentPos;	// 現在の座標
	XMFLOAT3	m_oldPos;		// 過去の座標
	XMFLOAT3	m_targetPos;	// ターゲット座標

	bool m_AttackFlg;

};


#endif