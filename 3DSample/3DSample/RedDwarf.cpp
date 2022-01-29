//****************************************************
//
//	�ԏ��l
//	�쐬�ҁF�ɒn�c�^��
//	
//	2021/12/04 : �쐬(�ɒn�c)
//	2021/12/09 : ���f�ޓ���(�ɒn�c)
//	2021/12/21 : �V�f��
//
//
//****************************************************


//========================= �C���N���[�h�� ===========================
#include "RedDwarf.h"
#include "MyVector.h"
#include "Collision.h"
#include "Player.h"
#include "Texture.h"
#include "GameScene.h"
#include "FBX//FBXPlayer.h"
#include "DrawBuffer.h"




//========================= �萔��` ===========================

//========================= �O���[�o���ϐ���` ===========================
DrawBuffer *RedDwarf::m_pBuffer = NULL;
FBXPlayer *RedDwarf::m_pFBX = NULL;


//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
RedDwarf::RedDwarf() 
{
	//----- �ϐ������� -----
	LoadTextureFromFile("Assets/Model/kobitored.png", &m_pRedDwarfTex);

	m_DwarfAngle = 0.0f;

	SetRBFlg(true);	// �ԏ��l
	use = true;
	m_CircumferenceTimer = TARGETSET_TIME;
	m_BulletAliveTimer = 0;
}


//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
RedDwarf:: ~RedDwarf()
{
	Uninit();
}


//====================================================================
//
//		������
//
//====================================================================
bool RedDwarf::Init()
{
	/* �ȉ��̓��f����������g�p */
	if (m_pBuffer == NULL) {
		RedDwarf::LoadDwarf("Assets/Model/kobitored.fbx");
	}

	GameObject::Init();
	return true;
}


//====================================================================
//
//		�I������
//
//====================================================================
void RedDwarf::Uninit()
{
	SAFE_RELEASE(m_pRedDwarfTex);
	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pFBX;
		m_pFBX = NULL;
	}

	GameObject::Uninit();
	
}


//====================================================================
//
//		�X�V����
//
//====================================================================
void RedDwarf::Update()
{	
	//----- �ϐ������� -----
	//static bool jumpFlg;
	float Differ;		// ���l�ƒe�̋����̍�
	float vAngle;		// �ړI�ʒu�̊p�x
	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);
	SetMoveFlg(true);
	if (m_BulletAliveTimer > 0) {
		m_CircumferenceTimer = m_BulletAliveTimer;
	}
	m_CircumferenceTimer--;

	// �Ǐ]����^�[�Q�b�g�̍��W
	XMVECTOR vTarget = XMLoadFloat3(&m_targetPos);
	// ���l�̍��W
	XMVECTOR vRedDwarfPos = XMLoadFloat3(&m_pos);
	// �i�s����							�@�@���x�N�g���̈����Z
	XMVECTOR vDirection = XMVectorSubtract(vTarget, vRedDwarfPos);
	// ���̑��x�ɂ��邽�߂ɐ��K��
	// ���x��ς���Ȃ�vDirecton�ɑ��x��������B
	vDirection = XMVector3Normalize(vDirection);
	// ������֐�								  �������鐔
	if (GetFollowFlg()) {		// �ǐՃt���O�������Ă���Ƃ�
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * DWARF_FOLLOW_SPEED);
	} else if (GetrunFlg()) {	// �e���瓦����Ƃ�
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * -DWARF_RUN_SPEED);
	} else if (GetColFlg()) {		// �Ԃ����Ĕ��]����Ƃ�
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * -DWARF_REVERSE_SPEED);
	} else {
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * DWARF_DEFAULT_SPEED);
	}

	// Float3�^�ɕϊ�
	XMStoreFloat3(&m_move, vDirection);


	//if (jumpFlg) {
	//	m_move.y -= 0.21f;
	//}

	//----- �e�̋߂��ɂ���Ƃ��̏��� -----
	Differ = fabsf(m_targetPos.x - m_pos.x) + fabsf(m_targetPos.z - m_pos.z);
	if (GetrunFlg() && Differ > 25.0f) {	// �Ȃ�ƂȂ����ꂽ�Ƃ��B�}�W�b�N�i���o�[�ł��߂�B
		SetrunFlg(false);
		SetMoveFlg(false);
	}
	if (Differ < 0.05f && GetFollowFlg() && GetColFlg()) {
		SetColFlg(false);
		SetFollowFlg(false);
		SetMoveFlg(false);
	}
	if (Differ < 0.025f && GetFollowFlg()) {	// �Ȃ�ƂȂ��߂��ɂ���Ƃ��B�}�W�b�N�i���o�[�ł��߂�B
		SetFollowFlg(false);
		SetMoveFlg(false);
	}


	//----- ������̋z����͂������邩�A�d�͂������邩 -----
	if (!GetLiftFlg()) {
		// �d�͂�������
		m_move.y -= GRAVITY;
	} else {
		// ����
		m_move.y += LIFTPOWER;
		if (m_pos.y > COLLECTOR_POS_Y) {
			SetLiftFlg(false);
		}
	}

	//----- �i�s�����ɂ�����Ă܂���Ă���ړ����� -----
	vAngle = XMConvertToDegrees(atan2(m_move.z, m_move.x));
	float DiffAngle = vAngle - m_DwarfAngle;
	if (DiffAngle >= 180.0f) {
		DiffAngle -= 360.0f;
	}
	if (DiffAngle < -180.0f) {
		DiffAngle += 360.0f;
	}
	m_DwarfAngle += DiffAngle * RATE_ROTATE_DWARF;
	if (m_DwarfAngle >= 180.0f) {
		m_DwarfAngle -= 360.0f;
	}
	if (m_DwarfAngle < -180.0f) {
		m_DwarfAngle += 360.0f;
	}

	//----- �ړ����t���O�������Ă��Ȃ��Ƃ��͈ړ����Ȃ��i�v���v�����Ȃ����߁j -----
	if (GetMoveFlg()) {
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
		m_pos.z += m_move.z;
		if (GetLiftFlg()) {
			m_pos.x += 0.0f;
			m_pos.y += m_move.y;
			m_pos.z += 0.0f;
		}
	} else {
		if (GetLiftFlg()) {
			m_pos.x += 0.0f;
			m_pos.y += m_move.y;
			m_pos.z += 0.0f;
		}
	}

	//----- �����_���ňړ����邽�߂̐ݒ� -----
	if (m_CircumferenceTimer < 0) {
		if (!GetrunFlg() && !GetFollowFlg()) {
			SetCircumferenceFlg(true);
		}
		SetColFlg(false);
	}
	if (m_CircumferenceTimer < 0 || GetCircumferenceFlg()) {
		m_CircumferenceTimer = TARGETSET_TIME;
	}

	//----- �����蔻�� -----
	if (m_pos.y < 0.5f) {
		/* todo: �Q�[���I�[�o�[�̏u�Ԃɂ��̏��l�ɃJ������� */
		RedDwarf::SetAliveFlg(false);
	}

	m_currentPos = m_pos;

}


//====================================================================
//
//		�`�揈��
//
//====================================================================
void RedDwarf::Draw()
{

	// ���l�̃e�N�X�`��
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixRotationY(-XMConvertToRadians(m_DwarfAngle) + (XM_PI * 0.5f))
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pRedDwarfTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}




//====================================================================
//
//		�e�N�X�`���ǂݍ���
//
//====================================================================
bool RedDwarf::LoadDwarf(const char* pFilePath)
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