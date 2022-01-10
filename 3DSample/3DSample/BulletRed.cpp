//====================================================================
//
// �Ԓe[BulletRed.cpp]
// �쐬��:�ɒn�c�^��
// 
// �X�V��:2022/01/08	�쐬
//====================================================================

//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************
#include "BulletRed.h"
#include "MyVector.h"
#include "Texture.h"

//========================= �O���[�o���ϐ���` ===========================
DrawBuffer* BulletRed::m_pBuffer = NULL;
FBXPlayer* BulletRed::m_pFBX = NULL;


//==============================================================
//
//	BulletRed::�R���X�g���N�^
// 
//==============================================================
BulletRed::BulletRed()
{
	//----- �ϐ������� -----
	LoadTextureFromFile("Assets/Texture/flowerred.png", &m_pBulletRedTex);
	SetRBFlg(true);	// �Ԓe
}

//==============================================================
//
//	BulletRed::�f�X�g���N�^
// 
//==============================================================
BulletRed::~BulletRed()
{
	Uninit();
}

//==============================================================
//
//	BulletRed::������
// 
//==============================================================
bool BulletRed::Init()
{
	/* �ȉ��̓��f����������g�p */
	if (m_pBuffer == NULL) {
		BulletRed::LoadBullet("Assets/Model/flowerred.fbx");
	}

	GameObject::Init();
	return true;

}

//==============================================================
//
//	BulletRed::�I������
// 
//==============================================================
void BulletRed::Unint()
{
	SAFE_RELEASE(m_pBulletRedTex);
	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pFBX;
		m_pFBX = NULL;
	}

	GameObject::Uninit();

}

//==============================================================
//
//	BulletRed::�`��
// 
//==============================================================
void BulletRed::Draw()
{
	// �e�̃e�N�X�`��
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			//* DirectX::XMMatrixRotationY(-m_DwarfAngle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pBulletRedTex);
		/*
		SHADER->SetTexture(m_fbx.GetTexture(i));
		*/

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

}


//====================================================================
//
//		�e�N�X�`���ǂݍ���
//
//====================================================================
bool BulletRed::LoadBullet(const char* pFilePath)
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