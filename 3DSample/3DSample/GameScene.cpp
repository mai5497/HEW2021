/**
 * @file GameScene.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成(園田)
 *		 2021/12/03 ピクミン追加(伊地田)
 *		 2021/12/09 エネミーが球に追跡するのを削除(濱口)
 *		 2021/12/11 弾の追跡の処理の変更（ピクミンが来て、攻撃を始める）(伊地田)
 *					敵の追跡の処理の変更（ピクミンに当たったら消える）(伊地田)
 *		 2021/12/17 ぷっしゅてすと(伊地田)
 *		 2021/12/17 ぷっしゅ(吉原)
 *		 2021/12/25 小人フィールドから落ちる(伊地田)
 *		 2021/12/25 整理！(吉原)
 *		 2022/01/02 ステージ選択できるようにした（伊地田）
 *		 2022/01/10 バレットの使用変更～(吉原)
 *  	 2022/01/16 バレットの落下地点のオブジェクト追加(吉原)
 *		 2022/01/17 ゲームオーバークリアが同時に出るのなおした（伊地田）
 *		 2022/01/18 ステージのオブジェクトの配置(吉原)
 *		 2022/01/20 小人挙動いじった（伊地田）
 *		 2022/01/21 回収いじった（伊地田）
 *
 * @brief ゲームシーンに関する処理
 */

//*******************************************************************************
// インクルード部
//*******************************************************************************

//---システム関連
#include "Camera.h"
#include "Input.h"
#include "TPSCamera.h"
#include "Collision.h"
#include "Shader.h"
#include "Defines.h"

// ---シーン関連
#include "GameScene.h"
#include "SelectScene.h"
#include "Clear.h"
#include "GameOver.h"


// ---ステージ関連
#include "Stage.h"
#include "StageObjectManager.h"

// ---ゲーム関連-プレイヤー
#include "Player.h"
#include "GameObject.h"

// ---ゲーム関連-エネミー
#include "Enemy.h"
#include "EnemyManager.h"

// ---ゲーム関連-小人
#include "DwarfManager.h"
#include "DwarfStageCollision.h"

// ---ゲーム関連-弾
#include "BulletManager.h"
#include "BulletTarget.h"

// ---ゲーム関連-回収
#include "Collector.h"
#include "CollectionPoint.h"

// ---ゲーム関連-UI
#include "Tutorial.h"
#include "Score.h"
#include "Timer.h"


//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define CONTROL_NUM		(5)
#define RECORD_MARGIN	(10)


//*******************************************************************************
// グローバル宣言
//*******************************************************************************
Camera				*g_pCamera;
//TPSCamera			*g_pTPSCamera;
Player				*g_pPlayer;
GamePolygon			*g_pPolygon;

StageManager		*g_pStageManager;
StageObjectManager* g_pStageObjectManager;

Collision			*g_pCollision;
Collector			*g_pCollector;
CollectionPoint		*g_pCollectionPoint;
SelectScene			*g_pSelectScene;
DwarfManager		*g_pDwarfManager;
DwarfStageCollision	*g_pDwarfStageCollision;

BulletManager		*g_pBulletManger;
BulletTarget			* g_pBulletTarget;

Tutorial			*g_pTutorial;
Score				*g_pScore;
Timer*				g_pTimer;

Shadow				*g_pShadow;

//Enemy				*g_pEnemy;
//EnemyManager		*g_pEnemyManager;

XMFLOAT3 g_recPlayerPos;
XMFLOAT3 g_recBulletPos;
XMFLOAT3 g_recordPos[CONTROL_NUM * RECORD_MARGIN];

int g_LastBulletNun = -1;
BulletBase *g_pBullet[MAX_BULLET];

//==============================================================
//
//	GameSceneクラス::コンストラクタ
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
GameScene::GameScene(void)
{

}

//==============================================================
//
//	GameSceneクラス::デストラクタ
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
GameScene::~GameScene(void)
{

}

