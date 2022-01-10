#pragma once
#include "Texture.h"
#include "GameObject.h"
#include "Camera.h"

class Tutorial
{
public:
	Tutorial();
	~Tutorial();

	void Init();
	void Uninit();
	void Update();
	void Draw();


private:
	ID3D11ShaderResourceView*	m_pTexTutorial;

	GameObject*		m_pObjectTutorial;
	Camera*			m_pCameraTutorial;

};

