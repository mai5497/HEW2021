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

	void SetAttackFlg(bool flg);	// �t���O���Z�b�g�i�Z�b�g�������������j
	bool GetAttackFlg();			// �t���O���擾
protected:

	DirectX::XMFLOAT3 m_targetPos;
	bool m_AttackFlg;		// �U�����J�n���邩�ǂ���(true�̎��ɍU��)
};
#endif