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

#define POSSETTIME	(90)	// 回収終了後からプラスの時間


//====================================================================
//
//		コンストラクタ
//
//====================================================================
CollectionPoint::CollectionPoint()
{
	m_size	= XMFLOAT3(5.0f, 0.0f, 5.0f);


	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 2.0f, 0.0f);	// ランダム
	//----- 乱数で座標を設定 -----
	randomPos.x = (float)(rand() % 18 - 9.0f);	//-9.0 ~ 9.0の間の乱数
	randomPos.z = (float)(rand() % 20 - 10.0f);	//-10.0 ~ 10.0の間の乱数

	m_pos = randomPos;

	m_Radius = XMFLOAT3(2.0f, 0.1f, 2.0f);
	m_Angle	= XMFLOAT3(0, 0, 0);
	m_PosSetTime = POSSETTIME;	
	m_TimerStart = false;

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
	if (m_nowCollectTimer < 1 && !m_TimerStart) {
		m_TimerStart = true;
	}

	if (m_TimerStart) {
		m_PosSetTime--;
	}

	if(m_PosSetTime < 0){
		XMFLOAT3 randomPos = XMFLOAT3(0.0f, 2.0f, 0.0f);	// ランダム
		//----- 乱数で座標を設定 -----
		randomPos.x = (float)(rand() % 18 - 9.0f);	//-9.0 ~ 9.0の間の乱数
		randomPos.z = (float)(rand() % 20 - 10.0f);	//-9.0 ~ 9.0の間の乱数

		m_pos = randomPos;
		m_TimerStart = false;
		m_PosSetTime = POSSETTIME;
	}
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


//====================================================================
//
//		回収中フラグセット
//
//====================================================================
void CollectionPoint::SetNowCollectFlg(bool flg) {
	m_nowCollectFlg = flg;
}


//====================================================================
//
//		回収中タイマーセット
//
//====================================================================
void CollectionPoint::SetnowCollectTimer(int time) {
	m_nowCollectTimer = time;
}



//====================================================================
//
//		ターゲットの座標の取得
//
//====================================================================
XMFLOAT3 CollectionPoint::GetTargetPos() {
	return m_pos;
}

