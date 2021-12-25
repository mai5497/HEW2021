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
 * @brief ゲームシーンに関する処理
 */

//*******************************************************************************
// インクルード部
//*******************************************************************************
#include "GameScene.h"
#include "Input.h"
#include "Player.h"
#include "stage.h"
#include "GameObject.h"
#include "FieldManager.h"
#include "model.h"
#include "TPSCamera.h"
#include "Collision.h"
#include "Shader.h"
#include "Defines.h"
#include "Cube.h"
#include "PlayerToEnemy.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "DwarfManager.h"
#include "Collector.h"
#include "CollectionPoint.h"

//*******************************************************************************
// 定数・マクロ定義
//*******************************************************************************
#define CONTROL_NUM		(5)
#define RECORD_MARGIN	(10)

//*******************************************************************************
// グローバル宣言
//*******************************************************************************
Cube				*g_pCube;
Model				*g_pModel;
Camera				*g_pCamera;
TPSCamera			*g_pTPSCamera;
Player				*g_pPlayer;
DwarfManager		*g_pDwarfManager;
Stage				*g_pStage;
Collision			*g_pCollision;
PlayerToEnemy		*g_pPlayerToEnemy;
Collector			*g_pCollector;
CollectionPoint		*g_pCollectionPoint;

//Enemy				*g_pEnemy;
//EnemyManager		*g_pEnemyManager;
//Shot				*g_pShot;

XMFLOAT3 g_recPlayerPos;
XMFLOAT3 g_recBulletPos;
XMFLOAT3 g_recordPos[CONTROL_NUM * RECORD_MARGIN];

int g_LastBulletNun = -1;
Bullet *g_pBullet[5];

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
//	引数		： void
//
//==============================================================
void GameScene::Init()
{
	// 立方体クラスの実体化
	g_pCube = new Cube();

	// モデルクラスの実体化
	g_pModel = new Model();
	g_pModel->LoadModel("Assets/Model/tyoutin.fbx");

	// カメラクラスの実体化
	//g_pCamera = new Camera();
	//g_pCamera->Init();
	
	// プレイヤークラス実体化
	g_pPlayer = new Player();
	g_pPlayer->Init();

	// TPSカメラはプレイヤーより後
	g_pTPSCamera = new TPSCamera();
	g_pTPSCamera->SetTargetObj(g_pPlayer);
	g_pTPSCamera->Init();
	g_pCamera = new Camera();
	g_pCamera->Init();

	g_pPlayer->SetControllCamera(g_pTPSCamera);
	g_pPlayer->GetCameraPos(g_pTPSCamera);

	// 小人管理クラス実体化
	g_pDwarfManager = new DwarfManager();
	g_pDwarfManager->Init();

	// 回収車
	g_pCollector = new Collector();
	g_pCollector->Init();

	g_pCollectionPoint = new CollectionPoint();
	g_pCollectionPoint->Init();



	// 敵クラス実体化
	//g_pEnemy = new Enemy();
	//g_pEnemy->LoadEnemy("Assets/Model/tyoutinobake.fbx");
	//g_pEnemy->Init();

	// 敵の管理クラスの実体
	//g_pEnemyManager = new EnemyManager();
	//g_pEnemyManager->Init();

	// 弾クラスの実体
	//	g_pShot = new Shot();
	//	g_pShot->Init();

	// ステージクラスの実体化
	g_pStage = new Stage();
	g_pStage->Init();

	// 当たり判定クラス
	g_pCollision = new Collision();
	g_pCollision->Init();

	// プレイヤーtoエネミーの当たり判定クラス
	g_pPlayerToEnemy = new PlayerToEnemy();
	g_pPlayerToEnemy->Init();


}

