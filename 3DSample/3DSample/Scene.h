#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include "Scene.h"
#include "Sound.h"

// シーン遷移
typedef enum {

	SCENE_NONE,
	SCENE_TITLE,
	SCENE_SELECT,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_END,

	SCENE_MAX,

}SCENE;
// ゲームシーン上のステート
typedef enum
{
	STATE_CONTINUE,
	STATE_NEXT,
	STATE_SELECT,
	STATE_RETRY,
	STATE_END,

	STATE_MAX
}GAMESCENE_STATE;


// シーンを完了するクラス
class Scene
{
public:
	Scene(void);
	~Scene(void);

	virtual void Init(void);
	virtual void Uninit(void);
	virtual SCENE Update(void);
	virtual void Draw(void);

};

#endif // !__SCENE_H__

