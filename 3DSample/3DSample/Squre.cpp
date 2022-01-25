//====================================================================
//
// 四角ポリゴン[Squre.cpp]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/23	作成
//====================================================================

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"Squre.h"

//==============================================================
//
//	Squreクラス::コンストラクタ
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
Squre::Squre()
	:m_posX(0.0f),m_posY(0.0f),m_posZ(0.0f)
	,m_Width(1.0f),m_Depth(1.0f)
	,m_R(1.0f),m_G(1.0f),m_B(1.0f),m_A(1.0f)
{
	//---頂点バッファ
	typedef struct{
		float pos[3];		//x-y-z
		float coloar[4];	//r-g-b-a
		float uv[2];		//x-y
	}VERTEX;

	const float l = 0.5f;

	//---頂点データ
	VERTEX vtx[] = {
		{{-l, l, l},{m_R,m_G,m_B,m_A},{0.0f,0.0f} },
		{{ l, l, l},{m_R,m_G,m_B,m_A},{1.0f,0.0f} },
		{{-l,-l, l},{m_R,m_G,m_B,m_A},{0.0f,1.0f} },
		{{ l,-l, l},{m_R,m_G,m_B,m_A},{1.0f,1.0f} },
	};

	//---インデックスデータ
	long idx[] = {
		0,1,2, 1,3,2,	// 手前
	};

	//---バッファ作成
	m_buffer.CreateVertexBuffer(vtx, sizeof(VERTEX), sizeof(vtx), sizeof(VERTEX));

	//---インデックス作成
	m_buffer.CreateIndexBuffer(idx, sizeof(idx) / sizeof(long));
}

//==============================================================
//
//	Squreクラス::デストラクタ
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
Squre::~Squre()
{
	
}

//==============================================================
//
//	Squreクラス::更新
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void Squre::Update()
{
	//---頂点バッファ
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
//	Squreクラス::Draw
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void Squre::Draw()
{
	m_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

//==============================================================
//
//	Squreクラス::座標設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： float 型 x,y,z座標
//
//==============================================================
void Squre::SetPos(float x, float y, float z) {
	m_posX = x;
	m_posY = y;
	m_posZ = z;
}

//==============================================================
//
//	Squreクラス::サイズ設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： flaot w,d　横、奥行き
//
//==============================================================
void Squre::SetSize(float w, float d) {
	m_Width = w;
	m_Depth = d;
}

//==============================================================
//
//	Squreクラス::角度設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： flaot x,y,z 座標
//
//==============================================================
void Squre::SetAngle(float Ax, float Ay,float Az) {
	m_AngleX = Ax;
	m_AngleY = Ay;
	m_AngleZ = Az;
}

//==============================================================
//
//	Squreクラス::色の設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： flaot r,g,b,a(色、透明度)
//
//==============================================================
void Squre::SetRGBA(float r, float g, float b,float a) {
	m_R = r;
	m_G = g;
	m_B = b;
	m_A = a;
}