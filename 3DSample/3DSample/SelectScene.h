#ifndef _SELECT_SCENE_H_
#define _SELECT_SCENE_H_

#include "Scene.h"
#include "GameObject.h"

class SelectScene :public Scene
{
public:
	SelectScene();
	~SelectScene();

	void Init();
	void Uninit();
	SCENE Update();
	void Draw();

	int GetStageNum();	// ƒV[ƒ“”Ô†æ“¾
	
	void SetScore(int stageNum, int score);

private:
	int m_StageNum;
	DirectX::XMFLOAT3 m_moveAngle;
};


#endif // _TITLE_SCENE_H_
