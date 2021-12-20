#pragma once
#include "EnemyBase.h"

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

	EnemyBase *GetEnemy(int index);
	int GetEnemyNum();

	void SetEnemyTarget(XMFLOAT3);
	void DestroyEnemy(int index);

private:

	// “®“IŠm•Û
	EnemyBase * *m_ppEnemys;
	int m_nEnemyNum;


};