//==============================================================
//
//	GameSceneクラス::Init
//	作成者	： 園田翔大
//	戻り値	： void
//	引数	： void
//
//==============================================================
void GameScene::Init(int StageNum)
{

	//---カメラ
	g_pCamera = new Camera();
	g_pCamera->Init();

	//---ポリゴンクラス
	g_pPolygon = new GamePolygon;
	g_pPolygon->Init();

	//---影
	g_pShadow = new Shadow;
	g_pShadow->Init();

	// メンバ変数初期化
	m_StageNum = StageNum;					// 現在のステージ番号保存
	m_NextStageNum = m_StageNum;			// 次のステージ番号保存（現在と次が一致しなかった場合次のステージへ移行）
	m_IsClear = false;						// クリアフラグ
	m_IsGameOver = false;					// ゲームオーバーフラグ
	
	// 弾の管理クラス
	g_pBulletManger = new BulletManager();
	g_pBulletManger->Init();

	// 弾の落下地点クラス
	g_pBulletTarget = new BulletTarget();
	g_pBulletTarget->Init();

	// 小人管理クラス実体化
	g_pDwarfManager = new DwarfManager();
	g_pDwarfManager->Init(StageNum);

	// 小人のステージの当たり判定用のブロックたち初期化
	g_pDwarfStageCollision = new DwarfStageCollision();
	g_pDwarfStageCollision->Init();

	// プレイヤークラス実体化
	g_pPlayer = new Player();
	g_pPlayer->Init();
	
	// TPSカメラはプレイヤーより後
	//g_pTPSCamera = new TPSCamera();
	//g_pTPSCamera->SetTargetObj(g_pPlayer);
	//g_pTPSCamera->Init(XMFLOAT3(0, 12.0f, -22.5f));

	//g_pPlayer->SetControllCamera(g_pTPSCamera);
	//g_pPlayer->GetCameraPos(g_pTPSCamera);

	// 回収ポイント
	g_pCollectionPoint = new CollectionPoint();
	g_pCollectionPoint->Init(StageNum);
	
	// 回収車
	g_pCollector = new Collector();
	g_pCollector->Init();
	g_pCollector->SetTargetPos(g_pCollectionPoint->GetTargetPos());


	// 敵クラス実体化
	//g_pEnemy = new Enemy();
	//g_pEnemy->LoadEnemy("Assets/Model/tyoutinobake.fbx");
	//g_pEnemy->Init();

	// 敵の管理クラスの実体
	//g_pEnemyManager = new EnemyManager();
	//g_pEnemyManager->Init();

	// ステージクラスの実体化
	g_pStageManager = new StageManager();
	g_pStageManager->Init(StageNum);

	// ステージオブジェクトの実体化
	g_pStageObjectManager = new StageObjectManager;
	g_pStageObjectManager->Init(StageNum);

	
	// 当たり判定クラス
	g_pCollision = new Collision();
	g_pCollision->Init();

	// チュートリアルクラス
	g_pTutorial = new Tutorial();
	g_pTutorial->Init();

	// スコアクラス
	g_pScore = new Score();
	g_pScore->Init();

	// タイマークラス
	g_pTimer = new Timer();
	g_pTimer->Init();


	// ゲームクリア初期化
	InitClear();

	// ゲームオーバー初期化
	InitGameOver();

	// 当たり判定配列にデータを入れる
	for (int i = 0; i < g_pDwarfManager->GetDwarfNum(); i++) {
		for (int j = 0; j < g_pDwarfStageCollision->GetStageNum(); j++) {
			g_pCollision->Register(g_pDwarfManager->GetDwarf(i), g_pDwarfStageCollision->GetDwarfStageCollision(j));
		}
		for (int k = i+1; k < g_pDwarfManager->GetDwarfNum(); k++) {
			g_pCollision->Register(g_pDwarfManager->GetDwarf(i), g_pDwarfManager->GetDwarf(k));
		}
	}


	// BGM再生
	CSound::Play(GAME_BGM);
}

