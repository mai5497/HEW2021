#ifndef __ATTACKPIKMIN_H__
#define __ATTACKPIKMIN_H__

//========================= �C���N���[�h�� ===========================
#include "PikminBase.h"
#include "FBX/FBXPlayer.h"

//========================= �N���X��` ===========================
class AttackPikmin : public PikminBase
{
public:
	//---�֐�
	AttackPikmin();
	~AttackPikmin();
	bool Init();
	void Uninit();
	virtual void Update();
	void Draw();


	//---�ϐ�
	ID3D11ShaderResourceView *m_pAttackPikminTex;

private:
	//---�֐�
	void Attack();
	bool LoadPikmin(const char *pFilePath);

	//---�ϐ�
	float m_PikminAngle;
	XMFLOAT3 m_dir;
	static DrawBuffer *m_pBuffer;
	static FBXPlayer *m_pFBX;		// FBX�t�@�C������N���X
};


#endif