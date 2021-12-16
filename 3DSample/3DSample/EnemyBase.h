#ifndef __ENEMY_BASE_H__
#define __ENEMY_BASE_H__

#include "GameObject.h"

class EnemyBase :public GameObject
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	//キャラクターの座標データが
	//足元になるように補正
	virtual void Draw();

	void TargetPos(DirectX::XMFLOAT3);
	virtual void EnemyStop();

	void SetAttackFlg(bool flg);	// フラグをセット（セットしたい方いれる）
	bool GetAttackFlg();			// フラグを取得
protected:

	DirectX::XMFLOAT3 m_targetPos;
	bool m_AttackFlg;		// 攻撃を開始するかどうか(trueの時に攻撃)
};
#endif