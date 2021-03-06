//====================================================================
//
// 板ポリゴン[GamePolygon.cpp]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/23	作成
//====================================================================

//*******************************************************************************
// インクルード部
//*******************************************************************************
#include "GamePolygon.h"
#include "Shader.h"

//==============================================================
//
//	Squreクラス::コンストラクタ
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
GamePolygon::GamePolygon()
	:m_pSqure(nullptr)
	,m_pos(0.0f,0.0f,0.0f)
	,m_size(10.0f,10.0f,10.0f)
	,m_move(0.0f,0.0f,0.0f)
	,m_Angle(0.0f,0.0f,0.0f)
	,m_Color(1.0f,1.0f,1.0f,1.0f)
	,m_Radius(5.0f,5.0f,5.0)
	,m_CollisionType(POLYGON_COLLSION_STATIC)
{

}

//==============================================================
//
//	Squreクラス::デストラクタ
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
GamePolygon::~GamePolygon()
{
	Uninit();
}

//==============================================================
//
//	Squreクラス::初期化
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
bool GamePolygon::Init()
{
	//---ポリゴンの作成
	m_pSqure = new Squre();
	m_pSqure->SetPos(m_pos.x, m_pos.y, m_pos.z);				// 初期位置
	m_pSqure->SetSize(m_size.x, m_size.y);						// 初期の大きさ
	m_pSqure->SetAngle(m_Angle.x, m_Angle.y, m_Angle.z);		// 初期角度

	return true;

}

//==============================================================
//
//	Squreクラス::終了
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void GamePolygon::Uninit()
{
	if (m_pSqure != nullptr) {
		delete m_pSqure;
		m_pSqure = nullptr;
	}
}

//==============================================================
//
//	Squreクラス::更新
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void GamePolygon::Update()
{
	//---色の変更があった場合にその色に設定
		if (m_Color.w != 1.0f || m_Color.x != 1.0f || m_Color.y != 1.0f || m_Color.z != 1.0f) {		// 色の変更がかかっている場合更新する
		m_pSqure->SetRGBA(m_Color.x, m_Color.y, m_Color.z, m_Color.w);
		m_pSqure->Update();
	}
}

//==============================================================
//
//	Squreクラス::描画
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
void GamePolygon::Draw()
{
	//---ワールド変換
	SHADER->SetWorld(
		XMMatrixScaling(m_size.x,m_size.y,m_size.z) *
		XMMatrixRotationX(m_Angle.x) * 
		XMMatrixTranslation(m_pos.x,m_pos.y,m_pos.z));

	m_pSqure->Draw();
}

//==============================================================
//
//	Squreクラス::生成
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： 座標、向き、速度
//
//==============================================================
void GamePolygon::CreatPolygon(XMFLOAT3 pos, XMFLOAT3 dir, XMFLOAT3 move)
{
	//---何もしない
}


/* ---------------------------------setter------------------------------------ */
//==============================================================
//
//	Squreクラス::座標設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： XMFLOAT3型
//
//==============================================================
void GamePolygon::SetPos(XMFLOAT3 pos)
{
	m_pos = pos;
}


//==============================================================
//
//	Squreクラス::サイズ設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： XMFLOAT3型
//
//==============================================================
void GamePolygon::SetSize(XMFLOAT3 size)
{
	m_size = size;
}

//==============================================================
//
//	Squreクラス::移動距離の設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： XMFLOAT3型
//
//==============================================================
void GamePolygon::SetMove(XMFLOAT3 move)
{
	m_move = move;

}

//==============================================================
//
//	Squreクラス::角度の設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： XMFLOAT3型
//
//==============================================================
void GamePolygon::SetAngle(XMFLOAT3 angle)
{
	m_Angle = angle;
}

//==============================================================
//
//	Squreクラス::色の設定
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： XMFLOAT3型
//
//==============================================================
void GamePolygon::SeColor(XMFLOAT4 color)
{
	m_Color = color;
}

/* ---------------------------------getter------------------------------------ */
//==============================================================
//
//	Squreクラス::座標取得
//	作成者	： 吉原飛鳥
//	戻り値	： XMFLOAT3
//	引数		： void 
//
//==============================================================
XMFLOAT3 GamePolygon::GetPos()
{
	return m_pos;
}

//==============================================================
//
//	Squreクラス::サイズ設定
//	作成者	： 吉原飛鳥
//	戻り値	： XMFLOAT3
//	引数		： void 
//
//==============================================================
XMFLOAT3 GamePolygon::GetSize()
{
	return m_size;
}

//==============================================================
//
//	Squreクラス::移動速度取得
//	作成者	： 吉原飛鳥
//	戻り値	： XMFLOAT3
//	引数		： void 
//
//==============================================================
XMFLOAT3 GamePolygon::GetMove()
{
	return m_move;
}

//==============================================================
//
//	Squreクラス::境界面取得
//	作成者	： 吉原飛鳥
//	戻り値	： XMFLOAT3
//	引数		： void 
//
//==============================================================
XMFLOAT3 GamePolygon::GetRadius()
{
	return m_Radius;
}

//==============================================================
//
//	Squreクラス::角度取得
//	作成者	： 吉原飛鳥
//	戻り値	： XMFLOAT3
//	引数		： void 
//
//==============================================================
XMFLOAT3 GamePolygon::GetAngle()
{
	return m_Angle;
}

//==============================================================
//
//	Squreクラス::色取得　
//	作成者	： 吉原飛鳥
//	戻り値	： XMFLOAT3
//	引数		： void 
//
//==============================================================
XMFLOAT4 GamePolygon::GetColor()
{
	return m_Color;
}

//==============================================================
//
//	Squreクラス::当たり判定の取得　
//	作成者	： 吉原飛鳥
//	戻り値	： PolygonCollisionType
//	引数		： void 
//
//==============================================================
PolygonCollisionType GamePolygon::GetCollisionType()
{
	return m_CollisionType;
}