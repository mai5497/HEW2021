//====================================================================
//
// 板ポリゴン[GamePolygon.h]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/23	作成
//====================================================================

/* -----------------インクルードガード------------------ */
#pragma once

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	<DirectXMath.h>
#include	"Squre.h"
#include	"Shader.h"

//*******************************************************************************
// 名前空間
//*******************************************************************************
using namespace DirectX;


//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************	

enum PolygonCollisionType {
	POLYGON_COLLSION_STATIC,			
	POLYGON_COLLSION_DYNAMIC,
	POLYGON_COLLISIOM_OVERLAP,
};

//*******************************************************************************
// クラス定義
//*******************************************************************************
class GamePolygon
{
public:
	GamePolygon();
	virtual ~GamePolygon();

	//---関数
	virtual bool Init();
	virtual void Uninit();
	virtual void Update();
	virtual void Draw();

	virtual void OnCollision(GamePolygon*) {}
	virtual void CreatPolygon(XMFLOAT3 pos, XMFLOAT3 dir, XMFLOAT3 move);

	//---値設定
	void SetPos(XMFLOAT3 pos);
	void SetSize(XMFLOAT3 size);
	void SetMove(XMFLOAT3 move);
	void SetAngle(XMFLOAT3 angle);
	void SeColor(XMFLOAT4 color);

	//---値取得
	XMFLOAT3 GetPos();
	XMFLOAT3 GetSize();
	XMFLOAT3 GetMove();
	XMFLOAT3 GetRadius();
	XMFLOAT3 GetAngle();
	XMFLOAT4 GetColor();
	PolygonCollisionType GetCollisionType();
	

private:
	//---変数
	XMFLOAT3 m_pos;			// 座標
	XMFLOAT3 m_size;		// サイズ
	XMFLOAT3 m_move;		// 速度
	XMFLOAT3 m_Angle;		// 角度
	XMFLOAT4 m_Color;		// 色
	XMFLOAT3 m_Radius;		// 半径

	Squre *m_pSqure;									// スクエアのポインタ情報
	PolygonCollisionType m_CollisionType;		// 当たり判定の種類

};

