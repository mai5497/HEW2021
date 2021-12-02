#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "GameObject.h"

//---定数定義
//当たり判定を行う組み合わせの最大数
//※本当はリスト構造で制限がないほうがいい
#define MAX_COLLISION_REGISTER (1000)

class Collision
{
public:
	Collision();
	~Collision();

	bool Init();
	void Uninit();
	void Update();

	void Register(GameObject *pA,GameObject *pB);
	
private:
	GameObject *m_pList[MAX_COLLISION_REGISTER][2];
	int m_registerNum;	//登録した数
	void Push(
		GameObject *pDynamic,
		GameObject *pStatic);
};



#endif
