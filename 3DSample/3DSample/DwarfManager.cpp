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
	m_DwarfNum(0)
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
bool DwarfManager::Init(int stagenum) {
	//----- ローカル変数初期化 -----
	int rednum;
	int bluenum;

	if (stagenum == 1) {
		rednum = MAX_RED_DWARF_1;
		bluenum = MAX_BLUE_DWARF_1;
		m_DwarfNum = MAX_DWARF_1;
	} else if (stagenum == 2) {
		rednum = MAX_RED_DWARF_2;
		bluenum = MAX_BLUE_DWARF_2;
		m_DwarfNum = MAX_DWARF_2;
	} else if (stagenum == 3) {
		rednum = MAX_RED_DWARF_3;
		bluenum = MAX_BLUE_DWARF_3;
		m_DwarfNum = MAX_DWARF_3;
	}


	XMFLOAT3 basePos = XMFLOAT3(0.0f, 0.0f, 0.0f);		// 指定した位置付近に配置できる
	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 0.0f, 0.0f);	// ランダム

	srand(time(NULL));

	// ポインタを格納する配列を作成
		
	m_ppDwarf = new DwarfBase*[m_DwarfNum];

	for (int i = 0; i < m_DwarfNum; i++){
		// 小人をランダムで初期配置
		randomPos.x = (float)(rand() % 30 - 15.0f);	//-10.0 ~ 10.0の間の乱数
		randomPos.z = (float)(rand() % 30 - 15.0f);

		// ランダムで算出した値を基準位置に加算して代入
		XMFLOAT3(basePos.x + randomPos.x, 5.0f, basePos.z + randomPos.z);
		// それぞれの配列に小人をメモリ確保
		if (i < rednum) {
			m_ppDwarf[i] = new RedDwarf;
		} else {
			m_ppDwarf[i] = new BlueDwarf;
		}

		m_ppDwarf[i]->TargetPos(XMFLOAT3(basePos.x + randomPos.x, 5.0f, basePos.z + randomPos.z));
		m_ppDwarf[i]->SetPos(XMFLOAT3(basePos.x + randomPos.x, 5.0f, basePos.z + randomPos.z));
		m_ppDwarf[i]->SetSize(XMFLOAT3(DWARF_SIZE, DWARF_SIZE, DWARF_SIZE));
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
	for (int i = 0; i < m_DwarfNum; i++)
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
void DwarfManager::Update() {
	static int Timer;
	Timer--;

	for (int i = 0; i < m_DwarfNum; i++) {
		if (!m_ppDwarf[i]->GetAliveFlg()) {
			return; // 一体でも死んだらゲームオーバーの為
		}
		if (m_ppDwarf[i]->GetCollectionFlg()) {
			continue;
		}

		for (int j = 0; j < MAX_BULLET; j++) {
			if (!m_pBullet->GetBullet(j)->use) {
				continue;
			}
			if (!CollisionSphere(m_ppDwarf[i], m_pBullet->GetBullet(j))) {		// 近くにいなかったら下の処理をしない
				continue;
			}

			if (m_pBullet->GetBullet(j)->GetRBFlg() == m_ppDwarf[i]->GetRBFlg()) {	// 投げた弾と小人の色が同じだったら
				if (m_ppDwarf[i]->GetLiftFlg()) {
					continue;
				}
				//m_ppDwarf[i]->SetMoveFlg(true);		// 移動許可
				m_ppDwarf[i]->SetFollowFlg(true);	// 追跡を始める
				m_ppDwarf[i]->SetrunFlg(false);		// 弾から離れない
			} else {
				if (m_ppDwarf[i]->GetLiftFlg()) {
					continue;
				}
				//m_ppDwarf[i]->SetMoveFlg(false);	// 移動許可しない
				m_ppDwarf[i]->SetFollowFlg(false);	// 追跡しない
				m_ppDwarf[i]->SetrunFlg(true);		// 弾から離れる
			}
		}

		for (int k = i + 1; k < m_DwarfNum; k++) {
			if (CollisionSphere(m_ppDwarf[i], m_ppDwarf[k])) {
				m_ppDwarf[i]->SetColFlg(true);
				m_ppDwarf[k]->SetColFlg(true);
			}
		}

		//if (Timer < 0) {
		//	if (!m_ppDwarf[i]->GetrunFlg() && !m_ppDwarf[i]->GetFollowFlg()) {
		//		m_ppDwarf[i]->SetCircumferenceFlg(true);
		//	}
		//	m_ppDwarf[i]->SetColFlg(false);
		//}
		m_ppDwarf[i]->Update();
	}

	//if (Timer < 0) {
	//	Timer = TARGETSET_TIME;
	//}

}


//====================================================================
//
//		描画処理
//
//====================================================================
void DwarfManager::Draw() 
{
	for (int i = 0; i < m_DwarfNum; i++)
	{
		if (!m_ppDwarf[i]->GetAliveFlg()) {
			return; // 一体でも死んだらゲームオーバーの為
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
	if (index < m_DwarfNum) {
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
//	回収数カウントアップ
//	作成者	: 伊地田真衣
//	戻り値	: void
//	引数	: void
//
//==============================================================
void DwarfManager::AddCollectionSum() 
{
	m_collectionSum++;
}

//==============================================================
//
//	回収数カウントダウン
//	作成者	: 伊地田真衣
//	戻り値	: void
//	引数	: void
//
//==============================================================
void DwarfManager::SubCollectionSum() {
	m_collectionSum--;
}


//==============================================================
//
//	回収数の取得
//	作成者	: 伊地田真衣
//	戻り値	: void
//	引数	: void
//
//==============================================================
int DwarfManager::GetCollectionSum()
{
	return m_collectionSum;
}