//==============================================================
//
//	GameSceneクラス::Uninit
//	作成者	： 園田翔大
//	戻り値	： void
//	引数	： void
//
//==============================================================
void GameScene::Uninit()
{
	// ポリゴン
	g_pPolygon->Uninit();
	delete g_pPolygon;

	// 影
	g_pShadow->Uninit();
	delete g_pShadow;

	// タイマークラスの終了処理
	g_pTimer->Uninit();
	delete g_pTimer;

	// スコアクラスの終了処理
	g_pScore->Uninit();
	delete g_pScore;

	// チュートリアルシーンの終了処理
	g_pTutorial->Uninit();
	delete g_pTutorial;

	// 当たり判定クラスの終了処理
	g_pCollision->Uninit();
	delete g_pCollision;

	// ステージクラスの終了処理
	g_pStageManager->Uninit();
	delete g_pStageManager;

	// ステージオブジェクトの終了処理
	g_pStageObjectManager->Uninit();
	delete g_pStageObjectManager;

	//プレイヤーの終了処理
	g_pPlayer->Uninit();
	delete g_pPlayer;

	// 小人のステージの当たり判定終了
	g_pDwarfStageCollision->Uninit();
	delete g_pDwarfStageCollision;

	// 小人終了処理
	g_pDwarfManager->Uninit();
	delete g_pDwarfManager;

	// 弾のクラス解放
	g_pBulletManger->Uninit();
	delete g_pBulletManger;

	// 弾の落下地点クラス解放
	g_pBulletTarget->Uninit();
	delete g_pBulletTarget;

	// 回収ポイント
	g_pCollectionPoint->Uninit();
	delete g_pCollectionPoint;
	
	// 回収者
	g_pCollector->Uninit();
	delete g_pCollector;

	// エネミー終了処理
	//delete g_pEnemy;

	// カメラ類終了
	g_pCamera->Uninit();
	delete g_pCamera;
	//g_pTPSCamera->Uninit();
	//delete g_pTPSCamera;

	// ゲームクリア終了
	UninitClear();

	// ゲームオーバー終了
	UninitGameOver();

	// BGM停止
	CSound::Stop(GAME_BGM);
}

