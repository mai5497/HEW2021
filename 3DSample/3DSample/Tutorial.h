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
	ID3D11ShaderResourceView*	m_pTexTutorial[3];

	GameObject*		m_pObjectTutorial[3];
	Camera*			m_pCameraTutorial;

};

