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

//↓みことみことみことみことみことみことみことみことみことみことみことみことみこと

//---柵
#define	FENCE			XMFLOAT3(0.0f,1.5f,0.0f),\
						XMFLOAT3(1.45f, 0.7f, 1.45f),\
						LPCSTR("Assets/Model/fence.png"),\
						LPCSTR("Assets/Model/fenceall.fbx")

//---ボール
#define	BALL			XMFLOAT3(5.0f,1.0f,5.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/ball.png"),\
						LPCSTR("Assets/Model/ball.fbx")

//---ブルドーザー
#define BULLDOZER		XMFLOAT3(0.0f,1.0f,0.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/bulldozer.png"),\
						LPCSTR("Assets/Model/bulldozer.fbx")

//---かつての攻撃ピクミン
#define RED_HELMET		XMFLOAT3(10.0f,1.0f,10.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/kougeki_lambert11_BaseColor.png"),\
						LPCSTR("Assets/Model/helmet.fbx")

//---かつての破壊ピクミン
#define BLUE_HELMET		XMFLOAT3(-10.0f,1.0f,10.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/hakai_lambert5_BaseColor.png"),\
						LPCSTR("Assets/Model/helmet2.fbx")

//---ジェンガ
#define	JENGA			XMFLOAT3(-10.0f,1.0f,20.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/jenga.png"),\
						LPCSTR("Assets/Model/jenga1.fbx")


//---クレヨン
#define KUREYON			XMFLOAT3(30.0f,1.0f,-8.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/kureyon.png"),\
						LPCSTR("Assets/Model/kureyon.fbx")

//---ピンクカー
#define PINKCAR			XMFLOAT3(-30.0f,1.0f,0.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/pinkcar.png"),\
						LPCSTR("Assets/Model/pinkcar.fbx")

//---レゴ
#define REGO			XMFLOAT3(0.0f,1.0f,5.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/rego.png"),\
						LPCSTR("Assets/Model/rego.fbx")

//---ルービックキューブ
#define RUBIKCUBE		XMFLOAT3(0.0f,1.0f,10.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/rubikcube.png"),\
						LPCSTR("Assets/Model/rubikcube.fbx")

//---スタンドライト
#define STANDLIGHT		XMFLOAT3(0.0f,1.0f,15.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/standlight.png"),\
						LPCSTR("Assets/Model/standlight.fbx")

//---電車
#define TRAIN			XMFLOAT3(10.0f,1.0f,10.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/train.png"),\
						LPCSTR("Assets/Model/train.fbx")

//---トランプタワー
#define TRUMPTOWER		XMFLOAT3(15.0f,1.0f,10.0f),\
						XMFLOAT3(1.0f, 1.0f,1.0f),\
						LPCSTR("Assets/Model/trumptower.png"),\
						LPCSTR("Assets/Model/trumptower.fbx")

//---ツミキの城
#define TUMIKICASTLE	XMFLOAT3(0.0f,1.5f,25.0f),\
						XMFLOAT3(2.0f, 2.0f,2.0f),\
						LPCSTR("Assets/Model/tumikicastel.png"),\
						LPCSTR("Assets/Model/tumikicastel.fbx")

//上みことみことみことみことみことみことみことみことみことみことみことみことみこと

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
	m_SelectStageNm = SelectStageNum;

	//---ステージオブジェクトの情報
	typedef struct {
		XMFLOAT3 pos;				// 座標
		XMFLOAT3 size;				// 大きさ
		LPCSTR TexPath;			// テクスチャパス
		LPCSTR ModelPath;		// モデルパス
	}StageObjectInfo;
	
	//---ステージ1に配置するオブジェクト
	StageObjectInfo Stage1ObjectSet[] =
	{
		//---(柵)
		FENCE,
	};

	//---ステージ2に配置する
	StageObjectInfo Stage2ObjectSet[] =
	{
		
		BALL,
		BULLDOZER,
		RED_HELMET,
		BLUE_HELMET,
		KUREYON,
		PINKCAR,
		REGO,
		RUBIKCUBE,
		STANDLIGHT,
		TRAIN,
		TUMIKICASTLE,

	};

	switch (m_SelectStageNm)
	{

	case STAGE_1:				// ステージ１

	 	//---最大数を取得
		m_StageObjectNum = sizeof(Stage1ObjectSet) / sizeof(Stage1ObjectSet[0]);

		//---オブジェクトベースのメモリ確保
		m_ppStageObject = new  StageObjectBase * [m_StageObjectNum];

		//オブジェクトの最大数メモリ確保
		for (int i = 0; i < m_StageObjectNum; i++) {
			m_ppStageObject[i] = new StageObjectBase;
			m_ppStageObject[i]->Init();
			m_ppStageObject[i]->CreateStageObject(Stage1ObjectSet[i].pos, Stage1ObjectSet[i].size, Stage1ObjectSet[i].TexPath, Stage1ObjectSet[i].ModelPath);
		}
		break;

	case STAGE_2:				// ステージ2

		//---最大数を取得
		m_StageObjectNum = sizeof(Stage2ObjectSet) / sizeof(Stage2ObjectSet[0]);

		//---オブジェクトベースのメモリ確保
		m_ppStageObject = new  StageObjectBase * [m_StageObjectNum];

		//オブジェクトの最大数メモリ確保
		for (int i = 0; i < m_StageObjectNum; i++) {
			m_ppStageObject[i] = new StageObjectBase;
			m_ppStageObject[i]->Init();
			m_ppStageObject[i]->CreateStageObject(Stage2ObjectSet[i].pos, Stage2ObjectSet[i].size, Stage2ObjectSet[i].TexPath, Stage2ObjectSet[i].ModelPath);
		}
		break;

	case STAGE_3:				// ステージ3

		break;

	default:					// 例外処理
		break;

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
	switch (m_SelectStageNm)
	{
	case STAGE_1:
		// メモリ開放
		for (int i = 0; i < m_StageObjectNum; i++)
		{
			m_ppStageObject[i]->Uninit();
			delete m_ppStageObject[i];
			m_ppStageObject[i] = nullptr;
		}
		delete[] m_ppStageObject;
		m_ppStageObject = nullptr;
		break;

	case STAGE_2:
		// メモリ開放
		for (int i = 0; i < m_StageObjectNum; i++)
		{
			m_ppStageObject[i]->Uninit();
			delete m_ppStageObject[i];
			m_ppStageObject[i] = nullptr;
		}
		delete[] m_ppStageObject;
		m_ppStageObject = nullptr;
		break;

	case STAGE_3:
		break;


	default:
		break;
	}


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

	switch (m_SelectStageNm)
	{
	case STAGE_1:
		// ステージオブジェクトの描画
		for (int i = 0; i < m_StageObjectNum; i++) {
			m_ppStageObject[i]->Draw();
		}
		break;

	case STAGE_2:
		// ステージオブジェクトの描画
		for (int i = 0; i < m_StageObjectNum; i++) {
			m_ppStageObject[i]->Draw();
		}
		break;

	case STAGE_3:
		break;


	default:
		break;
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
