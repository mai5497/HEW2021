#ifndef __CHARACTER_BASE_H__
#define __CHARACTER_BASE_H__

#include "GameObject.h"

class CharacterBase :public GameObject
{
public:
	CharacterBase();
	virtual ~CharacterBase();

	//�L�����N�^�[�̍��W�f�[�^��
	//�����ɂȂ�悤�ɕ␳
	virtual void Draw();
};
#endif