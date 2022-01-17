#ifndef __STAGEMANAGER_H__
#define __STAGEMANAGER_H__

#include "Stage.h"
#include "FBX/FBXPlayer.h"


class StageManager
{
public:
	StageManager();
	~StageManager();

	bool Init(int SelectStageNum);
	void Uninit();
	void Update();
	void Draw();

	Stage *GetStage(int index);
	int GetStageNum();

private:
	bool LoadStage(const char* pFilePath);
	static DrawBuffer * m_pBuffer;
	static FBXPlayer *m_pfbx;	//FBXファイル操作クラス


	Stage **m_ppStages;
	int m_nStageNum;
	int m_SelectStageNum;		// 選択されたステージ番号
};


#endif
