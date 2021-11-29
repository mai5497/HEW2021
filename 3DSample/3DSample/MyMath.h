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

//@brief 要素のゼロチェック
bool IsZero(const XMFLOAT2&);
//@brief 大きさ
float Magnitude(const XMFLOAT2&);
//@brief 大きさの二乗
float MagnitudeSquared(const XMFLOAT2&);
//@brief 角度(0 ~ 2PI)
float Angle(const XMFLOAT2&);
//@brief 符号付き角度(-PI/2 ~ PI/2)
float SignedAngle(const XMFLOAT2&);
//@brief 始点から終点までの角度(0 ~ 2PI)
float PointAngle(const XMFLOAT2&, const XMFLOAT2&);
//@brief 始点から終点までの符号付き角度(-PI/2 ~ PI/2)
float PointSignedAngle(const XMFLOAT2&);
//@brief 始点から終点までの距離
float PointDistance(const XMFLOAT2&, const XMFLOAT2&);
//@brief 始点から終点までの距離の二乗
float PointDistanceSquared(const XMFLOAT2&);
//@brief ベクトルとの向きの差
float AngleDefferens(const XMFLOAT2&);
//@brief 始点から終点に向かって移動させた座標を求める
XMFLOAT2 Towards(const XMFLOAT2&, const XMFLOAT2&, const float);
//@brief 始点から終点の間を線形補完した間の座標を求める
XMFLOAT2 Leap(const XMFLOAT2&, const XMFLOAT2&, const float);
//@brief 大きさを指定した範囲に収めたベクトルを求める
XMFLOAT2 Clamp(const XMFLOAT2&, const XMFLOAT2&, const XMFLOAT2&);
//@brief 大きさを指定した範囲に収めたベクトルを求める
XMFLOAT2 ClampMagnitude(const XMFLOAT2&, const float, const float);
//@brief 両軸を指定した範囲に収めたベクトルを求める
XMFLOAT2 ClampAxes(const XMFLOAT2&, const float, const float);
//@brief 両軸を四捨五入したベクトルを求める
XMFLOAT2 RoundAxes(const XMFLOAT2&);
//@brief 向きを回転させたベクトルを求める
XMFLOAT2 Rotate(const XMFLOAT2&, const float);
//@brief 時計回りに90度垂直なベクトルを求める
XMFLOAT2 Perpendicular(const XMFLOAT2&);
//@brief 法線を基準にして反射したベクトルを求める
XMFLOAT2 Reflect(const XMFLOAT2&, const XMFLOAT2&);
//@brief 内積
float DotProduct(const XMFLOAT2&, const XMFLOAT2&);
//@brief 外積
float CrossProduct(const XMFLOAT2&, const XMFLOAT2&);
//@brief 各軸の最小値で構成されたベクトルを求める
XMFLOAT2 MinAxes(const XMFLOAT2&, const XMFLOAT2&);
//@brief 各軸の最大値で構成されたベクトルを求める
XMFLOAT2 MaxAxes(const XMFLOAT2&, const XMFLOAT2&);
//@brief 方向から正規化したベクトルを求める
XMFLOAT2 MakeNormalized(const float);
//@brief 長さと角度からベクトルを求める
XMFLOAT2 MakeMagnitudeAndAngle(const float, const float);