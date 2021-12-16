#ifndef __ATTACKPIKMIN_H__
#define __ATTACKPIKMIN_H__

//========================= インクルード部 ===========================
#include "PikminBase.h"
#include "FBX/FBXPlayer.h"

//========================= クラス定義 ===========================
class AttackPikmin : public PikminBase
{
public:
	//---関数
	AttackPikmin();
	~AttackPikmin();
	bool Init();
	void Uninit();
	virtual void Update();
	void Draw();


	//---変数
	ID3D11ShaderResourceView *m_pAttackPikminTex;

private:
	//---関数
	void Attack();
	bool LoadPikmin(const char *pFilePath);

	//---変数
	float m_PikminAngle;
	XMFLOAT3 m_dir;
	static DrawBuffer *m_pBuffer;
	static FBXPlayer *m_pFBX;		// FBXファイル操作クラス
};


#endif