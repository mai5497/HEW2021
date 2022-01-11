/**
 * @file GameScene.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬(���c)
 *		 2021/12/03 �s�N�~���ǉ�(�ɒn�c)
 *		 2021/12/09 �G�l�~�[�����ɒǐՂ���̂��폜(�_��)
 *		 2021/12/11 �e�̒ǐՂ̏����̕ύX�i�s�N�~�������āA�U�����n�߂�j(�ɒn�c)
 *					�G�̒ǐՂ̏����̕ύX�i�s�N�~���ɓ��������������j(�ɒn�c)
 *		 2021/12/17 �Ղ�����Ă���(�ɒn�c)
 *		 2021/12/17 �Ղ�����(�g��)
 *		 2021/12/25 ���l�t�B�[���h���痎����(�ɒn�c)
 *		 2021/12/25 �����I(�g��)
 *		 2022/01/02 �X�e�[�W�I���ł���悤�ɂ����i�ɒn�c�j
 *		 2022/01/10 �o���b�g�̎g�p�ύX�`
 * @brief �Q�[���V�[���Ɋւ��鏈��
 */

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************
#include "GameScene.h"
#include "Input.h"
#include "Player.h"
#include "StageManager.h"
#include "GameObject.h"
#include "Stage.h"
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
#include "SelectScene.h"
#include "Clear.h"
#include "BulletManager.h"
#include "Score.h"
#include "Tutorial.h"


//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define CONTROL_NUM		(5)
#define RECORD_MARGIN	(10)
#define TARGETSET_TIME	(300)

//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
Cube				*g_pCube;
Model				*g_pModel;
Camera				*g_pCamera;
TPSCamera			*g_pTPSCamera;
Player				*g_pPlayer;
StageManager		*g_pStageManager;
Collision			*g_pCollision;
PlayerToEnemy		*g_pPlayerToEnemy;
Collector			*g_pCollector;
CollectionPoint		*g_pCollectionPoint;
SelectScene			*g_pSelectScene;
DwarfManager		*g_pDwarfManager;
BulletManager		*g_pBulletManger;

Score				*g_pScore;
Tutorial			*g_pTutorial;


//Enemy				*g_pEnemy;
//EnemyManager		*g_pEnemyManager;
//Shot				*g_pShot;

XMFLOAT3 g_recPlayerPos;
XMFLOAT3 g_recBulletPos;
XMFLOAT3 g_recordPos[CONTROL_NUM * RECORD_MARGIN];

int g_LastBulletNun = -1;
BulletBase *g_pBullet[MAX_BULLET];

//==============================================================
//
//	GameScene�N���X::�R���X�g���N�^
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
GameScene::GameScene(void)
{

}

//==============================================================
//
//	GameScene�N���X::�f�X�g���N�^
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
GameScene::~GameScene(void)
{

}

