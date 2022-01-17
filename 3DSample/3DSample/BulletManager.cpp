//====================================================================
//
// �e�Ǘ�
// �쐬��:�g����
// 
// �X�V��:2021/12/26	�쐬
//		 :2022/01/10	�萔��`�̈ꕔ���w�b�_�ֈړ�(������)
//		 :2022/01/11	�T�E���h�ǉ�
//====================================================================

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"BulletManager.h"
#include	"GameObject.h"
#include	"BulletRed.h"
#include	"BulletBlue.h"
#include	"Input.h"
#include	"Sound.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define BULLET_SPEED		(0.1f)								// �e�̑��x

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
float g_ThrowTimer = 0.0f;				// �����鎞��


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
	if (IsRelease('E') || IsRelease(JPadButton::X)) {
		rbflg = false;		// �e�Z�b�g
		CSound::Play(SE_BULLET_1);
		CreateBullet(rbflg);

	}

	if (IsRelease('Q') || IsRelease(JPadButton::B)) {
		rbflg = true;		// �Ԓe�Z�b�g
		CSound::Play(SE_BULLET_1);
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
		}
		else {
			m_ppBullets[i] = new BulletBlue;
			m_ppBullets[i]->Init();
		}
		m_ppBullets[i]->use = true;

		//m_ppBullets[i]->SetPos(m_PlayerPos);


		//XMFLOAT3 dir;		// �ˏo����

		//float dirY;			// �ł��o���p�x(Y������)
		//dirY = 90.0f;

		////---�ˏo����
		////dir.x = -(m_PlayerPos.x - m_PlayerAngle.x);
		////dir.y = dirY;
		////dir.z = -(m_PlayerPos.z - m_PlayerAngle.z);

		////---�ˏo����
		//dir.x = -m_PlayerPos.x;
		//dir.y = dirY / FPS;
		//dir.z = -m_PlayerPos.z;
		// 
		// 
		////�x�N�g���̑傫��
		//float L;
		//L = sqrtf((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));

		////// dir �̒�����1�ɂ���(���K��)
		//dir.x = dir.x / L;
		//dir.y = dir.y / L;
		//dir.z = dir.z / L;

		//// ������1�ɂȂ����x�N�g���Ɉړ������������x��������(�藠���̑��x)
		//dir.x = dir.x * BULLET_SPEED;
		//dir.y = dir.y;
		//dir.z = dir.z * BULLET_SPEED;

		////m_ppBullets[i]->SetMove(dir);
		//m_ppBullets[i]->SetMove(dir);

		XMFLOAT3 StartPos = m_PlayerPos;									// ���˒n�_(�v���C���[�̍��W)
		XMFLOAT3 EndPos = m_TargetPos;										// �����n�_(�^�[�Q�b�g�̍��W)

		//---����_
		XMFLOAT3 CenterPos = XMFLOAT3((StartPos.x + EndPos.x) / 2.0f,		// X���W ... ���˒n�_�Ɨ����n�_�̒��_
			7.0f,								// Y���W ... �����͔C�ӂ̒l
			(StartPos.z + EndPos.z) / 2.0f);	// Z���W ... ���˒n�_�Ɨ����n�_�̒��_

		XMFLOAT3 CurrentPos;

		g_ThrowTimer = 0.0f;												// �������Ԃ����Z�b�g

		////---���������x�W�F�Ȑ��̌v�Z�ŏ������s��
		// �x�W�F�Ȑ��ŎZ�o�����l���e���W�Ɋi�[
		CurrentPos.x = (1.0f - g_ThrowTimer) * (1.0f - g_ThrowTimer) * StartPos.x +
			2 * (1.0f - g_ThrowTimer) * g_ThrowTimer * CenterPos.x +
			g_ThrowTimer * g_ThrowTimer * EndPos.x;

		CurrentPos.y = (1.0f - g_ThrowTimer) * (1.0f - g_ThrowTimer) * StartPos.y +
			2 * (1.0f - g_ThrowTimer) * g_ThrowTimer * CenterPos.y +
			g_ThrowTimer * g_ThrowTimer * EndPos.y;

		CurrentPos.z = (1.0f - g_ThrowTimer) * (1.0f - g_ThrowTimer) *StartPos.z +
			2 * (1.0f - g_ThrowTimer) * g_ThrowTimer * CenterPos.z +
			g_ThrowTimer * g_ThrowTimer * EndPos.z;

		m_ppBullets[i]->SetPos(CurrentPos);
		m_ppBullets[i]->SetBezierInfo(StartPos, EndPos, CenterPos,g_ThrowTimer);

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
	//m_PlayerAngle = angle;
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

//==============================================================
//
//	BulletManager::�^�[�Q�b�g���W��ݒ�
//	�쐬��	: �g����
//	�߂�l	: void
//	����		: XMFLOAT3�^
//
//==============================================================
void BulletManager::SetTargetPos(XMFLOAT3 Pos)
{
	m_TargetPos = Pos;
}