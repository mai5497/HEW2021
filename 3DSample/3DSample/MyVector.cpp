#include "MyVector.h"
#include <math.h>

// �R���X�g���N�^
MyVector2::MyVector2()
{
	x = 0;
	y = 0;
}

MyVector2::MyVector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

MyVector2::MyVector2(DirectX::XMFLOAT2 vec)
{
	this->x = vec.x;
	this->y = vec.y;
}

// �v�f�̐ݒ�
void MyVector2::operator()(float x, float y)
{
	this->x = x;
	this->y = y;
}

void MyVector2::operator()(DirectX::XMFLOAT2 vec)
{
	this->x = vec.x;
	this->y = vec.y;
}

// �x�N�g�� + �x�N�g��
MyVector2 MyVector2::operator+(MyVector2 vec)
{
	MyVector2 ret;

	ret.x = x + vec.x;
	ret.y = x + vec.y;

	return ret;
}

// �x�N�g�� - �x�N�g��
MyVector2 MyVector2::operator-(MyVector2 vec)
{
	MyVector2 ret;

	ret.x = x - vec.x;
	ret.y = y - vec.y;

	return ret;
}

// �x�N�g�� * �X�J���[
MyVector2 MyVector2::operator*(float sc)
{
	MyVector2 ret;

	ret.x = x * sc;
	ret.y = x * sc;

	return ret;
}


// �X�J���[ * �x�N�g��
MyVector2 operator*(float scalar, MyVector2 vec)
{
	MyVector2 ret;

	ret.x = vec.x * scalar;
	ret.y = vec.y * scalar;

	return ret;
}


// �x�N�g�� / �X�J���[
MyVector2 MyVector2::operator/(float scalar)
{
	MyVector2 ret;

	ret.x = x / scalar;
	ret.y = y / scalar;

	return ret;
}


// ����
float MyVector2::dot(MyVector2 vec1, MyVector2 vec2)
{
	return vec1.x * vec2.x + vec1.y * vec2.y;
}


// �O��
float MyVector2::cross(MyVector2 vec1, MyVector2 vec2)
{
	return vec1.x*vec2.y - vec1.y*vec2.x;
}


// 2�̃x�N�g���̂Ȃ��p 0...��
float MyVector2::GetRadian(MyVector2 vec1, MyVector2 vec2)
{
	// �[���x�N�g���Ȃ�Ȃ��p���o���Ȃ�
	if (GetLength(vec1) * GetLength(vec2) == 0)
		return 0;

	float x = dot(vec1, vec2) / (GetLength(vec1) * GetLength(vec2));
	if (x > 1.0f)
	{
		x = 1.0f;
	}
	else if (x < -1.0f)
	{
		x = -1.0f;
	}

	// rad = arccos( A dot B / |A|*|B| )
	//return acosf(dot(vec1, vec2) / (GetLength(vec1) * GetLength(vec2)));
	return acosf(x);
}


// �x�N�g���̑傫���擾
float MyVector2::GetLength()
{
	return sqrtf(x * x + y * y);
}


float MyVector2::GetLength(MyVector2 vec)
{
	return sqrtf(vec.x*vec.x + vec.y*vec.y);
}


// �P�ʃx�N�g�����擾
MyVector2 MyVector2::GetNormalize()
{
	MyVector2 ret;

	if (GetLength() == 0)
	{
		return ret;
	}

	ret.x = x;
	ret.y = y;

	return ret / GetLength();
}