//==============================================================
//
//	GameScene�N���X::Init
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����	�F void
//
//==============================================================
void GameScene::Init(int StageNum)
{
	// �����o�ϐ�������
	m_StageNum = StageNum;			// ���݂̃X�e�[�W�ԍ��ۑ�
	m_NextStageNum = m_StageNum;	// ���̃X�e�[�W�ԍ��ۑ��i���݂Ǝ�����v���Ȃ������ꍇ���̃X�e�[�W�ֈڍs�j
	m_IsClear = false;				// �N���A�t���O

	// �����̃N���X�̎��̉�
	g_pCube = new Cube();

	// ���f���N���X�̎��̉�
	g_pModel = new Model();
	g_pModel->LoadModel("Assets/Model/tyoutin.fbx");

	// �J�����N���X�̎��̉�
	//g_pCamera = new Camera();
	//g_pCamera->Init();
	
	// �e�̊Ǘ��N���X
	g_pBulletManger = new BulletManager();
	g_pBulletManger->Init();

	// ���l�Ǘ��N���X���̉�
	g_pDwarfManager = new DwarfManager();
	g_pDwarfManager->Init();

	// �v���C���[�N���X���̉�
	g_pPlayer = new Player();
	g_pPlayer->Init();

	// TPS�J�����̓v���C���[����
	g_pTPSCamera = new TPSCamera();
	g_pTPSCamera->SetTargetObj(g_pPlayer);
	g_pTPSCamera->Init();
	g_pCamera = new Camera();
	g_pCamera->Init();

	g_pPlayer->SetControllCamera(g_pTPSCamera);
	g_pPlayer->GetCameraPos(g_pTPSCamera);

	// �����
	g_pCollector = new Collector();
	g_pCollector->Init();

	g_pCollectionPoint = new CollectionPoint();
	g_pCollectionPoint->Init();



	// �G�N���X���̉�
	//g_pEnemy = new Enemy();
	//g_pEnemy->LoadEnemy("Assets/Model/tyoutinobake.fbx");
	//g_pEnemy->Init();

	// �G�̊Ǘ��N���X�̎���
	//g_pEnemyManager = new EnemyManager();
	//g_pEnemyManager->Init();

	// �e�N���X�̎���
	//	g_pShot = new Shot();
	//	g_pShot->Init();

	// �X�e�[�W�N���X�̎��̉�
	g_pStageManager = new StageManager();
	g_pStageManager->Init(StageNum);

	// �����蔻��N���X
	g_pCollision = new Collision();
	g_pCollision->Init();

	// �v���C���[to�G�l�~�[�̓����蔻��N���X
	g_pPlayerToEnemy = new PlayerToEnemy();
	g_pPlayerToEnemy->Init();

	g_pScore = new Score();
	g_pScore->Init();

	g_pTutorial = new Tutorial();
	g_pTutorial->Init();

	// �Q�[���N���A������
	InitClear();
}

//==============================================================
//
//	GameScene�N���X::Uninit
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����	�F void
//
//==============================================================
void GameScene::Uninit()
{
	g_pScore->Uninit();
	delete g_pScore;

	g_pTutorial->Uninit();
	delete g_pTutorial;

	// �����蔻��N���X�̏I������
	g_pCollision->Uninit();
	delete g_pCollision;

	// �v���C���[to�G�l�~�[�N���X�̏I������
	g_pPlayerToEnemy->Uninit();
	delete g_pPlayerToEnemy;

	// �X�e�[�W�N���X�̏I������
	g_pStageManager->Uninit();
	delete g_pStageManager;

	//�v���C���[�̏I������
	g_pPlayer->Uninit();
	delete g_pPlayer;

	// ���l�I������
	g_pDwarfManager->Uninit();
	delete g_pDwarfManager;

	// �e�̃N���X���
	g_pBulletManger->Uninit();
	delete g_pBulletManger;

	// �����
	g_pCollector->Uninit();
	delete g_pCollector;
	
	// ����|�C���g
	g_pCollectionPoint->Uninit();
	delete g_pCollectionPoint;

	// �G�l�~�[�I������
	//delete g_pEnemy;

	// �G�l�~�[�}�l�[�W���I��
	//g_pEnemyManager->Uninit();
	//delete g_pEnemyManager;

	// �o���b�g�I��
	//	delete g_pBullet;

	// �J�����ޏI��
	g_pCamera->Uninit();
	delete g_pCamera;
	g_pTPSCamera->Uninit();
	delete g_pTPSCamera;

	// ���f���I��
	delete g_pModel;

	// �L���[�u�I��
	delete g_pCube;

	// �Q�[���N���A�I��
	UninitClear();
}

