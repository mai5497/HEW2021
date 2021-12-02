/**
 * @file EnemyManager.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 * @brief �G�̊Ǘ��Ɋւ��鏈��
 */
#include "EnemyManager.h"
#include "Enemy.h"

EnemyManager::EnemyManager()
	: m_ppEnemys(NULL)
	, m_nEnemyNum(0)
{

}

EnemyManager::~EnemyManager()
{

}

bool EnemyManager::Init()
{
	struct EnemySetting
	{
		DirectX::XMFLOAT3 pos;
		//DirectX::XMFLOAT3 size;
	};

	// �L�����N�^�[��ݒu
	EnemySetting settings[] = {
	{ DirectX::XMFLOAT3(6,0.5f,4) },
	{ DirectX::XMFLOAT3(10,0.5f,15) },
	{ DirectX::XMFLOAT3(22,0.5f,45) },
	{ DirectX::XMFLOAT3(47,0.5f,38) },
	{ DirectX::XMFLOAT3(33,0.5f,29) },
	};

	// �����f�[�^����G�̐����v�Z
	m_nEnemyNum = sizeof(settings) / sizeof(settings[0]);

	// �|�C���^���i�[����z����쐬
	m_ppEnemys = new EnemyBase*[m_nEnemyNum];

	// ���ꂼ��̔z��ɓG���������m��
	for (int i = 0; i < m_nEnemyNum; i++)
	{
		//m_ppEnemys[i] = new Enemy(settings[i].size);
		m_ppEnemys[i] = new Enemy;
		m_ppEnemys[i]->SetPos(settings[i].pos);
		m_ppEnemys[i]->Init();
	}

	return true;
}

void EnemyManager::Uninit()
{
	for (int i = 0; i < m_nEnemyNum; i++)
	{
		delete m_ppEnemys[i];
		m_ppEnemys[i] = NULL;
	}
	delete[] m_ppEnemys;
	m_ppEnemys = NULL;
}

void EnemyManager::Update()
{
	for (int i = 0; i < m_nEnemyNum; i++)
	{
		m_ppEnemys[i]->Update();
	}
}

void EnemyManager::Draw()
{
	for (int i = 0; i < m_nEnemyNum; i++)
	{
		m_ppEnemys[i]->Draw();
	}
}

EnemyBase *EnemyManager::GetEnemy(int index)
{
	if (index < m_nEnemyNum)
	{
		return m_ppEnemys[index];
	}
	return NULL;
}

int EnemyManager::GetEnemyNum()
{
	return m_nEnemyNum;
}

void EnemyManager::SetEnemyTarget(DirectX::XMFLOAT3 pos)
{
	for (int i = 0; i < m_nEnemyNum; i++)
	{
		m_ppEnemys[i]->TargetPos(pos);
	}
}
