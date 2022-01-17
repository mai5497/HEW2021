//====================================================================
//
// 弾管理
// 作成者:吉原飛鳥
// 
// 更新日:2021/12/26	作成
//		 :2022/01/10	定数定義の一部をヘッダへ移動(いちだ)
//		 :2022/01/11	サウンド追加
//====================================================================

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"BulletManager.h"
#include	"GameObject.h"
#include	"BulletRed.h"
#include	"BulletBlue.h"
#include	"Input.h"
#include	"Sound.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define BULLET_SPEED		(0.1f)								// 弾の速度

//*******************************************************************************
// グローバル変数
//*******************************************************************************
float g_ThrowTimer = 0.0f;				// 投げる時間


//==============================================================
//
//	BulletManager::コンストラクタ
// 
//==============================================================
BulletManager::BulletManager():m_ppBullets(nullptr),m_BulletNum(MAX_BULLET)
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
	m_ppBullets = new BulletBase * [MAX_BULLET];

	// 弾の最大数分メモリ確保
	for (int i = 0; i < MAX_BULLET; ++i){
		// それぞれの配列に弾をメモリ確保
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
	for (int i = 0; i < MAX_BULLET; i++)
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
	if (IsRelease('E') || IsRelease(JPadButton::X)) {
		rbflg = false;		// 青弾セット
		CSound::Play(SE_BULLET_1);
		CreateBullet(rbflg);

	}

	if (IsRelease('Q') || IsRelease(JPadButton::B)) {
		rbflg = true;		// 赤弾セット
		CSound::Play(SE_BULLET_1);
		CreateBullet(rbflg);
	}

	// 弾の最大数更新処理
	for (int i = 0; i < MAX_BULLET; i++) {
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
	for (int i = 0; i < MAX_BULLET; i++){
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
	for (int i = 0; i < MAX_BULLET; ++i) {
		if (m_ppBullets[i]->use) {
			continue;
		}
		m_ppBullets[i]->SetRBFlg(rbFlg);
		if (rbFlg == true) {	// trueが赤
			m_ppBullets[i] = new BulletRed;
			m_ppBullets[i]->Init();
		}
		else {
			m_ppBullets[i] = new BulletBlue;
			m_ppBullets[i]->Init();
		}
		m_ppBullets[i]->use = true;

		//m_ppBullets[i]->SetPos(m_PlayerPos);


		//XMFLOAT3 dir;		// 射出方向

		//float dirY;			// 打ち出す角度(Y軸方向)
		//dirY = 90.0f;

		////---射出方向
		////dir.x = -(m_PlayerPos.x - m_PlayerAngle.x);
		////dir.y = dirY;
		////dir.z = -(m_PlayerPos.z - m_PlayerAngle.z);

		////---射出方向
		//dir.x = -m_PlayerPos.x;
		//dir.y = dirY / FPS;
		//dir.z = -m_PlayerPos.z;
		// 
		// 
		////ベクトルの大きさ
		//float L;
		//L = sqrtf((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));

		////// dir の長さを1にする(正規化)
		//dir.x = dir.x / L;
		//dir.y = dir.y / L;
		//dir.z = dir.z / L;

		//// 長さが1になったベクトルに移動させたい速度をかける(手裏剣の速度)
		//dir.x = dir.x * BULLET_SPEED;
		//dir.y = dir.y;
		//dir.z = dir.z * BULLET_SPEED;

		////m_ppBullets[i]->SetMove(dir);
		//m_ppBullets[i]->SetMove(dir);

		XMFLOAT3 StartPos = m_PlayerPos;									// 発射地点(プレイヤーの座標)
		XMFLOAT3 EndPos = m_TargetPos;										// 落下地点(ターゲットの座標)

		//---制御点
		XMFLOAT3 CenterPos = XMFLOAT3((StartPos.x + EndPos.x) / 2.0f,		// X座標 ... 発射地点と落下地点の中点
			7.0f,								// Y座標 ... 高さは任意の値
			(StartPos.z + EndPos.z) / 2.0f);	// Z座標 ... 発射地点と落下地点の中点

		XMFLOAT3 CurrentPos;

		g_ThrowTimer = 0.0f;												// 投擲時間をリセット

		////---放物線をベジェ曲線の計算で処理を行う
		// ベジェ曲線で算出した値を各座標に格納
		CurrentPos.x = (1.0f - g_ThrowTimer) * (1.0f - g_ThrowTimer) * StartPos.x +
			2 * (1.0f - g_ThrowTimer) * g_ThrowTimer * CenterPos.x +
			g_ThrowTimer * g_ThrowTimer * EndPos.x;

		CurrentPos.y = (1.0f - g_ThrowTimer) * (1.0f - g_ThrowTimer) * StartPos.y +
			2 * (1.0f - g_ThrowTimer) * g_ThrowTimer * CenterPos.y +
			g_ThrowTimer * g_ThrowTimer * EndPos.y;

		CurrentPos.z = (1.0f - g_ThrowTimer) * (1.0f - g_ThrowTimer) *StartPos.z +
			2 * (1.0f - g_ThrowTimer) * g_ThrowTimer * CenterPos.z +
			g_ThrowTimer * g_ThrowTimer * EndPos.z;

		m_ppBullets[i]->SetPos(CurrentPos);
		m_ppBullets[i]->SetBezierInfo(StartPos, EndPos, CenterPos,g_ThrowTimer);

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
	for (int i = 0; i < MAX_BULLET; ++i)
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
	//m_PlayerAngle = angle;
}

//====================================================================
//
//		弾情報取得
//
//====================================================================
BulletBase* BulletManager::GetBullet(int index) {
	if (index < MAX_BULLET) {
		return m_ppBullets[index];
	}
	return NULL;
}

//==============================================================
//
//	BulletManager::ターゲット座標を設定
//	作成者	: 吉原飛鳥
//	戻り値	: void
//	引数		: XMFLOAT3型
//
//==============================================================
void BulletManager::SetTargetPos(XMFLOAT3 Pos)
{
	m_TargetPos = Pos;
}