//========================= インクルード部 ===========================
#include "Stage.h"
#include "Texture.h"


//========================= グローバル変数定義 ===========================
//DrawBuffer *Stage::m_pBuffer = NULL;
//FBXPlayer *Stage::m_pFBX = NULL;

static LPCSTR g_TexName[MODEL_MAX] = {
	"Assets/Model/base1.png",
	"Assets/Model/ground.png",
	"Assets/Model/ground.png",
	"Assets/Model/ground.png",
	"Assets/Model/ground.png",
	"Assets/Model/ground.png",
};

static LPCSTR g_ModelName[MODEL_MAX] = {
	"Assets/Model/base1.fbx",
	"Assets/Model/ground.fbx",
	"Assets/Model/ground.fbx",
	"Assets/Model/ground.fbx",
	"Assets/Model/ground.fbx",
	"Assets/Model/ground.fbx",
};



Stage::Stage():m_ppFields(NULL),m_nFieldNum(0)
{
	for (int i = 0; i < MODEL_MAX; i++) {
		LoadTextureFromFile(g_TexName[i], &m_pStageTex[i]);
	}
}
Stage::~Stage()
{
	Uninit();
}

bool Stage::Init()
{

	struct FieldSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};

	FieldSetting settings[] =
	{
		//大きい床
		{ DirectX::XMFLOAT3(0,-0.5f,0),
		  DirectX::XMFLOAT3(50,1,50),
		},
		//小人のステージ
		{ DirectX::XMFLOAT3(0,0.5f,0),
		 DirectX::XMFLOAT3(13,1,13),
		},
		//右の壁
		{DirectX::XMFLOAT3(10,-0.5f,0),
		DirectX::XMFLOAT3(2.5f,3,20)},
		//左の壁
		{DirectX::XMFLOAT3(-10,-0.5f,0),
		DirectX::XMFLOAT3(2.5f,3,20) },
		//奥の壁
		{DirectX::XMFLOAT3(0,-0.5f,10),
		DirectX::XMFLOAT3(22.5,3,2.5f)},
		//手前の壁
		{DirectX::XMFLOAT3(0,-0.5f,-10),
		DirectX::XMFLOAT3(22.5,3,2.5f)}
	};

	//初期データからフィールドの数を計算
	m_nFieldNum = sizeof(settings) / sizeof(settings[0]);

	//ポインタを格納する配列を作成
	m_ppFields = new FieldManager *[m_nFieldNum];

	//それぞれの配列にフィールドをメモリ確保
	for (int i = 0; i < m_nFieldNum; i++)
	{
		Stage::LoadStage(g_ModelName[i], i);
		m_ppFields[i] = new FieldManager(settings[i].size);
		m_ppFields[i]->SetPos(settings[i].pos);
		m_ppFields[i]->Init();
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


void Stage::Uninit()
{
	delete[] m_pBuffer;
	m_pBuffer = NULL;
	for (int i = 0; i < MODEL_MAX; i++) {
		delete[] m_pFBX;
	}
	m_pFBX = NULL;


	if (m_ppFields != NULL){
		for (int i = 0; i < m_nFieldNum; i++){
			//個別に削除
			delete m_ppFields[i];
		}
		//配列を削除
		delete[] m_ppFields;
		m_ppFields = NULL;
	}
}


void Stage::Update()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Update();
	}
}


void Stage::Draw()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Draw();
	}
}


FieldManager *Stage::GetField(int index)
{
	if (index < m_nFieldNum)
	{
		return m_ppFields[index];
	}
	return NULL;
}


int Stage::GetFieldNum()
{
	return m_nFieldNum;
}


//====================================================================
//
//		テクスチャ読み込み
//
//====================================================================
bool Stage::LoadStage(const char* pFilePath,int num) {
	/* 以下はモデルが来たら使用 */
	HRESULT hr;
	m_pFBX[num] = new FBXPlayer;
	hr = m_pFBX[num]->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//モデルのメッシュの数だけ頂点バッファ作成
	int meshNum = m_pFBX[num]->GetMeshNum();
	m_pBuffer[num] = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
		//メッシュごとに頂点バッファ作成
		m_pBuffer[num][i].CreateVertexBuffer(
			m_pFBX[num]->GetVertexData(i),
			m_pFBX[num]->GetVertexSize(i),
			m_pFBX[num]->GetVertexCount(i)
		);
		//インデックスバッファ作成
		m_pBuffer[num][i].CreateIndexBuffer(
			m_pFBX[num]->GetIndexData(i),
			m_pFBX[num]->GetIndexCount(i)
		);

	}
	return true;
}
