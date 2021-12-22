#pragma once

#include "GameObject.h"

class CollectionPoint : public GameObject
{
public:
	CollectionPoint();
	~CollectionPoint();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

private:



};

