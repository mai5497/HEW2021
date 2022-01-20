//****************************************************
//
//	小人のステージの当たり判定のためのブロックたち
//	作成者：伊地田真衣
//	
//	2022/01/18 : 作成
//
//****************************************************

//========================= インクルード部 ===========================
#include "DwarfStageCollision.h"


//====================================================================
//
//		コンストラクタ
//
//====================================================================
DwarfStageCollision::DwarfStageCollision() {
	
}


//====================================================================
//
//		デストラクタ
//
//====================================================================
DwarfStageCollision::~DwarfStageCollision() {

}


//====================================================================
//
//		初期化
//
//====================================================================
void DwarfStageCollision::Init() {
	//----- 設定 -----
	struct StageSetting {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};

	StageSetting settings[] =
	{
		// 一番上
		{ XMFLOAT3(0.0f,1.0f, 15.5f),
		  XMFLOAT3(19.0f,1.0f,1.0f),
		},
		//上から２番目
		{ XMFLOAT3(0.0f,1.0f, 14.5f),
		  XMFLOAT3(22.0f,1.0f,1.0f),
		},
		//上から3番目
		{ XMFLOAT3(0.0f,1.0f, 13.5f),
		  XMFLOAT3(25.0f,1.0f,1.0f),
		},
		//上から4番目
		{ XMFLOAT3(0.0f,1.0f, 12.0f),
		  XMFLOAT3(31.0f,1.0f,2.0f),
		},
		// 真ん中
		{ XMFLOAT3(0.0f,1.0f,10.0f),
		  XMFLOAT3(35.0f,1.0f,2.0f),
		},
		// 下から４番目
		{ XMFLOAT3(0.0f,1.0f,7.5f),
		  XMFLOAT3(40.0f,1.0f,3.0f),
		},
		// 下から３番目
		{ XMFLOAT3(0.0f,1.0f,4.0f),
		  XMFLOAT3(46.0f,1.0f,4.0f),
		},
		// 下から二番目
		{ XMFLOAT3(0.0f,1.0f,-1.5f),
		  XMFLOAT3(52.0f,1.0f,7.0f),
		},
		//一番下
		{ XMFLOAT3(0.0f, 1.0f, -10.0f),
		  XMFLOAT3(56.0f, 1.0f,10.0f),
		},

	};

	//初期データからフィールドの数を計算
	m_DawarfStageNum = sizeof(settings) / sizeof(settings[0]);

	//ポインタを格納する配列を作成
	m_ppDwarfStageCollision = new GameObject *[m_DawarfStageNum];

	//それぞれの配列にフィールドをメモリ確保
	for (int i = 0; i < m_DawarfStageNum; i++) {
		m_ppDwarfStageCollision[i] = new GameObject;
		m_ppDwarfStageCollision[i]->SetSize(settings[i].size);
		m_ppDwarfStageCollision[i]->SetPos(settings[i].pos);
		m_ppDwarfStageCollision[i]->Init();
	}
}


//====================================================================
//
//		終了処理
//
//====================================================================
void DwarfStageCollision::Uninit() {
	if (m_ppDwarfStageCollision != NULL) {
		for (int i = 0; i < m_DawarfStageNum; i++) {
			//個別に削除
			delete m_ppDwarfStageCollision[i];
		}
		//配列を削除
		delete[] m_ppDwarfStageCollision;
		m_ppDwarfStageCollision = NULL;
	}
}



//====================================================================
//
//		描画処理
//
//====================================================================
void DwarfStageCollision::Draw() {
	for (int i = 0; i < m_DawarfStageNum; ++i) {
		m_ppDwarfStageCollision[i]->Draw();
	}
}

//====================================================================
//
//		小人の当たり判定のステージ取得
//
//====================================================================
GameObject* DwarfStageCollision::GetDwarfStageCollision(int num) {
	if (num < m_DawarfStageNum) {
		return m_ppDwarfStageCollision[num];
	}
	return nullptr;
}

//====================================================================
//
//		箱がいくつあるかを返す
//
//====================================================================
int DwarfStageCollision::GetStageNum() {
	return m_DawarfStageNum;
}