//==============================================================
//
//	GameSceneクラス::Uninit
//	作成者	： 園田翔大
//	戻り値	： void
//	引数		： void
//
//==============================================================
void GameScene::Uninit()
{
	// 当たり判定クラスの終了処理
	g_pCollision->Uninit();
	delete g_pCollision;


	// プレイヤーtoエネミークラスの終了処理
	g_pPlayerToEnemy->Uninit();
	delete g_pPlayerToEnemy;

	// ショットクラスの終了処理
	//	g_pShot->Uninit();
	//	delete g_pShot;

	// ステージクラスの終了処理
	g_pStage->Uninit();
	delete g_pStage;

	//プレイヤーの終了処理
	g_pPlayer->Uninit();
	delete g_pPlayer;

	// 小人終了処理
	g_pDwarfManager->Uninit();
	delete g_pDwarfManager;

	// 回収者
	g_pCollector->Uninit();
	delete g_pCollector;

	g_pCollectionPoint->Uninit();
	delete g_pCollectionPoint;


	// エネミー終了処理
	//delete g_pEnemy;

	// エネミーマネージャ終了
	//g_pEnemyManager->Uninit();
	//delete g_pEnemyManager;

	// バレット終了
	//	delete g_pBullet;

	// カメラ類終了
	g_pCamera->Uninit();
	delete g_pCamera;
	g_pTPSCamera->Uninit();
	delete g_pTPSCamera;

	// モデル終了
	delete g_pModel;

	// キューブ終了
	delete g_pCube;
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
	// プレイヤー更新
	g_pPlayer->SetDwarfInfo(g_pDwarfManager);						// playerのメンバ変数に情報を渡す
	g_pPlayer->Update();

	// 小人更新処理
	g_pDwarfManager->SetStageInfo(g_pStage);		// 小人のメンバ変数に情報を渡す
	g_pDwarfManager->Update();

	// バレット更新
	//	g_pBullet->Update();
	
	// 回収者
	g_pCollector->Update();
	g_pCollectionPoint->Update();


	// エネミー更新
	//g_pEnemy->Update();
	//g_pEnemyManager->Update();

	// ステージ更新
	g_pPlayer->SetStageInfo(g_pStage);
	g_pStage->Update();

	// ショット更新
	//g_pShot->Update();

	g_recPlayerPos = g_pPlayer->GetPos();
	//g_pEnemy->TargetPos(g_recPlayerPos);

	//g_pEnemyManager->SetEnemyTarget(g_recPlayerPos);

	/* 弾の発射はplayer.cppに移動 */


	//***************************************************************
	// すべての移動(更新処理)がすんでから
	// すべてのオブジェクトの当たり判定を行う
	//*************************************************************+*
	//----- プレイヤーと床 -----
	for (int i = 0; i < g_pStage->GetFieldNum(); i++)
	{
		g_pCollision->Register(g_pPlayer, g_pStage->GetField(i));
	}

	//----- 小人と床 -----
	for (int i = 0; i < g_pDwarfManager->GetDwarfNum(); i++) 
	{
		g_pCollision->Register(g_pDwarfManager->GetDwarf(i), g_pStage->GetField(1));
	}


	//----- 弾と床 -----
	//for (int i = 0; i < g_pPlayer->GetBulletNum(); i++) {
	//	g_pCollision->Register(g_pPlayer->GetBullet(i), g_pStage->GetField(1));
	//}


	//***************************************************************
	// 小人回収
	//***************************************************************
	for (int i = 0; i < g_pDwarfManager->GetDwarfNum(); i++) {
		if (CollisionSphere(g_pDwarfManager->GetDwarf(i), g_pCollector)) {
			// 小人回収
			g_pDwarfManager->GetDwarf(i)->use = false;
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

	//****************************************************************************
	//	弾の追跡
	//****************************************************************************
	for (int i = 0; i < g_pPlayer->GetBulletNum(); i++){
		g_pBullet[i] = g_pPlayer->GetBullet(i);						// 弾情報取得
		if (g_pBullet[i]->use) {											// 最後の指示を通す
			g_LastBulletNun = i;
		}
		for (int j = 0; j  <  g_pDwarfManager->GetDwarfNum(); j++){
			g_pPlayer->SetDwarfInfo(g_pDwarfManager);						// playerのメンバ変数に情報を渡す
			if (!g_pBullet[i]->use){										// 弾未使用ならスキップ
				continue;
			}
			if (!g_pDwarfManager->GetDwarf(j)->GetMoveFlg()) {		// 移動許可がないときは動かない
				continue;
			}
			g_recBulletPos = g_pBullet[g_LastBulletNun]->GetPos();	// 最後の指示位置を保存

			//---ピクミンの弾への追尾
			g_pDwarfManager->GetDwarf(j)->TargetPos(g_recBulletPos);
			//g_pCollision->Register(g_pPlayer->GetBullet(i), g_pDwarfManager->GetDwarf(j));

			if (!CollisionSphere(g_pPlayer->GetBullet(i), g_pDwarfManager->GetDwarf(j))) {
				continue;
			}
			g_pDwarfManager->GetDwarf(j)->SetAttackFlg(true);
		}

		//*******************************************************************************
		//	当たり判定取得
		//*******************************************************************************
		g_pCollision->Register(g_pPlayer->GetBullet(i), g_pStage->GetField(0));				// 弾とフィールドの当たり判定

		// 円での当たり判定(中心点の距離計算は0.5f)
		//if (g_pCollision->CollisionSphere(g_pBullet[i], g_pStage->GetField(1), 1.0f)) {
		//	g_pPlayer->GetBullet(i)->SetCollor(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
		//}

	}
	
	//*******************************************************************************
	//	キー入力で弾削除
	//*******************************************************************************
	if (IsTrigger('X')){				// Xキー判定
		g_pPlayer->DestroyBullet();
	}

	//***************************************************************
	//	カメラ更新
	//***************************************************************	
	g_pTPSCamera->Update();
	g_pPlayerToEnemy->Update();
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
	//						軌跡の計算
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
	if (IsTrigger('1')) { return SCENE_RESULT; }		// '1'入力
	
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
	SHADER->Bind(
		//頂点シェーダで使用する計算の種類
		VS_WORLD,
		//ピクセルシェーダで使用する計算の種類
		//PS_UNLIT...影をつけない
		//PS_LAMBERT...DiffuseとAmbientのみ
		//			　 金属表現は行わない
		//PS_PHONG...Lambertに
		//			 Specularを加える
		PS_PHONG);
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

	//SetLight〜　光源の色を設定
	//Set〜　光が当たった物体の反射しやすい色

	/*SHADER->SetLightAmbient(
		DirectX::XMFLOAT4(0.6f, 0.6f, 0.6f, 0.6f)
	);
	SHADER->SetLightSpecular(
		DirectX::XMFLOAT4(1, 1, 1, 1),
		20);*/

	//�@オブジェクトごとに
	//　ローカル座標を持つ(頂点)
	//�Aローカル座標をワールド座標に変換
	//�Bワールド座標をカメラ座標に変換
	//�Cカメラの画角に収まる範囲に変換(スクリーン座標)
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
	DirectX::XMVectorSet(0, 2, -5, 0),
	DirectX::XMVectorSet(0, 0, 0, 0),
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
	));*/

	//g_pTPSCamera->Bind();
	g_pCamera->Bind();
	
	///g_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//とりあえずキューブは画面の奥に移動
	SHADER->SetWorld(DirectX::XMMatrixTranslation(sinf(a) * 3, 0, 3));

	//そもそも描画関数コメントアウトしておけばよかった
	//	g_pCube->Draw();

	//モデルが大きいので小さくする
	SHADER->SetWorld(DirectX::XMMatrixScaling(0.01f, 0.01f, 0.01f));
	//g_pModel->Draw();

	// プレイヤー描画

		// 回収者の描画
	g_pCollector->Draw();
	g_pCollectionPoint->Draw();



	// 敵の描画
	//g_pEnemyManager->Draw();

	// ピクミン描画
	g_pDwarfManager->Draw();

	//g_pEnemy->Draw();
	SHADER->SetTexture(NULL);
	//	g_pBullet->Draw();

	// ステージ描画
	g_pStage->Draw();


	// g_pShot->Draw();
	g_pPlayer->Draw();
	SHADER->SetWorld(DirectX::XMMatrixIdentity());
	
	//	EnableCulling(false);
	
	//	EnableCulling(true);
}
