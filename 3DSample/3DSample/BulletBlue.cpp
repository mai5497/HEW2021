//====================================================================
//
// �e[BlueBullet.cpp]
// �쐬��:�g����
// 
// �X�V��:2022/01/09	�쐬
//====================================================================
 
//*******************************************************************************
// �C���N���[�h��
//*******************************************************************************
#include	"BulletBlue.h"
#include	"MyVector.h"
#include	"Texture.h"

//========================= �O���[�o���ϐ���` ===========================
DrawBuffer* BulletBlue::m_pBuffer = NULL;
FBXPlayer* BulletBlue::m_pFBX = NULL;

//==============================================================
//
//	BlueBullet::�R���X�g���N�^
// 
//==============================================================
BulletBlue::BulletBlue()
{
	/* �e�N�X�`���ǂݍ��� */
	LoadTextureFromFile("Assets/Texture/flowerblue.png", &m_pBulletBlueTex);
	SetRBFlg(false);	// �e
	
}

//==============================================================
//
//	BlueBullet::�f�X�g���N�^
// 
//==============================================================
BulletBlue::~BulletBlue()
{
	Uninit();
}

//====================================================================
//
//	BlueBullet::������
//
//====================================================================
bool BulletBlue::Init()
{
	/* ���f���ǂݍ��� */
	if (m_pBuffer == NULL) {
		LoadBullet("Assets/Model/flowerblue.fbx");
	}
	//m_floweAnim[0] = m_pFBX->LoadAnimation("Assets/Model/flowerblue_anime.fbx");

	return true;
}

//void BulletBlue::Update() {
//	m_pFBX->Play(0);
//	m_pFBX->Step();
//}

//==============================================================
//
//	BlueBullet::�I������
// 
//==============================================================
void BulletBlue::Unint()
{
	SAFE_RELEASE(m_pBulletBlueTex);
	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pFBX;
		m_pFBX = NULL;
	}

}

//==============================================================
//
//	RedBullet::�`��
// 
//==============================================================
void BulletBlue::Draw()
{
	//SHADER->Bind(VS_ANIMATION,PS_UNLIT);
	//m_pFBX->Step();

	// �e�̃e�N�X�`��
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			//* DirectX::XMMatrixRotationY(-m_DwarfAngle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		SHADER->SetAnimation(m_pFBX->GetAnimeMatrix(i), m_pFBX->GetAnimeMatrixNum(i));
		SHADER->SetTexture(m_pBulletBlueTex);

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
bool BulletBlue::LoadBullet(const char* pFilePath)
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