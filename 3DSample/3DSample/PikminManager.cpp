//****************************************************
//
//	ピクミン管理
//	作成者：伊地田真衣
//	
//	2021/12/06 : 作成
//
//****************************************************


//========================= インクルード部 ===========================
#include <time.h>
#include "PikminManager.h"
#include "AttackPikmin.h"
#include "GameObject.h"


//====================================================================
//
//		コンストラクタ
//
//====================================================================
PikminManager::PikminManager() : m_ppPikmin(nullptr),m_pikminNum(MAX_PIKMIN)
{


}

//====================================================================
//
//		デストラクタ
//
//====================================================================
PikminManager::~PikminManager() 
{

}


//====================================================================
//
//		初期化
//
//====================================================================
bool PikminManager::Init() 
{
	struct PikminSetting 
	{
		XMFLOAT3 pos;
	};

	// キャラクターを設置
	PikminSetting AtattckPikminSet[MAX_PIKMIN];

	XMFLOAT3 basePos = XMFLOAT3(0.0f, 0.0f, 0.0f);		// 指定した位置付近に配置できる
	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 0.0f, 0.0f);	// ランダム

	srand(time(NULL));

	// ポインタを格納する配列を作成
	m_ppPikmin = new PikminBase*[MAX_PIKMIN];

	for (int i = 0; i < MAX_PIKMIN; i++) 
	{
		// ピクミンをランダムで初期配置
		randomPos.x = (float)rand() / RAND_MAX - 2.0f; //-2.0 ~ 2.0の間の乱数
		randomPos.z = (float)rand() / RAND_MAX - 2.0f;
		// ランダムで算出した値を基準位置に加算して代入
		AtattckPikminSet[i].pos = XMFLOAT3(basePos.x + randomPos.x, 0.5f, basePos.z + randomPos.z);
		// それぞれの配列にピクミンをメモリ確保
		m_ppPikmin[i] = new AttackPikmin;
		m_ppPikmin[i]->TargetPos(AtattckPikminSet[i].pos);
		m_ppPikmin[i]->SetPos(AtattckPikminSet[i].pos);
		m_ppPikmin[i]->SetSize(XMFLOAT3(1.0f / 2, 1.0f / 2, 1.0f / 2));
		m_ppPikmin[i]->Init();
	}
	return true;
}


//====================================================================
//
//		終了処理
//
//====================================================================
void PikminManager::Uninit() 
{
	for (int i = 0; i < MAX_PIKMIN; i++)
	{
		delete m_ppPikmin[i];
		m_ppPikmin[i] = NULL;
	}
	delete[] m_ppPikmin;
	m_ppPikmin = NULL;

}


//====================================================================
//
//		更新処理
//
//====================================================================
void PikminManager::Update() 
{
	for (int i = 0; i < MAX_PIKMIN; i++) 
	{
		m_ppPikmin[i]->Update();
	}
}


//====================================================================
//
//		描画処理
//
//====================================================================
void PikminManager::Draw() 
{
	for (int i = 0; i < MAX_PIKMIN; i++)
	{
		m_ppPikmin[i]->Draw();
	}

}


//====================================================================
//
//		ピクミン情報取得
//
//====================================================================
PikminBase* PikminManager::GetPikmin(int index) 
{
	if (index < MAX_PIKMIN) {
		return m_ppPikmin[index];
	}
	return NULL;
}

//====================================================================
//
//		ピクミン数取得
//
//====================================================================
int PikminManager::GetPikminNum() 	
{
	return m_pikminNum;
}

//====================================================================
//
//		ピクミン情報取得
//
//====================================================================
void PikminManager::SetPikminTarget(XMFLOAT3 pos) 
{
	for (int i = 0; i < m_pikminNum; i++) 
	{
		m_ppPikmin[i]->TargetPos(pos);
	}
}


