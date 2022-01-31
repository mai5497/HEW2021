#pragma once

//========================= �C���N���[�h�� ===========================
#include "Texture.h"
#include "GameObject.h"
#include "Camera.h"

//========================= �N���X��` ===========================
class Tutorial
{
	//---�֐�
public:
	Tutorial();
	~Tutorial();

	void Init();
	void Uninit();
	void Update();
	void Draw();


	//---�ϐ�
private:
	ID3D11ShaderResourceView*	m_pTexTutorial[4];

	GameObject*		m_pObjectTutorial[4];
	Camera*			m_pCameraTutorial;

};

