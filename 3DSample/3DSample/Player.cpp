/**
 * @file Player.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 *		 2021/12/19 �Ԑe���킯�đłĂ�悤��
 * @brief �v���C���[�Ɋւ��鏈��
 */
#include "Player.h"
#include "Input.h"
#include "TPSCamera.h"
#include "MyVector.h"
#include "Collision.h"
#include <math.h>
#include "Controller.h"
#include "MyMath.h"

#define FPS 60

DirectX::XMFLOAT3 pOldCameraPos;

Player::Player()
	:m_pControllCamera(nullptr)
	, m_ppBullets(NULL)
	, m_nBulletNum(0)
{
	m_pos.y = 1.0f;
	m_Angle = DirectX::XMFLOAT3(0, 0, 0);
	m_collisionType = COLLISION_DYNAMIC;
}
Player::~Player()
{
	m_pControllCamera = nullptr;
	Uninit();
}

bool Player::Init()
{
	struct BulletSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};


	BulletSetting settings[] = {
		{ DirectX::XMFLOAT3(m_pos),
		DirectX::XMFLOAT3(30,1,30), },
	{ DirectX::XMFLOAT3(m_pos),
	DirectX::XMFLOAT3(30,1,30), },
	{ DirectX::XMFLOAT3(m_pos),
	DirectX::XMFLOAT3(30,1,30), },
	{ DirectX::XMFLOAT3(m_pos),
	DirectX::XMFLOAT3(30,1,30), },
	{ DirectX::XMFLOAT3(m_pos),
	DirectX::XMFLOAT3(30,1,30), },
	};

	//�����f�[�^����e�����v�Z
	m_nBulletNum = sizeof(settings) / sizeof(settings[0]);
	//�|�C���^���i�[����z����쐬
	m_ppBullets = new Bullet *[m_nBulletNum];
	//���ꂼ��̔z��ɒe���������m��
	for (int i = 0; i < m_nBulletNum; i++)
	{
		m_ppBullets[i] = new Bullet(settings[i].size);
		m_ppBullets[i]->SetPos(settings[i].pos);
		m_ppBullets[i]->Init();	// �e�p������
	}
	GameObject::Init();	// �v���C���[�p�������H
	return true;
}

void Player::Uninit()
{
	if (m_ppBullets != NULL)
	{
		for (int i = 0; i < m_nBulletNum; i++)
		{
			//�ʂɍ폜
			delete m_ppBullets[i];
		}
		//�z����폜
		delete[] m_ppBullets;
		m_ppBullets = NULL;
	}
	GameObject::Uninit();
}

void Player::Update()
{
	//----- �ϐ������� -----
	XMFLOAT2 Axis = LeftThumbPosition();
	bool rbFlg = true;

	bool keyL = IsPress('A');
	bool keyR = IsPress('D');
	bool keyU = IsPress('W');
	bool keyD = IsPress('S');
	bool keyBlue = IsPress('E');
	bool keyRed = IsPress('Q');
	bool keyJ = IsTrigger(VK_SPACE);

	//�P�b�ԁi60FPS�j��2M�i���Ƃ�\���B
	const float Move = 10.0f / 60;
	m_move = DirectX::XMFLOAT3(Axis.x, m_move.y, Axis.y);
	float CameraRad = m_pControllCamera->GetxzAngle() * 3.14159265359f / 180.0f;
	
	//�v���C���[�ړ�
	m_move.y -= 0.01f;
	if (keyL) 
	{
		m_move.x -= Move;
		if (m_Angle.y >= -CameraRad - 90.0f * 3.1415926f / 180.0f)
		{
			m_Angle.y -= 0.1f;
		}
	}

	if (keyR) 
	{ 
		m_move.x += Move;

		if (m_Angle.y <= -CameraRad + 90.0f * 3.1415926f / 180.0f)
		{
			m_Angle.y += 0.1f;
		}
	}
	if (keyU)
	{
		m_move.z += Move;
		if (m_Angle.y <= -CameraRad)
			m_Angle.y += 0.1f;
		if (m_Angle.y >= -CameraRad)
			m_Angle.y -= 0.1f;
	}

	if (keyRed) {
		rbFlg = true;	// ��
	}

	if (keyBlue) {
		rbFlg = false;	// ��
	}

	if (keyD) { m_move.z -= Move; }
	if (keyJ) { m_move.y += 0.2f; }

	if (IsTrigger('Z'))
	{
		CreateBullet(m_pControllCamera,rbFlg);
		//for (int i = 0; i < g_pPikminManager->GetPikminNum(); i++) {
		//	g_pPikminManager->GetPikmin(i)->SetFollowFlg(true);
		//}

	}


	//if (Input::instance().getControllerConnection())
	//{

	//}

	MyVector2 direction(0, 0);

	// �ɍ��W���g����TPS���_
	direction.x = m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	direction.y = m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);
	direction = direction.GetNormalize();

	////���W���X�V
	//m_pos.x += m_move.x;
	//m_pos.y += m_move.y;
	//m_pos.z += m_move.z;

	//m_pos.x += m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//m_pos.y += m_move.y;
	//m_pos.z += m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);

	//�����蔻��
	m_move.x = direction.x * Move;
	m_move.z = direction.y * Move;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (!m_ppBullets[i]->use)
		{
			continue;
		}
		m_ppBullets[i]->Update();
	}
}

