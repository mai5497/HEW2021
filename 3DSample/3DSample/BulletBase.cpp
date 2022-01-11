//====================================================================
//
// 弾のベース
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/03	作成
//		 :2022/01/11	サウンド追加
//====================================================================

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"BulletBase.h"
#include	"Player.h"
#include	"Sound.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define BULLET_GRAVITY						(0.3f / FPS)
#define BULLET_DESTOROY_CNT			(180)							// 弾が消えるまでの時間

//==============================================================
//
//	BulletBase::コンストラクタ
// 
//==============================================================
BulletBase::BulletBase() : m_rbFlg(true),m_ColFlg(false)
{
	// ---変数初期化	
	m_pos.x = 1000.0f;						//初期座標x
	m_pos.y = 1000.0f;						//初期座標y
	m_pos.z = 1000.0f;						//初期座標z
	m_size.x = 0.25f;
	m_size.y = 0.25f;
	m_size.z = 0.25f;
	m_sleep = 0;
	m_sleep2 = 0;

	m_BulletAngle = 0.0f;								// 角度の初期化
	m_dir = XMFLOAT3(0.0f, 0.0f, 0.0f);			// 向き
	m_AliveTime = BULLET_DESTOROY_CNT;	// 生存時間
}


//==============================================================
//
//	BulletBase::デストラクタ
//
//==============================================================
BulletBase::~BulletBase()
{

}

//==============================================================
//
//	更新処理
//
//==============================================================
void BulletBase::Update()
{
	// 重力追加
	m_move.y -= BULLET_GRAVITY;


	// 弾の時間経過での破壊処理
	m_AliveTime--;					// 生存時間のカウントダウン
	if (m_AliveTime < 0){			// 0
		use = false;					// 使用フラグを変更
	}
	//if (m_ColFlg) {
	if (m_pos.y < 1.0f) {							// 今は高さで判定
		CSound::Play(SE_BULLET_2);

		m_move.x = 0.0f;
		m_move.y = 0.0f;
		m_move.z = 0.0f;

		SetMove(m_move);
	}

	//座標更新
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

}

//==============================================================
//
//	描画処理
//
//==============================================================
void BulletBase::Draw()
{
	/* テクスチャ描画 */
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * 
					DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

	m_pCube->Draw();
}

//=============================================================
//
//	投げた弾が赤か青かセットする
//	作成者	： 伊地田真衣
//	戻り値	： void
//　引数	： 赤か青かセットtrueが赤falseが青
//
//=============================================================
void BulletBase::SetRBFlg(bool flg)
{
	m_rbFlg = flg;
}


//=============================================================
//
//	弾が赤か青か取得
//	作成者	： 伊地田真衣
//	戻り値	： 赤か青かtrueが赤falseが青
//　引数	： void
//
//=============================================================
bool BulletBase::GetRBFlg()
{
	return m_rbFlg;
}

//=============================================================
//
//	当たり判定のセット
//	作成者	： 園田翔大
//	戻り値	： フラグ
//　引数		： なし 
//
//=============================================================
void BulletBase::SetColFlg(bool flg) {
	m_ColFlg = flg;
}