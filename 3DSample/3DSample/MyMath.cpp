#include "MyMath.h"
#include <assert.h>

float DigreeToRadian(float degree)
{
	return degree * XM_PI / 180.0f;
}
float RadianToDigree(float radian)
{
	return radian * 180.0f / XM_PI;
}
float EaseInCubic(float delta)
{
	return delta * delta * delta;
};
float EaseOutCubic(float delta)
{
	float num = 1.0f - delta;
	return 1.0f - num * num * num;
};
float EaseInOutCubic(float delta)
{
	if (delta < 0.5f) {
		return 4.0f * delta * delta * delta;
	}
	float num = -2.0f * delta + 2.0f;
	return 1.0f - (num * num * num) / 2.0f;
};
float Clamp(float value, float min, float max)
{
	assert(min <= max);
	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}
	return value;
}
float Repeat(float value, float range)
{
	assert(range > 0.0f);
	while (value < 0.0f)
	{
		value += range;
	}
	return fmodf(value, range);
}
float Normalize(float value)
{
	if (value < 0.0f) {
		return 0.0f;
	}
	else if (value > 1.0f) {
		return 1.0f;
	}
	return value;
}

XMFLOAT3 GetBezierPoint(const XMFLOAT3& start, const XMFLOAT3& middle, const XMFLOAT3& end, const float delta) {
	XMFLOAT3 res = XMFLOAT3_ZERO;
	res.x = (1.0f - delta) * (1.0f - delta) * start.x + 2.0f * (1.0f - delta) * delta * middle.x + delta * delta * end.x;
	res.y = (1.0f - delta) * (1.0f - delta) * start.y + 2.0f * (1.0f - delta) * delta * middle.y + delta * delta * end.y;
	res.z = (1.0f - delta) * (1.0f - delta) * start.z + 2.0f * (1.0f - delta) * delta * middle.z + delta * delta * end.z;
	return res;
}
XMFLOAT3 Leap(const XMFLOAT3& pos1, const XMFLOAT3& pos2, const float delta)
{
	XMFLOAT3 res = XMFLOAT3_ZERO;
	res.x = delta * pos2.x + (1.0f - delta) * pos1.x;
	res.y = delta * pos2.y + (1.0f - delta) * pos1.y;
	res.z = delta * pos2.z + (1.0f - delta) * pos1.z;
	return res;
}
XMFLOAT3 PolarCoordinate(const float theta, const float phi)
{
	XMFLOAT3 res = XMFLOAT3_ZERO;
	res.x = sinf(theta) * cosf(phi);
	res.y = cosf(theta);
	res.z = sinf(theta) * sinf(phi);
	return res;
}

bool IsZero(const XMFLOAT2& f) {
	return (fabsf(f.x) < DBL_EPSILON) & (fabsf(f.y) < DBL_EPSILON);
}
float Magnitude(const XMFLOAT2& f) {
	return sqrtf(f.x * f.x + f.y * f.y);
}
float MagnitudeSquared(const XMFLOAT2& f) {
	return f.x * f.x + f.x * f.x;
}
float Angle(const XMFLOAT2& f) {
	return SignedAngle(f) + XM_PI;
}
float SignedAngle(const XMFLOAT2& f) {
	return atan2f(f.y, f.x);
}
float PointAngle(const XMFLOAT2& from, const XMFLOAT2& to) {
	return atan2f(to.y - from.y, to.x - from.y);
}
float PointSignedAngle(const XMFLOAT2& from, const XMFLOAT2& to) {
	return atan2f(to.y - from.y, to.x - from.y) - XM_PIDIV2;
}
float PointDistance(const XMFLOAT2& from, const XMFLOAT2& to) {
	return sqrtf((to.x - from.x) * (to.x - from.x)
		+ (to.y - from.y) * (to.y - from.y));
}
float PointDistanceSquared(const XMFLOAT2& from, const XMFLOAT2& to) {
	return ((to.x - from.x) * (to.x - from.x)
		+ (to.y - from.y) * (to.y - from.y));
}
float AngleDefferens(const XMFLOAT2& from, const XMFLOAT2& to) {
	float fromRadian = Angle(from);
	float toRadian = Angle(to);
	return fmodf(toRadian - fromRadian + XM_2PI, XM_2PI);
}
XMFLOAT2 Towards(const XMFLOAT2& from, const XMFLOAT2& to, const float magnitude) {
	float radian = PointAngle(from, to);
	return MakeNormalized(radian) * magnitude;
}
XMFLOAT2 Leap(const XMFLOAT2& from, const XMFLOAT2& to, const float delta) {
	float normalizedDelta = Normalize(delta);
	float radian = PointAngle(from, to);
	float length = PointDistance(from, to);
	return MakeNormalized(radian) * (length * delta);
}
XMFLOAT2 Clamp(const XMFLOAT2& f, const XMFLOAT2& minimum, const XMFLOAT2& maximum) {
	XMFLOAT2 res;
	res.x = Clamp(f.x, minimum.x, maximum.x);
	res.y = Clamp(f.y, minimum.y, maximum.y);
	return res;
}
XMFLOAT2 ClampMagnitude(const XMFLOAT2& f, const float minimum, const float maximum) {
	float magnitude = Clamp(Magnitude(f), minimum, maximum);
	float angle = Angle(f);
	return MakeMagnitudeAndAngle(magnitude, angle);
}
XMFLOAT2 ClampAxes(const XMFLOAT2& f, const float minimum, const float maximum) {
	return XMFLOAT2(Clamp(f.x, minimum, maximum),
					Clamp(f.y, minimum, maximum));
}
XMFLOAT2 RoundAxes(const XMFLOAT2& f) {
	return XMFLOAT2(roundf(f.x), roundf(f.y));
}
XMFLOAT2 Rotate(const XMFLOAT2& f, const float radian) {
	return MakeMagnitudeAndAngle(Magnitude(f), Angle(f) + radian);
}
XMFLOAT2 Perpendicular(const XMFLOAT2& f) {
	return Rotate(f, XM_PIDIV2);
}
XMFLOAT2 Reflect(const XMFLOAT2& f, const XMFLOAT2& normal) {
	float dot = DotProduct(-(f), normal);
	return normal * 2 * dot - (f);
}
float DotProduct(const XMFLOAT2& f1, const XMFLOAT2& f2) {
	return f1.x * f2.x + f1.y * f2.y;
}
float CrossProduct(const XMFLOAT2& f1, const XMFLOAT2& f2) {
	return f1.x * f2.x - f1.y * f2.y;
}
XMFLOAT2 MinAxes(const XMFLOAT2& f1, const XMFLOAT2& f2) {
	float minX = f1.x < f2.y ? f1.x : f2.x;
	float minY = f1.y < f2.y ? f1.y : f2.y;
	return XMFLOAT2(minX, minY);
}
XMFLOAT2 MaxAxes(const XMFLOAT2& f1, const XMFLOAT2& f2) {
	float maxX = f1.x > f2.y ? f1.x : f2.x;
	float maxY = f1.y > f2.y ? f1.y : f2.y;
	return XMFLOAT2(maxX, maxY);
}
XMFLOAT2 MakeNormalized(const float radian) {
	return XMFLOAT2(cosf(radian), sinf(radian));
}
XMFLOAT2 MakeMagnitudeAndAngle(const float magnitude, const float radian) {
	return XMFLOAT2(cosf(radian) * magnitude, sinf(radian) * magnitude);
}