//==============================================================
//
//	GameScene�N���X::Update
//	�쐬��	�F ���c�đ�
//	�߂�l	�F SCENE�̒l(���͂���Ȃ��Ȃ�V�[���J�ڂ��Ȃ�)
//	����		�F void
//
//==============================================================
SCENE GameScene::Update()
{
	// �v���C���[�X�V
	g_pPlayer->Update();

	// �e�X�V
	g_pBulletManger->SetPlayePos(g_pPlayer->GetPlayerPos());
	g_pBulletManger->SetPlayerAngle(g_pPlayer->GetPlayerAngle());
	g_pBulletManger->Update();

	// ���l�X�V����
	//g_pDwarfManager->SetBulletInfo(g_pBulletManger);	// �e�̏������l�̃����o�ϐ��ɓn��
	g_pDwarfManager->Update();
	
	// �����
	g_pCollector->Update();
	g_pCollectionPoint->Update();


	// �G�l�~�[�X�V
	//g_pEnemy->Update();
	//g_pEnemyManager->Update();

	// �X�e�[�W�X�V
	g_pStageManager->Update();

	g_recPlayerPos = g_pPlayer->GetPos();
	//g_pEnemy->TargetPos(g_recPlayerPos);

	//g_pEnemyManager->SetEnemyTarget(g_recPlayerPos);

	/* �e�̔��˂�player.cpp�Ɉړ� */

	g_pScore->Update();

	g_pTutorial->Update();


	//***************************************************************
	// ���ׂĂ̈ړ�(�X�V����)������ł���
	// ���ׂẴI�u�W�F�N�g�̓����蔻����s��
	//*************************************************************+*
	//----- �v���C���[�Ə� -----
	for (int i = 0; i < g_pStageManager->GetStageNum(); i++)
	{
		g_pCollision->Register(g_pPlayer, g_pStageManager->GetStage(i));
	}

	//----- ���l�Ə� -----
	for (int i = 0; i < g_pDwarfManager->GetDwarfNum(); i++) 
	{
		g_pCollision->Register(g_pDwarfManager->GetDwarf(i), g_pStageManager->GetStage(1));
	}


	//----- �e�Ə� -----
	//for (int i = 0; i < g_pPlayer->GetBulletNum(); i++) {
	//	g_pCollision->Register(g_pPlayer->GetBullet(i), g_pStage->GetField(1));
	//}


	//***************************************************************
	// ���l���
	//***************************************************************
	for (int i = 0; i < g_pDwarfManager->GetDwarfNum(); i++) {
		if (CollisionSphere(g_pDwarfManager->GetDwarf(i), g_pCollector)) {
			// ���l���
			g_pDwarfManager->GetDwarf(i)->SetCollectionFlg(true);
			g_pScore->SetScore(g_pDwarfManager->GetDwarfNum());

		}
	}


	//***************************************************************
	// �G�l�~�[���v���C���[��ǐ�
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
			//---�����ň�ԋ߂���Ƀ^�[�Q�b�g���ڂ�����
			//g_pEnemyManager->SetEnemyTarget();
		}
	 	//g_pEnemy->EnemyStop();
	} */


	//****************************************************************************
	//	���l�̒ǐՏ����i�����_���ňړ��挈�߂Ă��낤�낳����j
	//****************************************************************************
	static int Timer;
	if (Timer < 0) {
		XMFLOAT3 randomPos = XMFLOAT3(0.0f, 0.0f, 0.0f);	// �����_��
		for (int j = 0; j < g_pDwarfManager->GetDwarfNum(); j++) {
			//----- �����ŖړI�n��ݒ� -----
			randomPos.x = (float)(rand() % 20 - 10.0f);	//-10.0 ~ 10.0�̊Ԃ̗���
			randomPos.z = (float)(rand() % 20 - 10.0f);
			g_pDwarfManager->GetDwarf(j)->TargetPos(randomPos);
		}
		Timer = TARGETSET_TIME;
	}
	Timer--;


	//****************************************************************************
	//	���l�̒ǐՏ���
	//****************************************************************************
	for (int i = 0; i < MAX_BULLET; i++){
		g_pBullet[i] = g_pBulletManger->GetBullet(i);						// �e���擾
		if (g_pBullet[i]->use) {									// �Ō�̎w����ʂ�
			g_LastBulletNun = i;
		}
		for (int j = 0; j  <  g_pDwarfManager->GetDwarfNum(); j++){
			if (!g_pBullet[i]->use){								// �e���g�p�Ȃ�X�L�b�v
				continue;
			}
			//if (!g_pDwarfManager->GetDwarf(j)->GetMoveFlg()) {		// �ړ������Ȃ��Ƃ��͓����Ȃ�
			//	continue;
			//}
			g_recBulletPos = g_pBullet[g_LastBulletNun]->GetPos();	// �Ō�̎w���ʒu��ۑ�

			//---�s�N�~���̒e�ւ̒ǔ�
			g_pDwarfManager->GetDwarf(j)->TargetPos(g_recBulletPos);
		}
	}


	
