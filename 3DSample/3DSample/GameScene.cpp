/**
 * @file GameScene.cpp
 * @Author 園田翔大
 * @date 2021/11/29 作成
 *		 2021/12/03 ピクミン追加
 *		 2021/12/09 エネミーが球に追跡するのを削除
 *		 2021/12/11 弾の追跡の処理の変更（ピクミンが来て、攻撃を始める）
 *					敵の追跡の処理の変更（ピクミンに当たったら消える）
 *		 2021/12/17 ぷっしゅてすと
 *		 2021/12/17 ぷっしゅ
 * @brief ゲームシーンに関する処理
 */

#include "GameScene.h"
#include "Input.h"
#include "Player.h"
#include "stage.h"
#include "GameObject.h"
#include "field.h"
#include "model.h"
#include "TPSCamera.h"
#include "Collision.h"
#include "Shader.h"
#include "Defines.h"
#include "Cube.h"
#include "PlayerToEnemy.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "PikminManager.h"


#define CONTROL_NUM (5)
#define RECORD_MARGIN (10)

Cube			*g_pCube;
Model			*g_pModel;
Camera			*g_pCamera;
TPSCamera		*g_pTPSCamera;
Player			*g_pPlayer;
PikminManager	*g_pPikminManager;
Stage			*g_pStage;
Collision		*g_pCollision;
PlayerToEnemy	*g_pPlayerToEnemy;
//Enemy			*g_pEnemy;
EnemyManager	*g_pEnemyManager;
//Shot			*g_pShot;

DirectX::XMFLOAT3 g_recPlayerPos;
XMFLOAT3 g_recBulletPos;
DirectX::XMFLOAT3 g_recordPos[CONTROL_NUM * RECORD_MARGIN];

int g_LastBulletNun = -1;
Bullet *g_pBullet[5];


GameScene::GameScene(void)
{

}

GameScene::~GameScene(void)
{

}

void GameScene::Init()
{
	//立方体クラスの実体化
	g_pCube = new Cube();

	//モデルクラスの実体化
	g_pModel = new Model();
	g_pModel->LoadModel("Assets/Model/tyoutin.fbx");

	//カメラクラスの実体化
	/*
	g_pCamera = new Camera();
	g_pCamera->Init();
	*/
	//プレイヤークラス実体化
	g_pPlayer = new Player();
	g_pPlayer->Init();
	// TPSカメラはプレイヤーより後
	g_pTPSCamera = new TPSCamera();
	g_pTPSCamera->SetTargetObj(g_pPlayer);
	g_pTPSCamera->Init();

	g_pPlayer->SetControllCamera(g_pTPSCamera);

	g_pPlayer->GetCameraPos(g_pTPSCamera);

	// ピクミン管理クラス実体化
	g_pPikminManager = new PikminManager();
	g_pPikminManager->Init();

	//敵クラス実体化
	//g_pEnemy = new Enemy();
	//g_pEnemy->LoadEnemy("Assets/Model/tyoutinobake.fbx");
	//g_pEnemy->Init();

	// 敵の管理クラスの実体
	g_pEnemyManager = new EnemyManager();
	g_pEnemyManager->Init();

	//	g_pShot = new Shot();
	//	g_pShot->Init();

	//ステージクラスの実体化
	g_pStage = new Stage();
	g_pStage->Init();

	//当たり判定クラス
	g_pCollision = new Collision();
	g_pCollision->Init();

	g_pPlayerToEnemy = new PlayerToEnemy();
	g_pPlayerToEnemy->Init();


}

