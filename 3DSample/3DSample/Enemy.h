#pragma once
#include "EnemyBase.h"
#include "FBX/FBXPlayer.h"
#include "DrawBuffer.h"

class Enemy :public EnemyBase
{
public:
	Enemy();
	virtual ~Enemy();

	ID3D11ShaderResourceView *m_pEnemyTex;

//	bool LoadEnemy(const char* pFilePath);

	bool Init();
	virtual void Uninit();

	virtual void Update();
//	void DrawEnemyModel();
	void Draw();
	virtual void EnemyStop();


private:
	bool LoadEnemy(const char* pFilePath);
	static DrawBuffer * m_pBuffer;
	static FBXPlayer *m_pfbx;	//FBXファイル操作クラス

	XMFLOAT3 m_dir;
	float m_EnemyAngle;

};