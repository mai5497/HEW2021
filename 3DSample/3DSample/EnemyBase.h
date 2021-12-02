#ifndef __ENEMY_BASE_H__
#define __ENEMY_BASE_H__

#include "GameObject.h"

class EnemyBase :public GameObject
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	//�L�����N�^�[�̍��W�f�[�^��
	//�����ɂȂ�悤�ɕ␳
	virtual void Draw();

	void TargetPos(DirectX::XMFLOAT3);
	virtual void EnemyStop();

protected:

	DirectX::XMFLOAT3 m_targetPos;
};
#endif