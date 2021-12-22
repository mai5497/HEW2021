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
DwarfManager::DwarfManager() : m_ppDwarf(nullptr),m_DwarfNum(MAX_DWARF)
{


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
		randomPos.x = (float)(rand() % 80 - 40.0f);	//-40.0 ~ 40.0の間の乱数
		randomPos.z = (float)(rand() % 80 - 40.0f);
		// ランダムで算出した値を基準位置に加算して代入
		DwarfSet[i].pos = XMFLOAT3(basePos.x + randomPos.x, 0.5f, basePos.z + randomPos.z);
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
//		小人情報取得
//
//====================================================================
void DwarfManager::SetDwarfTarget(XMFLOAT3 pos) 
{
	for (int i = 0; i < m_DwarfNum; i++) 
	{
		m_ppDwarf[i]->TargetPos(pos);
	}
}


