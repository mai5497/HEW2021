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
#define BULLET_THROW_HEIGHT	(50.0f)								// �e�̂Ȃ��鍂��

//*******************************************************************************
// �O���[�o���ϐ�
//*******************************************************************************
float g_ThrowTimer = 0.0f;				// �����鎞��


//==============================================================
//
//	BulletManager::�R���X�g���N�^
// 
//==============================================================
BulletManager::BulletManager():m_BulletNum(MAX_BULLET)
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
	// �e�̍ő吔���������m��
	for (int i = 0; i < MAX_BULLET;i++) {
		// ���ꂼ��̔z��ɒe���������m��
		if (i < MAX_RED_BULLET) {						// �Ԓe�̃������m��
			m_pBullets[i] = new BulletRed;
		}else{											// �e�̃������m��
			m_pBullets[i] = new BulletBlue;
		}
		m_pBullets[i]->Init();
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
		m_pBullets[i]->Uninit();
		delete m_pBullets[i];
		m_pBullets[i] = nullptr;
	}
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

	if (IsRelease('Q') || IsRelease(JPadButton::A)) {
		rbflg = true;		// �Ԓe�Z�b�g
		CSound::Play(SE_BULLET_1);
		CreateBullet(rbflg);

	}

	// �e�̍ő吔�X�V����
	for (int i = 0; i < MAX_BULLET; i++) {
		if (!m_pBullets[i]->use) {
			continue;
		}
		m_pBullets[i]->Update();
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
		if (!m_pBullets[i]->use){
			continue;
		}
		m_pBullets[i]->Draw();
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
void BulletManager::CreateBullet(bool rbFlg) {
	int search = 999;
	if (rbFlg == true) {	// true����
		for (int i = 0; i < MAX_RED_BULLET; i++) {
			if (m_pBullets[i]->use) {
				continue;
			}
			search = i;
		}
		if (search > MAX_RED_BULLET) {
			return;
		}
	} else {
		for (int i = MAX_RED_BULLET; i < MAX_BULLET; i++) {
			if (m_pBullets[i]->use) {
				continue;
			}
			search = i;
		}
		if (search > MAX_BULLET) {
			return;
		}
	}
	m_pBullets[search]->use = true;
	m_pBullets[search]->Init();

	XMFLOAT3 StartPos = m_PlayerPos;									// ���˒n�_(�v���C���[�̍��W)
	XMFLOAT3 EndPos = m_TargetPos;										// �����n�_(�^�[�Q�b�g�̍��W)

	//---����_
	XMFLOAT3 CenterPos = XMFLOAT3((StartPos.x + EndPos.x) / 2.0f,		// X���W ... ���˒n�_�Ɨ����n�_�̒��_
		BULLET_THROW_HEIGHT,								// Y���W ... �����͔C�ӂ̒l
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

	m_pBullets[search]->SetPos(CurrentPos);
	m_pBullets[search]->SetBezierInfo(StartPos, EndPos, CenterPos, g_ThrowTimer);

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
		if (!m_pBullets[i]->use)
		{
			continue;
		}
		m_pBullets[i]->use = false;
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
		return m_pBullets[index];
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