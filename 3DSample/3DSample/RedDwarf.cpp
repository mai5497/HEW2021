//****************************************************
//
//	�ԏ��l
//	�쐬�ҁF�ɒn�c�^��
//	
//	2021/12/04 : �쐬
//	2021/12/09 : ���f�ޓ���
//
//****************************************************


//========================= �C���N���[�h�� ===========================
#include "RedDwarf.h"
#include "MyVector.h"
#include "Collision.h"
#include "Player.h"
#include "Texture.h"
#include "Bullet.h"
#include "GameScene.h"

#define DWARF_SIZE (1.0f)

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
	LoadTextureFromFile("Assets/Model/kougeki.png", &m_pRedDwarfTex);

	m_move.x = 0.0f;
	m_move.y = 0.0f;
	m_move.z = 0.0f;

}


//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
RedDwarf:: ~RedDwarf()
{

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
		RedDwarf::LoadDwarf("Assets/Model/kougeki.fbx");
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
	if (m_pBuffer != NULL) 
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pFBX;
		m_pFBX = NULL;
	}
}


//====================================================================
//
//		�X�V����
//
//====================================================================
void RedDwarf::Update()
{	
	//----- �ϐ������� -----
	static bool jumpFlg;

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
	vDirection = XMVectorScale(vDirection, 1.0f / 60);

	// Float3�^�ɕϊ�
	XMStoreFloat3(&m_move, vDirection * 5);

	// �A�[�N�^���W�F���g(�t����)
	m_DwarfAngle = atan2(m_move.z, m_move.x);
	m_DwarfAngle -= DirectX::XM_PI * 0.5f;

	if(m_AttackFlg) {
		m_move.y += 0.2f;
		jumpFlg = true;
	} else {
		jumpFlg = false;
	}

	if (jumpFlg) {
		m_move.y -= 0.21f;
	}

	// �ړ�
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;

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

		SHADER->SetWorld(
			DirectX::XMMatrixScaling(DWARF_SIZE, DWARF_SIZE, DWARF_SIZE)
			*DirectX::XMMatrixRotationY(-m_DwarfAngle)
			*DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pRedDwarfTex);
		/*SHADER->SetTexture(
		m_fbx.GetTexture(i)
		);*/

		m_pBuffer[i].Draw(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
	}
}


//====================================================================
//
//		�U��
//
//====================================================================
void RedDwarf::Attack()
{


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