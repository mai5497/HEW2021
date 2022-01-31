//====================================================================
//
// 青弾[BlueBullet.cpp]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/09	作成
//====================================================================
 
//*******************************************************************************
// インクルード部
//*******************************************************************************
#include	"BulletBlue.h"
#include	"MyVector.h"
#include	"Texture.h"
#include	"Sound.h"

//==============================================================
//
//	BlueBullet::コンストラクタ
// 
//==============================================================
BulletBlue::BulletBlue()
{
	/* モデル読み込み */
	m_pBlueModel = m_pBulletModel[BLUE_BULLET];
	m_pBlueBuffer = m_pBuffer[BLUE_BULLET];

	SetRBFlg(false);	// 青弾
}

//==============================================================
//
//	BlueBullet::デストラクタ
// 
//==============================================================
BulletBlue::~BulletBlue()
{
	Uninit();
}

//====================================================================
//
//	BlueBullet::初期化
//
//====================================================================
bool BulletBlue::Init()
{
	m_AliveTime = BULLET_DESTOROY_CNT;		// 生存時間

	return true;
}


//==============================================================
//
//	BlueBullet::終了処理
// 
//==============================================================
void BulletBlue::Unint()
{

}

//==============================================================
//
//	BlueBullet::更新
// 
//==============================================================
void BulletBlue::Update() {

	// 弾の投擲時間を進める(定数で投げ終わる時間を決めれる)
	m_ThrowTimer += 1.3f / BULLET_THROW_CNT;


	if (m_ThrowTimer <= 1.0f) {

		m_pos.x = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.x + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.x + m_ThrowTimer * m_ThrowTimer * m_EndPos.x;

		m_pos.y = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.y + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.y + m_ThrowTimer * m_ThrowTimer * m_EndPos.y;

		m_pos.z = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.z + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.z + m_ThrowTimer * m_ThrowTimer * m_EndPos.z;
	} else {
		m_ColFlg = true;
	}
	if (m_ColFlg) {
		if (m_AliveTime == BULLET_DESTOROY_CNT) {
			// サウンド
			CSound::Play(SE_BULLET_2);
			//m_pFBX->Play(0);
			m_LandingFlg = true;	// 弾が地面についた瞬間
		} else {
			m_LandingFlg = false;
		}

		// 弾の時間経過での破壊処理
		m_AliveTime--;					// 生存時間のカウントダウン
		//if (m_AliveTime < 25) {
		//	if (!m_pBlueModel->IsPlay()) {
		//		m_pBlueModel->Play(m_flowerAnim[BLUE_BLAST]);
		//	}
		//}
		if (m_AliveTime < 0) {			// 0以下になったら
			use = false;					// 使用フラグを変更
			Uninit();
		}
	}

	//if (m_pBlueModel->IsPlay()) {
	//	m_pBlueModel->Step();
	//}
}

//==============================================================
//
//	RedBullet::描画
// 
//==============================================================
void BulletBlue::Draw()
{
	//SHADER->Bind(VS_ANIMATION,PS_UNLIT);
	//m_pFBX->Step();

	// 弾のテクスチャ
	int meshNum = m_pBlueModel->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			//* DirectX::XMMatrixRotationY(-m_DwarfAngle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		//SHADER->SetAnimation(m_pBlueModel->GetAnimeMatrix(i), m_pBlueModel->GetAnimeMatrixNum(i));
		SHADER->SetTexture(m_pBulletTex[BLUE_BULLET]);

		/*
		SHADER->SetTexture(m_fbx.GetTexture(i));
		*/

		m_pBlueBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}