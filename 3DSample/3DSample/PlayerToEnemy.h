#ifndef _PLAYER_TO_ENEMY_H_
#define _PLAYER_TO_ENEMY_H_

#include "GameObject.h"

//定数
//当たり判定を行う組み合わせの最大数
//※ほんとはリスト構造で制限のないほうが良い
#define MAX_PlayerToEnemy_REGISTER (1000)

class PlayerToEnemy
{
public:
	PlayerToEnemy();
	~PlayerToEnemy();

	bool Init();
	void Uninit();
	void Update();

	void PlayerToEnemyRegister(GameObject *pC, GameObject *pD);
	bool isHitSphere(GameObject *pC, GameObject *pD);


private:
	GameObject* m_pList[MAX_PlayerToEnemy_REGISTER][2];
	int m_registerNum;	//登録した数
	
};

#endif // !_PlayerToEnemy_H_
