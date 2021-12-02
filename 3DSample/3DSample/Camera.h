#ifndef _CAMERA_H_
#define _CAMERA_H_

//DirectX���񋟂��Ă��鐔�w�n�̃��C�u����
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
	//�ɍ��W//
	//XZ����ł̊p�x(0����-Z�̈ʒu)
	float m_xzAngle;
	//XZ���W�ŉ�]�����p�x�i�O���Ő����j
	float m_yAngle;
	//���S����̋���
	float m_radius;

	const float PI = 3.14159265359f;

};


#endif // ! _CAMERA_H_
