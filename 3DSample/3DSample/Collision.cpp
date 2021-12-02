#include "Collision.h"

#define EventRad1 (3.0f)
#define EventRad2 (3.0f)

Collision::Collision()
	:m_registerNum(0)
{
}
Collision::~Collision()
{
	Uninit();
}

bool Collision::Init()
{
	for (int i = 0; i < MAX_COLLISION_REGISTER; ++i)
	{
		m_pList[i][0] = m_pList[i][1] = NULL;
	}
	return true;
}
void Collision::Uninit()
{
	for (int i = 0; i < MAX_COLLISION_REGISTER; ++i)
	{
		m_pList[i][0] = m_pList[i][1] = NULL;
	}
}
void Collision::Update()
{
	//�����蔻�菈��
	for (int i = 0; i < MAX_COLLISION_REGISTER; i++)
	{
		GameObject *pA = m_pList[i][0];
		GameObject *pB = m_pList[i][1];
		//�o�^����Ă��Ȃ��f�[�^�͏������Ȃ�
		if (pA == NULL || pB == NULL)
		{
			continue;
		}
		
		//�l�p�`���m�̓����蔻��
		//2D�ł�3D�ł����S�܂ł̋����������̑傫���𑫂����킹����
		//�͕ς��Ȃ��B�v�Z���鎲�������邾��
		DirectX::XMFLOAT3 aPos = pA->GetPos();
		DirectX::XMFLOAT3 bPos = pB->GetPos();
		DirectX::XMFLOAT3 aSize = pA->GetSize();
		DirectX::XMFLOAT3 bSize = pB->GetSize();

		DirectX::XMFLOAT3 distance(
			fabsf(bPos.x - aPos.x),
			fabsf(bPos.y - aPos.y),
			fabsf(bPos.z - aPos.z)
		);
		bool hitX = distance.x < (aSize.x + bSize.x) * 0.5f;
		bool hitY = distance.y < (aSize.y + bSize.y) * 0.5f;
		bool hitZ = distance.z < (aSize.z + bSize.z) * 0.5f;

		//�藠���̓����蔻��
		if ((bPos.x - aPos.x) * (bPos.x - aPos.x) +
			(bPos.y - aPos.y) * (bPos.y - aPos.y) +
			(bPos.z - aPos.z) * (bPos.z - aPos.z)
			<= (EventRad1 + EventRad2) * (EventRad1 + EventRad2))
		{
			if (pA->GetCollisionType() == COLLISION_DYNAMIC &&
				pB->GetCollisionType() == COLLISION_ENEMY)
			{
				pA->OnCollision(pB);
			}
		}

		//�����蔻��̌���
		if (hitX && hitY && hitZ)
		{
			//dynamic - static
			if (pA->GetCollisionType() == COLLISION_DYNAMIC &&
				pB->GetCollisionType() == COLLISION_STATIC)
			{
				Push(pA, pB);
			}
			if (pA->GetCollisionType() == COLLISION_ENEMY &&
				pB->GetCollisionType() == COLLISION_STATIC)
			{
				Push(pA, pB);
			}
			if (pA->GetCollisionType() == COLLISION_STATIC &&
				pB->GetCollisionType() == COLLISION_DYNAMIC)
			{
				Push(pB, pA);
			}
			//dynamic - dynamic

			//dynamic - overlap
		}
	}
	m_registerNum = 0;
}


void Collision::Register(GameObject *pA, GameObject *pB)
{
	if (m_registerNum < MAX_COLLISION_REGISTER)
	{
		m_pList[m_registerNum][0] = pA;
		m_pList[m_registerNum][1] = pB;
		++m_registerNum;
	}
}


