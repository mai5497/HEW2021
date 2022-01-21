#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include"Texture.h"
#include "Scene.h"
#include "GameObject.h"

//---�V�X�e���֘A
#include "Camera.h"
#include "Input.h"
#include "TPSCamera.h"
#include "Collision.h"
#include "Shader.h"
#include "Defines.h"

// ---�V�[���֘A
#include "GameScene.h"
#include "SelectScene.h"
#include "Tutorial.h"
#include "Clear.h"
#include "GameOver.h"

// ---�X�e�[�W�֘A
#include "Stage.h"
#include "StageObjectManager.h"

// ---�Q�[���֘A-�v���C���[
#include "Player.h"

// ---�Q�[���֘A-�G�l�~�[
#include "Enemy.h"
#include "EnemyManager.h"

// ---�Q�[���֘A-���l
#include "DwarfManager.h"
#include "DwarfStageCollision.h"

// ---�Q�[���֘A-�e
#include "BulletManager.h"
#include "BulletTarget.h"

// ---�Q�[���֘A-���
#include "Collector.h"
#include "CollectionPoint.h"

// ---�Q�[���֘A-UI
#include "Score.h"


class GameScene :public Scene
{
public:
	GameScene(void);
	~GameScene(void);

	void Init(int StageNum);
	void Uninit();
	// �߂�l�ŃV�[�����ړ����邩�ǂ�������
	SCENE Update();
	void Draw();

private:
	int m_StageNum;			// ���݂̃X�e�[�W�ԍ�
	int m_NextStageNum;		// ���̃X�e�[�W�ԍ�
	bool m_IsClear;					// �N���A�t���O
	bool m_IsGameOver;			// �Q�[���I�[�o�[�t���O
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