#pragma once

//========================= インクルード部 ===========================
#include "Texture.h"
#include "GameObject.h"
#include "Camera.h"

//========================= クラス定義 ===========================
class Tutorial
{
	//---関数
public:
	Tutorial();
	~Tutorial();

	void Init();
	void Uninit();
	void Update();
	void Draw();


	//---変数
private:
	ID3D11ShaderResourceView*	m_pTexTutorial[4];

	GameObject*		m_pObjectTutorial[4];
	Camera*			m_pCameraTutorial;

};