#ifdef _DEBUG
	//*******************************************************************************
	//	�f�o�b�O�p�L�[����
	//*******************************************************************************
	if (IsTrigger('X')){				// X�L�[�Œe����
		g_pBulletManger->DestroyBullet();
	}
	if (IsTrigger('0')) {				// 0�L�[�ŃQ�[���N���A
		m_IsClear = true;
	}


#endif

	//***************************************************************
	//	�J�����X�V
	//***************************************************************	
	g_pTPSCamera->Update();
	g_pPlayerToEnemy->Update();
	g_pCollision->Update();

	//***************************************************************
	//	�O�Ղ̍X�V
	//***************************************************************		//�O�Ղ̍X�V
	for (int i = CONTROL_NUM * RECORD_MARGIN - 1; i > 0; i--)
	{
		g_recordPos[i] = g_recordPos[i - 1];
	}
	g_recordPos[0] = g_pPlayer->GetPos();

	//***************************************************************
	//						�O�Ղ̌v�Z
	//***************************************************************	
	for (int i = 0; i < CONTROL_NUM; i++)
	{
		//����_���Ή����Ă��郌�R�[�h�̔ԍ����v�Z
		int idx = i * RECORD_MARGIN;
		//����_�̍��W
		DirectX::XMFLOAT3 recPos =
			g_recordPos[idx];

		//�O�Ղ�\������Ƃ��͂�����
		//->SetVerTex(
	}

	//***************************************************************
	// �V�[���J��
	//***************************************************************	
	//if (IsTrigger('1')) { return SCENE_RESULT; }		// '1'����
	int sceneState = -1;
	if (m_IsClear) {
		sceneState = UpdateClear();
		if (sceneState == NEXTSTAGE) {
			/* todo�F���̃X�e�[�W�� */
		}
		if (sceneState == GO_SELECT) {
			return SCENE_SELECT;
		}
	}
	
	return SCENE_GAME;
}

