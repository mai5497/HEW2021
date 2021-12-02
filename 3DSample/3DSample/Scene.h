#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include "Scene.h"

typedef enum
{

	SCENE_NONE,
	SCENE_TITLE,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_MAX,

}SCENE;
// �V�[������������N���X
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

