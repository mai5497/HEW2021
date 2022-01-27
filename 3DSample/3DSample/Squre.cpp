//====================================================================
//
// �l�p�|���S��[Squre.cpp]
// �쐬��:�g����
// 
// �X�V��:2022/01/23	�쐬
//====================================================================

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"Squre.h"

//==============================================================
//
//	Squre�N���X::�R���X�g���N�^
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
Squre::Squre()
	:m_posX(0.0f),m_posY(0.0f),m_posZ(0.0f)
	,m_Width(1.0f),m_Depth(1.0f)
	,m_R(1.0f),m_G(1.0f),m_B(1.0f),m_A(1.0f)
{
	//---���_�o�b�t�@
	typedef struct{
		float pos[3];		//x-y-z
		float coloar[4];	//r-g-b-a
		float uv[2];		//x-y
	}VERTEX;

	const float l = 0.5f;

	//---���_�f�[�^
	VERTEX vtx[] = {
		{{-l, 0, l},{m_R,m_G,m_B,m_A},{0.0f,0.0f} },
		{{ l, 0, l},{m_R,m_G,m_B,m_A},{1.0f,0.0f} },
		{{-l, 0, l},{m_R,m_G,m_B,m_A},{0.0f,1.0f} },
		{{ l, 0, l},{m_R,m_G,m_B,m_A},{1.0f,1.0f} },
	};

	//---�C���f�b�N�X�f�[�^
	long idx[] = {
		0,1,2, 1,3,2,	// ��O
	};

	//---�o�b�t�@�쐬
	m_buffer.CreateVertexBuffer(vtx, sizeof(VERTEX), sizeof(vtx), sizeof(VERTEX));

	//---�C���f�b�N�X�쐬
	m_buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));
}

//==============================================================
//
//	Squre�N���X::�f�X�g���N�^
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
Squre::~Squre()
{
	
}

//==============================================================
//
//	Squre�N���X::�X�V
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void Squre::Update()
{
	//---���_�o�b�t�@
	struct VERTEX{
		float pos[3];
		float color[4];
		float uv[2];
	};

	const float l = 0.5f;


	VERTEX vtx[] = {
		{{-l, l,-l},{m_R,m_G,m_B,m_A},{0,0}},
		{{ l, l,-l},{m_R,m_G,m_B,m_A},{1,0}},
		{{-l,-l,-l},{m_R,m_G,m_B,m_A},{0,1}},
		{{ l,-l,-l},{m_R,m_G,m_B,m_A},{1,1}},
	};

	m_buffer.CreateVertexBuffer(vtx, sizeof(VERTEX), sizeof(vtx) / sizeof(VERTEX));

}

//==============================================================
//
//	Squre�N���X::Draw
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void Squre::Draw()
{
	m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

//==============================================================
//
//	Squre�N���X::���W�ݒ�
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F float �^ x,y,z���W
//
//==============================================================
void Squre::SetPos(float x, float y, float z) {
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

//==============================================================
//
//	Squre�N���X::�T�C�Y�ݒ�
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F flaot w,d�@���A���s��
//
//==============================================================
void Squre::SetSize(float w, float d) {
	m_Width = w;
	m_Depth = d;
}

//==============================================================
//
//	Squre�N���X::�p�x�ݒ�
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F flaot x,y,z ���W
//
//==============================================================
void Squre::SetAngle(float Ax, float Ay,float Az) {
	m_AngleX = Ax;
	m_AngleY = Ay;
	m_AngleZ = Az;
}

//==============================================================
//
//	Squre�N���X::�F�̐ݒ�
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F flaot r,g,b,a(�F�A�����x)
//
//==============================================================
void Squre::SetRGBA(float r, float g, float b,float a) {
	m_R = r;
	m_G = g;
	m_B = b;
	m_A = a;
}