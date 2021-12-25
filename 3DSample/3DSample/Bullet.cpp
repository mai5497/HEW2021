/**
 * @file Bullet.cpp
 * @Author	���c�đ�
 * @Edit	�g��(2021/12/19)
 * @date 2021/11/29 �쐬
 *		 2021/12/19 �Ԑʂ𔻕ʂ���ϐ���ǉ�
 *					�Ԑʔ��ʕϐ��̃Q�b�^�[�Z�b�^�[��ǉ�
					�t�B�[���h�ƒe�̓����蔻��̏�����ǉ�(�g��)
 * @brief			�v���C���[���甭�˂����e�Ɋւ��鏈��
 */

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include "Bullet.h"
#include <math.h>
#include "Texture.h"


//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define FPS (60)					//�t���[����
#define WAIT_TIME (1.0 * FPS)		//�x���̂��߂̎���
#define WAIT_TIME2 (0.8f * FPS)		//�x���̂��߂̎���
#define BULLET_GRAVITY (0.1f)		// �e�ɂ�����d��

//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
DrawBuffer* Bullet::m_pBuffer = NULL;			
FBXPlayer* Bullet::m_pFBX = NULL;				

//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
Bullet::Bullet(DirectX::XMFLOAT3 size):m_rbFlg(true),m_ColFlg(false)
{
	// �e�N�X�`���ǂݍ���
	LoadTextureFromFile("Assets/Model/flowerred.png", &m_pBulletTex);

	// ---�ϐ�������	m_pos.y = 1000.0f;						//�������Wx
	m_pos.z = 1000.0f;						//�������Wy
	m_pos.x = 1000.0f;						//�������Wz
	m_size.x = 0.25f;				
	m_size.y = 0.25f;
	m_size.z = 0.25f;
	m_sleep = 0;
	m_sleep2 = 0;

}

//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
Bullet::~Bullet()
{
	Uninit();
}

//====================================================================
//
//		������
//
//====================================================================
bool Bullet::Init()
{
	// ---���f���ǂݍ���
	if (m_pBuffer) {
		Bullet::LoadBullet("Assets/Model/flowerred.fbx");
	}

	GameObject::Init();
	return true;
}

//====================================================================
//
//		�I������
//
//====================================================================
void Bullet::Uninit()
{
	// ---�e�N�X�`�����
	SAFE_RELEASE(m_pBulletTex);

	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;

		delete m_pFBX;
		m_pFBX = NULL;
	}

	// ---�L���[�u�̉��
	GameObject::Uninit();
}

//====================================================================
//
//		�X�V����
//
//====================================================================
void Bullet::Update()
{
	//���t���[��������
//	m_move = DirectX::XMFLOAT3(0, m_move.y, 0);

	//��莞�Ԍ�ɏd�͂�������
	//if (m_sleep > WAIT_TIME)
	//{
	//	//���̃R�����g�A�E�g���O���ƈ�莞�Ԍ�ɒe��������藎�����܂�
	//	//m_move.y -= 3.0f / FPS;
	//	m_move.x = 0;
	//	m_move.y = 0;
	//	m_move.z = 0;
	//	m_sleep = 0;
	//}
	
	//if (m_sleep2 > WAIT_TIME2)
	//{
	//	if (m_pos.y > 0.1f)
	//		m_move.y -= 1.5f / FPS;

	//	m_sleep2 = 0;
	//}

	//m_sleep++;
	//m_sleep2++;

	//if (use == true && m_pos.y > 0.5f) {
	//	
	//	m_move.y -= BULLET_GRAVITY / FPS;			// �d�͒ǉ�
	//}

	// �d�͒ǉ�
	m_move.y -= BULLET_GRAVITY;

	//if (m_ColFlg) {
	if (m_pos.y < 1.0f) {							// ���͍����Ŕ���
		m_move.x = 0.0f;
		m_move.y = 0.0f;
		m_move.z = 0.0f;

		SetMove(m_move);
	}

	//���W�X�V
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	// �I�u�W�F�N�g�̍X�V(�e�̍X�V)
	GameObject::Update();
}


