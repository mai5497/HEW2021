#include "Camera.h"
#include "Input.h"
#include "Shader.h"
#include "Defines.h"


Camera::Camera()
	: m_pos(0, 12.0f, -20.0f)
	, m_look(0, 0, 0)
	, m_up(0, 1, 0)
	, m_angle(60.0f)
	, m_near(0.5f)
	, m_far(1000.0f)
	, m_xzAngle(0.0f)
	, m_yAngle(30.0f)
	, m_radius(5.0f)
{

}

Camera::~Camera()
{

}

void Camera::Init()
{

}

void Camera::Uninit()
{

}

void Camera::Update()
{
	//�ɍ��W�n
	//�p�x�ƒ����ō��W��\��
	//�������W�n
	//X����Y���ō��W�A�������W�n�͐l���p�b�ƌ��ŗ������₷���B
	//�ɍ��W�n�͉~��`���悤�ȓ������Č����₷��
	//x = sin�� * r;
	//y = -cos�� * r;
	//��...�p�x/r...���a
	//3D�̋ɍ��W
	//x = cos�� * sin�� * r
	//z = cos�� * -cos�� * r
	//y = sin�� * r



	//�J�����̊p�x�ύX
	if (IsPress(VK_LEFT))
	{
		m_xzAngle += 1.0f;
	}
	if (IsPress(VK_RIGHT))
	{
		m_xzAngle -= 1.0f;
	}
	if (IsPress(VK_UP))
	{
		if (IsPress(VK_SHIFT))
		{
			m_radius -= 10.0f / 60.0f;
			if (m_radius <= 1.0f)
				m_radius = 1.0f;
		}
		else
		{
			m_yAngle += 1.0f;
		}

		//�J�����̏���x�N�g������ɏ�������Ă���̂łЂ�����G�͎��Ȃ�
		//����ɂ܂�������������Ԃ̊G������
		//�ʏ�A�RD�̃c�[���ł̓J�������^�ォ�猩���낷�A�^�����猩�グ��G�ɂȂ�Ȃ��悤�Ɉړ��̐����������Ă���
		if (m_yAngle >= 90.0f)
		{
			m_yAngle = 89.0f;
		}

	}
	if (IsPress(VK_DOWN))
	{
		if (IsPress(VK_SHIFT))
		{
			m_radius += 10.0f / 60.0f;
		}
		else
		{
			m_yAngle -= 1.0f;
		}
		if (m_yAngle <= -90.0f)
		{
			m_yAngle = -89.0f;
		}
	}


	//�J�����ʒu�v�Z
	float xzRad = m_xzAngle * 3.141592f / 180.0f;
	float yRad = m_yAngle * 3.141592f / 180.0f;
	m_pos.x = cos(yRad) * sin(xzRad) * m_radius;
	m_pos.z = cos(yRad) * -cos(xzRad) * m_radius;
	m_pos.y = sin(yRad) * m_radius;
}

void Camera::Bind()
{
	//�J�����̃p�����[�^��Shader�ɓn��
	SHADER->SetView(
		DirectX::XMMatrixLookAtLH(
			DirectX::XMVectorSet(
				m_pos.x, m_pos.y, m_pos.z, 0),
			DirectX::XMVectorSet(
				m_look.x, m_look.y, m_look.z, 0),
			DirectX::XMVectorSet(
				m_up.x, m_up.y, m_up.z, 0)
		)
	);
	SHADER->SetProjection(
		DirectX::XMMatrixPerspectiveFovLH(
			m_angle * 3.141592f / 180.0f,
			(float)SCREEN_WIDTH / SCREEN_HEIGHT,
			m_near, m_far
		)
	);
	SHADER->SetPSCameraPos(m_pos);


}

void Camera::Bind2D()
{
	SHADER->SetView
	(
		DirectX::XMMatrixLookAtLH
		(
			DirectX::XMVectorSet(0, 0, 0, 0.0f),		// �������F�J�����̈ʒu
			DirectX::XMVectorSet(0, 0, 300, 0.0f),		// �������F�J�����̒����_
			DirectX::XMVectorSet(0, 1, 0, 0.0f)			// ��O�����F�J�����̏�����x�N�g��
		)
	);

	SHADER->SetProjection
	(
		DirectX::XMMatrixOrthographicLH
		(
			1, (float)SCREEN_HEIGHT / SCREEN_WIDTH,		// �c����(x,y)
			0.5f, 500.0f									// �j�A�A�t�@�[�N���b�v
		)
	);
	SHADER->SetPSCameraPos(DirectX::XMFLOAT3(0, 0, 0));
}
float Camera::GetxzAngle()
{
	return m_xzAngle;
}