void GameScene::Uninit()
{
	g_pCollision->Uninit();
	delete g_pCollision;
	g_pPlayerToEnemy->Uninit();
	delete g_pPlayerToEnemy;
	//	g_pShot->Uninit();
	//	delete g_pShot;

	g_pStage->Uninit();
	delete g_pStage;
	g_pPlayer->Uninit();
	delete g_pPlayer;

	// ピクミン終了処理
	g_pPikminManager->Uninit();
	delete g_pPikminManager;

	//delete g_pEnemy;
	g_pEnemyManager->Uninit();
	delete g_pEnemyManager;
	//	delete g_pBullet;


	g_pCamera->Uninit();
	delete g_pCamera;
	g_pTPSCamera->Uninit();
	delete g_pTPSCamera;
	delete g_pModel;
	delete g_pCube;
}
SCENE GameScene::Update()
{

	g_pPlayer->Update();

	// ピクミン更新処理
	g_pPikminManager->Update();

	//	g_pBullet->Update();
	//g_pEnemy->Update();
	g_pEnemyManager->Update();


	g_pStage->Update();

	//	g_pShot->Update();

	g_recPlayerPos = g_pPlayer->GetPos();
	//g_pEnemy->TargetPos(g_recPlayerPos);

	g_pEnemyManager->SetEnemyTarget(g_recPlayerPos);

	if(IsTrigger('Z'))
	{
		g_pPlayer->CreateBullet(g_pTPSCamera);
		for (int i = 0; i < g_pPikminManager->GetPikminNum(); i++) {
			g_pPikminManager->GetPikmin(i)->SetFollowFlg(true);
		}
		
	}


	//すべての移動(更新処理)がすんでから
	//すべてのオブジェクトの当たり判定を行う
	for (int i = 0; i < g_pStage->GetFieldNum(); i++)
	{
		g_pCollision->Register(g_pPlayer, g_pStage->GetField(i));
	}

	for (int i = 0; i < g_pStage->GetFieldNum(); i++)
	{
		//g_pCollision->Register(g_pEnemy, g_pStage->GetField(i));
		for (int j = 0; j < g_pEnemyManager->GetEnemyNum(); j++)
		{
			g_pCollision->Register(g_pEnemyManager->GetEnemy(j), g_pStage->GetField(i));
		}
	}

	
	// エネミーがプレイヤーを追いかける
	for (int i = 0; i < g_pEnemyManager->GetEnemyNum(); i++)
	{
		if (!g_pEnemyManager->GetEnemy(i)->use) {
			continue;
		}
		for (int j = 0; j < g_pPikminManager->GetPikminNum(); j++) {
			if (!g_pCollision->CollisionSphere(g_pEnemyManager->GetEnemy(i), g_pPikminManager->GetPikmin(j),0.3f)) {
				continue;
			}
			g_pEnemyManager->GetEnemy(i)->SetAttackFlg(true);

			if (g_pPikminManager->GetPikmin(j)->GetAttackFlg()) {
				g_pEnemyManager->DestroyEnemy(i);
			}
		}
		if (&PlayerToEnemy::isHitSphere){
	 		g_pPlayerToEnemy->PlayerToEnemyRegister(g_pPlayer, g_pEnemyManager->GetEnemy(i));
			//---ここで一番近いやつにターゲットを移したい
			//g_pEnemyManager->SetEnemyTarget();
		}
	 	//g_pEnemy->EnemyStop();
	}



	

	// 弾の追跡と当たり判定
	for (int i = 0; i < g_pPlayer->GetBulletNum(); i++)
	{
		g_pBullet[i] = g_pPlayer->GetBullet(i);	// 弾情報取得
		if (g_pBullet[i]->use) {	// 最後の指示を通す
			g_LastBulletNun = i;
		}
		for (int j = 0; j < g_pPikminManager->GetPikminNum(); j++)
		{
			if (!g_pBullet[i]->use){	// 弾未使用ならスキップ
				continue;
			}
			if (!g_pPikminManager->GetPikmin(j)->GetFollowFlg()) {	// 追跡フラグが立っていないときは動かない
				continue;
			}
			g_recBulletPos = g_pBullet[g_LastBulletNun]->GetPos();	// 最後の指示位置を保存
			//---ピクミンの弾への追尾
			g_pPikminManager->SetPikminTarget(g_recBulletPos);
			//g_pCollision->Register(g_pPlayer->GetBullet(i), g_pPikminManager->GetPikmin(j));

			if (!g_pCollision->CollisionSphere(g_pPlayer->GetBullet(i), g_pPikminManager->GetPikmin(j))) {
				continue;
			}
			g_pPikminManager->GetPikmin(j)->SetAttackFlg(true);


		}
		g_pCollision->Register(g_pPlayer->GetBullet(i), g_pStage->GetField(i));	// 弾とフィールドの当たり判定
	}
	
	if (IsTrigger('X')){
		g_pPlayer->DestroyBullet();
	}

	g_pTPSCamera->Update();
	g_pPlayerToEnemy->Update();
	g_pCollision->Update();
	//軌跡の更新
	for (int i = CONTROL_NUM * RECORD_MARGIN - 1; i > 0; i--)
	{
		g_recordPos[i] = g_recordPos[i - 1];
	}
	g_recordPos[0] = g_pPlayer->GetPos();

	//軌跡の計算
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
	if (IsTrigger('1')) { return SCENE_RESULT; }
	
	return SCENE_GAME;
}
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

	//SetLight～　光源の色を設定
	//Set～　光が当たった物体の反射しやすい色

	/*SHADER->SetLightAmbient(
		DirectX::XMFLOAT4(0.6f, 0.6f, 0.6f, 0.6f)
	);
	SHADER->SetLightSpecular(
		DirectX::XMFLOAT4(1, 1, 1, 1),
		20);*/

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
	SHADER->SetWorld(
		DirectX::XMMatrixRotationY(
			a += 3.141592f / 180.0f
		));
	SHADER->SetWorld(
		DirectX::XMMatrixTranslation(0, 0, 0)
	);
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



	g_pTPSCamera->Bind();
	

	///g_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//とりあえずキューブは画面の奥に移動
	SHADER->SetWorld(
		DirectX::XMMatrixTranslation(sinf(a) * 3, 0, 3));
	//そもそも描画関数コメントアウトしておけばよかった
	//	g_pCube->Draw();

	//モデルが大きいので小さくする
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(
			0.01f, 0.01f, 0.01f
		));
	//g_pModel->Draw();

	// プレイヤー描画

	// 敵の描画
	g_pEnemyManager->Draw();

	// ピクミン描画
	g_pPikminManager->Draw();

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
