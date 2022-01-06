#ifndef __COLLISION_H__
#define __COLLISION_H__

#include "GameObject.h"

//---�萔��`
//�����蔻����s���g�ݍ��킹�̍ő吔
//���{���̓��X�g�\���Ő������Ȃ��ق�������
#define MAX_COLLISION_REGISTER (1000)

bool CollisionSphere(GameObject *pC, GameObject *pD);	// �������Ă���true��Ԃ�
bool CollisionAABB(GameObject *pE, GameObject *pF);		// �������Ă�����true��Ԃ�
void Push(GameObject *pDynamic,GameObject *pStatic);	// �����o��


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
	int m_registerNum;	//�o�^������
};



#endif