//�����o������
void Collision::Push(GameObject *pDynamic,GameObject *pStatic)
{
	//---���O�Ɋe�I�u�W�F�N�g�̏��𔲂����
	DirectX::XMFLOAT3 dPos = pDynamic->GetPos();
	DirectX::XMFLOAT3 sPos = pStatic->GetPos();
	DirectX::XMFLOAT3 dSize = pDynamic->GetSize();
	DirectX::XMFLOAT3 sSize = pStatic->GetSize();
	DirectX::XMFLOAT3 dMove = pDynamic->GetMove();

	//---�v�Z���𔲂��o��
	//�ړ��ʂ���ړ�������������߂�
	//���ړ���������͂P��-1�ŕ\��
	//�O�����Z�qA ? B : C
	//A�̏������������Ă���B�A�s�����Ȃ�C
	DirectX::XMFLOAT3 dir(
		dMove.x > 0 ? 1 : -1,
		dMove.y > 0 ? 1 : -1,
		dMove.z > 0 ? 1 : -1);
	//����ƈꏏ
	/*
	if (dMove.x > 0)
	{
		dMove.x = 1;
	}
	else
	{
		dMove.y = -1;
	}
	*/

	//���ۂɓ����蔻��̂߂荞�񂾂̂́A
	//�I�u�W�F�N�g�̍��W�ł͂Ȃ��A�p������
	//�߂荞��ł��邱�Ƃ�����̂ŁA
	//�Ώۂ̊p���v�Z�ŋ��߂�
	DirectX::XMFLOAT3 dPoint(
		dPos.x + dir.x * dSize.x * 0.5f,
		dPos.y + dir.y * dSize.y * 0.5f,
		dPos.z + dir.z * dSize.z * 0.5f);
	//�ړ��O�̊p�̍��W
	//���̂܂܂̈ړ��ʂňړ��O�̍��W��\������
	//����ƕ��������_�̌v�Z�덷�ɂ��A�ړ�
	//�x�N�g���̎��_���ʂ̓����ɂ��邱�ƂɂȂ�A
	//�ђʂ��Ă��Ȃ��Ɣ��肳���B
	//�����������邽�߂Ɉړ��̑O�̈ʒu�������Ȃ�
	//�悤�Ɍv�Z�̎������A�ړ��ʂ�傫������
	DirectX::XMFLOAT3 prePoint(
		dPoint.x - dMove.x * 1.1f,
		dPoint.y - dMove.y * 1.1f,
		dPoint.z - dMove.z * 1.1f);
	//�Փ˂��ꂽ���̊p���v�Z
	//�Փ˂��ꂽ���̊p�͈ړ������𔽓]����
	//�����Ɍ������đ傫���̔����𑫂��Ƌ��߂���
	DirectX::XMFLOAT3 sPoint(
		sPos.x - dir.x * sSize.x * 0.5f,
		sPos.y - dir.y * sSize.y * 0.5f,
		sPos.z - dir.z * sSize.z * 0.5f);
	//�ʏ�̈�_����ړ��x�N�g���̎n�_�ƏI�_��
	//�������x�N�g�����v�Z����
	DirectX::XMFLOAT3 vStart(
		prePoint.x - sPoint.x,
		prePoint.y - sPoint.y,
		prePoint.z - sPoint.z);
	DirectX::XMFLOAT3 vEnd(
		dPoint.x - sPoint.x,
		dPoint.y - sPoint.y,
		dPoint.z - sPoint.z);

	//���ꂼ��̖ʂƌv�Z
	//�e�ʂ̖@���x�N�g��
	DirectX::XMFLOAT3 Normal[] =
	{
		DirectX::XMFLOAT3(-dir.x, 0, 0),
		DirectX::XMFLOAT3(0, -dir.y, 0),
		DirectX::XMFLOAT3(0, 0, -dir.z),
	};
	for (int i = 0; i < _countof(Normal); i++)
	{
		//�ʂ̖@���Ƃ̓��ς��v�Z
		float dotS =
			vStart.x * Normal[i].x +
			vStart.y * Normal[i].y +
			vStart.z * Normal[i].z;
		float dotE =
			vEnd.x * Normal[i].x +
			vEnd.y * Normal[i].y +
			vEnd.z * Normal[i].z;
		//���ꂼ��̓��ς̌��ʂ����ƕ���
		//����Έړ��x�N�g����ʂ��ђʂ��Ă���
		//���ƕ��̑g�ݍ��킹���ǂ�����
		//�|���Z�Ŕ���ł���
		//(��x��=��/��x��=��/��x��=��)
		if (dotS * dotE < 0)
		{
			//�ړ��x�N�g���̕����ɂ߂荞�񂾗ʂ�
			//�߂��̂ł͂Ȃ��A�ʂ̕����Ɍ�������
			//�߂�(�߂������͓��ς̒l�Ɠ�����)
			dotE = fabsf(dotE);
			dPos.x += Normal[i].x * dotE;
			dPos.y += Normal[i].y * dotE;
			dPos.z += Normal[i].z * dotE;
			pDynamic->SetPos(dPos);
			//���ׂĂ̈ړ��ʂ�0�ɂ��Ă��܂���
			//�ق��̃I�u�W�F�N�g�Ɖ����o���̌v�Z��
			//����ۂɈړ��ʂ��Ȃ����ƂɂȂ�̂�
			//�ړ��ʂ�0�ɂ��Ȃ���΂Ȃ�Ȃ���������
			//0�ɂ���
			dMove.x *= 1 - fabsf(Normal[i].x);
			dMove.y *= 1 - fabsf(Normal[i].y);
			dMove.z *= 1 - fabsf(Normal[i].z);
			pDynamic->SetMove(dMove);
			break;
		}
	}
}