//==============================================================
//
//	GameSceneクラス::Update
//	作成者	： 園田翔大
//	戻り値	： SCENEの値(入力されないならシーン遷移しない)
//	引数		： void
//
//==============================================================
SCENE GameScene::Update()
{
	// ポリゴン
	g_pPolygon->Update();
	
	// 影
	g_pShadow->Update();

	// プレイヤー更新
	g_pPlayer->SetBulletTargetPos(g_pBulletTarget->GetBulletTargetPos());
	g_pPlayer->Update();

	// プレイヤーの向きをBulletTargetに取得
	g_pBulletTarget->SetPlayerDrawAngle(g_pPlayer->GetPlayerDrawAngle());

	// 落下地点の更新
	g_pBulletTarget->Update();
	g_pBulletTarget->SetPlayerPos(g_pPlayer->GetPlayerPos());				// プレイヤーの座標を設定(バレットターゲット内で使用)


	// 弾更新
	g_pBulletManger->SetPlayePos(g_pPlayer->GetPlayerPos());				// プレイヤーの座標を設定
	g_pBulletManger->SetTargetPos(g_pBulletTarget->GetBulletTargetPos());	// ターゲットの座標を設定
	g_pBulletManger->SetPlayerAngle(g_pPlayer->GetPlayerAngle());
	g_pBulletManger->Update();

	// 小人更新処理
	g_pDwarfManager->SetBulletInfo(g_pBulletManger);	// 弾の情報を小人のメンバ変数に渡す
	g_pDwarfManager->Update();
	
	// 回収者
	g_pCollector->Update();
	g_pCollectionPoint->SetnowCollectTimer(g_pCollector->GetnowCollectTimer());
	g_pCollector->SetTargetPos(g_pCollectionPoint->GetTargetPos());
	g_pCollectionPoint->Update();


	// エネミー更新
	//g_pEnemy->Update();
	//g_pEnemyManager->Update();

	// ステージ更新
	g_pStageManager->Update();

	// ステージオブジェクト更新
	g_pStageObjectManager->Update();


	//----- プレイヤーの座標を取得 -----
	g_recPlayerPos = g_pPlayer->GetPos();
	//g_pEnemy->TargetPos(g_recPlayerPos);
	//g_pEnemyManager->SetEnemyTarget(g_recPlayerPos);

	// チュートリアル表示更新
	g_pTutorial->Update();

	// スコア更新
	g_pScore->Update();

	// タイマー更新
	g_pTimer->Update();


	//***************************************************************
	// 小人処理
	//***************************************************************
	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 1.5f + DWARF_SIZE, 0.0f);	// ランダム
	for (int j = 0; j < g_pDwarfManager->GetDwarfNum(); j++) {
		if (g_pDwarfManager->GetDwarf(j)->GetCircumferenceFlg() && !g_pDwarfManager->GetDwarf(j)->GetLiftFlg()) {
			//----- 乱数で目的地を設定 -----
			randomPos.x = (float)(rand() % 40 - 20.0f);	//-20.0 ~ 20.0の間の乱数
			randomPos.z = (float)(rand() % 40 - 20.0f);
			g_pDwarfManager->GetDwarf(j)->TargetPos(randomPos);
			g_pDwarfManager->GetDwarf(j)->SetCircumferenceFlg(false);
		}
	}


	for (int i = 0; i < g_pDwarfManager->GetDwarfNum(); i++) 
	{
		if (!g_pDwarfManager->GetDwarf(i)->GetAliveFlg()) {		// 生存してなかったらやらない
			if (!m_IsClear) {
				m_IsGameOver = true;
			}
			break;
		}
		if (g_pDwarfManager->GetDwarf(i)->GetCollectionFlg()) {	// すでに回収済みならやらない
			continue;
		}

		//----- 小人回収処理 -----
		if (CollisionSphere(g_pDwarfManager->GetDwarf(i), g_pCollectionPoint)) {
			if ((g_pCollectionPoint->GetColorNum()) == RED && g_pDwarfManager->GetDwarf(i)->GetRBFlg()) {
				if (g_pCollector->GetNowCollectFlg()) {
					g_pDwarfManager->GetDwarf(i)->SetLiftFlg(true);
				}
			}else if ((g_pCollectionPoint->GetColorNum()) == BLUE && !g_pDwarfManager->GetDwarf(i)->GetRBFlg()) {
				if (g_pCollector->GetNowCollectFlg()) {
					g_pDwarfManager->GetDwarf(i)->SetLiftFlg(true);
				}
			}else  if((g_pCollectionPoint->GetColorNum()) == REDBLUE){
				if (g_pCollector->GetNowCollectFlg()) {
					g_pDwarfManager->GetDwarf(i)->SetLiftFlg(true);
				}
			}
		}
		if (CollisionSphere(g_pDwarfManager->GetDwarf(i), g_pCollector)) {
			g_pDwarfManager->GetDwarf(i)->SetCollectionFlg(true);
			//g_pScore->SetScore(g_pDwarfManager->GetDwarfNum());
			g_pDwarfManager->AddCollectionSum();
		}

		//----- 小人の追跡処理 -----
		for (int j = 0; j < MAX_BULLET; j++) {
			//g_pBullet[j] = g_pBulletManger->GetBullet(j);						// 弾情報取得
			//if (g_pBullet[j]->use) {									// 最後の指示を通す
			//	g_LastBulletNun = j;
			//}
			if (!g_pBulletManger->GetBullet(j)->use) {								// 弾未用ならスキップ
				continue;
			}
			//if (!g_pDwarfManager->GetDwarf(i)->GetMoveFlg()) {
			//	continue;
			//}
			if (!g_pBulletManger->GetBullet(j)->GetColFlg()) {		// 弾が着地
				continue;
			}
			if (!CollisionSphere(g_pDwarfManager->GetDwarf(i), g_pBulletManger->GetBullet(j))) {
				continue;
			}
			//---小人の弾への追尾
			g_recBulletPos = g_pBulletManger->GetBullet(j)->GetPos();
			g_pDwarfManager->GetDwarf(i)->TargetPos(g_recBulletPos);
			g_pDwarfManager->GetDwarf(i)->SetBulletAliveTimer(g_pBulletManger->GetBullet(j)->GetAliveTime());
		}

	}

	//----- ゲームクリア -----
	if (g_pDwarfManager->GetCollectionSum() == g_pDwarfManager->GetDwarfNum()) {		// 小人全回収でクリア
		if (!m_IsGameOver) {
			m_IsClear = true;
		}
	}

	//***************************************************************
	// エネミーがプレイヤーを追跡
	//***************************************************************
	/*for (int i = 0; i < g_pEnemyManager->GetEnemyNum(); i++)
	{
		if (!g_pEnemyManager->GetEnemy(i)->use) {
			continue;
		}
		for (int j = 0; j < g_pDwarfManager->GetDwarfNum(); j++) 
		{
			if (!g_pCollision->CollisionSphere(g_pEnemyManager->GetEnemy(i), g_pDwarfManager->GetDwarf(j),0.3f)) {
				continue;
			}
			g_pEnemyManager->GetEnemy(i)->SetAttackFlg(true);

			if (g_pDwarfManager->GetDwarf(j)->GetAttackFlg()) {
				g_pEnemyManager->DestroyEnemy(i);
			}
		}
		if (&PlayerToEnemy::isHitSphere){
	 		g_pPlayerToEnemy->PlayerToEnemyRegister(g_pPlayer, g_pEnemyManager->GetEnemy(i));
			//---ここで一番近いやつにターゲットを移したい
			//g_pEnemyManager->SetEnemyTarget();
		}
	 	//g_pEnemy->EnemyStop();
	} */	
