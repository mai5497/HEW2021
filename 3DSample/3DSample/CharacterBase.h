#ifndef __CHARACTER_BASE_H__
#define __CHARACTER_BASE_H__

#include "GameObject.h"

class CharacterBase :public GameObject
{
public:
	CharacterBase();
	virtual ~CharacterBase();

	//キャラクターの座標データが
	//足元になるように補正
	virtual void Draw();
};
#endif