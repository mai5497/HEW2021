#ifndef _PLAYER_TO_ENEMY_H_
#define _PLAYER_TO_ENEMY_H_

#include "GameObject.h"

//�萔
//�����蔻����s���g�ݍ��킹�̍ő吔
//���ق�Ƃ̓��X�g�\���Ő����̂Ȃ��ق����ǂ�
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
	int m_registerNum;	//�o�^������
	
};

#endif // !_PlayerToEnemy_H_
