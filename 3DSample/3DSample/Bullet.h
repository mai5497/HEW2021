#ifndef __BULLET_H__
#define __BULLET_H__


#include "CharacterBase.h"
#include "Collision.h"

class Bullet : public CharacterBase
{
public:
	Bullet(DirectX::XMFLOAT3 size);
	virtual ~Bullet();


	virtual void OnCollision(GameObject*);
	

	virtual void Update();

	void SetRB(bool flg);	// 投げた弾が赤か青かセットする
	bool GetRB();
	void SetColFlg(bool flg);	// 当たり判定フラグセット
	bool GetColFlg();


private:
	
	int m_sleep;
	int m_sleep2;

	bool m_rbFlg;	// true　→　赤			false　→　青
	bool m_ColFlg;	// true　→　接している		false → 接していない

	Collision *m_pCollision;
};


#endif