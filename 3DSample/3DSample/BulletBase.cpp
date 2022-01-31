//====================================================================
//
// �e�̃x�[�X
// �쐬��:�g����
// 
// �X�V��:2022/01/03	�쐬
//		 :2022/01/11	�T�E���h�ǉ�
//		 :2022/01/16	���nSE���邹������Â��ɂ����i�ɒn�c�j
//		 :2022/01/17	�e���n�ʂɓ��������u�Ԃ��Ƃ�t���O�̍쐬�i�ɒn�c�j
//====================================================================

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"BulletBase.h"
#include	"Sound.h"

//========================= �O���[�o���ϐ���` ===========================
DrawBuffer* BulletBase::m_pBuffer[MAX_BULLET_COLOR] = { nullptr, nullptr };
FBXPlayer* BulletBase::m_pBulletModel[MAX_BULLET_COLOR] = { nullptr, nullptr };


//==============================================================
//
//	BulletBase::�R���X�g���N�^
// 
//==============================================================
BulletBase::BulletBase() :
	m_rbFlg(true),
	m_ColFlg(false),
	m_LandingFlg(false)
{
	// ---�ϐ�������	
	m_pos.x = 1000.0f;						//�������Wx
	m_pos.y = 1000.0f;						//�������Wy
	m_pos.z = 1000.0f;						//�������Wz
	m_size.x = 2.0f;
	m_size.y = 2.0f;
	m_size.z = 2.0f;
	m_sleep = 0;
	m_sleep2 = 0;
	m_Radius = XMFLOAT3(10.0f, 0.1f, 10.0f);

	m_BulletAngle = 0.0f;					// �p�x�̏�����
	m_dir = XMFLOAT3(0.0f, 0.0f, 0.0f);		// ����
	m_AliveTime = BULLET_DESTOROY_CNT;		// ��������

	//----- ���f���E�e�N�X�`���ꊇ�Ǎ� -----
	LoadTextureFromFile("Assets/Texture/flowerblue.png", &m_pBulletTex[BLUE_BULLET]);
	LoadTextureFromFile("Assets/Texture/flowerred.png", &m_pBulletTex[RED_BULLET]);

	for (int i = 0; i < MAX_BULLET_COLOR; i++) {
		m_pBulletModel[i] = new FBXPlayer;
	}
	LoadModel("Assets/Model/flowerblue.fbx", BLUE_BULLET);
	m_flowerAnim[BLUE_BLAST] = m_pBulletModel[BLUE_BULLET]->LoadAnimation("Assets/Model/flowerblue_anime.fbx");
	LoadModel("Assets/Model/flowerred.fbx", RED_BULLET);
	m_flowerAnim[RED_BLAST] = m_pBulletModel[RED_BULLET]->LoadAnimation("Assets/Model/flowerred_anime.fbx");

}


//==============================================================
//
//	BulletBase::�f�X�g���N�^
//
//==============================================================
BulletBase::~BulletBase()
{
	for (int i = 0; i < MAX_BULLET_COLOR; i++) {
		SAFE_RELEASE(m_pBulletTex[i]);
	}
	for (int i = 0; i < MAX_BULLET_COLOR; i++) {
		delete m_pBulletModel[i];
		m_pBulletModel[i] = nullptr;
	}
	if (m_pBuffer != nullptr) {
		for (int i = 0; i < MAX_BULLET_COLOR; i++) {
			delete[] m_pBuffer[i];
			m_pBuffer[i] = nullptr;
		}
	}
}

//==============================================================
//
//	�X�V����
//
//==============================================================
void BulletBase::Update()
{
	// �d�͒ǉ�
	//m_move.y -= BULLET_GRAVITY;

	//---���������x�W�F�Ȑ��̌v�Z�ŏ������s��
	// �x�W�F�Ȑ��ŎZ�o�����l���e���W�Ɋi�[
	// CurrentPos = m_pos �ƂȂ� 

	// �e�̓������Ԃ�i�߂�(�萔�œ����I��鎞�Ԃ����߂��)
	m_ThrowTimer += 1.3f / BULLET_THROW_CNT;


	if (m_ThrowTimer <= 1.0f) {

	m_pos.x = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.x + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.x + m_ThrowTimer * m_ThrowTimer * m_EndPos.x;

	m_pos.y = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.y + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.y + m_ThrowTimer * m_ThrowTimer * m_EndPos.y;

	m_pos.z = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.z + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.z + m_ThrowTimer * m_ThrowTimer * m_EndPos.z;
	}
	else {

		//if (m_ColFlg) {
		//if (m_pos.y < 1.7f) {							// ���͍����Ŕ���
		//if(m_ThrowTimer > 1.0f){
			m_ColFlg = true;
			//m_move.x = 0.0f;
			//m_move.y = 0.0f;
			//m_move.z = 0.0f;

			//SetMove(m_move);

			//use = false;
		//}
	}
	if (m_ColFlg) {
		if (m_AliveTime == BULLET_DESTOROY_CNT) {
			// �T�E���h
			CSound::Play(SE_BULLET_2);
			m_LandingFlg = true;	// �e���n�ʂɂ����u��
		} else {
			m_LandingFlg = false;
		}


		// �e�̎��Ԍo�߂ł̔j�󏈗�
		m_AliveTime--;					// �������Ԃ̃J�E���g�_�E��
		if (m_AliveTime < 0) {			// 0�ȉ��ɂȂ�����
			use = false;					// �g�p�t���O��ύX
			Uninit();
		}
	}

}

