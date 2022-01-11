//****************************************************
//
//	小人管理
//	作成者：伊地田真衣
//	
//	2021/12/06 : 作成
//	2021/12/21 : 青小人を追加
//
//****************************************************


//========================= インクルード部 ===========================
#include <time.h>
#include "DwarfManager.h"
#include "GameObject.h"
#include "RedDwarf.h"
#include "BlueDwarf.h"


//====================================================================
//
//		コンストラクタ
//
//====================================================================
DwarfManager::DwarfManager() : 
	m_ppDwarf(nullptr),
	m_DwarfNum(MAX_DWARF)
{
	m_collectionSum = 0;
}

//====================================================================
//
//		デストラクタ
//
//====================================================================
DwarfManager::~DwarfManager() 
{

}


//====================================================================
//
//		初期化
//
//====================================================================
bool DwarfManager::Init() 
{
	struct DwarfSetting 
	{
		XMFLOAT3 pos;
	};

	// キャラクターを設置
	DwarfSetting DwarfSet[MAX_DWARF];

	XMFLOAT3 basePos = XMFLOAT3(0.0f, 0.0f, 0.0f);		// 指定した位置付近に配置できる
	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 0.0f, 0.0f);	// ランダム

	srand(time(NULL));

	// ポインタを格納する配列を作成
	m_ppDwarf = new DwarfBase*[MAX_DWARF];

	for (int i = 0; i < MAX_DWARF; i++){
		// 小人をランダムで初期配置
		randomPos.x = (float)(rand() % 20 - 10.0f);	//-10.0 ~ 10.0の間の乱数
		randomPos.z = (float)(rand() % 20 - 10.0f);
		// ランダムで算出した値を基準位置に加算して代入
		DwarfSet[i].pos = XMFLOAT3(basePos.x + randomPos.x, 2.0f, basePos.z + randomPos.z);
		// それぞれの配列に小人をメモリ確保
		if (i < MAX_RED_DWARF) {
			m_ppDwarf[i] = new RedDwarf;
		} else {
			m_ppDwarf[i] = new BlueDwarf;
		}

		m_ppDwarf[i]->TargetPos(DwarfSet[i].pos);
		m_ppDwarf[i]->SetPos(DwarfSet[i].pos);
		m_ppDwarf[i]->SetSize(XMFLOAT3(1.0f / 2, 1.0f / 2, 1.0f / 2));
		m_ppDwarf[i]->Init();
	}

	return true;
}


//====================================================================
//
//		終了処理
//
//====================================================================
void DwarfManager::Uninit() 
{
	for (int i = 0; i < MAX_DWARF; i++)
	{
		m_ppDwarf[i]->Uninit();
		delete m_ppDwarf[i];
		m_ppDwarf[i] = NULL;
	}
	delete[] m_ppDwarf;
	m_ppDwarf = NULL;

}


//====================================================================
//
//		更新処理
//
//====================================================================
void DwarfManager::Update() 
{
	for (int i = 0; i < MAX_DWARF; i++) 
	{
		if (!m_ppDwarf[i]->GetAliveFlg()) {
			continue;
			//return // 一体でも死んだらゲームオーバーの為
		}
		if (m_ppDwarf[i]->GetCollectionFlg()) {
			continue;
		}
	
		for (int j = 0; j < MAX_BULLET; j++) 
		{
			if (!CollisionSphere(m_ppDwarf[i], m_pBullet->GetBullet(j))) {		// 近くにいなかったら下の処理をしない
				continue;
			}

			if (m_pBullet->GetBullet(j)->GetRBFlg() == m_ppDwarf[i]->GetRBFlg()) {	// 投げた弾と小人の色が同じだったら
				//m_ppDwarf[i]->SetMoveFlg(true);		// 移動許可
				m_ppDwarf[i]->SetFollowFlg(true);	// 追跡を始める
				m_ppDwarf[i]->SetrunFlg(false);		// 弾から離れない
			} else {
				//m_ppDwarf[i]->SetMoveFlg(false);	// 移動許可しない
				m_ppDwarf[i]->SetFollowFlg(false);	// 追跡しない
				m_ppDwarf[i]->SetrunFlg(true);		// 弾から離れる
			}
		}

		m_ppDwarf[i]->Update();
	}

}


//====================================================================
//
//		描画処理
//
//====================================================================
void DwarfManager::Draw() 
{
	for (int i = 0; i < MAX_DWARF; i++)
	{
		if (!m_ppDwarf[i]->GetAliveFlg()) {
			continue;
			//return // 一体でも死んだらゲームオーバーの為
		}
		if (m_ppDwarf[i]->GetCollectionFlg()) {
			continue;
		}
		m_ppDwarf[i]->Draw();
	}

}


//====================================================================
//
//		小人情報取得
//
//====================================================================
DwarfBase* DwarfManager::GetDwarf(int index) 
{
	if (index < MAX_DWARF) {
		return m_ppDwarf[index];
	}
	return NULL;
}

//====================================================================
//
//		小人数取得
//
//====================================================================
int DwarfManager::GetDwarfNum() 	
{
	return m_DwarfNum;
}

//====================================================================
//
//		ターゲットセット
//
//====================================================================
void DwarfManager::SetAllDwarfTarget(XMFLOAT3 pos) 
{
	for (int i = 0; i < m_DwarfNum; i++) 
	{
		m_ppDwarf[i]->TargetPos(pos);
	}
}

//==============================================================
//
//	弾の情報の取得
//	作成者	: 伊地田真衣
//	戻り値	: void
//	引数	: 弾管理クラスのポインタ
//
//==============================================================
void DwarfManager::SetBulletInfo(BulletManager *pBullet)
{
	m_pBullet = pBullet;
}

//==============================================================
//
//	弾の情報の取得
//	作成者	: 伊地田真衣
//	戻り値	: void
//	引数	: 弾管理クラスのポインタ
//
//==============================================================
void DwarfManager::AddCollectionSum() 
{
	m_collectionSum++;
}


