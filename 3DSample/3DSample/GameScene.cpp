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
 *		 2022/01/18 �X�e�[�W�̃I�u�W�F�N�g�̔z�u(�g��)
 *		 2022/
 *
 * @brief �Q�[���V�[���Ɋւ��鏈��
 */

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************

////---�V�X�e���֘A
//#include "Camera.h"
//#include "Input.h"
//#include "TPSCamera.h"
//#include "Collision.h"
//#include "Shader.h"
//#include "Defines.h"

//// ---�V�[���֘A
#include "GameScene.h"
//#include "SelectScene.h"
//#include "Tutorial.h"
#include "Clear.h"
#include "GameOver.h"


//// ---�X�e�[�W�֘A
//#include "Stage.h"
//#include "StageObjectManager.h"
//
//// ---�Q�[���֘A-�v���C���[
//#include "Player.h"
//#include "GameObject.h"
//
//// ---�Q�[���֘A-�G�l�~�[
//#include "Enemy.h"
//#include "EnemyManager.h"
//
//// ---�Q�[���֘A-���l
//#include "DwarfManager.h"
//#include "DwarfStageCollision.h"
//
//// ---�Q�[���֘A-�e
//#include "BulletManager.h"
//#include "BulletTarget.h"
//
//// ---�Q�[���֘A-���
//#include "Collector.h"
//#include "CollectionPoint.h"
//
//// ---�Q�[���֘A-UI
//#include "Score.h"



//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define CONTROL_NUM		(5)
#define RECORD_MARGIN	(10)


//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
//Camera				*g_pCamera;
//TPSCamera			*g_pTPSCamera;
//Player				*g_pPlayer;
//
//StageManager		*g_pStageManager;
//StageObjectManager* g_pStageObjectManager;
//
//Collision			*g_pCollision;
//Collector			*g_pCollector;
//CollectionPoint		*g_pCollectionPoint;
//SelectScene			*g_pSelectScene;
//DwarfManager		*g_pDwarfManager;
//DwarfStageCollision	*g_pDwarfStageCollision;
//
//BulletManager		*g_pBulletManger;
//BulletTarget			* g_pBulletTarget;
//
//Score				*g_pScore;
//Tutorial			*g_pTutorial;


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
	m_pCamera = new Camera();
	m_pCamera->Init();

	// �����o�ϐ�������
	m_StageNum = StageNum;					// ���݂̃X�e�[�W�ԍ��ۑ�
	m_NextStageNum = m_StageNum;			// ���̃X�e�[�W�ԍ��ۑ��i���݂Ǝ�����v���Ȃ������ꍇ���̃X�e�[�W�ֈڍs�j
	m_IsClear = false;						// �N���A�t���O
	m_IsGameOver = false;					// �Q�[���I�[�o�[�t���O
	
	// �e�̊Ǘ��N���X
	m_pBulletManger = new BulletManager();
	m_pBulletManger->Init();

	// �e�̗����n�_�N���X
	m_pBulletTarget = new BulletTarget();
	m_pBulletTarget->Init();

	// ���l�Ǘ��N���X���̉�
	m_pDwarfManager = new DwarfManager();
	m_pDwarfManager->Init();

	// ���l�̃X�e�[�W�̓����蔻��p�̃u���b�N����������
	m_pDwarfStageCollision = new DwarfStageCollision();
	m_pDwarfStageCollision->Init();

	// �v���C���[�N���X���̉�
	m_pPlayer = new Player();
	m_pPlayer->Init();
	
	// TPS�J�����̓v���C���[����
	//g_pTPSCamera = new TPSCamera();
	//g_pTPSCamera->SetTargetObj(g_pPlayer);
	//g_pTPSCamera->Init(XMFLOAT3(0, 12.0f, -22.5f));


	//g_pPlayer->SetControllCamera(g_pTPSCamera);
	//g_pPlayer->GetCameraPos(g_pTPSCamera);

	// �����
	m_pCollector = new Collector();
	m_pCollector->Init();
	
	// ����|�C���g
	m_pCollectionPoint = new CollectionPoint();
	m_pCollectionPoint->Init();

	// �G�N���X���̉�
	//g_pEnemy = new Enemy();
	//g_pEnemy->LoadEnemy("Assets/Model/tyoutinobake.fbx");
	//g_pEnemy->Init();

	// �G�̊Ǘ��N���X�̎���
	//g_pEnemyManager = new EnemyManager();
	//g_pEnemyManager->Init();

	// �X�e�[�W�N���X�̎��̉�
	m_pStageManager = new StageManager();
	m_pStageManager->Init(StageNum);

	// �X�e�[�W�I�u�W�F�N�g�̎��̉�
	m_pStageObjectManager = new StageObjectManager;
	m_pStageObjectManager->Init(StageNum);

	
	// �����蔻��N���X
	m_pCollision = new Collision();
	m_pCollision->Init();

	// �X�R�A�N���X
	m_pScore = new Score();
	m_pScore->Init();

	// �`���[�g���A���N���X
	m_pTutorial = new Tutorial();
	m_pTutorial->Init();

	// �Q�[���N���A������
	InitClear();

	// �Q�[���I�[�o�[������
	InitGameOver();

	// �����蔻��z��Ƀf�[�^������
	for (int i = 0; i < MAX_DWARF; i++) {
		for (int j = 0; j < m_pDwarfStageCollision->GetStageNum(); j++) {
			m_pCollision->Register(m_pDwarfManager->GetDwarf(i), m_pDwarfStageCollision->GetDwarfStageCollision(j));
		}
		//for (int k = i+1; k < MAX_DWARF; k++) {
		//	g_pCollision->Register(g_pDwarfManager->GetDwarf(i), g_pDwarfManager->GetDwarf(k));
		//}
	}


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
	m_pScore->Uninit();
	delete m_pScore;

	// �`���[�g���A���V�[���̏I������
	m_pTutorial->Uninit();
	delete m_pTutorial;

	// �����蔻��N���X�̏I������
	m_pCollision->Uninit();
	delete m_pCollision;

	// �X�e�[�W�N���X�̏I������
	m_pStageManager->Uninit();
	delete m_pStageManager;

	// �X�e�[�W�I�u�W�F�N�g�̏I������
	m_pStageObjectManager->Uninit();
	delete m_pStageObjectManager;

	//�v���C���[�̏I������
	m_pPlayer->Uninit();
	delete m_pPlayer;

	// ���l�̃X�e�[�W�̓����蔻��I��
	m_pDwarfStageCollision->Uninit();
	delete m_pDwarfStageCollision;

	// ���l�I������
	m_pDwarfManager->Uninit();
	delete m_pDwarfManager;

	// �e�̃N���X���
	m_pBulletManger->Uninit();
	delete m_pBulletManger;

	// �e�̗����n�_�N���X���
	m_pBulletTarget->Uninit();
	delete m_pBulletTarget;

	// �����
	m_pCollector->Uninit();
	delete m_pCollector;
	
	// ����|�C���g
	m_pCollectionPoint->Uninit();
	delete m_pCollectionPoint;

	// �G�l�~�[�I������
	//delete g_pEnemy;

	// �J�����ޏI��
	m_pCamera->Uninit();
	delete m_pCamera;
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
	// �����n�_�̍X�V
	m_pBulletTarget->Update();

	// �v���C���[�X�V
	m_pPlayer->SetBulletTargetPos(m_pBulletTarget->GetBulletTargetPos());
	m_pPlayer->Update();

	// �e�X�V
	m_pBulletManger->SetPlayePos(m_pPlayer->GetPlayerPos());				// �v���C���[�̍��W��ݒ�
	m_pBulletManger->SetTargetPos(m_pBulletTarget->GetBulletTargetPos());	// �^�[�Q�b�g�̍��W��ݒ�
	m_pBulletManger->SetPlayerAngle(m_pPlayer->GetPlayerAngle());
	m_pBulletManger->Update();

	// ���l�X�V����
	m_pDwarfManager->SetBulletInfo(m_pBulletManger);	// �e�̏������l�̃����o�ϐ��ɓn��
	m_pDwarfManager->Update();
	
	// �����
	m_pCollector->Update();
	m_pCollectionPoint->Update();


	// �G�l�~�[�X�V
	//g_pEnemy->Update();
	//g_pEnemyManager->Update();

	// �X�e�[�W�X�V
	m_pStageManager->Update();

	// �X�e�[�W�I�u�W�F�N�g�X�V
	m_pStageObjectManager->Update();


	//----- �v���C���[�̍��W���擾 -----
	g_recPlayerPos = m_pPlayer->GetPos();
	//g_pEnemy->TargetPos(g_recPlayerPos);
	//g_pEnemyManager->SetEnemyTarget(g_recPlayerPos);

	// �X�R�A�X�V
	m_pScore->Update();

	// �`���[�g���A���\���X�V
	m_pTutorial->Update();


	//***************************************************************
	// ���l����
	//***************************************************************
	XMFLOAT3 randomPos = XMFLOAT3(0.0f, 1.5f + DWARF_SIZE, 0.0f);	// �����_��
	for (int j = 0; j < m_pDwarfManager->GetDwarfNum(); j++) {
		if (m_pDwarfManager->GetDwarf(j)->GetCircumferenceFlg()) {
			//----- �����ŖړI�n��ݒ� -----
			randomPos.x = (float)(rand() % 30 - 15.0f);	//-10.0 ~ 10.0�̊Ԃ̗���
			randomPos.z = (float)(rand() % 30 - 15.0f);
			m_pDwarfManager->GetDwarf(j)->TargetPos(randomPos);
			m_pDwarfManager->GetDwarf(j)->SetCircumferenceFlg(false);
		}
	}


	for (int i = 0; i < m_pDwarfManager->GetDwarfNum(); i++) 
	{
		if (!m_pDwarfManager->GetDwarf(i)->GetAliveFlg()) {		// �������ĂȂ���������Ȃ�
			if (!m_IsClear) {
				m_IsGameOver = true;
			}
			break;
		}
		//----- ���l������� -----
		if (CollisionSphere(m_pDwarfManager->GetDwarf(i), m_pCollector)) {
			m_pDwarfManager->GetDwarf(i)->SetCollectionFlg(true);
			m_pScore->SetScore(m_pDwarfManager->GetDwarfNum());
			m_pDwarfManager->AddCollectionSum();
		}

		//----- ���l�̒ǐՏ��� -----
		for (int j = 0; j < MAX_BULLET; j++) {
			g_pBullet[j] = m_pBulletManger->GetBullet(j);						// �e���擾
			if (g_pBullet[j]->use) {									// �Ō�̎w����ʂ�
				g_LastBulletNun = j;
			}
			if (!g_pBullet[j]->use) {								// �e���p�Ȃ�X�L�b�v
				continue;
			}
			//if (!g_pDwarfManager->GetDwarf(i)->GetMoveFlg()) {
			//	continue;
			//}
			if (m_pBulletManger->GetBullet(j)->GetLandingFlg()) {		// �e�����n�����u�Ԃɂ��̍��W��ۑ�����
				g_recBulletPos = g_pBullet[g_LastBulletNun]->GetPos();	// �Ō�̎w���ʒu��ۑ�
			}
			//---�s�N�~���̒e�ւ̒ǔ�
			m_pDwarfManager->GetDwarf(i)->TargetPos(g_recBulletPos);
		}

	}
	//----- �Q�[���N���A -----
	if (m_pDwarfManager->GetCollectionSum() == MAX_DWARF) {		// ���l�S����ŃN���A
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
	if (IsRelease('0') || IsRelease(JPadButton::R_SHOULDER)) {				// 0�L�[�ŃQ�[���N���A
		if (!m_IsGameOver) {
			m_IsClear = true;
		}
	}
	if (IsRelease('9') || IsRelease(JPadButton::L_SHOULDER)) {				// �X�L�[�ŃQ�[���I�[�o�[
		if (!m_IsClear) {
			m_IsGameOver = true;
		}
	}
#endif

	//***************************************************************
	//	�J�����X�V
	//***************************************************************	
	//g_pTPSCamera->Update();
	m_pCamera->Update();


	//***************************************************************
	// ���ׂĂ̈ړ�(�X�V����)������ł���
	// ���ׂẴI�u�W�F�N�g�̓����蔻����s��
	//*************************************************************+*
	m_pCollision->Update();

	//***************************************************************
	//	�O�Ղ̍X�V
	//***************************************************************		//�O�Ղ̍X�V
	for (int i = CONTROL_NUM * RECORD_MARGIN - 1; i > 0; i--)
	{
		g_recordPos[i] = g_recordPos[i - 1];
	}
	g_recordPos[0] = m_pPlayer->GetPos();

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
	m_pCamera->Bind();
	
	//g_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�Ƃ肠�����L���[�u�͉�ʂ̉��Ɉړ�
	SHADER->SetWorld(DirectX::XMMatrixTranslation(sinf(a) * 3, 0, 3));

	//���f�����傫���̂ŏ���������
	SHADER->SetWorld(DirectX::XMMatrixScaling(0.01f, 0.01f, 0.01f));


	// ����҂̕`��
	m_pCollector->Draw();
	m_pCollectionPoint->Draw();

	// �G�̕`��
	//g_pEnemyManager->Draw();

	// �s�N�~���`��
	m_pDwarfManager->Draw();

	// �e�̕`��
	m_pBulletManger->Draw();

	// �����n�_�̕`��
	m_pBulletTarget->Draw();


	//g_pEnemy->Draw();
	//SHADER->SetTexture(NULL);

	// �X�e�[�W�`��
	m_pStageManager->Draw();
#ifdef _DEBUG
	// ���l�̃X�e�[�W�̓����蔻��悤�u���b�N�`��
	m_pDwarfStageCollision->Draw();
#endif 


	// �X�e�[�W�I�u�W�F�N�g�`��
	m_pStageObjectManager->Draw();


	// �v���C���[�`��
	m_pPlayer->Draw();


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
	m_pScore->Draw();

	// �`���[�g���A���`��
	//g_pTutorial->Draw();

}

