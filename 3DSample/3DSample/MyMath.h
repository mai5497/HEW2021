#pragma once
#include <DirectXMath.h>
#include <cmath>
#include "XMFloatHelper.h"

using namespace DirectX;

float DigreeToRadian(float);
float RadianToDigree(float);
float EaseInCubic(float);
float EaseOutCubic(float);
float EaseInOutCubic(float);
float Clamp(float, float, float);
float Repeat(float, float);
float Normalize(float);

XMFLOAT3 GetBezierPoint(const XMFLOAT3&, const XMFLOAT3&, const XMFLOAT3&, const float);
XMFLOAT3 Leap(const XMFLOAT3&, const XMFLOAT3&, const float);
XMFLOAT3 PolarCoordinate(const float, const float);

//@brief �v�f�̃[���`�F�b�N
bool IsZero(const XMFLOAT2&);
//@brief �傫��
float Magnitude(const XMFLOAT2&);
//@brief �傫���̓��
float MagnitudeSquared(const XMFLOAT2&);
//@brief �p�x(0 ~ 2PI)
float Angle(const XMFLOAT2&);
//@brief �����t���p�x(-PI/2 ~ PI/2)
float SignedAngle(const XMFLOAT2&);
//@brief �n�_����I�_�܂ł̊p�x(0 ~ 2PI)
float PointAngle(const XMFLOAT2&, const XMFLOAT2&);
//@brief �n�_����I�_�܂ł̕����t���p�x(-PI/2 ~ PI/2)
float PointSignedAngle(const XMFLOAT2&);
//@brief �n�_����I�_�܂ł̋���
float PointDistance(const XMFLOAT2&, const XMFLOAT2&);
//@brief �n�_����I�_�܂ł̋����̓��
float PointDistanceSquared(const XMFLOAT2&);
//@brief �x�N�g���Ƃ̌����̍�
float AngleDefferens(const XMFLOAT2&);
//@brief �n�_����I�_�Ɍ������Ĉړ����������W�����߂�
XMFLOAT2 Towards(const XMFLOAT2&, const XMFLOAT2&, const float);
//@brief �n�_����I�_�̊Ԃ���`�⊮�����Ԃ̍��W�����߂�
XMFLOAT2 Leap(const XMFLOAT2&, const XMFLOAT2&, const float);
//@brief �傫�����w�肵���͈͂Ɏ��߂��x�N�g�������߂�
XMFLOAT2 Clamp(const XMFLOAT2&, const XMFLOAT2&, const XMFLOAT2&);
//@brief �傫�����w�肵���͈͂Ɏ��߂��x�N�g�������߂�
XMFLOAT2 ClampMagnitude(const XMFLOAT2&, const float, const float);
//@brief �������w�肵���͈͂Ɏ��߂��x�N�g�������߂�
XMFLOAT2 ClampAxes(const XMFLOAT2&, const float, const float);
//@brief �������l�̌ܓ������x�N�g�������߂�
XMFLOAT2 RoundAxes(const XMFLOAT2&);
//@brief ��������]�������x�N�g�������߂�
XMFLOAT2 Rotate(const XMFLOAT2&, const float);
//@brief ���v����90�x�����ȃx�N�g�������߂�
XMFLOAT2 Perpendicular(const XMFLOAT2&);
//@brief �@������ɂ��Ĕ��˂����x�N�g�������߂�
XMFLOAT2 Reflect(const XMFLOAT2&, const XMFLOAT2&);
//@brief ����
float DotProduct(const XMFLOAT2&, const XMFLOAT2&);
//@brief �O��
float CrossProduct(const XMFLOAT2&, const XMFLOAT2&);
//@brief �e���̍ŏ��l�ō\�����ꂽ�x�N�g�������߂�
XMFLOAT2 MinAxes(const XMFLOAT2&, const XMFLOAT2&);
//@brief �e���̍ő�l�ō\�����ꂽ�x�N�g�������߂�
XMFLOAT2 MaxAxes(const XMFLOAT2&, const XMFLOAT2&);
//@brief �������琳�K�������x�N�g�������߂�
XMFLOAT2 MakeNormalized(const float);
//@brief �����Ɗp�x����x�N�g�������߂�
XMFLOAT2 MakeMagnitudeAndAngle(const float, const float);