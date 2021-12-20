/**
 * @file Cube.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 *		 2021/12/19 キューブの色変えたくてUpdate作成
 * @brief キューブの情報など
 */
#include "Cube.h"

Cube::Cube()
	:m_posX(0),m_posY(0),m_posZ(0)
	,m_width(1),m_height(1),m_depth(1)
	, m_R(1.0f), m_G(1.0f), m_B(1.0f), m_A(1.0f)
{
	//頂点バッファ
	struct Vertex
	{
		float pos[3];
		float color[4];
		float uv[2];
	};

	const float l = 0.5f;
	Vertex vtx[] = {
		{{ -l, l,-l },{ m_R,m_G,m_B,m_A },{ 0,0 }},
		{{  l, l,-l },{ m_R,m_G,m_B,m_A },{ 1,0 }},
		{{ -l,-l,-l },{ m_R,m_G,m_B,m_A },{ 0,1 }},
		{{  l,-l,-l },{ m_R,m_G,m_B,m_A },{ 1,1 }},
		{{  l, l, l },{ m_R,m_G,m_B,m_A },{ 0,0 }},
		{{ -l, l, l },{ m_R,m_G,m_B,m_A },{ 1,0 }},
		{{  l,-l, l },{ m_R,m_G,m_B,m_A },{ 0,1 }},
		{{ -l,-l, l },{ m_R,m_G,m_B,m_A },{ 1,1 }},
	};
	//インデックスデータ
	long idx[] = {
		0,1,2, 1,3,2,	//手前
		1,4,3, 4,6,3,	//右
		4,5,6, 5,7,6,	//奥
		5,0,7, 0,2,7,	//左
		1,0,4, 0,5,4,	//上
		2,3,7, 3,6,7,	//下
	};

	//バッファ作成
	m_buffer.CreateVertexBuffer(
		vtx, sizeof(Vertex),
		sizeof(vtx) / sizeof(Vertex));
	m_buffer.CreateIndexBuffer(
		idx, sizeof(idx) / sizeof(long)
	);
}

Cube::~Cube()
{
}

void Cube::Update() {
	/*
	 *	ここではifなどで囲んでいないが、毎回呼び出しされて、頂点バッファを作成するわけではなく、
	 *	呼び出し元のGameObjectのUpdateでカラーの設定が初期値と異なった場合のみこのUpdateが呼ばれる。
	 *	GameObjectを継承してUpdateを作るときは、仮想関数にすることが必須となる。
	*/

	//頂点バッファ
	struct Vertex {
		float pos[3];
		float color[4];
		float uv[2];
	};
	const float l = 0.5f;
	Vertex vtx[] = {
		{{ -l, l,-l },{ m_R,m_G,m_B,m_A },{ 0,0 }},
		{{  l, l,-l },{ m_R,m_G,m_B,m_A },{ 1,0 }},
		{{ -l,-l,-l },{ m_R,m_G,m_B,m_A },{ 0,1 }},
		{{  l,-l,-l },{ m_R,m_G,m_B,m_A },{ 1,1 }},
		{{  l, l, l },{ m_R,m_G,m_B,m_A },{ 0,0 }},
		{{ -l, l, l },{ m_R,m_G,m_B,m_A },{ 1,0 }},
		{{  l,-l, l },{ m_R,m_G,m_B,m_A },{ 0,1 }},
		{{ -l,-l, l },{ m_R,m_G,m_B,m_A },{ 1,1 }},
	};

	m_buffer.CreateVertexBuffer(
		vtx, sizeof(Vertex),
		sizeof(vtx) / sizeof(Vertex));
}


void Cube::SetPos(float x, float y, float z)
{
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}
void Cube::SetSize(float w, float h, float d)
{
	m_width = w;
	m_height = h;
	m_depth = d;
}
void Cube::SetAngle(float ax, float ay, float az)
{
	m_AngleX = ax;
	m_AngleY = ay;
	m_AngleZ = az;
}

// 色変更
void Cube::SetRGBA(float r, float g, float b, float a)
{
	m_R = r;
	m_G = g;
	m_B = b;
	m_A = a;
}


void Cube::Draw()
{
	m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}


	