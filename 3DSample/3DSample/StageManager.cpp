//****************************************************
//
//	ステージ管理
//	作成者：園田翔大
//	
//	2021/12/01 : 作成
//	2022/01/02 : コメント追加（伊地田）
//				 ステージ番号の変数を追加（伊地田）
//
//****************************************************

//========================= インクルード部 ===========================
#include "StageManager.h"
#include "Texture.h"

#define STAGE_SIZE (0.007f)

ID3D11ShaderResourceView *m_pStageTex[3];

DrawBuffer *StageManager::m_pBuffer = NULL;
FBXPlayer *StageManager::m_pfbx = NULL;


//====================================================================
//
//		コンストラクタ
//
//====================================================================
StageManager::StageManager():m_ppStages(NULL),m_nStageNum(0)
{
	//LoadTextureFromFile("Assets/Model/woodground.jpg", &m_pStageTex[0]);
	LoadTextureFromFile("Assets/Model/base1.jpg", &m_pStageTex[0]);
	LoadTextureFromFile("Assets/Model/ground.png", &m_pStageTex[1]);
	LoadTextureFromFile("Assets/Model/base2.jpg", &m_pStageTex[2]);
}


//====================================================================
//
//		デストラクタ
//
//====================================================================
StageManager::~StageManager()
{
	Uninit();
}

bool StageManager::LoadStage(const char* pFilePath) {
	HRESULT hr;
	m_pfbx = new FBXPlayer;
	hr = m_pfbx->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//モデルのメッシュの数だけ頂点バッファ作成
	int meshNum = m_pfbx->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
		//メッシュごとに頂点バッファ作成
		m_pBuffer[i].CreateVertexBuffer(
			m_pfbx->GetVertexData(i),
			m_pfbx->GetVertexSize(i),
			m_pfbx->GetVertexCount(i)
		);
		//インデックスバッファ作成
		m_pBuffer[i].CreateIndexBuffer(
			m_pfbx->GetIndexData(i),
			m_pfbx->GetIndexCount(i)
		);

	}
	return true;
}



//====================================================================
//
//		初期化
//		引数　：選択されたステージ
//		戻り値：初期化できたかどうか
//
//====================================================================
bool StageManager::Init(int SelectStageNum)
{
	//----- メンバ変数初期化 -----
	m_SelectStageNum = SelectStageNum;
	if (m_pBuffer == NULL) {
		LoadStage("Assets/Model/ground2.fbx");
	}



	//----- ステージ設定 -----
	struct StageSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};

	StageSetting settings[] =
	{
		//大きい床
		{ XMFLOAT3(0.0f,-0.5f, 0.0f),
		  XMFLOAT3(50.0f, 1.0f,50.0f),
		},
		//小人のステージ
		{ XMFLOAT3(0.0f,0.5f, 0.0f),
		  XMFLOAT3(0.8f,1.0f,0.8f),
		},
		////右の壁
		//{ XMFLOAT3(12.5f,0.0f,0.0f),
		// XMFLOAT3(2.0f,3.0f,27.0f)
		//},
		////左の壁
		//{ XMFLOAT3(-12.5f,0.0f,0.0f),
		//  XMFLOAT3(2.0f,3.0f,27.0f)
		//},
		////奥の壁
		//{ XMFLOAT3(0.0f,0.0f,12.5f),
		//  XMFLOAT3(27.0f,3.0f,2.0f)
		//},
		////手前の壁
		//{ XMFLOAT3(0.0f,0.0f,-12.5f),
		//  XMFLOAT3(27.0f,3.0f,2.0f)
		//},
		//大きい壁右
		{ XMFLOAT3(25,0.0f,0),
		  XMFLOAT3(1,30,50),
		},

		//大きい壁左
		{ XMFLOAT3(-25,0.0f,0),
		  XMFLOAT3(1,30,50),
		},

		//大きい壁奥
		{ XMFLOAT3(0,0.0f,25),
		  XMFLOAT3(50,30,1),
		},

	};


	//switch (m_SelectStageNum) {
	//	case 1:
	//		settings[1] =
	//		{
	//			//小人のステージ
	//			XMFLOAT3(0.0f,0.5f, 0.0f),
	//			XMFLOAT3(0.8f,0.8f,0.8f),
	//		};
	//		break;
	//	case 2:
	//		settings[1] =
	//		{
	//			//小人のステージ
	//			XMFLOAT3(0.0f,0.5f, 0.0f),
	//			XMFLOAT3(0.5f,0.5f,0.5f),
	//		};
	//		break;
	//	case 3:
	//		settings[1] =
	//		{
	//			//小人のステージ
	//			XMFLOAT3(0.0f,0.5f, 0.0f),
	//			XMFLOAT3(0.6f,0.6f,0.6f),
	//		};
	//		break;
	//	default:
	//		break;
	//}
	//初期データからフィールドの数を計算
	m_nStageNum = sizeof(settings) / sizeof(settings[0]);

	//ポインタを格納する配列を作成
	m_ppStages = new Stage *[m_nStageNum];

	//それぞれの配列にフィールドをメモリ確保
	for (int i = 0; i < m_nStageNum; i++)
	{
		m_ppStages[i] = new Stage(settings[i].size);
		m_ppStages[i]->SetPos(settings[i].pos);
		m_ppStages[i]->Init();

	}
	//※クラスを配列でメモリ確保する場合は
	//既定のコンストラクタ(引数のないコンストラクタ)
	//が必要。どうしても引数付きのコンストラクタを
	//配列で呼び出したいときは、ポインタを格納する
	//配列を確保し、配列一つ一つの要素にメモリ確報を
	//行うことで引数付きのコンストラクタを
	//呼び出すやり方がある。


	return true;
}