//==============================================================
//
//	GameScene�`�揈��
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void GameScene::Draw()
{
	SHADER->Bind(
		//���_�V�F�[�_�Ŏg�p����v�Z�̎��
		VS_WORLD,
		//�s�N�Z���V�F�[�_�Ŏg�p����v�Z�̎��
		//PS_UNLIT...�e�����Ȃ�
		//PS_LAMBERT...Diffuse��Ambient�̂�
		//			�@ �����\���͍s��Ȃ�
		//PS_PHONG...Lambert��
		//			 Specular��������
		PS_PHONG);
	//3D�̕��̂ɉe�����d�g��
	//3D�̖ʂɑ΂��Đ����Ȑ����l����(�@��)
	//��������̌��̌����ƁA�ʂ̖@����
	//���������������Ă�����A�e��������
	//�ʂƂ��Čv�Z���s��

	//�e������Ƃ��̃p�����[�^(�}�e���A��)
	//Diffuse(�g�U��)...���̂̐F
	//�����ɂ͐l�Ԃ̖ڂ͔�э���ł���
	//���̔g���ŐF��F�����Ă���̂�
	//���̂��ǂ̌��𒵂˕Ԃ��₷���̂���\��
	//���ڕ��̂ɓ�������B

	//Ambient(����)...�e�̐F
	//����̕��̂��璵�˕Ԃ�������
	//���̂ɓ������Ĕ��˂��Ă�����

	//Specular(���ˌ�)
	//���˂��Ă߂��Ⴍ��������Ă��镔��
	//�����̂悤�ȕ\�����s��

	//Emissive(����)
	//������镨�̂̌��̐F

	//SetLight�`�@�����̐F��ݒ�
	//Set�`�@���������������̂̔��˂��₷���F

	/*SHADER->SetLightAmbient(
		DirectX::XMFLOAT4(0.6f, 0.6f, 0.6f, 0.6f)
	);
	SHADER->SetLightSpecular(
		DirectX::XMFLOAT4(1, 1, 1, 1),
		20);*/

	//�@�I�u�W�F�N�g���Ƃ�
	//�@���[�J�����W������(���_)
	//�A���[�J�����W�����[���h���W�ɕϊ�
	//�B���[���h���W���J�������W�ɕϊ�
	//�C�J�����̉�p�Ɏ��܂�͈͂ɕϊ�(�X�N���[�����W)
	static float a = 0.0f;
	//���[���h���W�֕ϊ�
	//XMMatrixTranslation �ړ�
	//XMMatrixRotationX X���ŉ�]
	//XMMatrixRotationY Y���ŉ�]
	//XMMatrixRotationZ Z���ŉ�]
	//XMMatrixScaling �g�k
	//���ꂼ��̕ϊ��s���DirectX���v�Z���Ă����
	SHADER->SetWorld(XMMatrixRotationY(a += 3.141592f / 180.0));
	SHADER->SetWorld(XMMatrixTranslation(0, 0, 0));

	/*
	//�J�������W�n�ɕϊ�
	//��1����:�J�����̈ʒu
	//��2����:�J�����̒����_
	//��3����:�J�����̏����
	SHADER->SetView(
	DirectX::XMMatrixLookAtLH(
	DirectX::XMVectorSet(0, 2, -5, 0),
	DirectX::XMVectorSet(0, 0, 0, 0),
	DirectX::XMVectorSet(0, 1, 0, 0)
	));
	//�J�����̉�p��ݒ�
	//��1����:��p(���W�A���p
	//��2����:�A�X�y�N�g��
	//��3����:�j�A�N���b�v(�ߌi
	//��4����:�t�@�[�N���b�v(���i
	SHADER->SetProjection(
	DirectX::XMMatrixPerspectiveFovLH(
	3.141592f / 3,
	(float)SCREEN_WIDTH / SCREEN_HEIGHT,
	1.0f, 1000.0f
	));*/

	//g_pTPSCamera->Bind();

	if (m_IsClear) {
		DrawClear();
	}

	g_pCamera->Bind();
	
	///g_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�Ƃ肠�����L���[�u�͉�ʂ̉��Ɉړ�
	SHADER->SetWorld(DirectX::XMMatrixTranslation(sinf(a) * 3, 0, 3));

	//���������`��֐��R�����g�A�E�g���Ă����΂悩����
	//	g_pCube->Draw();

	//���f�����傫���̂ŏ���������
	SHADER->SetWorld(DirectX::XMMatrixScaling(0.01f, 0.01f, 0.01f));
	//g_pModel->Draw();


	// ����҂̕`��
	g_pCollector->Draw();
	g_pCollectionPoint->Draw();



	// �G�̕`��
	//g_pEnemyManager->Draw();

	// �s�N�~���`��
	g_pDwarfManager->Draw();

	// �e�̕`��
	g_pBulletManger->Draw();

	//g_pEnemy->Draw();
	SHADER->SetTexture(NULL);
	//	g_pBullet->Draw();

	// �X�e�[�W�`��
	g_pStageManager->Draw();


	// g_pShot->Draw();
	// �v���C���[�`��
	g_pPlayer->Draw();
	SHADER->SetWorld(DirectX::XMMatrixIdentity());
	
	//	EnableCulling(false);
	
	//	EnableCulling(true);

	g_pScore->Draw();

	g_pTutorial->Draw();

}

