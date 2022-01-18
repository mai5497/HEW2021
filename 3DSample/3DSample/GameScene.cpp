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
 *		 2022/01/10 �o���b�g�̎g�p�ύX�`(�g��)
 *  	 2022/01/16 �o���b�g�̗����n�_�̃I�u�W�F�N�g�ǉ�(�g��)
 *		 2022/01/17 �Q�[���I�[�o�[�N���A�������ɏo��̂Ȃ������i�ɒn�c�j
 *
 * @brief �Q�[���V�[���Ɋւ��鏈��
 */

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************

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
#include "StageManager.h"

// ---�Q�[���֘A-�v���C���[
#include "Player.h"
#include "GameObject.h"

// ---�Q�[���֘A-�G�l�~�[
#include "Enemy.h"
#include "EnemyManager.h"

// ---�Q�[���֘A-���l
#include "DwarfManager.h"

// ---�Q�[���֘A-�e
#include "BulletManager.h"
#include "BulletTarget.h"

// ---�Q�[���֘A-���
#include "Collector.h"
#include "CollectionPoint.h"

// ---�Q�[���֘A-UI
#include "Score.h"



//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define CONTROL_NUM		(5)
#define RECORD_MARGIN	(10)
#define TARGETSET_TIME	(300)

//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
Camera				*g_pCamera;
TPSCamera			*g_pTPSCamera;
Player				*g_pPlayer;
StageManager		*g_pStageManager;
Collision			*g_pCollision;
Collector			*g_pCollector;
CollectionPoint		*g_pCollectionPoint;
SelectScene			*g_pSelectScene;
DwarfManager		*g_pDwarfManager;

BulletManager		*g_pBulletManger;
BulletTarget			* g_pBulletTarget;

Score				*g_pScore;
Tutorial			*g_pTutorial;


//Enemy				*g_pEnemy;
//EnemyManager		*g_pEnemyManager;

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
	g_pCamera = new Camera();
	g_pCamera->Init();

	// �����o�ϐ�������
	m_StageNum = StageNum;					// ���݂̃X�e�[�W�ԍ��ۑ�
	m_NextStageNum = m_StageNum;			// ���̃X�e�[�W�ԍ��ۑ��i���݂Ǝ�����v���Ȃ������ꍇ���̃X�e�[�W�ֈڍs�j
	m_IsClear = false;						// �N���A�t���O
	m_IsGameOver = false;					// �Q�[���I�[�o�[�t���O
	
	// �e�̊Ǘ��N���X
	g_pBulletManger = new BulletManager();
	g_pBulletManger->Init();

	// �e�̗����n�_�N���X
	g_pBulletTarget = new BulletTarget();
	g_pBulletTarget->Init();

	// ���l�Ǘ��N���X���̉�
	g_pDwarfManager = new DwarfManager();
	g_pDwarfManager->Init();

	// �v���C���[�N���X���̉�
	g_pPlayer = new Player();
	g_pPlayer->Init();
	
	// TPS�J�����̓v���C���[����
	//g_pTPSCamera = new TPSCamera();
	//g_pTPSCamera->SetTargetObj(g_pPlayer);
	//g_pTPSCamera->Init(XMFLOAT3(0, 12.0f, -22.5f));


	//g_pPlayer->SetControllCamera(g_pTPSCamera);
	//g_pPlayer->GetCameraPos(g_pTPSCamera);

	// �����
	g_pCollector = new Collector();
	g_pCollector->Init();
	
	// ����|�C���g
	g_pCollectionPoint = new CollectionPoint();
	g_pCollectionPoint->Init();

	// �G�N���X���̉�
	//g_pEnemy = new Enemy();
	//g_pEnemy->LoadEnemy("Assets/Model/tyoutinobake.fbx");
	//g_pEnemy->Init();

	// �G�̊Ǘ��N���X�̎���
	//g_pEnemyManager = new EnemyManager();
	//g_pEnemyManager->Init();

	// �X�e�[�W�N���X�̎��̉�
	
	g_pStageManager = new StageManager();
	g_pStageManager->Init(StageNum);

	// �����蔻��N���X
	g_pCollision = new Collision();
	g_pCollision->Init();

	// �X�R�A�N���X
	g_pScore = new Score();
	g_pScore->Init();

	// �`���[�g���A���N���X
	g_pTutorial = new Tutorial();
	g_pTutorial->Init();

	// �Q�[���N���A������
	InitClear();

	// �Q�[���I�[�o�[������
	InitGameOver();

	// BGM�Đ�
	CSound::Play(GAME_BGM);

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
	// �X�R�A�N���X�̏I������
	g_pScore->Uninit();
	delete g_pScore;

	// �`���[�g���A���V�[���̏I������
	g_pTutorial->Uninit();
	delete g_pTutorial;

	// �����蔻��N���X�̏I������
	g_pCollision->Uninit();
	delete g_pCollision;

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

	// �e�̗����n�_�N���X���
	g_pBulletTarget->Uninit();
	delete g_pBulletTarget;

	// �����
	g_pCollector->Uninit();
	delete g_pCollector;
	
	// ����|�C���g
	g_pCollectionPoint->Uninit();
	delete g_pCollectionPoint;

	// �G�l�~�[�I������
	//delete g_pEnemy;

	// �J�����ޏI��
	g_pCamera->Uninit();
	delete g_pCamera;
	//g_pTPSCamera->Uninit();
	//delete g_pTPSCamera;

	// �Q�[���N���A�I��
	UninitClear();

	// �Q�[���I�[�o�[�I��
	UninitGameOver();

	// BGM��~
	CSound::Stop(GAME_BGM);
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

	// �����n�_�̍X�V
	g_pBulletTarget->Update();

	// �e�X�V
	g_pBulletManger->SetPlayePos(g_pPlayer->GetPlayerPos());				// �v���C���[�̍��W��ݒ�
	g_pBulletManger->SetTargetPos(g_pBulletTarget->GetBulletTargetPos());	// �^�[�Q�b�g�̍��W��ݒ�
	g_pBulletManger->SetPlayerAngle(g_pPlayer->GetPlayerAngle());
	g_pBulletManger->Update();

	// ���l�X�V����
	g_pDwarfManager->SetBulletInfo(g_pBulletManger);	// �e�̏������l�̃����o�ϐ��ɓn��
	g_pDwarfManager->Update();
	
	// �����
	g_pCollector->Update();
	g_pCollectionPoint->Update();


	// �G�l�~�[�X�V
	//g_pEnemy->Update();
	//g_pEnemyManager->Update();

	// �X�e�[�W�X�V
	g_pStageManager->Update();

	//----- �v���C���[�̍��W���擾 -----
	g_recPlayerPos = g_pPlayer->GetPos();
	//g_pEnemy->TargetPos(g_recPlayerPos);
	//g_pEnemyManager->SetEnemyTarget(g_recPlayerPos);

	// �X�R�A�X�V
	g_pScore->Update();

	// �`���[�g���A���\���X�V
	g_pTutorial->Update();


	//***************************************************************
	// ���ׂĂ̈ړ�(�X�V����)������ł���
	// ���ׂẴI�u�W�F�N�g�̓����蔻����s��
	//*************************************************************+*
	//----- �e�Ə� -----
	//for (int i = 0; i < g_pPlayer->GetBulletNum(); i++) {
	//	g_pCollision->Register(g_pPlayer->GetBullet(i), g_pStage->GetField(1));
	//}


	//***************************************************************
	// ���l����
	//***************************************************************
	static int Timer;
	Timer--;
	if (Timer < 0) {
		XMFLOAT3 randomPos = XMFLOAT3(0.0f, 1.0f + DWARF_SIZE, 0.0f);	// �����_��
		for (int j = 0; j < g_pDwarfManager->GetDwarfNum(); j++) {
			//----- �����ŖړI�n��ݒ� -----
			randomPos.x = (float)(rand() % 20 - 10.0f);	//-10.0 ~ 10.0�̊Ԃ̗���
			randomPos.z = (float)(rand() % 20 - 10.0f);
			g_pDwarfManager->GetDwarf(j)->TargetPos(randomPos);
		}
		Timer = TARGETSET_TIME;
	}

	for (int i = 0; i < g_pDwarfManager->GetDwarfNum(); i++) 
	{
		if (!g_pDwarfManager->GetDwarf(i)->GetAliveFlg()) {		// �������ĂȂ���������Ȃ�
			if (!m_IsClear) {
				m_IsGameOver = true;
			}
			break;
		}
		//----- ���l�Ə��̓����蔻�� -----
		g_pCollision->Register(g_pDwarfManager->GetDwarf(i), g_pStageManager->GetStage(0));
		g_pCollision->Register(g_pDwarfManager->GetDwarf(i), g_pStageManager->GetStage(1));
		g_pCollision->Register(g_pDwarfManager->GetDwarf(i), g_pStageManager->GetStage(2));

		//----- ���l������� -----
		if (CollisionSphere(g_pDwarfManager->GetDwarf(i), g_pCollector)) {
			g_pDwarfManager->GetDwarf(i)->SetCollectionFlg(true);
			g_pScore->SetScore(g_pDwarfManager->GetDwarfNum());
			g_pDwarfManager->AddCollectionSum();
		}

		//----- ���l�̒ǐՏ��� -----
		for (int j = 0; j < MAX_BULLET; j++) {
			g_pBullet[j] = g_pBulletManger->GetBullet(j);						// �e���擾
			if (g_pBullet[j]->use) {									// �Ō�̎w����ʂ�
				g_LastBulletNun = j;
			}
			if (!g_pBullet[j]->use) {								// �e���p�Ȃ�X�L�b�v
				continue;
			}
			if (g_pBulletManger->GetBullet(j)->GetLandingFlg()) {		// �e�����n�����u�Ԃɂ��̍��W��ۑ�����
				g_recBulletPos = g_pBullet[g_LastBulletNun]->GetPos();	// �Ō�̎w���ʒu��ۑ�
			}
			//---�s�N�~���̒e�ւ̒ǔ�
			g_pDwarfManager->GetDwarf(i)->TargetPos(g_recBulletPos);
		}

	}
	//----- �Q�[���N���A -----
	if (g_pDwarfManager->GetCollectionSum() == MAX_DWARF) {		// ���l�S����ŃN���A
		if (!m_IsGameOver) {
			m_IsClear = true;
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
#ifdef _DEBUG
	//*******************************************************************************
	//	�f�o�b�O�p�L�[����
	//*******************************************************************************
	//if (IsRelease('X')){				// X�L�[�Œe����
	//	g_pBulletManger->DestroyBullet();
	//}
	if (IsRelease('0' || IsRelease(JPadButton::R_SHOULDER))) {				// 0�L�[�ŃQ�[���N���A
		if (!m_IsGameOver) {
			m_IsClear = true;
		}
	}
	if (IsRelease('9' || IsRelease(JPadButton::L_SHOULDER))) {				// �X�L�[�ŃQ�[���I�[�o�[
		if (!m_IsClear) {
			m_IsGameOver = true;
		}
	}
#endif

	//***************************************************************
	//	�J�����X�V
	//***************************************************************	
	//g_pTPSCamera->Update();
	g_pCamera->Update();


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
	//	�O�Ղ̌v�Z
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
	int sceneState = -1;
	if (m_IsClear) {
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

	//SHADER->SetAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//SHADER->SetLightAmbient(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//SHADER->SetLightSpecular(XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f),0.0f);

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
	DirectX::XMVectorSet(0, 10, 0, 0),
	DirectX::XMVectorSet(0, 1, 0, 0),
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
	));
	*/

	//g_pTPSCamera->Bind();
	g_pCamera->Bind();
	
	//g_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�Ƃ肠�����L���[�u�͉�ʂ̉��Ɉړ�
	SHADER->SetWorld(DirectX::XMMatrixTranslation(sinf(a) * 3, 0, 3));

	//���f�����傫���̂ŏ���������
	SHADER->SetWorld(DirectX::XMMatrixScaling(0.01f, 0.01f, 0.01f));


	// ����҂̕`��
	g_pCollector->Draw();
	g_pCollectionPoint->Draw();

	// �G�̕`��
	//g_pEnemyManager->Draw();

	// �s�N�~���`��
	g_pDwarfManager->Draw();

	// �e�̕`��
	g_pBulletManger->Draw();

	// �����n�_�̕`��
	g_pBulletTarget->Draw();


	//g_pEnemy->Draw();
	//SHADER->SetTexture(NULL);

	// �X�e�[�W�`��
	g_pStageManager->Draw();

	// �v���C���[�`��
	g_pPlayer->Draw();




	SHADER->SetWorld(DirectX::XMMatrixIdentity());
	
	//	EnableCulling(false);
	//	EnableCulling(true);
 


	// �Q�[���N���A�t���O�������Ă���Ƃ��N���A�`��
	if (m_IsGameOver) {
		DrawGameOver();
	}

	// �Q�[���I�[�o�[�t���O�������Ă���Ƃ��Q�[���I�[�o�[�`��
	if (m_IsClear) {
		DrawClear();
	}
	
	// �X�R�A�`��
	g_pScore->Draw();

	// �`���[�g���A���`��
	//g_pTutorial->Draw();

}

