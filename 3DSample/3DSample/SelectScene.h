#ifndef _SELECT_SCENE_H_
#define _SELECT_SCENE_H_

#include "Scene.h"

class SelectScene :public Scene
{
public:
	SelectScene();
	~SelectScene();

	void Init();
	void Uninit();
	SCENE Update();
	void Draw();

	int GetStageNum();	// シーン番号取得

private:
	int m_StageNum;

};


#endif // _TITLE_SCENE_H_