//====================================================================
//
//		終了処理
//
//====================================================================
void StageManager::Uninit()
{
	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pfbx;
		m_pfbx = NULL;
	}

	for (int i = 0; i < m_nStageNum; i++) {
		SAFE_RELEASE(m_pStageTex[i]);
	}

	if (m_ppStages != NULL){
		for (int i = 0; i < m_nStageNum; i++){
			//個別に削除
			delete m_ppStages[i];
		}
		//配列を削除
		delete[] m_ppStages;
		m_ppStages = NULL;
	}
}


//====================================================================
//
//		更新処理
//
//====================================================================
void StageManager::Update()
{
	for (int i = 0; i < m_nStageNum; ++i)
	{
		m_ppStages[i]->Update();
	}
}


//====================================================================
//
//		描画処理
//
//====================================================================
void StageManager::Draw()
{
	int meshNum = m_pfbx->GetMeshNum();

	SHADER->SetTexture(m_pStageTex[0]);
	m_ppStages[0]->Draw();

	// 小人のステージ
	for (int j = 0; j < meshNum; ++j) {
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(m_ppStages[1]->GetSize().x, m_ppStages[1]->GetSize().y, m_ppStages[1]->GetSize().z)
			*DirectX::XMMatrixRotationY(XM_PI)
			*DirectX::XMMatrixTranslation(m_ppStages[1]->GetPos().x, m_ppStages[1]->GetPos().y, m_ppStages[1]->GetPos().z));

		SHADER->SetTexture(m_pStageTex[1]);
		m_pBuffer[j].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	SHADER->SetTexture(m_pStageTex[2]);
	m_ppStages[2]->Draw();
	m_ppStages[3]->Draw();
	m_ppStages[4]->Draw();


	SHADER->SetTexture(NULL);




	//for (int i = 0; i < m_nStageNum; ++i)
	//{
	//	m_ppStages[i]->Draw();
	//}
}


//====================================================================
//
//		ステージの取得
//
//====================================================================
Stage *StageManager::GetStage(int index)
{
	if (index < m_nStageNum)
	{
		return m_ppStages[index];
	}
	return NULL;
}

//====================================================================
//
//		何個目のステージかを返す
//
//====================================================================
int StageManager::GetStageNum()
{
	return m_nStageNum;
}

