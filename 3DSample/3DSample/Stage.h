#ifndef __STAGE_H__
#define __STAGE_H__

//========================= �C���N���[�h�� ===========================
#include "DwarfBase.h"
#include "FBX/FBXPlayer.h"
#include "FieldManager.h"

//========================= �萔�E�}�N����` ===========================
enum MODELNUM {
	LOWESTGROUND = 0,
	DWARFGROUND,
	PLAYERGROUND_R,
	PLAYERGROUND_L,
	PLAYERGROUND_INSIDE,
	PLAYERGROUND_BEFORE,

	MODEL_MAX
};


//========================= �N���X��` ===========================
class Stage
{
public:
	//---�֐�
	Stage();
	~Stage();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

	FieldManager *GetField(int index);
	int GetFieldNum();

	//---�ϐ�
	ID3D11ShaderResourceView *m_pStageTex[MODEL_MAX];

private:
	//---�֐�
	bool LoadStage(const char *pFilePath,int num);

	//---�ϐ�
	FieldManager **m_ppFields;
	int m_nFieldNum;
	static DrawBuffer *m_pBuffer[MODEL_MAX];
	static FBXPlayer *m_pFBX[MODEL_MAX];		// FBX�t�@�C������N���X
};


#endif
