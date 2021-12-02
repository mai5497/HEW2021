// �C���N���[�h��
#include "TPSCamera.h"
#include "Camera.h"
#include "Input.h"
#include <math.h>
#include "MyMath.h"

TPSCamera::TPSCamera()
	:m_pTargetObj(nullptr)
{

}
TPSCamera::~TPSCamera()
{

}

void TPSCamera::Update()
{
	// �����I�u�W�F�N�g�����ݒ�Ȃ�I��
	if (m_pTargetObj == nullptr)
	{
		return;
	}
	// ���_����

	XMFLOAT2 Axis = LeftThumbPosition();

	bool KeyUp = IsPress(VK_UP);
	bool KeyDown = IsPress(VK_DOWN);
	bool KeyLeft = IsPress(VK_LEFT);
	bool KeyRight = IsPress(VK_RIGHT);

	//m_yAngle = DirectX::XMFLOAT3(Axis.x, m_yAngle.y, Axis.y);
	//Angle = fmodf(Angle + a + 360.0f, 360.0f);

	// �p�b�h
	/*if (IsJoyPadConnection)
	{
		if (IsPress(JPadButton::R_THUMB_UP))
		{
			m_yAngle -= 1.0f;
			if (m_yAngle <= -90.0f)
			{
				m_yAngle = -89.999f;
			}
		}
		if (IsPress(JPadButton::R_THUMB_DOWN))
		{
			m_yAngle += 1.0f;
			if (m_yAngle >= 90.0f)
			{
				m_yAngle = 89.999f;
			}
		}
		if (IsPress(JPadButton::R_THUMB_LEFT))
		{
			m_xzAngle += 1.0f;
			if (m_xzAngle >= 360.0f)
			{
				m_xzAngle = 0.0f;
			}
		}
		if (IsPress(JPadButton::R_THUMB_RIGHT))
		{
			m_xzAngle -= 1.0f;
			if (m_xzAngle <= -360.0f)
			{
				m_xzAngle = 0.0f;
			}
		}
	}
	else*/
	
		// �L�[�{�[�h
		if (KeyUp)
		{
			m_yAngle -= 1.0f;
			if (m_yAngle <= -90.0f)
			{
				m_yAngle = -89.999f;
			}
		}
		if (KeyDown)
		{
			m_yAngle += 1.0f;
			if (m_yAngle >= 90.0f)
			{
				m_yAngle = 89.999f;
			}
		}
		if (KeyLeft)
		{
			m_xzAngle += 1.0f;
			if (m_xzAngle >= 360.0f)
			{
				m_xzAngle = 0.0f;
			}
		}
		if (KeyRight)
		{
			m_xzAngle -= 1.0f;
			if (m_xzAngle <= -360.0f)
			{
				m_xzAngle = 0.0f;
			}
		}
	

	// �����_
	DirectX::XMFLOAT3 targetPos = m_pTargetObj->GetPos();
	m_look = targetPos;
	// �J�����ʒu�v�Z
	float xzRad = m_xzAngle * PI / 180.0f;		// ��
	float xyRad = m_yAngle * PI / 180.0f;		// ��

	m_pos.x = cos(xyRad) * sin(xzRad) * m_radius + targetPos.x;
	m_pos.z = cos(xyRad) * -cos(xzRad) * m_radius + targetPos.z;
	m_pos.y = sin(xyRad) * m_radius + targetPos.y;
}

void TPSCamera::SetTargetObj(GameObject* pObj)
{
	m_pTargetObj = pObj;

}
void TPSCamera::SetCameraRadius(float fRadius)
{
	m_radius = fRadius;
}