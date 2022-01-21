#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include"Texture.h"
#include "Scene.h"
#include "GameObject.h"

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
#include "Tutorial.h"
#include "Clear.h"
#include "GameOver.h"

// ---ステージ関連
#include "Stage.h"
#include "StageObjectManager.h"

// ---ゲーム関連-プレイヤー
#include "Player.h"

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
#include "Score.h"


class GameScene :public Scene
{
public:
	GameScene(void);
	~GameScene(void);

	void Init(int StageNum);
	void Uninit();
	// 戻り値でシーンを移動するかどうか判定
	SCENE Update();
	void Draw();

private:
	int m_StageNum;			// 現在のステージ番号
	int m_NextStageNum;		// 次のステージ番号
	bool m_IsClear;					// クリアフラグ
	bool m_IsGameOver;			// ゲームオーバーフラグ
	//ID3D11ShaderResourceView* m_pTexture[2];
	//bool m_isFadeOut;

	Camera* m_pCamera;
	Collision* m_pCollision;

	Player* m_pPlayer;

	StageManager* m_pStageManager;
	StageObjectManager* m_pStageObjectManager;

	Collector* m_pCollector;
	CollectionPoint* m_pCollectionPoint;

	SelectScene* m_pSelectScene;

	DwarfManager* m_pDwarfManager;
	DwarfStageCollision* m_pDwarfStageCollision;

	BulletManager* m_pBulletManger;
	BulletTarget* m_pBulletTarget;

	Score* m_pScore;
	Tutorial* m_pTutorial;


};

#endif