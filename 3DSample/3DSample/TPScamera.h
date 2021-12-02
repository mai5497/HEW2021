#pragma once
// 
// 3�l�̎��_�J����
// 

#include "Camera.h"
#include "GameObject.h"

class TPSCamera
	:public Camera
{
public:
	TPSCamera();
	~TPSCamera();

	void Update();

	void SetTargetObj(GameObject* pObj);
	void SetCameraRadius(float fRadius);

protected:
	GameObject * m_pTargetObj;		// �Ǐ]����I�u�W�F�N�g
};
