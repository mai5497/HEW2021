#pragma once
#include "Texture.h"
#include "GameObject.h"
#include "Camera.h"

class Score
{
public:
	Score();
	~Score();

	void Init();
	void Uninit();
	void Update();
	void Draw();

	void SetScore(int num);

private:
	ID3D11ShaderResourceView*	m_pTexScore[4];
	
	GameObject*		m_pObjectScore;
	Camera*			m_pCameraScore;

	int		m_nScore;
};

