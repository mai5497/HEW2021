//====================================================================
//
// 弾管理
// 作成者:吉原飛鳥
// 
// 更新日:2021/12/26	作成
//====================================================================

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"BulletManager.h"
#include	"GameObject.h"
#include	"BulletRed.h"
#include	"BulletBlue.h"
#include	"Input.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define	MAX_RED_BULLET		(5)									// 赤弾の最大値
#define	MAX_BLUE_BULLET		(5)									// 青弾の最大値
#define	MAX_BULET			(MAX_RED_BULLET + MAX_BLUE_BULLET)	// 弾の最大値(赤弾 + 青弾)
#define BULLET_SPEED		(0.5f)								// 弾の速度

//==============================================================
//
//	BulletManager::コンストラクタ
// 
//==============================================================
BulletManager::BulletManager():m_ppBullets(nullptr),m_BulletNum(MAX_BULET)
{

}

//==============================================================
//
//	BulletManager::デストラクタ
// 
//==============================================================
BulletManager::~BulletManager()
{

}

//==============================================================
//
//	初期化処理
// 
//==============================================================
bool BulletManager::Init()
{
	/* ---弾の情報の構造体---- */
	typedef struct
	{
		XMFLOAT3 pos;
	}BulletSettings;

	// 弾の初期化...BulletBaseのコンストラクタで行うためここではとりあえず行わない。-2021/01/09時点

	// ポインタを格納する配列を作成
	m_ppBullets = new BulletBase * [MAX_BULET];

	// 弾の最大数分メモリ確保
	for (int i = 0; i < MAX_BULET; ++i){
		// それぞれの配列に小人をメモリ確保
		if (i < MAX_RED_BULLET){						// 赤弾のメモリ確保
			m_ppBullets[i] = new BulletRed;
		}else{											// 青弾のメモリ確保
			m_ppBullets[i] = new BulletBlue;

		}

		m_ppBullets[i]->Init();
	}

	return true;
}

//==============================================================
//
//	終了処理
// 
//==============================================================
void BulletManager::Uninit()
{
	// 弾の最大数メモリ開放
	for (int i = 0; i < MAX_BULET; i++)
	{
		m_ppBullets[i]->Uninit();
		delete m_ppBullets[i];
		m_ppBullets[i] = NULL;
	}
	delete[] m_ppBullets;
	m_ppBullets = NULL;
}
//==============================================================
//
//	更新処理
// 
//==============================================================
void BulletManager::Update()
{
	static bool rbflg;

	if (IsPress('E')){		
		rbflg = false;		// 青弾セット
	}
	if (IsPress('Q')) {
		rbflg = true;		// 赤弾セット
	}
	if (IsTrigger('Z')) {
		CreateBullet(rbflg);
	}
	// 弾の最大数更新処理
	for (int i = 0; i < MAX_BULET; i++) {
		if (!m_ppBullets[i]->use) {
			continue;
		}
		m_ppBullets[i]->Update();
	}
}

//==============================================================
//
//	描画処理
// 
//==============================================================
void BulletManager::Draw()
{
	//　弾の最大数描画処理
	for (int i = 0; i < MAX_BULET; i++){
		if (!m_ppBullets[i]->use){
			continue;
		}
		m_ppBullets[i]->Draw();

	}
}


//==============================================================
//
//	BulletManager::弾を生成する処理(プレイヤー座標を元に)
//	作成者	： 園田翔大
//	編集者	： 伊地田真衣
//	戻り値	： void
//	引数		： 色判定
//
//==============================================================
void BulletManager::CreateBullet(bool rbFlg)
{
	for (int i = 0; i < MAX_BULET; ++i) {
		if (m_ppBullets[i]->use) {
			continue;
		}
		m_ppBullets[i]->use = true;
		m_ppBullets[i]->SetRBFlg(rbFlg);
		if (m_ppBullets[i]->GetRBFlg()) {	// trueが赤
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 0.5f));	// 赤をセット
		}
		else {
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 0.5f));	// 青をセット
		}

		m_ppBullets[i]->SetPos(m_PlayerPos);
		XMFLOAT3 dir;


		float dirY;
		dirY = 30.0f / FPS;

		dir.x = -(m_PlayerPos.x - m_PlayerAngle.x);
		dir.y = dirY;
		dir.z = -(m_PlayerPos.z - m_PlayerAngle.z);

		//ベクトルの大きさ
		float L;
		L = sqrtf((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));

		//// dir の長さを1にする(正規化)
		dir.x = dir.x / L;
		dir.y = dir.y / L;
		dir.z = dir.z / L;

		// 長さが1になったベクトルに移動させたい速度をかける(手裏剣の速度)
		dir.x = dir.x * BULLET_SPEED;
		dir.y = dir.y * BULLET_SPEED;
		dir.z = dir.z * BULLET_SPEED;

		//m_ppBullets[i]->SetMove(dir);
		m_ppBullets[i]->SetMove(dir);
		break;
	}
}


//==============================================================
//
//	BulletManager::弾を破壊する処理
//	作成者	: 園田翔大
//	戻り値	: void
//	引数		: void
//
//==============================================================
void BulletManager::DestroyBullet()
{
	for (int i = 0; i < MAX_BULET; ++i)
	{
		if (!m_ppBullets[i]->use)
		{
			continue;
		}
		m_ppBullets[i]->use = false;
		break;
	}
	
}

//==============================================================
//
//	BulletManager::プレイヤーの座標を設定
//	作成者	: 伊地田真衣
//	戻り値	: void
//	引数		: XMFLOAT3型
//
//==============================================================
void BulletManager::SetPlayePos(XMFLOAT3 pos)
{
	m_PlayerPos = pos;
}

//==============================================================
//
//	BulletManager::プレイヤーの角度を設定
//	作成者	: 伊地田真衣
//	戻り値	: void
//	引数		: XMFLOAT3型
//
//==============================================================
void BulletManager::SetPlayerAngle(XMFLOAT3 angle)
{
	m_PlayerAngle = angle;
}