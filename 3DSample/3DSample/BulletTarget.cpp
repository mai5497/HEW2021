//====================================================================
//
// �e�̗����n�_[BulletTarget.cpp]
// �쐬��:�g����
// 
// �X�V��:2022/01/15	�쐬
//====================================================================

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	<math.h>
#include	"MyMath.h"

#include	"BulletTarget.h"
#include	"Input.h"
#include	"Controller.h"



 //*******************************************************************************
 // �萔�E�}�N����`
 //*******************************************************************************
#define TARGET_POS_X		(0.0f)
#define TARGET_POS_Y		(1.2f)
#define TARGET_POS_Z		(0.0f)

#define TARGET_SIZE_X	(1.0f)
#define TARGET_SIZE_Y		(0.0f)
#define TARGET_SIZE_Z		(1.0f)

#define L_PI			(3.1415926f)		// ��
#define L_H_DEG			(180.0f)			// �p�x
#define	TRANS_RADIAN	(L_PI / L_H_DEG)	// ���W�A���ɕϊ�

//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
//DrawBuffer* BulletTarget::m_pBuffer = NULL;
//FBXPlayer* BulletTarget::m_pFBX = NULL;
Camera* g_pBulletTargetCamera;

//==============================================================
//
//	BulletTarget�N���X::�R���X�g���N�^
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
BulletTarget::BulletTarget() : m_pCamera(nullptr)
{

}

//==============================================================
//
//	BulletTarget�N���X::�f�X�g���N�^
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
BulletTarget::~BulletTarget()
{

}

//==============================================================
//
//	BulletTarget�N���X::������
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
bool BulletTarget::Init()
{
	LoadTextureFromFile("Assets/Model/Target.png", &m_pBulletTargetTex);

	GameObject::Init();

	// �J�����C���X�^���X�̏�����
	//m_pCamera = new Camera;
	//m_pCamera->Init();
	g_pBulletTargetCamera = new Camera;
	g_pBulletTargetCamera->Init();

	//---�e�N�X�`���ǂݍ���

	//---�ϐ�������
	m_pos = XMFLOAT3(TARGET_POS_X, TARGET_POS_Y, TARGET_POS_Z);
	m_size = XMFLOAT3(TARGET_SIZE_X, TARGET_SIZE_Y, TARGET_SIZE_Z);
	m_Angle = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_collisionType = COLLISION_DYNAMIC;			// �����蔻������Ƃ��̃I�u�W�F�N�g�̎�ނ̐ݒ�



	return true;

}


//==============================================================
//
//	BulletTarget�N���X::�I��
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void BulletTarget::Uninit()
{
	//if (m_pBuffer != NULL) {
	//	delete[] m_pBuffer;
	//	m_pBuffer = NULL;
	//}

	//if (m_pFBX != NULL) {
	//	delete[] m_pFBX;
	//	m_pFBX = NULL;
	//}

	//---�e�N�X�`�����
	SAFE_RELEASE(m_pBulletTargetTex);

	//// �J�����C���X�^���X���
	m_pCamera->Uninit();
	delete m_pCamera;
	//g_pBulletTargetCamera->Uninit();
	//delete g_pBulletTargetCamera;

	GameObject::Uninit();
}

//==============================================================
//
//	BulletTarget�N���X::�X�V
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void BulletTarget::Update()
{
	//---�ϐ�������
	XMFLOAT2 Axis = XMFLOAT2(0.0f, 0.0f);
	Axis = LeftThumbPosition();
	bool moveFlg = false;					// �ړ��t���O

	const float Move = (10.0f / FPS) * 4;	// 1�b�Ԃ�4M�i��

	m_move = XMFLOAT3(Axis.x, m_move.y, Axis.y);

	//---�J�����̌������擾(���W�A���ɕϊ�)
	//float CameraRad = m_pCamera->GetxzAngle() * TRANS_RADIAN;
	
	// �^�[�Q�b�g�I�u�W�F�N�g�ړ�
	//if (m_move.x != 0.0f && m_move.y != 0.0f) {
		if (IsPress(VK_LEFT)) {			// ��
			moveFlg = true;
			m_move.x -= Move;
		}
		if (IsPress(VK_RIGHT)) {		// �E
			moveFlg = true;
			m_move.x += Move;
		}
		if (IsPress(VK_UP)) {			// ��
			moveFlg = true;
			m_move.z += Move;
		}
		if (IsPress(VK_DOWN)) {			// ��
			moveFlg = true;
			m_move.z -= Move;
		}
	//}
	//MyVector2 Direction(0.0f, 0.0f);

	// �ɍ��W���g����TPS���_
	//Direction.x = m_move.x * cosf(CameraRad) - m_move.z * sinf(CameraRad);
	//Direction.y = m_move.x * sinf(CameraRad) + m_move.z * cosf(CameraRad);
	//Direction = Direction.GetNormalize();
	//Direction.x = m_move.x - m_move.z;
	//Direction.y = m_move.x + m_move.z;

	// �`��p�p�x�ύX����
	// atan ... �A�[�N�^���W�F���g�̊֐�
	if (moveFlg == true) {
		m_DrawAngle  = atan2(m_move.z, m_move.x);
		m_DrawAngle -= XM_PI * 0.5f;
	}

	//m_move.x = Direction.x * Move;
	//m_move.z = Direction.y * Move;

	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
 }

//==============================================================
//
//	BulletTarget�N���X::�`��
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void BulletTarget::Draw()
{
	SHADER->Bind(VS_WORLD, PS_PHONG);
	//m_pCamera->Bind();

	//int MeshNum = m_pFBX->GetMeshNum();
	//for (int i = 0; i < MeshNum; ++i){
	SHADER->SetTexture(m_pBulletTargetTex);

	SHADER->SetWorld
	(
		XMMatrixScaling(m_size.x, m_size.y, m_size.z)*
		XMMatrixRotationY(-m_DrawAngle)*
		XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);

	GameObject::Draw();

	SHADER->SetTexture(NULL);

	//	m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//}

}


//==============================================================
//
//	BulletTarget�N���X::���W�擾
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
XMFLOAT3 BulletTarget::GetBulletTargetPos()
{
	return m_pos;
}