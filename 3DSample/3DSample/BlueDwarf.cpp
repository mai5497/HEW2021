//****************************************************
//
//	���l
//	�쐬�ҁF�ɒn�c�^��
//	
//	2021/12/21 : �Ԃ��R�s�[���č쐬
//				 �ǐՒǉ�
//				 ���f�������ւ�
//
//****************************************************


//========================= �C���N���[�h�� ===========================
#include "BlueDwarf.h"
#include "MyVector.h"
#include "Collision.h"
#include "Player.h"
#include "Texture.h"
#include "GameScene.h"

//========================= �萔��` ===========================
#define DWARF_SIZE (0.7f)
#define GRAVITY		(0.3f)


//========================= �O���[�o���ϐ���` ===========================
DrawBuffer *BlueDwarf::m_pBuffer = NULL;
FBXPlayer *BlueDwarf::m_pFBX = NULL;

//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
BlueDwarf::BlueDwarf()
{
	Init();
}


//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
BlueDwarf:: ~BlueDwarf()
{
	Uninit();
}


//====================================================================
//
//		������
//
//====================================================================
bool BlueDwarf::Init()
{
	//----- �ϐ������� -----
	LoadTextureFromFile("Assets/Model/kobitoblue.png", &m_pBlueDwarfTex);

	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);

	m_size = XMFLOAT3(DWARF_SIZE, DWARF_SIZE, DWARF_SIZE);

	m_Radius = XMFLOAT3(2.0f, 1.0f, 2.0f);

	SetRBFlg(false);	// ���l

	if (m_pBuffer == NULL) {
		LoadDwarf("Assets/Model/kobitoblue.fbx");
	}

	GameObject::Init();
	return true;
}


//====================================================================
//
//		�I������
//
//====================================================================
void BlueDwarf::Uninit()
{
	if (m_pBuffer != NULL) 
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pFBX;
		m_pFBX = NULL;
	}

	SAFE_RELEASE(m_pBlueDwarfTex);
	GameObject::Uninit();
}


//====================================================================
//
//		�X�V����
//
//====================================================================
void BlueDwarf::Update()
{	
	//----- �ϐ������� -----
	//static bool jumpFlg;
	float Differ;		// ���l�ƒe�̋����̍�


	// �Ǐ]����^�[�Q�b�g�̍��W
	XMVECTOR vTarget = XMLoadFloat3(&m_targetPos);
	// ���l�̍��W
	XMVECTOR vBlueDwarfPos = XMLoadFloat3(&m_pos);
	// �i�s����							�@�@���x�N�g���̈����Z
	XMVECTOR vDirection = XMVectorSubtract(vTarget, vBlueDwarfPos);
	// ���̑��x�ɂ��邽�߂ɐ��K��
	// ���x��ς���Ȃ�vDirecton�ɑ��x��������B
	vDirection = XMVector3Normalize(vDirection);
	// ������֐�							�������鐔
	vDirection = XMVectorScale(vDirection, 1.0f / 60);

	XMStoreFloat3(&m_move, vDirection);

	// Float3�^�ɕϊ�
	if (GetFollowFlg()) {	// �ǐՃt���O�������Ă���Ƃ�
		XMStoreFloat3(&m_move, vDirection * 5);
	}
	if (GetrunFlg()) {		// �e���瓦����Ƃ�
		XMStoreFloat3(&m_move, -(vDirection * 2.5));
	}

	// �A�[�N�^���W�F���g(�t����)
	m_DwarfAngle = atan2(m_move.z, m_move.x);
	m_DwarfAngle -= DirectX::XM_PI * 0.5f;


	//if (jumpFlg) {
	//	m_move.y -= 0.21f;
	//}

	//Differ = fabsf(m_targetPos.x - m_pos.x) + fabsf(m_targetPos.z - m_pos.z);
	//if (Differ < 0.05f) {	// �Ȃ�ƂȂ��߂��ɂ���Ƃ��B�}�W�b�N�i���o�[�ł��߂�B
	//	SetMoveFlg(false);		// �ړ������낷
	//}

	// �d�͂�������
	m_move.y -= GRAVITY;


	// �ړ�
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

	if (m_pos.y < 0.8f) {
		BlueDwarf::SetAliveFlg(false);
	}

	m_currentPos = m_pos;
}


//====================================================================
//
//		�`�揈��
//
//====================================================================
void BlueDwarf::Draw()
{
	// ���l�̃e�N�X�`��
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(
			DirectX::XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			*DirectX::XMMatrixRotationY(-m_DwarfAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pBlueDwarfTex);

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}




//====================================================================
//
//		�e�N�X�`���ǂݍ���
//
//====================================================================
bool BlueDwarf::LoadDwarf(const char* pFilePath)
{
	HRESULT hr;
	m_pFBX = new FBXPlayer;
	hr = m_pFBX->LoadModel(pFilePath);
	if (FAILED(hr)){
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