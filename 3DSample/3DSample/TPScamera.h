#pragma once
// 
// 3人称視点カメラ
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
	GameObject * m_pTargetObj;		// 追従するオブジェクト
};
