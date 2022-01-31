/**
 * @file Player.cpp
 * @Author ���c�đ�
 * @date 2021/11/29 �쐬
 *		 2021/12/19 �Ԑe���킯�đłĂ�悤��(�ɒn�c)
 * @brief �v���C���[�Ɋւ��鏈��
 */

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"Player.h"
#include	"Input.h"
#include	"TPSCamera.h"
#include	"MyVector.h"
#include	<math.h>
#include	"Controller.h"
#include	"MyMath.h"
#include	"Camera.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define FPS				(60)
#define PLAYER_SIZE_X	(0.8)
#define PLAYER_SIZE_Y	(0.8f)
#define PLAYER_SIZE_Z	(0.8f)

//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
XMFLOAT3 pOldCameraPos;


//==============================================================
//
//	Player�N���X::�R���X�g���N�^
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����	�F void
//
//==============================================================
Player::Player():
	m_pControllCamera(nullptr),
	m_throwFlg(false)
{
	//----- �ϐ������� -----
	LoadTextureFromFile("Assets/Model/player.png", &m_pPlayerTex);

	// ---�ϐ�������
	m_pos.x = 0.0f;
	m_pos.y = 2.0f;
	m_pos.z = -25.0f;
	m_Angle = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_DrawAngle = XM_PI;
	m_size = XMFLOAT3(PLAYER_SIZE_X, PLAYER_SIZE_Y, PLAYER_SIZE_Z);

	m_pBuffer = nullptr;
	m_pFBX = nullptr;

	m_collisionType = COLLISION_DYNAMIC;
}

//==============================================================
//
//	Player�N���X::�f�X�g���N�^
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
Player::~Player()
{
	m_pControllCamera = nullptr;
	SAFE_RELEASE(m_pPlayerTex);
	
	Uninit();
}

//==============================================================
//
//	Player�N���X::Init
//	�쐬��	�F ���c�đ�
//	�߂�l	�F bool�^
//	����		�F void
//
//==============================================================
bool Player::Init()
{
	//----- �v���C���[���� -----
	if (m_pBuffer == nullptr) {
		LoadPlayer("Assets/Model/player.fbx");
	}
	m_playerAnim[STAND] = m_pFBX->LoadAnimation("Assets/Model/player_standby.fbx");
	m_playerAnim[THROW] = m_pFBX->LoadAnimation("Assets/Model/player_throw.fbx");

	return true;
}

//==============================================================
//
//	Player�N���X::Uninit
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void Player::Uninit()
{

	if (m_pBuffer != nullptr) {
		delete[] m_pBuffer;
		m_pBuffer = nullptr;

		delete m_pFBX;
		m_pFBX = nullptr;
	}
	SAFE_RELEASE(m_pPlayerTex);
}

//==============================================================
//
//	Player�N���X::Update
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void Player::Update() {
	//----- �ϐ������� -----
	//XMFLOAT2 Axis = LeftThumbPosition();
	//bool moveFlg = false;

	m_move = XMFLOAT3(m_BulletTargetPos.x, m_BulletTargetPos.y, m_BulletTargetPos.z - m_pos.z);
	
	if (IsRelease('E') || IsRelease('Q')) {
		m_pFBX->Play(m_playerAnim[THROW]);
	} 
	//m_pFBX->Play(m_playerAnim[STAND]);



	//�`��p�p�x�ݒ�
	m_DrawAngle = atan2(m_move.z, m_move.x);
	m_DrawAngle -= XM_PI * 0.5f;
	if (m_pFBX->IsPlay()) {
		m_pFBX->Step();
	}
}

//==============================================================
//
//	Player�N���X::Draw
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void Player::Draw()
{
	SHADER->Bind(VS_ANIMATION,PS_UNLIT);


	XMFLOAT3 pPos = m_pos;
	XMFLOAT3 pSize = m_size;


	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixRotationY(-m_DrawAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		SHADER->SetAnimation(m_pFBX->GetAnimeMatrix(i), m_pFBX->GetAnimeMatrixNum(i));
		SHADER->SetTexture(m_pPlayerTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}


}

//==============================================================
//
//	Player�N���X::�v���C���[�ɒǐՂ��鏈��(�G�l�~�[��)
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F �Q�[���I�u�W�F�N�g�^
//
//==============================================================
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
	L = sqrtf((dir.x * dir.x) + (dir.y * dir.y) + (dir.z * dir.z));			// �������Œl�Z�o

	// dir �̒�����1�ɂ���(���K��)
	// ���K�� ... �x�N�g���̕����͈ێ������܂܁A�傫����1�̒l�ɂ��邱��
	dir.x = dir.x / L;
	dir.y = dir.y / L;
	dir.z = dir.z / L;

	// ������1�ɂȂ����x�N�g���Ɉړ������������x��������(�G�̑��x)
	dir.x = dir.x * 0.08f;
	dir.y = dir.y * 0.08f;
	dir.z = dir.z * 0.08f;

	pObj->SetMove(dir);

}


//==============================================================
//
//	Player�N���X::�J�������v���C���[�̈ʒu�ɃZ�b�g�H
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F �J�����N���X�^
//
//==============================================================
void Player::SetControllCamera(Camera* pCamera)
{
	m_pControllCamera = pCamera;
}


//==============================================================
//
//	Player�N���X::�J�����ʒu���擾
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F TPSCamera�^�̃|�W�V����
//
//==============================================================
void Player::GetCameraPos(TPSCamera* pCamera)
{
	pOldCameraPos = pCamera->GetCameraPos();
}

//====================================================================
//
//		�e�N�X�`���ǂݍ���
//
//====================================================================
bool Player::LoadPlayer(const char* pFilePath) {
	HRESULT hr;
	m_pFBX = new FBXPlayer;
	hr = m_pFBX->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
	int meshNum = m_pFBX->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++) {
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

//==============================================================
//
//	Player�N���X::�v���C���[�̍��W���擾
//	�쐬��	: �g����
//	�߂�l	: XMFLOAT3
//	����		: �Ȃ� 
//==============================================================
XMFLOAT3 Player::GetPlayerPos()
{
	return m_pos;
}

//==============================================================
//
//	Player�N���X::�v���C���[�̊p�x���擾
//	�쐬��	: �g����
//	�߂�l	: XMFLOAT3
//	����		: �Ȃ� 
//==============================================================
XMFLOAT3 Player::GetPlayerAngle()
{
	return m_Angle;
}

//==============================================================
//
//	Player�N���X::�v���C���[�̕`��p�x���擾
//	�쐬��	: �g����
//	�߂�l	: float
//	����		: �Ȃ� 
//==============================================================
float Player::GetPlayerDrawAngle()
{
	return m_DrawAngle;
}


//==============================================================
//
//	Player�N���X::�e�̃^�[�Q�b�g�̍��W�̎擾
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: �Ȃ�
//	����		: �e�̃^�[�Q�b�g�̍��W 
//==============================================================
void Player::SetBulletTargetPos(XMFLOAT3 pos) {
	m_BulletTargetPos = pos;
}


//==============================================================
//
//	Player�N���X::�����Ă���t���O�Z�b�g
//	�쐬��	: �ɒn�c�^��
//	�߂�l	: �Ȃ�
//	����		: �e�̃^�[�Q�b�g�̍��W 
//==============================================================
void Player::SetThrowFlg(bool flg) {
	m_throwFlg = flg;
}