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
	//極座標系
	//角度と長さで座標を表す
	//直交座標系
	//X軸とY軸で座標、直交座標系は人がパッと見で理解しやすい。
	//極座標系は円を描くような動きを再現しやすい
	//x = sinΘ * r;
	//y = -cosΘ * r;
	//Θ...角度/r...半径
	//3Dの極座標
	//x = cosΦ * sinΘ * r
	//z = cosΦ * -cosΘ * r
	//y = sinΦ * r



	//カメラの角度変更
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

		//カメラの上方ベクトルが常に上を向いているのでひっくり絵は取れない
		//※常にまっすぐ立った状態の絵が取れる
		//通常、３Dのツールではカメラが真上から見下ろす、真下から見上げる絵にならないように移動の制限をかけている
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


	//カメラ位置計算
	float xzRad = m_xzAngle * 3.141592f / 180.0f;
	float yRad = m_yAngle * 3.141592f / 180.0f;
	m_pos.x = cos(yRad) * sin(xzRad) * m_radius;
	m_pos.z = cos(yRad) * -cos(xzRad) * m_radius;
	m_pos.y = sin(yRad) * m_radius;
}

void Camera::Bind()
{
	//カメラのパラメータをShaderに渡す
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
			DirectX::XMVectorSet(0, 0, 0, 0.0f),		// 第一引数：カメラの位置
			DirectX::XMVectorSet(0, 0, 300, 0.0f),		// 第二引数：カメラの注視点
			DirectX::XMVectorSet(0, 1, 0, 0.0f)			// 第三引数：カメラの上方向ベクトル
		)
	);

	SHADER->SetProjection
	(
		DirectX::XMMatrixOrthographicLH
		(
			1, (float)SCREEN_HEIGHT / SCREEN_WIDTH,		// 縦横比(x,y)
			0.5f, 500.0f									// ニア、ファークリップ
		)
	);
	SHADER->SetPSCameraPos(DirectX::XMFLOAT3(0, 0, 0));
}
float Camera::GetxzAngle()
{
	return m_xzAngle;
}