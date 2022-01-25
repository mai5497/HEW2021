/**
 * @file Cube.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 *		 2021/12/19 キューブの色変えたくてUpdate作成
 * @brief キューブの情報など
 * 2022/01/25 頂点情報を変更
 */
#include "Cube.h"

Cube::Cube()
	:m_posX(0),m_posY(0),m_posZ(0)
	,m_width(1),m_depth(1)
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

	//Vertex vtx[] = {
	//	{{ -l, l,-l },{ m_R,m_G,m_B,m_A },{ 0,0 }},
	//	{{  l, l,-l },{ m_R,m_G,m_B,m_A },{ 1,0 }},
	//	{{ -l,-l,-l },{ m_R,m_G,m_B,m_A },{ 0,1 }},
	//	{{  l,-l,-l },{ m_R,m_G,m_B,m_A },{ 1,1 }},
	//	{{  l, l, l },{ m_R,m_G,m_B,m_A },{ 0,0 }},
	//	{{ -l, l, l },{ m_R,m_G,m_B,m_A },{ 1,0 }},
	//	{{  l,-l, l },{ m_R,m_G,m_B,m_A },{ 0,1 }},
	//	{{ -l,-l, l },{ m_R,m_G,m_B,m_A },{ 1,1 }},
	//};

	//---頂点24個に変更
	Vertex vtx[] = {
	//---手前
	{{ -l, l,-l },{ m_R,m_G,m_B,m_A },{ 0,0 }},		//0
	{{  l, l,-l },{ m_R,m_G,m_B,m_A },{ 1,0 }},		//1
	{{ -l,-l,-l },{ m_R,m_G,m_B,m_A },{ 0,1 }},		//2
	{{  l,-l,-l },{ m_R,m_G,m_B,m_A },{ 1,1 }},		//3
	//---右
	{{  l, l, -l },{ m_R,m_G,m_B,m_A },{ 0,0 }},		//4
	{{  l, l,  l },{ m_R,m_G,m_B,m_A },{ 1,0 }},		//5
	{{  l,-l, -l },{ m_R,m_G,m_B,m_A },{ 0,1 }},		//6
	{{  l,-l,  l },{ m_R,m_G,m_B,m_A },{ 1,1 }},		//7
	//---奥
	{{ -l, l,  l },{ m_R,m_G,m_B,m_A },{ 0,0 }},		//8
	{{  l, l,  l },{ m_R,m_G,m_B,m_A },{ 1,0 }},		//9
	{{ -l,-l, l },{ m_R,m_G,m_B,m_A },{ 0,1 }},		//10
	{{  l,-l,  l },{ m_R,m_G,m_B,m_A },{ 1,1 }},		//11
	//---左
	{{ -l, l,  l },{ m_R,m_G,m_B,m_A },{ 0,0 }},		//12
	{{ -l, l, -l },{ m_R,m_G,m_B,m_A },{ 1,0 }},		//13
	{{ -l,-l, l },{ m_R,m_G,m_B,m_A },{ 0,1 }},		//14
	{{ -l,-l,-l },{ m_R,m_G,m_B,m_A },{ 1,1 }},		//15

	//---上
	{{ -l, l,  l },{ m_R,m_G,m_B,m_A },{ 0,0 }},		//16
	{{  l, l,  l },{ m_R,m_G,m_B,m_A },{ 1,0 }},		//17
	{{ -l, l, -l },{ m_R,m_G,m_B,m_A },{ 0,1 }},		//18
	{{  l, l, -l },{ m_R,m_G,m_B,m_A },{ 1,1 }},		//19

	//---下
	{{ -l,-l, l },{ m_R,m_G,m_B,m_A },{ 0,0 }},		//20
	{{  l,-l,  l },{ m_R,m_G,m_B,m_A },{ 1,0 }},		//21
	{{ -l,-l, -l },{ m_R,m_G,m_B,m_A },{ 0,1 }},		//22
	{{  l,-l, -l },{ m_R,m_G,m_B,m_A },{ 1,1 }},		//23

	};


	//インデックスデータ
	long idx[] = {
		0, 1,  2,  1, 3, 2,		//手前
		4, 5,  6,  5, 7, 6,		//右
		8, 9,10,  9,11,10,		//奥
		12,13,14, 13,15,14,	//左
		16,17,18, 17,19,18,	//上
		20,21,22, 21,23,22,	//下
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
void Cube::SetSize(float w, float h,float d)
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


	