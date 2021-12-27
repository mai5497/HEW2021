//****************************************************
//
//	回収装置
//	作成者：伊吹汰輝
//	
//	2021/12/21 : 作成
//	2021/12/22 : 移動処理追加
//	2021/12/25 : 定数化 / コメント追記
//	2021/12/26 : モデル変更
//
//****************************************************

//========================= インクルード部 ===========================
#include "Collector.h"
#include "Texture.h"

#define ENEMY_SIZE (0.5f)

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define COLLECTOR_SIZE		(0.3f)
#define FPS					(60)					// フレーム数
#define WAIT_TIME			(10)					// 待機時間

#define START_POS_X			(22.0f)					// 開始地点 X
#define START_POS_Y			(10.0f)					// 開始地点 Y
#define COLLECT_POS_X		(0.0f)					// 回収地点 X
#define COLLECT_POS_Y		(1.0f)					// 回収地点 Y

Collector::Collector()
{
	LoadTextureFromFile("Assets/Model/tyoutingazou.png", &m_pCollectorTex);

//*******************************************************************************
// グローバル宣言
//*******************************************************************************
DrawBuffer* Collector::m_pBuffer = NULL;
FBXPlayer* Collector::m_pfbx = NULL;


//====================================================================
//
//		コンストラクタ
//
//====================================================================
Collector::Collector()
{
	LoadTextureFromFile("Assets/Model/ufo.png", &m_pCollectorTex);

	m_pos = XMFLOAT3(START_POS_X, START_POS_Y, 0.0f);
	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Radius = XMFLOAT3(0.8f, 0.8f, 0.8f);

	m_timer = WAIT_TIME * FPS + 59;
	m_timeFlg = true;
	use = true;

	m_collisionType = COLLISION_DYNAMIC;
}


//====================================================================
//
//		デストラクタ
//
//====================================================================
Collector::~Collector()
{

}

//====================================================================
//
//		FBX読込
//
//====================================================================
bool Collector::LoadFBX(const char* pFilePath)
{
	HRESULT hr;
	m_pfbx = new FBXPlayer;
	hr = m_pfbx->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//モデルのメッシュの数だけ頂点バッファ作成
	int meshNum = m_pfbx->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++)
	{
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
//
//====================================================================
bool Collector::Init()
{
	if (m_pBuffer == NULL)
	{
		Collector::LoadFBX("Assets/Model/tyoutinobake.fbx");
	}
	return true;
}


//====================================================================
//
//		終了処理
//
//====================================================================
void Collector::Uninit()
{
	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pfbx;
		m_pfbx = NULL;
	}
}


//====================================================================
//
//		更新
//
//====================================================================
void Collector::Update()
{
	// アークタンジェント(逆正接)
	m_angle = atan2(m_move.z, m_move.x);
	m_angle -= DirectX::XM_PI * 0.5f;

	if (m_timeFlg) {
		// 一定時間待機
		if (m_timer > 0) {
			m_timer--;
		}
		// 回収地点へ移動
		else {
			m_move.x = -(MOVE_SPEED / FPS);
		}
		if (m_pos.x < COLLECT_POS_X) {
			m_move.x = 0;
			if (m_pos.y > COLLECT_POS_Y) {
				m_move.y = -(MOVE_SPEED / FPS);
			}
			else {
				m_move.y = 0;
				m_timeFlg = false;
				m_timer = WAIT_TIME * FPS + 59;
			}
		}
	}

	if (!m_timeFlg) {
		// 一定時間待機
		if (m_timer > 0) {
			m_timer--;
		}
		// 開始地点へ戻る
		else {
			m_move.y = (MOVE_SPEED / FPS);
		}

		if (m_pos.y > START_POS_Y) {
			m_move.y = 0;
			if (m_pos.x < START_POS_X) {
				m_move.x = (MOVE_SPEED / FPS);
			}
			else {
				m_move.x = 0;
			}
		}
	}

	// 移動
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
}


//====================================================================
//
//		描画
//
//====================================================================
void Collector::Draw()
{
	int meshNum = m_pfbx->GetMeshNum();
	for (int i = 0; i < meshNum; ++i)
	{
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(COLLECTOR_SIZE, COLLECTOR_SIZE, COLLECTOR_SIZE)
			* DirectX::XMMatrixRotationY(-m_angle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pCollectorTex);

		m_pBuffer[i].Draw(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
	}
}

int Collector::GetTimer()
{
	return m_timer;
}
