/**
 * @file Cube.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 *		 2021/12/19 �L���[�u�̐F�ς�������Update�쐬
 * @brief �L���[�u�̏��Ȃ�
 */
#include "Cube.h"

Cube::Cube()
	:m_posX(0),m_posY(0),m_posZ(0)
	,m_width(1),m_height(1),m_depth(1)
	, m_R(1.0f), m_G(1.0f), m_B(1.0f), m_A(1.0f)
{
	//���_�o�b�t�@
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
	//�C���f�b�N�X�f�[�^
	long idx[] = {
		0,1,2, 1,3,2,	//��O
		1,4,3, 4,6,3,	//�E
		4,5,6, 5,7,6,	//��
		5,0,7, 0,2,7,	//��
		1,0,4, 0,5,4,	//��
		2,3,7, 3,6,7,	//��
	};

	//�o�b�t�@�쐬
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
	 *	�����ł�if�Ȃǂň͂�ł��Ȃ����A����Ăяo������āA���_�o�b�t�@���쐬����킯�ł͂Ȃ��A
	 *	�Ăяo������GameObject��Update�ŃJ���[�̐ݒ肪�����l�ƈقȂ����ꍇ�݂̂���Update���Ă΂��B
	 *	GameObject���p������Update�����Ƃ��́A���z�֐��ɂ��邱�Ƃ��K�{�ƂȂ�B
	*/

	//���_�o�b�t�@
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

// �F�ύX
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


	