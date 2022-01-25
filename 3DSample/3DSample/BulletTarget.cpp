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
#include	"Input.h"
#include	"Controller.h"
#include	"Camera.h"
#include	"Shader.h"

#include	"BulletTarget.h"



 //*******************************************************************************
 // �萔�E�}�N����`
 //*******************************************************************************

//---���W�n
#define TARGET_POS_X		(0.0f)			
#define TARGET_POS_Y		(5.0f)
#define TARGET_POS_Z		(-10.0f)

//---�T�C�Y�n
#define TARGET_SIZE_X		(3.0f)
#define TARGET_SIZE_Y		(0.0f)
#define TARGET_SIZE_Z		(3.0f)

//---���w�n
#define L_PI				(3.1415926f)		// ��
#define L_H_DEG				(180.0f)			// �p�x
#define	TRANS_RADIAN		(L_PI / L_H_DEG)	// ���W�A���ɕϊ�


//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
DrawBuffer* BulletTarget::m_pBTBuffer = NULL;
FBXPlayer* BulletTarget::m_pBTFBX = NULL;
Camera* g_pBulletTargetCamera;
GameObject* g_pBulletTarget;

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

	// �J�����C���X�^���X�̏�����
	//m_pCamera = new Camera;
	//m_pCamera->Init();
	//g_pBulletTargetCamera = new Camera;
	//g_pBulletTargetCamera->Init();

	//---�e�N�X�`���ǂݍ���
	LoadTextureFromFile("Assets/Model/Target2.png", &m_pBulletTargetTex);

	//g_pBulletTarget = new GameObject;
	//g_pBulletTarget->Init();

	GameObject::Init();

	//---�ϐ�������
	//g_pBulletTarget->SetPos((XMFLOAT3(TARGET_POS_X, TARGET_POS_Y, TARGET_POS_Z)));
	//g_pBulletTarget->SetSize(XMFLOAT3(TARGET_SIZE_X, TARGET_SIZE_Y, TARGET_SIZE_Z));
	//g_pBulletTarget->SetCollor(XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f));
	//g_pBulletTarget->SetAngle(XMFLOAT3(XM_PI / 2, 0.0f, 0.0f));

	m_pos = (XMFLOAT3(TARGET_POS_X, TARGET_POS_Y, TARGET_POS_Z));
	m_size = (XMFLOAT3(TARGET_SIZE_X, TARGET_SIZE_Y, TARGET_SIZE_Z));
	m_Color = (XMFLOAT4(1.0f, 1.0f, 1.0f, 0.0f));
	m_Angle = (XMFLOAT3(XM_PI / 2, 0.0, 0.0f));

	m_MoveSpeed = (1.0f / FPS) * 100.0f;
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
	//m_pCamera->Uninit();
	//delete m_pCamera;
	//g_pBulletTargetCamera->Uninit();
	//delete g_pBulletTargetCamera;

	//g_pBulletTarget->Uninit();
	//delete g_pBulletTarget;

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

	 float Move = (10.0f / FPS) * 4;	// 1�b�Ԃ�2M�i��

	m_move = XMFLOAT3(Axis.x, 0.0f, 0.0f);


	// �^�[�Q�b�g�I�u�W�F�N�g�ړ�
	//if (m_move.x != 0.0f && m_move.y != 0.0f) {
	if (IsPress('A')) {			// ��
		m_move.x -= Move;
		
		if (m_pos.x < -40.0f){
			m_pos.x = -40.0f;
		}
	}
	if (IsPress('D')) {		// �E
		m_move.x += Move;
		
		if (m_pos.x > 40.0f) {
			m_pos.x = 40.0f;
		}
	}

	if (IsRepeat(('Q'),1) || IsRepeat((JPadButton::X),1)|| 
		IsRepeat(('E'),1) || IsRepeat((JPadButton::B),1)){			// �ύX��[��
		/* 
			�L�[�͂Ȃ�����A���Ă����I�I�I�Ȃ�ŁI�I�I�I�킠�I�I�I�I	(2022/01/21���_)
			�ł����I�I�܂񂶁I�I								(2022/01/22���_)
		*/
		if (m_pos.z > 25.0f) {		// ���̉��܂�
			m_pos.z = 25.0f;
			m_MoveSpeed *= -1;		// �ړ��������]
		}

		if (m_pos.z < -23.0f) {		// ���̎�O�܂�
			m_pos.z = -23.0f;
			m_MoveSpeed *= -1;
		}
		m_move.z = m_MoveSpeed;		// �ړ��������]
	}


	m_pos.x += m_move.x;
	//m_pos.y += m_move.y;
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
	SHADER->Bind(VS_WORLD, PS_UNLIT);
	//m_pCamera->Bind2D();

	//g_pBulletTargetCamera->Bind2D();

	//int MeshNum = m_pBTFBX->GetMeshNum();

	//for (int i = 0; i < MeshNum; ++i){
	SHADER->SetTexture(m_pBulletTargetTex);

	SHADER->SetWorld
	(
		XMMatrixScaling(m_size.x, m_size.y, m_size.z)*
		XMMatrixRotationX(XM_PI / 2) * 
		XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);

	//g_pBulletTarget->Draw();


	GameObject::Draw();

	//SHADER->SetTexture(NULL);

		//m_pBTBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//}

}

//==============================================================
//
//	BulletTarget�N���X::���W�ݒ�
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void BulletTarget::SetBulletTargetPos(XMFLOAT3 pos) 
{
	m_pos = pos;
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