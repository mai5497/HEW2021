//====================================================================
//
// �e[Shadow.h]
// �쐬��:�g����
// 
// �X�V��:2022/01/24	�쐬
//====================================================================

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"Shadow.h"

//==============================================================
// 
//	Shadow�N���X::�R���X�g���N�^
// 
//==============================================================
Shadow::Shadow()
{

}

//==============================================================
// 
//	Shadow�N���X::�f�X�g���N�^
// 
//==============================================================
Shadow::~Shadow()
{

}

//==============================================================
// 
//	Shadow�N���X::������
// 
//==============================================================
bool Shadow::Init()
{
	
	//---�e�N�X�`���ǂݍ���
	LoadTextureFromFile("Assets/Model/shadow000.jpg", &m_pShadowTex);

	//---�I�u�W�F�N�g�C���X�^���X
	//m_pPolygonShadow = new GameObject;
	//m_pPolygonShadow->Init();
	//m_pPolygonShadow->SetPos(XMFLOAT3(0.0f, 5.0f, 0.0f));
	//m_pPolygonShadow->SetSize(XMFLOAT3(10.0f, 10.0f, 10.0f));
	GameObject::Init();

	m_pos = XMFLOAT3(0.0f, 1.6f, 0.0f);
	m_size = XMFLOAT3(3.0f, 0.0f, 3.0f);
	m_Color = XMFLOAT4(0.0f, 0.0f, 0.0f,1.0f);
	m_Angle = XMFLOAT3(0.0f, 0.0f, 0.0f);

	
	//---�J�����C���X�^���X
	//m_pCameraShadow = new Camera;
	//m_pCameraShadow->Init(XMFLOAT3(0.0f, 3.0f, 0.0f));

	return true;

}

//==============================================================
// 
//	Shadow�N���X::�I��
// 
//==============================================================
void Shadow::Uninit()
{
	SAFE_RELEASE(m_pShadowTex);

	//---�I�u�W�F�N�g�C���X�^���X���
	//m_pPolygonShadow->Uninit();
	//delete m_pPolygonShadow;
	GameObject::Uninit();

	//---�J�����C���X�^���X���
	//m_pCameraShadow->Uninit();
	//delete m_pCameraShadow;
}

//==============================================================
// 
//	Shadow�N���X::�X�V
// 
//==============================================================
void Shadow::Update()
{

}

//==============================================================
// 
//	Shadow�N���X::�`��
// 
//==============================================================
void Shadow::Draw()
{
	SHADER->Bind(VS_WORLD, PS_UNLIT);

	//m_pCameraShadow->Bind();

	SHADER->SetTexture(m_pShadowTex);

	SHADER->SetWorld
	(
		XMMatrixScaling(m_size.x, m_size.y, m_size.z) *
		XMMatrixRotationY(m_Angle.y) *
		XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	);

	GameObject::Draw();


	SHADER->SetTexture(NULL);
}

//==============================================================
// 
//	Shadow�N���X::���W�̐ݒ�
// 
//==============================================================
void Shadow::SetShadow(XMFLOAT3 pos)
{
	
}