//==============================================================
//
//	�`�揈��
//
//==============================================================
void BulletBase::Draw()
{
	/* �e�N�X�`���`�� */
	SHADER->SetWorld(DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z) * 
					DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

	m_pCube->Draw();
}

//====================================================================
//
//		���f���ǂݍ���
//
//====================================================================
bool BulletBase::LoadModel(const char* pFilePath,int index) {
	/* �ȉ��̓��f����������g�p */
	HRESULT hr;
	hr = m_pBulletModel[index]->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
	int meshNum = m_pBulletModel[index]->GetMeshNum();
	m_pBuffer[index] = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
		//���b�V�����Ƃɒ��_�o�b�t�@�쐬
		m_pBuffer[index][i].CreateVertexBuffer(
			m_pBulletModel[index]->GetVertexData(i),
			m_pBulletModel[index]->GetVertexSize(i),
			m_pBulletModel[index]->GetVertexCount(i)
		);
		//�C���f�b�N�X�o�b�t�@�쐬
		m_pBuffer[index][i].CreateIndexBuffer(
			m_pBulletModel[index]->GetIndexData(i),
			m_pBulletModel[index]->GetIndexCount(i)
		);

	}
	return true;
}

//=============================================================
//
//	�������e���Ԃ����Z�b�g����
//	�쐬��	�F �ɒn�c�^��
//	�߂�l	�F void
//�@����	�F �Ԃ����Z�b�gtrue����false����
//
//=============================================================
void BulletBase::SetRBFlg(bool flg)
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
bool BulletBase::GetRBFlg()
{
	return m_rbFlg;
}

//=============================================================
//
//	�����蔻��̃Z�b�g
//	�쐬��	�F �ɒn�c�^��
//	�߂�l	�F �Ȃ�
//�@����		�F �Z�b�g�������t���O 
//
//=============================================================
void BulletBase::SetColFlg(bool flg) {
	m_ColFlg = flg;
}

//=============================================================
//
//	�����蔻��t���O�i�n�ʂɓ��������u�ԁj�̃Z�b�g
//	�쐬��	�F �ɒn�c�^��
//	�߂�l	�F �t���O
//�@����		�F �Ȃ� 
//
//=============================================================
bool BulletBase::GetLandingFlg() {
	return m_LandingFlg;
}


//=============================================================
//
//	�x�W�F�Ȑ��ɂ��Z�o���s�����߂̍��W���擾
//	�쐬��	�F �g����
//	�߂�l	�F �Ȃ�
//�@����		�F XMFLOAT3�^��3�̍��W���擾 
//
//=============================================================
void BulletBase::SetBezierInfo(XMFLOAT3 startPos, XMFLOAT3 endPos, XMFLOAT3 centerPos,float ThrowTimer)		
{
	m_StarPos = startPos;
	m_EndPos = endPos;
	m_CenterPos = centerPos;
	m_ThrowTimer = ThrowTimer;
}


//=============================================================
//
//	���n�t���O�̎擾
//	�쐬��	�F �ɒn�c�^��
//	�߂�l	�F ���n�t���O
//�@����	�F �Ȃ� 
//
//=============================================================
bool BulletBase::GetColFlg() {
	return m_ColFlg;
}


//=============================================================
//
//	�e�̐������Ԃ̎擾
//	�쐬��	�F �ɒn�c�^��
//	�߂�l	�F �e�̐�������
//�@����	�F �Ȃ�
//
//=============================================================
int BulletBase::GetAliveTime() {
	return m_AliveTime;
}
