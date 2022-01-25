//****************************************************
//
//	�I�u�W�F�N�g�x�[�X[StageObjectBase.cpp]
//	�쐬�ҁF�g����
//	
//	2022/01/18 :�쐬 
//
//****************************************************

 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"StageObjectBase.h"

 //*******************************************************************************
 // �O���[�o���ϐ�
 //*******************************************************************************


//==============================================================
//
//	ObjectBase�N���X::�R���X�g���N�^
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
StageObjectBase::StageObjectBase()
{
	//---�ϐ�������
	/*m_pos.x = 0.0f;
	m_pos.y = 0.0f;
	m_pos.z = 0.0f;

	m_size.x = 1.0f;
	m_size.y = 1.0f;
	m_size.z = 1.0f;*/

	// �e�N�X�`���ǂݍ���
	//LoadTextureFromFile(m_TexPath, &m_pStageObjectTex);

	// ���f���ǂݍ���
	//LoadStageObject(m_ModelPath);


}

//==============================================================
//
//	ObjectBase�N���X::�f�X�g���N�^
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
StageObjectBase::~StageObjectBase()
{

}

//==============================================================
//
//	ObjectBase�N���X::������
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
bool StageObjectBase::Init()
{
	//---�ϐ�������
	m_pos = XMFLOAT3(0.0f,0.0f,0.0f);
	m_size = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Angle = XMFLOAT3(1.0f,1.0f , 1.0f);

	m_collisionType = COLLISION_STATIC;

	m_pBuffer = nullptr;
	m_pFBX = nullptr;

	GameObject::Init();

	return true;
}

//==============================================================
//
//	ObjectBase�N���X::������
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void StageObjectBase::Uninit()
{
	if (m_pBuffer != NULL)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;

		delete m_pFBX;
		m_pFBX = NULL;
	}

	SAFE_RELEASE(m_pStageObjectTex);
	GameObject::Uninit();

}
//==============================================================
//
//	ObjectBase�N���X::�X�V
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void StageObjectBase::Update()
{

}
//==============================================================
//
//	ObjectBase�N���X::�`��
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void StageObjectBase::Draw()
{
	int meshNum = m_pFBX->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->Bind(VS_WORLD,PS_LAMBERT);

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			* DirectX::XMMatrixRotationRollPitchYaw(
				XMConvertToRadians(m_Angle.x),
				XMConvertToRadians(m_Angle.y),
				XMConvertToRadians(m_Angle.z))
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		

		SHADER->SetTexture(m_pStageObjectTex);
		/*
		SHADER->SetTexture(m_fbx.GetTexture(i));
		*/

		m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}

//==============================================================
//
//	ObjectBase�N���X::�e�N�X�`���p�X��ݒ�
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void StageObjectBase::SetTexPath(LPCSTR TexPath)
{
	m_TexPath = TexPath;
}

//==============================================================
//
//	ObjectBase�N���X::���f���p�X�ݒ�
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
void StageObjectBase::SetModelPath(LPCSTR ModelPath)
{
	m_ModelPath = ModelPath;
}

//==============================================================
//
//	ObjectBase�N���X::�e�N�X�`���p�X���擾
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
LPCSTR StageObjectBase::GetTexPath()
{
	return m_TexPath;
}

//==============================================================
//
//	ObjectBase�N���X::���f���p�X���擾
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
LPCSTR StageObjectBase::GetModelPath()
{
	return m_ModelPath;
}

//==============================================================
//
//	ObjectBase�N���X::�I�u�W�F�N�g����
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F ���W�A�傫��,�p�x,�e�N�X�`���p�X,���f���p�X
//
//==============================================================
void StageObjectBase::CreateStageObject(XMFLOAT3 pos, XMFLOAT3 size, XMFLOAT3 angle,LPCSTR TexPath, LPCSTR ModelPath)
{
	//---���W�E�T�C�Y�E�A���O���̎w��
	m_pos= pos;					
	m_size = size;
	m_Angle = angle;


	//---�e�N�X�`���E���f���̓ǂݍ���
	if (m_pBuffer == NULL) {
		LoadTextureFromFile(TexPath, &m_pStageObjectTex);			// �e�N�X�`��
	}
	if (m_pFBX == NULL) {
		LoadStageObject(ModelPath);												// ���f��
	}

}

//==============================================================
//
//	ObjectBase�N���X::���f���ǂݍ���
//	�쐬��	�F �g����
//	�߂�l	�F void
//	����		�F void
//
//==============================================================
bool StageObjectBase::LoadStageObject(const char* pFilePath)
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