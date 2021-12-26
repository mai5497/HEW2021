#pragma once

//========================= インクルード部 ===========================
#include "GameObject.h"


//========================= クラス定義 ===========================
class CollectionPoint : public GameObject
{
public:
	//---関数
	CollectionPoint();
	~CollectionPoint();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

private:

};

