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
#define PLAYER_SIZE		(0.25f)

//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
XMFLOAT3 pOldCameraPos;
DrawBuffer *Player::m_pBuffer = NULL;
FBXPlayer *Player::m_pFBX = NULL;
Camera *g_pPlayerCamera;


//==============================================================
//
//	Player�N���X::�R���X�g���N�^
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����	�F void
//
//==============================================================
Player::Player():m_pControllCamera(nullptr)
{
	//----- �ϐ������� -----
	LoadTextureFromFile("Assets/Model/princess.png", &m_pPlayerTex);

	// ---�ϐ�������
	m_pos.x = 0.0f;
	m_pos.y = 3.0f;
	m_pos.z = -13.0f;
	m_Angle = XMFLOAT3(0, 0, 0);
	m_DrawAngle = 0.0f;

	m_size = XMFLOAT3(PLAYER_SIZE, PLAYER_SIZE, PLAYER_SIZE);


	g_pPlayerCamera = new Camera;
	g_pPlayerCamera->Init();

	m_collisionType = COLLISION_DYNAMIC;

	//g_pPlayerCamera = new Camera;
	//g_pPlayerCamera->Init();

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
	//g_pPlayerCamera->Uninit();
	//delete g_pPlayerCamera;

	m_pControllCamera = nullptr;
	SAFE_RELEASE(m_pPlayerTex);

	g_pPlayerCamera->Uninit();
	delete g_pPlayerCamera;
	g_pPlayerCamera = nullptr;
	
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
	GameObject::Init();	// �v���C���[�p�������H
	if (m_pBuffer == NULL) {
		Player::LoadPlayer("Assets/Model/princess.fbx");
	}


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

	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;

		delete m_pFBX;
		m_pFBX = NULL;
	}
	SAFE_RELEASE(m_pPlayerTex);

	GameObject::Uninit();
}

//==============================================================
//
//	Player�N���X::Update
//	�쐬��	�F ���c�đ�
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void Player::Update()
{
	//----- �ϐ������� -----
	XMFLOAT2 Axis = LeftThumbPosition();
	bool moveFlg = false;

	//bool keyL = IsPress('A');
	//bool keyR = IsPress('D');
	//bool keyU = IsPress('W');
	//bool keyD = IsPress('S');
	//bool keyJ = IsTrigger(VK_SPACE);

	//�P�b�ԁi60FPS�j��2M�i���Ƃ�\���B
	//const float Move = (10.0f / 60) * 2;

	m_move = XMFLOAT3(Axis.x, m_move.y, Axis.y);

	//float CameraRad = m_pControllCamera->GetxzAngle() * 3.14159265359f / 180.0f;
	
	//�v���C���[�ړ�
	//m_move.y -= 0.01f;	// �d��
	//if (m_pos.z == -13.0f) {
	//	if (keyL ) {
	//		moveFlg = true;
	//		m_move.x -= Move;
	//		if (m_Angle.y >= -CameraRad - 90.0f * 3.1415926f / 180.0f) {
	//			m_Angle.y -= 0.1f;
	//		}
	//	}

	//	if (keyR) {
	//		moveFlg = true;
	//		m_move.x += Move;
	//		if (m_Angle.y <= -CameraRad + 90.0f * 3.1415926f / 180.0f) {
	//			m_Angle.y += 0.1f;
	//		}
	//	}
	//} else if (m_pos.z < -13.0f) {
	//	m_pos.z = -13.0f;
	//}

	//if (m_pos.x == 12.5f) {
	//	if (keyU) {
	//		moveFlg = true;
	//		m_move.z += Move;
	//		if (m_Angle.y <= -CameraRad) {
	//			m_Angle.y += 0.1f;
	//		}
	//		if (m_Angle.y >= -CameraRad) {
	//			m_Angle.y -= 0.1f;
	//		}
	//	}
	//	if (keyD) {
	//		m_move.z -= Move;
	//	}
	//} else if (m_pos.x > 12.5f) {
	//	m_pos.x = 12.5f;
	//}

	//if (keyJ) { m_move.y += 0.2f; }			// �W�����v

	//if (IsPress(VK_UP)) {	// �e�̔�΂��ʒu�L�΂�
	//	/*todo �e�̔򋗗��L�΂�*/
	//}
	//if (IsPress(VK_DOWN)) {	// �e�̔�΂��ʒu�Z��
	//	/*todo �e�̔򋗗����Ƃ�*/
	//}

	//MyVector2 direction(0, 0);

	// �ɍ��W���g����TPS���_
	//direction.x = m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//direction.y = m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);
	//direction = direction.GetNormalize();

	////���W���X�V
	//m_pos.x += m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//m_pos.y += m_move.y;
	//m_pos.z += m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);

	//�`��p�p�x�ݒ�
	if (moveFlg == true) {
		m_DrawAngle = atan2(m_move.z, m_move.x);
		m_DrawAngle -= XM_PI * 0.5f;
	}

	//m_move.x = direction.x * Move;
	//m_move.z = direction.y * Move;

	//m_pos.x += m_move.x;
	//m_pos.y = 1.5f;
	//m_pos.z += m_move.z;
	
	// �J�����X�V
	//g_pPlayerCamera->Update();
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
	//SHADER->Bind(VS_WORLD, PS_PHONG);
	//g_pPlayerCamera->Bind();


	DirectX::XMFLOAT3 pPos = m_pos;
	DirectX::XMFLOAT3 pSize = m_size;


	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixRotationY(-m_DrawAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pPlayerTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	//CharacterBase::Draw();
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
