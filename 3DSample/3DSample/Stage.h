#ifndef __STAGE_H__
#define __STAGE_H__

//========================= インクルード部 ===========================
#include "DwarfBase.h"
#include "FBX/FBXPlayer.h"
#include "FieldManager.h"

//========================= 定数・マクロ定義 ===========================
enum MODELNUM {
	LOWESTGROUND = 0,
	DWARFGROUND,
	PLAYERGROUND_R,
	PLAYERGROUND_L,
	PLAYERGROUND_INSIDE,
	PLAYERGROUND_BEFORE,

	MODEL_MAX
};


//========================= クラス定義 ===========================
class Stage
{
public:
	//---関数
	Stage();
	~Stage();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

	FieldManager *GetField(int index);
	int GetFieldNum();

	//---変数
	ID3D11ShaderResourceView *m_pStageTex[MODEL_MAX];

private:
	//---関数
	bool LoadStage(const char *pFilePath,int num);

	//---変数
	FieldManager **m_ppFields;
	int m_nFieldNum;
	static DrawBuffer *m_pBuffer[MODEL_MAX];
	static FBXPlayer *m_pFBX[MODEL_MAX];		// FBXファイル操作クラス
};


#endif
