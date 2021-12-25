/**
 * @file Enemy.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 *		 2021/12/08	�e�ւ̒ǐՂ��폜
 *					�ǐՂ̑��x�𒲐�
 * @brief �G�Ɋւ��鏈��
 */
#include "Enemy.h"
#include "myVector.h"
#include "Collision.h"
#include "Player.h"
#include "Texture.h"

#define ENEMY_SIZE (0.007f)

DrawBuffer *Enemy::m_pBuffer = NULL;
FBXPlayer *Enemy::m_pfbx = NULL;

Enemy::Enemy()
{
	LoadTextureFromFile("Assets/Texture/tyoutingazou.png", &m_pEnemyTex);


	m_pos.x = 11.0f;
	m_pos.y = 0.5f;
	m_pos.z = 3.0f;

	m_move.x = 0.0f;
	m_move.y = 0.0f;
	m_move.z = 0.0f;

	use = true;
}

Enemy::~Enemy()
{

}

bool Enemy::LoadEnemy(const char* pFilePath)
{
	HRESULT hr;
	m_pfbx = new FBXPlayer;
	hr = m_pfbx->LoadModel(pFilePath);
	if (FAILED(hr)) { return false; }

	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
	int meshNum = m_pfbx->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++)
	{
		//���b�V�����Ƃɒ��_�o�b�t�@�쐬
		m_pBuffer[i].CreateVertexBuffer(
			m_pfbx->GetVertexData(i),
			m_pfbx->GetVertexSize(i),
			m_pfbx->GetVertexCount(i)
		);
		//�C���f�b�N�X�o�b�t�@�쐬
		m_pBuffer[i].CreateIndexBuffer(
			m_pfbx->GetIndexData(i),
			m_pfbx->GetIndexCount(i)
		);

	}
	return true;
}

bool Enemy::Init()
{
	if (m_pBuffer == NULL)
	{
		Enemy::LoadEnemy("Assets/Model/tyoutinobake.fbx");
	}
	return true;
}

void Enemy::Uninit()
{
	if (m_pBuffer != NULL)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pfbx;
		m_pfbx = NULL;
	}
}

void Enemy::Update()
{
	//----- �ϐ������� -----
	static int LifeCnt;

	//�G�l�~�̑��x�𒲐߂��邽�߂ɃR�����g�A�E�g����Ă������������ɖ߂���
	// �Ǐ]����^�[�Q�b�g�̍��W
	DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&m_targetPos);

	// Enemy�̍��W
	DirectX::XMVECTOR vEnemyPos = DirectX::XMLoadFloat3(&m_pos);

	// �i�s����							�@�@���x�N�g���̈����Z
	DirectX::XMVECTOR vDirection = DirectX::XMVectorSubtract(vTarget, vEnemyPos);

	// ���̑��x�ɂ��邽�߂ɐ��K��
	// ���x��ς���Ȃ�vDirecton�ɑ��x��������B
	vDirection = DirectX::XMVector3Normalize(vDirection);

	// ������֐�								  �������鐔
	vDirection = DirectX::XMVectorScale(vDirection, 1.0 / 60);

	// Float3�^�ɕϊ�
	DirectX::XMStoreFloat3(&m_move, vDirection);


	// �A�[�N�^���W�F���g(�t����)
	m_EnemyAngle = atan2(m_move.z, m_move.x);
	m_EnemyAngle -= DirectX::XM_PI * 0.5f;

	// �G�̃A�N�V����

	// �ړ�
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

}

void Enemy::Draw()
{

	// �G�l�~�[�̃e�N�X�`��
	int meshNum = m_pfbx->GetMeshNum();
	for (int i = 0; i < meshNum; ++i)
	{

		SHADER->SetWorld(
			DirectX::XMMatrixScaling(ENEMY_SIZE, ENEMY_SIZE, ENEMY_SIZE)
			*DirectX::XMMatrixRotationY(-m_EnemyAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pEnemyTex);
		/*SHADER->SetTexture(
		m_fbx.GetTexture(i)
		);*/

		m_pBuffer[i].Draw(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
	}
}

void Enemy::EnemyStop()
{
	m_move.x = 0.6f;
	m_move.y = 0.6f;
	m_move.z = 0.6f;
}