//====================================================================
//
// ステージオブジェクト
// 作成者:吉原飛鳥
// 
// 更新日:20212/01/18	作成
//====================================================================

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"StageObjectManager.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define MAX_STAGEOBJECT			(10)

typedef enum
{
	STAGE_1 =1,
	STAGE_2,
	STAGE_3,

	MAX_STAGE
}STAGE_NUMBER;
//==============================================================
//
//	StageObjectManager::コンストラクタ
// 
//==============================================================
StageObjectManager::StageObjectManager()
{

}

//==============================================================
//
//	StageObjectManager::デストラクタ
// 
//==============================================================
StageObjectManager::~StageObjectManager()
{

}

//==============================================================
//
//	StageObjectManager::初期化
// 
//==============================================================
bool StageObjectManager::Init(int SelectStageNum)
{
	//---ステージオブジェクトの情報
	typedef struct {
		XMFLOAT3 pos;				// 座標
		XMFLOAT3 size;				// 大きさ
		LPCSTR TexPath;			// テクスチャパス
		LPCSTR ModelPath;			// モデルパス
	}StageObjectInfo;
	
	StageObjectInfo StageObjectSet[] =
	{
		//---(柵)
		{
			XMFLOAT3(0.0f,1.5f,0.0f),
			XMFLOAT3(0.95f,0.7f,0.95f),
			LPCSTR("Assets/Model/fence.png"),
			LPCSTR("Assets/Model/fenceall.fbx"),
		},
 
		//---(ブルドーザー)
		//{
		//	XMFLOAT3(1.0f,5.0f,3.0f),
		//	XMFLOAT3(1.0f,1.0f,1.0f),
		//	LPCSTR("Assets/Model/bulldozer.png"),
		//	LPCSTR("Assets/Model/bulldozer.fbx"),
		//},
	};

	//switch (m_SelectStageNm)
	//{

	//case STAGE_1:				// ステージ１
	//	break;

	//case STAGE_2:				// ステージ2
	//	break;

	//case STAGE_3:				// ステージ3

	//	break;

	//default:					// 例外処理
	//	break;

	//}


	//---最大数を取得
	m_StageObjectNum = sizeof(StageObjectSet) / sizeof(StageObjectSet[0]);

	//---オブジェクトベースのメモリ確保
	m_ppStageObject = new  StageObjectBase *[m_StageObjectNum];

	// オブジェクトの最大数メモリ確保
	for (int i = 0; i < m_StageObjectNum; i++) {
		m_ppStageObject[i] = new StageObjectBase;
		m_ppStageObject[i]->Init();
		m_ppStageObject[i]->CreateStageObject(StageObjectSet[i].pos, StageObjectSet[i].size, StageObjectSet[i].TexPath, StageObjectSet[i].ModelPath);
	}

	return true;

}

//==============================================================
//
//	StageObjectManager::終了処理
// 
//==============================================================
void StageObjectManager::Uninit() 
{
	// メモリ開放
	for (int i = 0; i < m_StageObjectNum; i++)
	{
		m_ppStageObject[i]->Uninit();
		delete m_ppStageObject[i];
		m_ppStageObject[i] = nullptr;
	}
	delete[] m_ppStageObject;
	m_ppStageObject = nullptr;

}

//==============================================================
//
//	StageObjectManager::更新処理
// 
//==============================================================
void StageObjectManager::Update()
{
	//---とりあえず何もしたいと思いたい(無理だけどね)
}

//==============================================================
//
//	StageObjectManager::更新処理
// 
//==============================================================
void StageObjectManager::Draw()
{
	// ステージオブジェクトの描画
	for (int i = 0; i < m_StageObjectNum; i++){
		m_ppStageObject[i]->Draw();
	}

}

//==============================================================
//
//	ObjectBaseクラス::オブジェクト生成
//	作成者	： 吉原飛鳥
//	戻り値	： void
//	引数		： void
//
//==============================================================
//void StageObjectManager::CreateStageObject(int index, XMFLOAT3 pos, XMFLOAT3 size, LPCSTR TexPath, LPCSTR ModelPath)
//{
//	---座標・サイズの指定
//	m_pos= pos;					
//	m_size = size;
//	m_ppStageObject[index]->SetPos(pos);
//	m_ppStageObject[index]->SetSize(size);
//	m_ppStageObject[index]->GetPos() = pos;
//	m_ppStageObject[index]->GetSize() = size;
//
//	---テクスチャ・モデルの読み込み
//	LoadTextureFromFile(TexPath, &m_ppStageObject[index]->m_pStageObjectTex);			// テクスチャ
//	m_ppStageObject[index]->LoadStageObject(ModelPath);											// モデル
//
//	Init();
//}
