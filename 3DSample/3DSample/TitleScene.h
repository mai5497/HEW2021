#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "Scene.h"

class TitleScene :public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void Uninit();
	SCENE Update();
	void Draw();

};


#endif // _TITLE_SCENE_H_
