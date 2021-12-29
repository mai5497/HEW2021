#ifndef __STAGEMANAGER_H__
#define __STAGEMANAGER_H__

#include "Stage.h"

class StageManager
{
public:
	StageManager();
	~StageManager();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

	Stage *GetStage(int index);
	int GetStageNum();

private:
	Stage **m_ppStages;
	int m_nStageNum;

};


#endif
