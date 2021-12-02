#pragma once

//===== インクルード部 =====
#include <DirectXMath.h>

//===== 2次元ベクトル =====
class MyVector2
{
private:

public:
	float x, y;

	MyVector2();

	MyVector2(float x, float y);
	MyVector2(DirectX::XMFLOAT2);

	// 要素のセット
	void operator()(float x, float y);
	void operator()(DirectX::XMFLOAT2 vec);

	//===== ベクトルの演算 =====
	// ベクトル + ベクトル
	MyVector2 operator+(MyVector2 vec);

	// ベクトル - ベクトル
	MyVector2 operator-(MyVector2 vec);

	// ベクトル * スカラー
	MyVector2 operator*(float scalar);

	// ベクトル / スカラー
	MyVector2 operator/(float scalar);

	// ベクトルの大きさ取得
	float GetLength();

	static float GetLength(MyVector2 vec);

	// 内積
	static float dot(MyVector2 vec1, MyVector2 vec2);

	// 外積
	static float cross(MyVector2 vec1, MyVector2 vec2);

	// 2つのベクトルのなす角 0...π
	static float GetRadian(MyVector2 vec1, MyVector2 vec2);

	// 単位ベクトルを取得
	MyVector2 GetNormalize();

};

// スカラー * ベクトル
MyVector2 operator*(float scalar, MyVector2 vec);