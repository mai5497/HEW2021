#ifndef _CAMERA_H_
#define _CAMERA_H_

//DirectXが提供している数学系のライブラリ
#include <DirectXMath.h>


class Camera
{
public:
	Camera();
	~Camera();

	void Init();
	void Uninit();
	virtual void Update();

	void Bind();
	void Bind2D();
	DirectX::XMFLOAT3 GetCameraPos() { return m_pos; }

	float GetxzAngle();

protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_look;
	DirectX::XMFLOAT3 m_up;
	float m_angle;
	float m_near;
	float m_far;
	//極座標//
	//XZ軸上での角度(0°で-Zの位置)
	float m_xzAngle;
	//XZ座標で回転した角度（０°で水平）
	float m_yAngle;
	//中心からの距離
	float m_radius;

	const float PI = 3.14159265359f;

};


#endif // ! _CAMERA_H_
