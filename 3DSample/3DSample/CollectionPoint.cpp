//****************************************************
//
//	回収地点
//	作成者：伊吹汰輝
//	
//	2021/12/22 : 作成
//	2021/12/26 : コメント追記
//
//****************************************************

//========================= インクルード部 ===========================
#include "CollectionPoint.h"


//====================================================================
//
//		コンストラクタ
//
//====================================================================
CollectionPoint::CollectionPoint()
{
	m_size	= XMFLOAT3(2.5f, 0.1f, 2.5f);
	m_pos	= XMFLOAT3(0.0f, 1.0f, 0.0f);
	m_Angle	= XMFLOAT3(0, 0, 0);

	m_collisionType = COLLISION_STATIC;
}


//====================================================================
//
//		デストラクタ
//
//====================================================================
CollectionPoint::~CollectionPoint()
{
	Uninit();

}
//====================================================================
//
//		初期化
//
//====================================================================
bool CollectionPoint::Init()
{
	GameObject::Init();
	return true;
}


//====================================================================
//
//		終了処理
//
//====================================================================
void CollectionPoint::Uninit()
{
	GameObject::Uninit();

}


//====================================================================
//
//		更新処理
//
//====================================================================
void CollectionPoint::Update()
{


}


//====================================================================
//
//		描画処理
//
//====================================================================
void CollectionPoint::Draw()
{
	//ワールド座標変換
	SHADER->SetWorld(
		XMMatrixScaling(m_size.x, m_size.y, m_size.z)
		* XMMatrixRotationY(m_Angle.y)
		* XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);
	m_pCube->Draw();
}