#ifdef _DEBUG
	//*******************************************************************************
	//	デバッグ用キー処理
	//*******************************************************************************
	//if (IsRelease('X')){				// Xキーで弾消去
	//	g_pBulletManger->DestroyBullet();
	//}
	if (IsRelease('0') || IsRelease(JPadButton::R_SHOULDER)) {				// 0キーでゲームクリア
		if (!m_IsGameOver) {
			m_IsClear = true;
		}
	}
	if (IsRelease('9') || IsRelease(JPadButton::L_SHOULDER)) {				// ９キーでゲームオーバー
		if (!m_IsClear) {
			m_IsGameOver = true;
		}
	}
#endif

	//***************************************************************
	//	カメラ更新
	//***************************************************************	
	//g_pTPSCamera->Update();
	g_pCamera->Update();


	//***************************************************************
	// すべての移動(更新処理)がすんでから
	// すべてのオブジェクトの当たり判定を行う
	//*************************************************************+*
	g_pCollision->Update();

	//***************************************************************
	//	軌跡の更新
	//***************************************************************		//軌跡の更新
	for (int i = CONTROL_NUM * RECORD_MARGIN - 1; i > 0; i--)
	{
		g_recordPos[i] = g_recordPos[i - 1];
	}
	g_recordPos[0] = g_pPlayer->GetPos();

	//***************************************************************
	//	軌跡の計算
	//***************************************************************	
	for (int i = 0; i < CONTROL_NUM; i++)
	{
		//制御点が対応しているレコードの番号を計算
		int idx = i * RECORD_MARGIN;
		//制御点の座標
		DirectX::XMFLOAT3 recPos =
			g_recordPos[idx];

		//軌跡を表示するときはここに
		//->SetVerTex(
	}

	//***************************************************************
	// シーン遷移
	//***************************************************************	
	int sceneState = -1;
	if (m_IsClear) {
		g_pScore->SetScore(1);
		g_pSelectScene->SetScore(m_StageNum, 1);

		sceneState = UpdateClear();
		if (sceneState == STATE_NEXT) {
			GameScene::Uninit();
			GameScene::Init(m_StageNum + 1);
		}
		if (sceneState == STATE_SELECT) {
			return SCENE_SELECT;
		}
	}
	if (m_IsGameOver) {
		sceneState = UpdateGameOver();
		if (sceneState == STATE_RETRY){
			GameScene::Uninit();
			GameScene::Init(m_StageNum);
		}
		if (sceneState == STATE_SELECT) {
			return SCENE_SELECT;
		}
	}
	

	return SCENE_GAME;
}

