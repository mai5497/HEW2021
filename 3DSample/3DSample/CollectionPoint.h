#pragma once

//========================= �C���N���[�h�� ===========================
#include "GameObject.h"


//========================= �N���X��` ===========================
class CollectionPoint : public GameObject
{
public:
	//---�֐�
	CollectionPoint();
	~CollectionPoint();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

private:

};

