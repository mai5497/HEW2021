//====================================================================
//
// �e�Ǘ�
// �쐬��:�g����
// 
// �X�V��:2021/12/26	�쐬
//		 :2022/01/10	�萔��`�̈ꕔ���w�b�_�ֈړ�
//====================================================================

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"BulletManager.h"
#include	"GameObject.h"
#include	"BulletRed.h"
#include	"BulletBlue.h"
#include	"Input.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define BULLET_SPEED		(0.5f)								// �e�̑��x


//==============================================================
//
//	BulletManager::�R���X�g���N�^
// 
//==============================================================
BulletManager::BulletManager():m_ppBullets(nullptr),m_BulletNum(MAX_BULLET)
{

}

//==============================================================
//
//	BulletManager::�f�X�g���N�^
// 
//==============================================================
BulletManager::~BulletManager()
{

}

//==============================================================
//
//	����������
// 
//==============================================================
bool BulletManager::Init()
{
	/* ---�e�̏��̍\����---- */
	typedef struct
	{
		XMFLOAT3 pos;
	}BulletSettings;

	// �e�̏�����...BulletBase�̃R���X�g���N�^�ōs�����߂����ł͂Ƃ肠�����s��Ȃ��B-2021/01/09���_

	// �|�C���^���i�[����z����쐬
	m_ppBullets = new BulletBase * [MAX_BULLET];

	// �e�̍ő吔���������m��
	for (int i = 0; i < MAX_BULLET; ++i){
		// ���ꂼ��̔z��ɒe���������m��
		if (i < MAX_RED_BULLET){						// �Ԓe�̃������m��
			m_ppBullets[i] = new BulletRed;
		}else{											// �e�̃������m��
			m_ppBullets[i] = new BulletBlue;

		}
		m_ppBullets[i]->Init();
	}

	return true;
}

//==============================================================
//
//	�I������
// 
//==============================================================
void BulletManager::Uninit()
{
	// �e�̍ő吔�������J��
	for (int i = 0; i < MAX_BULLET; i++)
	{
		m_ppBullets[i]->Uninit();
		delete m_ppBullets[i];
		m_ppBullets[i] = NULL;
	}
	delete[] m_ppBullets;
	m_ppBullets = NULL;
}
//==============================================================
//
//	�X�V����
// 
//==============================================================
void BulletManager::Update()
{
	static bool rbflg;

	if (IsPress('E')){		
		rbflg = false;		// �e�Z�b�g
	}
	if (IsPress('Q')) {
		rbflg = true;		// �Ԓe�Z�b�g
	}
	if (IsTrigger('Z')) {
		CreateBullet(rbflg);
	}
	// �e�̍ő吔�X�V����
	for (int i = 0; i < MAX_BULLET; i++) {
		if (!m_ppBullets[i]->use) {
			continue;
		}
		m_ppBullets[i]->Update();
	}
}

//==============================================================
//
//	�`�揈��
// 
//==============================================================
void BulletManager::Draw()
{
	//�@�e�̍ő吔�`�揈��
	for (int i = 0; i < MAX_BULLET; i++){
		if (!m_ppBullets[i]->use){
			continue;
		}
		m_ppBullets[i]->Draw();

	}
}


//==============================================================
//
//	BulletManager::�e�𐶐����鏈��(�v���C���[���W������)
//	�쐬��	�F ���c�đ�
//	�ҏW��	�F �ɒn�c�^��
//	�߂�l	�F void
//	����		�F �F����
//
//==============================================================
void BulletManager::CreateBullet(bool rbFlg)
{
	for (int i = 0; i < MAX_BULLET; ++i) {
		if (m_ppBullets[i]->use) {
			continue;
		}
		m_ppBullets[i]->SetRBFlg(rbFlg);
		if (rbFlg == true) {	// true����
			m_ppBullets[i] = new BulletRed;
			m_ppBullets[i]->Init();
		} else {
			m_ppBullets[i] = new BulletBlue;
			m_ppBullets[i]->Init();
		}
		m_ppBullets[i]->use = true;

		m_ppBullets[i]->SetPos(m_PlayerPos);
		XMFLOAT3 dir;


		float dirY;
		dirY = 10;

		dir.x = -(m_PlayerPos.x - m_PlayerAngle.x);
		dir.y = dirY;
		dir.z = -(m_PlayerPos.z - m_PlayerAngle.z);

		//�x�N�g���̑傫��
		float L;
		L = sqrtf((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));

		//// dir �̒�����1�ɂ���(���K��)
		dir.x = dir.x / L;
		dir.y = dir.y / L;
		dir.z = dir.z / L;

		// ������1�ɂȂ����x�N�g���Ɉړ������������x��������(�藠���̑��x)
		dir.x = dir.x * BULLET_SPEED;
		dir.y = dir.y * BULLET_SPEED;
		dir.z = dir.z * BULLET_SPEED;

		//m_ppBullets[i]->SetMove(dir);
		m_ppBullets[i]->SetMove(dir);
		break;
	}
}


//==============================================================
//
//	BulletManager::�e��j�󂷂鏈��
//	�쐬��	: ���c�đ�
//	�߂�l	: void
//	����		: void
//
//==============================================================
void BulletManager::DestroyBullet()
{
	for (int i = 0; i < MAX_BULLET; ++i)
	{
		if (!m_ppBullets[i]->use)
		{
			continue;
		}
		m_ppBullets[i]->use = false;
		break;
	}
	
}

//==============================================================
//
//	BulletManager::�v���C���[�̍��W��ݒ�
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: void
//	����		: XMFLOAT3�^
//
//==============================================================
void BulletManager::SetPlayePos(XMFLOAT3 pos)
{
	m_PlayerPos = pos;
}

//==============================================================
//
//	BulletManager::�v���C���[�̊p�x��ݒ�
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: void
//	����		: XMFLOAT3�^
//
//==============================================================
void BulletManager::SetPlayerAngle(XMFLOAT3 angle)
{
	m_PlayerAngle = angle;
}

//====================================================================
//
//		�e���擾
//
//====================================================================
BulletBase* BulletManager::GetBullet(int index) {
	if (index < MAX_BULLET) {
		return m_ppBullets[index];
	}
	return NULL;
}