//==============================================================
//
//	GameScene描画処理
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
void GameScene::Draw()
{
	//SHADER->Bind(
		//頂点シェーダで使用する計算の種類
	//	VS_WORLD,
		//ピクセルシェーダで使用する計算の種類
		//PS_UNLIT...影をつけない
		//PS_LAMBERT...DiffuseとAmbientのみ
		//			　 金属表現は行わない
		//PS_PHONG...Lambertに
		//			 Specularを加える
	//	PS_PHONG);
	//3Dの物体に影がつく仕組み
	//3Dの面に対して垂直な線を考える(法線)
	//光源からの光の向きと、面の法線が
	//同じ方向を向いていたら、影が落ちる
	//面として計算を行う

	//影をつけるときのパラメータ(マテリアル)
	//Diffuse(拡散光)...物体の色
	//厳密には人間の目は飛び込んでくる
	//光の波長で色を認識しているので
	//物体がどの光を跳ね返しやすいのかを表す
	//直接物体に当たる光。

	//Ambient(環境光)...影の色
	//周りの物体から跳ね返った光が
	//物体に当たって反射してきた光

	//Specular(反射光)
	//反射してめちゃくちゃ光っている部分
	//金属のような表現を行う

	//Emissive(発光)
	//自ら光る物体の光の色

	//SetLight～　光源の色を設定
	//Set～　光が当たった物体の反射しやすい色

	//SHADER->SetAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//SHADER->SetLightAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//SHADER->SetLightSpecular(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f),0.0f);

	//①オブジェクトごとに
	//　ローカル座標を持つ(頂点)
	//②ローカル座標をワールド座標に変換
	//③ワールド座標をカメラ座標に変換
	//④カメラの画角に収まる範囲に変換(スクリーン座標)

	static float a = 0.0f;

	//ワールド座標へ変換
	//XMMatrixTranslation 移動
	//XMMatrixRotationX X軸で回転
	//XMMatrixRotationY Y軸で回転
	//XMMatrixRotationZ Z軸で回転
	//XMMatrixScaling 拡縮
	//それぞれの変換行列をDirectXが計算してくれる
	SHADER->SetWorld(XMMatrixRotationY(a += 3.141592f / 180.0));
	SHADER->SetWorld(XMMatrixTranslation(0, 0, 0));

	/* 
	//カメラ座標系に変換
	//第1引数:カメラの位置
	//第2引数:カメラの注視点
	//第3引数:カメラの上方向
	SHADER->SetView(
	DirectX::XMMatrixLookAtLH(
	DirectX::XMVectorSet(0, 10, 0, 0),
	DirectX::XMVectorSet(0, 1, 0, 0),
	DirectX::XMVectorSet(0, 1, 0, 0)
	));
	//カメラの画角を設定
	//第1引数:画角(ラジアン角
	//第2引数:アスペクト比
	//第3引数:ニアクリップ(近景
	//第4引数:ファークリップ(遠景
	SHADER->SetProjection(
	DirectX::XMMatrixPerspectiveFovLH(
	3.141592f / 3,
	(float)SCREEN_WIDTH / SCREEN_HEIGHT,
	1.0f, 1000.0f
	));
	*/

	SHADER->Bind(VS_WORLD, PS_PHONG);


	//g_pTPSCamera->Bind();
	g_pCamera->Bind();
	


	//g_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//とりあえずキューブは画面の奥に移動
	SHADER->SetWorld(DirectX::XMMatrixTranslation(sinf(a) * 3, 0, 3));

	//モデルが大きいので小さくする
	SHADER->SetWorld(DirectX::XMMatrixScaling(0.01f, 0.01f, 0.01f));


	// 回収者の描画
	g_pCollector->Draw();
	g_pCollectionPoint->Draw();

	// 敵の描画
	//g_pEnemyManager->Draw();

	// ピクミン描画
	g_pDwarfManager->Draw();

	// 弾の描画
	g_pBulletManger->Draw();

	// 落下地点の描画
	g_pBulletTarget->Draw();

	//g_pEnemy->Draw();
	//SHADER->SetTexture(NULL);

	// ステージ描画
	g_pStageManager->Draw();
#ifdef _DEBUG
	// 小人のステージの当たり判定ようブロック描画
	g_pDwarfStageCollision->Draw();
#endif 


	// ステージオブジェクト描画
	g_pStageObjectManager->Draw();


	// プレイヤー描画
	g_pPlayer->Draw();


	//影
	g_pShadow->Draw();

	SHADER->Bind(VS_WORLD, PS_PHONG);


	SHADER->SetWorld(DirectX::XMMatrixIdentity());
	
	//	EnableCulling(false);
	//	EnableCulling(true);

	//g_pCamera->Bind2D_Z();


	g_pCamera->Bind2D();



	// ゲームクリアフラグが立っているときクリア描画
	if (m_IsGameOver) {
		DrawGameOver();
	}

	// ゲームオーバーフラグが立っているときゲームオーバー描画
	if (m_IsClear) {
		DrawClear();
	}
	
	// チュートリアル描画
	g_pTutorial->Draw();

	// スコア描画
	g_pScore->Draw();

	// タイマー描画
	g_pTimer->Draw();
}

