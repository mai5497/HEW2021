#pragma once

//===== �C���N���[�h�� =====
#include <DirectXMath.h>

//===== 2�����x�N�g�� =====
class MyVector2
{
private:

public:
	float x, y;

	MyVector2();

	MyVector2(float x, float y);
	MyVector2(DirectX::XMFLOAT2);

	// �v�f�̃Z�b�g
	void operator()(float x, float y);
	void operator()(DirectX::XMFLOAT2 vec);

	//===== �x�N�g���̉��Z =====
	// �x�N�g�� + �x�N�g��
	MyVector2 operator+(MyVector2 vec);

	// �x�N�g�� - �x�N�g��
	MyVector2 operator-(MyVector2 vec);

	// �x�N�g�� * �X�J���[
	MyVector2 operator*(float scalar);

	// �x�N�g�� / �X�J���[
	MyVector2 operator/(float scalar);

	// �x�N�g���̑傫���擾
	float GetLength();

	static float GetLength(MyVector2 vec);

	// ����
	static float dot(MyVector2 vec1, MyVector2 vec2);

	// �O��
	static float cross(MyVector2 vec1, MyVector2 vec2);

	// 2�̃x�N�g���̂Ȃ��p 0...��
	static float GetRadian(MyVector2 vec1, MyVector2 vec2);

	// �P�ʃx�N�g�����擾
	MyVector2 GetNormalize();

};

// �X�J���[ * �x�N�g��
MyVector2 operator*(float scalar, MyVector2 vec);