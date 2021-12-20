#ifndef __DWARFBASE_H__
#define __DWARFBASE_H__

//========================= インクルード部 ===========================
#include "CharacterBase.h"
using namespace DirectX;

//=========================  定数・マクロ定義===========================
#define MAX_DWARF	(5)		// ピクミン最大値

//========================= クラス定義 ===========================
class DwarfBase : public CharacterBase 
{
public:
	//---関数
	DwarfBase();
	virtual ~DwarfBase();
	void Update();
	virtual void Draw();

	virtual void TargetPos(XMFLOAT3 pos);
	void SetAttackFlg(bool flg);	// フラグのセット（セットしたい方）
	bool GetAttackFlg();
	//---変数

private:
	//---関数

	//---変数

protected:
	//---関数

	//---変数
	int			m_hp;			// HP
	int			m_energy;		// ちから（攻撃力兼防御力）
	XMFLOAT3	m_currentPos;	// 現在の座標
	XMFLOAT3	m_oldPos;		// 過去の座標
	XMFLOAT3	m_targetPos;	// ターゲット座標

	bool m_AttackFlg;

};


#endif