void Player::Draw()
{
	DirectX::XMFLOAT3 pPos = m_pos;
	DirectX::XMFLOAT3 pSize = m_size;

	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (!m_ppBullets[i]->use)
		{
			continue;
		}
		m_ppBullets[i]->Draw();
	}

	CharacterBase::Draw();
}

Bullet *Player::GetBullet(int index)
{
	if (index < m_nBulletNum)
	{ 
		return m_ppBullets[index];
	}
	return NULL;
}

int Player::GetBulletNum()
{
	return m_nBulletNum;
}

void Player::SetControllCamera(Camera *pCamera)
{
	m_pControllCamera = pCamera;
}

// Player��Enemy���߂Â��Ă���֐�
void Player::PlayerToEnemy(GameObject* pObj)
{
	//�G�̈ʒu
	DirectX::XMFLOAT3 EnemyNear = pObj->GetPos();

	//�v���C���[�̈ʒu
	DirectX::XMFLOAT3 PlayerNear = m_pos;

	// �G�̈ړ�����(�ړ����x)���v���C���[�̕��֌�����
	DirectX::XMFLOAT3 dir;
	dir.x = m_pos.x - pObj->GetPos().x;
	dir.y = m_pos.y - pObj->GetPos().y;
	dir.z = m_pos.z - pObj->GetPos().z;

	//�x�N�g���̑傫��
	float L;
	L = sqrtf((dir.x * dir.x) +
		(dir.y * dir.y) +
		(dir.z * dir.z));

	//// dir �̒�����1�ɂ���(���K��)
	dir.x = dir.x / L;
	dir.y = dir.y / L;
	dir.z = dir.z / L;

	// ������1�ɂȂ����x�N�g���Ɉړ������������x��������(�G�̑��x)
	dir.x = dir.x * 0.08f;
	dir.y = dir.y * 0.08f;
	dir.z = dir.z * 0.08f;

	pObj->SetMove(dir);


}

void Player::GetCameraPos(TPSCamera* pCamera)
{
	pOldCameraPos = pCamera->GetCameraPos();
}

// �藠���𐶐�����֐�
void Player::CreateBullet(Camera* pCamera , bool rbFlg)
{
	DirectX::XMFLOAT3 pCameraPos = pCamera->GetCameraPos();
	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (m_ppBullets[i]->use){
			continue;
		}

		m_ppBullets[i]->use = true;
		m_ppBullets[i]->SetRB(rbFlg);
		if (m_ppBullets[i]->GetRB()) {	// true����
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));	// �Ԃ��Z�b�g
		} else {
			m_ppBullets[i]->SetCollor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));	// ���Z�b�g
		}
		m_ppBullets[i]->
		m_ppBullets[i]->SetPos(m_pos);
		DirectX::XMFLOAT3 dir;

		float dirY;
		dirY = pCameraPos.y - pOldCameraPos.y;
		
		dir.x = m_pos.x - pCameraPos.x;
		dir.y = m_pos.y - dirY;
		dir.z = m_pos.z - pCameraPos.z;

		//�x�N�g���̑傫��
		float L;
		L = sqrtf((dir.x * dir.x) +
			(dir.y * dir.y) +
			(dir.z * dir.z));

		//// dir �̒�����1�ɂ���(���K��)
		dir.x = dir.x / L;
		dir.y = dir.y / L;
		dir.z = dir.z / L;

		// ������1�ɂȂ����x�N�g���Ɉړ������������x��������(�藠���̑��x)
		dir.x = dir.x * 0.2;
		dir.y = dir.y * 0.2;
		dir.z = dir.z * 0.2;

		m_ppBullets[i]->SetMove(dir);
		break;
	}
}

void Player::DestroyBullet()
{
	for (int i = 0; i < m_nBulletNum; ++i)
	{
		if (!m_ppBullets[i]->use)
		{
			continue;
		}
		m_ppBullets[i]->use = false;
		break;
	}
}