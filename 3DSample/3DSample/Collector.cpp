//****************************************************
//
//	回収装置
//	作成者：伊吹汰輝
//	
//	2021/12/21 : 作成
//	2021/12/22 : 移動処理追加
//	2021/12/25 : 定数化 / コメント追記
//	2021/12/26 : モデル変更
// 2022/01/17 : 仕様変更
//****************************************************

//========================= インクルード部 ===========================
#include "Collector.h"
#include "Texture.h"
#include "Sound.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define COLLECTOR_SIZE		(1.0f)
#define FPS					(60)					// フレーム数
#define START_WAIT_TIME			(5)					// 待機時間
#define COLLECT_WAIT_TIME			(2)					// 待機時間

#define START_POS_X			(46.0f)					// 開始地点 X
#define START_POS_Z			(26.0f)					// 開始地点 
#define START_POS_Y			(17.0f)					// 開始地点 Y
#define COLLECT_POS_X		(0.0f)					// 回収地点 X
#define COLLECT_POS_Y		(1.0f)					// 回収地点 Y

#define MOVE_SPEED			(1.5f)					// 移動速度


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

	m_pos = XMFLOAT3(START_POS_X, START_POS_Y, START_POS_Z);
	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Radius = XMFLOAT3(5.0f, 0.1f, 5.0f);

	m_nowCollectTimer = COLLECT_WAIT_TIME * FPS + 59;
	m_timer = START_WAIT_TIME * FPS + 59;
	m_collectFlg = true;
	use = true;
	m_nowCollectFlg = false;

	m_moveFlg = false;

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
		Collector::LoadFBX("Assets/Model/ufo.fbx");
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
	SAFE_RELEASE(m_pCollectorTex);
}


//====================================================================
//
//		更新
//
//====================================================================
void Collector::Update()
{
	XMFLOAT3 targetpos;

	//----- 回収中待機タイマーカウントダウン -----
	if (m_nowCollectFlg) {
		m_nowCollectTimer--;
	}

	//----- 回収へ向かう -----
	if (m_collectFlg) {
		// 一定時間待機
		if (m_timer > 0) {
			m_timer--;	// スタートからの待機タイマーカウントダウン
		} else {
			m_moveFlg = true;	// 移動許可フラグを立てる
		}
		if (m_moveFlg) {
			// 追従するターゲットの座標
			targetpos = XMFLOAT3(m_targetPos.x, START_POS_Y, m_targetPos.z);	// Yは移動させないからスタート突っ込んでる
			if (m_pos.x <= targetpos.x && m_pos.z <= targetpos.z) {	// 目的地に到着
				m_nowCollectFlg = true;	// 回収中フラグを立てる
				m_moveFlg = false;		// 移動許可を下す（おろしておくと回収車がぷるぷるしない）
				if (m_nowCollectTimer < 0) {	// 回収中のタイマーが０
					m_moveFlg = true;							// 移動許可を立てる
					m_collectFlg = false;						// 帰還にうつるのでfalse
					m_nowCollectFlg = false;					// 回収中のフラグを下す
					m_nowCollectTimer = COLLECT_WAIT_TIME * FPS + 59;	// 回収中タイマーの初期化
				}
			}
		}
	} 

	//----- 帰還する -----
	if (!m_collectFlg) {
		if(m_pos.x <= START_POS_X && m_pos.z <= START_POS_Z){	// スタート位置に帰っていなかったら
			targetpos = m_targetPos = XMFLOAT3(START_POS_X, START_POS_Y, START_POS_Z);	// 追従するターゲットの座標
		} else {
			m_moveFlg = false;				// 移動許可をおろす
			m_collectFlg = true;			// 次は回収に向かうのでture
			m_timer = START_WAIT_TIME * FPS + 59;	// スタート位置での待機タイマーの初期化
		}
	}

	XMVECTOR m_vTarget = XMLoadFloat3(&targetpos);
	// 今の座標
	XMVECTOR vCollectorPos = XMLoadFloat3(&m_pos);
	// 進行方向							　　↓ベクトルの引き算
	XMVECTOR vDirection = XMVectorSubtract(m_vTarget, vCollectorPos);
	// 一定の速度にするために正規化
	// 速度を変えるならvDirectonに速度をかける。
	vDirection = XMVector3Normalize(vDirection);
	// かける関数								  ↓かける数
	if (m_collectFlg) {
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * 14);
	} else {
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * 28);
	}
	// Float3型に変換
	XMStoreFloat3(&m_move, vDirection);


	// アークタンジェント(逆正接)
	m_angle = atan2(m_move.z, m_move.x);
	m_angle -= DirectX::XM_PI * 0.5f;



	if (m_moveFlg) {
		// 移動
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
		m_pos.z += m_move.z;
	}
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

	SHADER->SetTexture(NULL);
}

int Collector::GetTimer()
{
	return m_timer;
}


//====================================================================
//
//		回収中タイムの取得
//
//====================================================================
int Collector::GetnowCollectTimer() {
	return m_nowCollectTimer;
}



//====================================================================
//
//		回収中フラグの取得
//
//====================================================================
bool Collector::GetNowCollectFlg() {
	return m_nowCollectFlg;
}


//====================================================================
//
//		回収場所の保存
//
//====================================================================
void Collector::SetTargetPos(XMFLOAT3 pos) {
	m_targetPos = pos;
}