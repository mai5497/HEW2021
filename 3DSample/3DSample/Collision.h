#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "GameObject.h"

//---定数定義
//当たり判定を行う組み合わせの最大数
//※本当はリスト構造で制限がないほうがいい
#define MAX_COLLISION_REGISTER (1000)

bool CollisionSphere(GameObject *pC, GameObject *pD);	// 当たってたらtrueを返す
bool CollisionAABB(GameObject *pE, GameObject *pF);	// 単純にオブジェクト同士の当たり判定


class Collision
{
public:
	Collision();
	~Collision();

	bool Init();
	void Uninit();
	void Update();

	void Register(GameObject *pA,GameObject *pB);
	bool CollisionSphere(GameObject *pC, GameObject *pD, float Radius);


private:
	GameObject *m_pList[MAX_COLLISION_REGISTER][2];
	int m_registerNum;	//登録した数
	void Push(
		GameObject *pDynamic,
		GameObject *pStatic);
};



#endif
