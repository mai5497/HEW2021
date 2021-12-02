///�C���N���[�h��///
#include "PlayerToEnemy.h"

PlayerToEnemy::PlayerToEnemy()
	:m_registerNum(0)
{

}
PlayerToEnemy::~PlayerToEnemy()
{
	Uninit();
}

bool PlayerToEnemy::Init()
{
	for (int i = 0; i < MAX_PlayerToEnemy_REGISTER; ++i)
	{
		m_pList[i][0] = m_pList[i][1] = NULL;
	}
	return true;
}
void PlayerToEnemy::Uninit()
{

}
void PlayerToEnemy::Update()
{
	//�����蔻��
	for (int i = 0; i < m_registerNum; i++)
	{
		GameObject *pC = m_pList[i][0];
		GameObject *pD = m_pList[i][1];

		//�o�^����Ă��Ȃ��f�[�^�͎��{���Ȃ�
		if (pC == NULL || pD == NULL)
		{
			continue;
		}

		//���Ƌ��̓����蔻��
		if (isHitSphere(pC, pD))
		{
			if (pC->GetCollisionType() == COLLISION_DYNAMIC &&
				pD->GetCollisionType() == COLLISION_ENEMY)
			{
				pC->PlayerToEnemy(pD);
			}
		}
	}
	m_registerNum = 0;
}

// pA��pB���������Ă���Γ��삷��
void PlayerToEnemy::PlayerToEnemyRegister(GameObject *pC, GameObject *pD)
{
	if (m_registerNum < MAX_PlayerToEnemy_REGISTER)
	{
		m_pList[m_registerNum][0] = pC;
		m_pList[m_registerNum][1] = pD;
		++m_registerNum;
	}
}


//���Ƌ��̓����蔻��
//(x2-x1)^2 + (y2-y1)^2 + (z2-z1)^2 <= (r1+r2)^2
bool PlayerToEnemy::isHitSphere(GameObject *pC, GameObject *pD)
{
	DirectX::XMFLOAT3 aPos = pC->GetPos();
	DirectX::XMFLOAT3 bPos = pD->GetPos();
	DirectX::XMFLOAT3 aSize = pC->GetRadius();
	DirectX::XMFLOAT3 bSize = pD->GetRadius();

	//���a
	float Radius1 = aSize.x;
	float Radius2 = bSize.x;

	//��1�Ƌ�2�̒��S�_�̋�����2��
	float distanceSqu =
		powf((bPos.x - aPos.x), 2) +
		powf((bPos.y - aPos.y), 2) +
		powf((bPos.z - aPos.z), 2);
	//(bPos.x - aPos.x) * (bPos.x - aPos.x) +
	//(bPos.y - aPos.y) * (bPos.y - aPos.y) +
	//(bPos.z - aPos.z) * (bPos.z - aPos.z);

	return (distanceSqu <= powf((Radius1 + Radius2), 2));

	/*if (distanceSqu <= powf((Radius1 + Radius2), 2))
	{
	return true;
	}

	return false;*/
}