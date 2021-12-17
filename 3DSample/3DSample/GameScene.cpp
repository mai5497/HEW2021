/**
 * @file GameScene.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 *		 2021/12/03 �s�N�~���ǉ�
 *		 2021/12/09 �G�l�~�[�����ɒǐՂ���̂��폜
 *		 2021/12/11 �e�̒ǐՂ̏����̕ύX�i�s�N�~�������āA�U�����n�߂�j
 *					�G�̒ǐՂ̏����̕ύX�i�s�N�~���ɓ��������������j
 *		 2021/12/17 �Ղ�����Ă���
 *		 2021/12/17 �Ղ�����
 * @brief �Q�[���V�[���Ɋւ��鏈��
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
	//�����̃N���X�̎��̉�
	g_pCube = new Cube();

	//���f���N���X�̎��̉�
	g_pModel = new Model();
	g_pModel->LoadModel("Assets/Model/tyoutin.fbx");

	//�J�����N���X�̎��̉�
	/*
	g_pCamera = new Camera();
	g_pCamera->Init();
	*/
	//�v���C���[�N���X���̉�
	g_pPlayer = new Player();
	g_pPlayer->Init();
	// TPS�J�����̓v���C���[����
	g_pTPSCamera = new TPSCamera();
	g_pTPSCamera->SetTargetObj(g_pPlayer);
	g_pTPSCamera->Init();

	g_pPlayer->SetControllCamera(g_pTPSCamera);

	g_pPlayer->GetCameraPos(g_pTPSCamera);

	// �s�N�~���Ǘ��N���X���̉�
	g_pPikminManager = new PikminManager();
	g_pPikminManager->Init();

	//�G�N���X���̉�
	//g_pEnemy = new Enemy();
	//g_pEnemy->LoadEnemy("Assets/Model/tyoutinobake.fbx");
	//g_pEnemy->Init();

	// �G�̊Ǘ��N���X�̎���
	g_pEnemyManager = new EnemyManager();
	g_pEnemyManager->Init();

	//	g_pShot = new Shot();
	//	g_pShot->Init();

	//�X�e�[�W�N���X�̎��̉�
	g_pStage = new Stage();
	g_pStage->Init();

	//�����蔻��N���X
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

	// �s�N�~���I������
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

	// �s�N�~���X�V����
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


	//���ׂĂ̈ړ�(�X�V����)������ł���
	//���ׂẴI�u�W�F�N�g�̓����蔻����s��
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

	
	// �G�l�~�[���v���C���[��ǂ�������
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
			//---�����ň�ԋ߂���Ƀ^�[�Q�b�g���ڂ�����
			//g_pEnemyManager->SetEnemyTarget();
		}
	 	//g_pEnemy->EnemyStop();
	}



	

	// �e�̒ǐՂƓ����蔻��
	for (int i = 0; i < g_pPlayer->GetBulletNum(); i++)
	{
		g_pBullet[i] = g_pPlayer->GetBullet(i);	// �e���擾
		if (g_pBullet[i]->use) {	// �Ō�̎w����ʂ�
			g_LastBulletNun = i;
		}
		for (int j = 0; j < g_pPikminManager->GetPikminNum(); j++)
		{
			if (!g_pBullet[i]->use){	// �e���g�p�Ȃ�X�L�b�v
				continue;
			}
			if (!g_pPikminManager->GetPikmin(j)->GetFollowFlg()) {	// �ǐՃt���O�������Ă��Ȃ��Ƃ��͓����Ȃ�
				continue;
			}
			g_recBulletPos = g_pBullet[g_LastBulletNun]->GetPos();	// �Ō�̎w���ʒu��ۑ�
			//---�s�N�~���̒e�ւ̒ǔ�
			g_pPikminManager->SetPikminTarget(g_recBulletPos);
			//g_pCollision->Register(g_pPlayer->GetBullet(i), g_pPikminManager->GetPikmin(j));

			if (!g_pCollision->CollisionSphere(g_pPlayer->GetBullet(i), g_pPikminManager->GetPikmin(j))) {
				continue;
			}
			g_pPikminManager->GetPikmin(j)->SetAttackFlg(true);


		}
		g_pCollision->Register(g_pPlayer->GetBullet(i), g_pStage->GetField(i));	// �e�ƃt�B�[���h�̓����蔻��
	}
	
	if (IsTrigger('X')){
		g_pPlayer->DestroyBullet();
	}

	g_pTPSCamera->Update();
	g_pPlayerToEnemy->Update();
	g_pCollision->Update();
	//�O�Ղ̍X�V
	for (int i = CONTROL_NUM * RECORD_MARGIN - 1; i > 0; i--)
	{
		g_recordPos[i] = g_recordPos[i - 1];
	}
	g_recordPos[0] = g_pPlayer->GetPos();

	//�O�Ղ̌v�Z
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
	if (IsTrigger('1')) { return SCENE_RESULT; }
	
	return SCENE_GAME;
}
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
	SHADER->SetWorld(
		DirectX::XMMatrixRotationY(
			a += 3.141592f / 180.0f
		));
	SHADER->SetWorld(
		DirectX::XMMatrixTranslation(0, 0, 0)
	);
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



	g_pTPSCamera->Bind();
	

	///g_buffer.Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//�Ƃ肠�����L���[�u�͉�ʂ̉��Ɉړ�
	SHADER->SetWorld(
		DirectX::XMMatrixTranslation(sinf(a) * 3, 0, 3));
	//���������`��֐��R�����g�A�E�g���Ă����΂悩����
	//	g_pCube->Draw();

	//���f�����傫���̂ŏ���������
	SHADER->SetWorld(
		DirectX::XMMatrixScaling(
			0.01f, 0.01f, 0.01f
		));
	//g_pModel->Draw();

	// �v���C���[�`��

	// �G�̕`��
	g_pEnemyManager->Draw();

	// �s�N�~���`��
	g_pPikminManager->Draw();

	//g_pEnemy->Draw();
	SHADER->SetTexture(NULL);
	//	g_pBullet->Draw();

	// �X�e�[�W�`��
	g_pStage->Draw();


	// g_pShot->Draw();
	g_pPlayer->Draw();
	SHADER->SetWorld(DirectX::XMMatrixIdentity());
	

	//	EnableCulling(false);
	
	//	EnableCulling(true);
}