//====================================================================
//
//		�`�揈��
//
//====================================================================
void Bullet::Draw()
{
	// �e�̃e�N�X�`��
	int meshNum = m_pFBX->GetMeshNum();
	for (int  i = 0; i < meshNum; ++i){
		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			* DirectX::XMMatrixRotationY(-m_BulletAngle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		SHADER->SetTexture(m_pBulletTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	}
}

//=============================================================
//
//	�e�̓����蔻�菈��
//	�쐬��	�F ���c�đ�
//	�߂�l	�F �I�u�W�F�N�g���
//�@����		�F �Ȃ� 
//
//=============================================================
void Bullet::OnCollision(GameObject* pObj)
{
	// �e���g���ĂȂ��Ƃ��͏I������
	if (use == false) { return; }

	DirectX::XMFLOAT3 m_Enemypos = pObj->GetPos();		//�G�̍��W�擾
	DirectX::XMFLOAT3 Target = m_pos;							//�e�̍��W���擾�i�G�Ƃ̓����蔻��ł���

	DirectX::XMFLOAT3 dir;
	/*
	dir.x = m_pos.x - m_Enemypos.x;
	dir.y = m_pos.y - m_Enemypos.y;
	dir.z = m_pos.z - m_Enemypos.z;

	float l;
	l = sqrtf(powf(dir.x, 2) + powf(dir.y, 2) + powf(dir.z, 2));
	dir.x = dir.x / l;
	dir.y = dir.y / l;
	dir.z = dir.z / l;

	dir.x = dir.x * 0.025f;
	dir.y = dir.y * 0.025f;
	dir.z = dir.z * 0.025f;
	*/

	dir.x = 0.0f;
	dir.y = 0.0f;
	dir.z = 0.0f;

	pObj->SetMove(dir);
}


//=============================================================
//
//	�����蔻��̃Z�b�g
//	�쐬��	�F ���c�đ�
//	�߂�l	�F �t���O
//�@����		�F �Ȃ� 
//
//=============================================================
void Bullet::SetColFlg(bool flg) {
	m_ColFlg = flg;
}


//=============================================================
//
//	�������e���Ԃ����Z�b�g����
//	�쐬��	�F �ɒn�c�^��
//	�߂�l	�F void
//�@����	�F �Ԃ����Z�b�gtrue����false����
//
//=============================================================
void Bullet::SetRB(bool flg)
{
	m_rbFlg = flg;
}





//=============================================================
//
//	�e���Ԃ����擾
//	�쐬��	�F �ɒn�c�^��
//	�߂�l	�F �Ԃ���true����false����
//�@����	�F void
//
//=============================================================
bool Bullet::GetRB()
{
	return m_rbFlg;
}



//=============================================================
//
//	���f���ǂݍ���
//	�쐬��	�F bool�^
//	�߂�l	�F void
//�@����		�F �t�@�C���p�X 
//
//=============================================================
bool Bullet::LoadBullet(const char* pFilePath)
{
	/* �ȉ��̓��f����������g�p */
	HRESULT hr;
	m_pFBX = new FBXPlayer;
	hr = m_pFBX->LoadModel(pFilePath);
	if (FAILED(hr))
	{
		return false;
	}

	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
	int meshNum = m_pFBX->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++)
	{
		//���b�V�����Ƃɒ��_�o�b�t�@�쐬
		m_pBuffer[i].CreateVertexBuffer(
			m_pFBX->GetVertexData(i),
			m_pFBX->GetVertexSize(i),
			m_pFBX->GetVertexCount(i)
		);
		//�C���f�b�N�X�o�b�t�@�쐬
		m_pBuffer[i].CreateIndexBuffer(
			m_pFBX->GetIndexData(i),
			m_pFBX->GetIndexCount(i)
		);

	}
	return true;
}


