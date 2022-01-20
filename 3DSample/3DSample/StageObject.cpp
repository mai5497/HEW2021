//****************************************************
//
//	�X�e�[�W�I�u�W�F�N�g[ObjectStage.cpp]
//	�쐬�ҁF�g����
//	
//	2022/01/18 :�쐬 
//
//****************************************************
// 
 //*******************************************************************************
 // �C���N���[�h��
 //*******************************************************************************
#include	"StageObject.h"

 //*******************************************************************************
 // �萔�E�}�N����`
 //*******************************************************************************
#define	OBJECT_SIZE		(XMFLOAT3(0.5f,0.5f,0.5f))

 //*******************************************************************************
 // �O���[�o���ϐ�
 //*******************************************************************************
//DrawBuffer* StageObject::m_pBuffer = NULL;
//FBXPlayer* StageObject::m_pFBX = NULL;

//==============================================================
//
//	BlueBullet::�R���X�g���N�^
// 
//==============================================================
StageObject::StageObject()
{

}

//==============================================================
//
//	BlueBullet::�f�X�g���N�^
// 
//==============================================================
StageObject::~StageObject()
{

}

//==============================================================
//
//	BlueBullet::������
// 
//==============================================================
bool StageObject::Init()
{
	//---�ϐ�������
	//m_pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	//m_size = (OBJECT_SIZE);

	GameObject::Init();

	return true;
}

//==============================================================
//
//	BlueBullet::�I��
// 
//==============================================================
void StageObject::Uninit()
{
	////---�e�N�X�`�����
	//SAFE_RELEASE(m_pObjectStageTex);

	//if (m_pBuffer != NULL) {
	//	delete[] m_pBuffer;
	//	m_pBuffer = NULL;
	//	delete m_pFBX;
	//	 m_pFBX  = NULL;
 //	}

	GameObject::Uninit();
}

//==============================================================
//
//	BlueBullet::�`��
// 
//==============================================================
void StageObject::Draw()
{
	////���f���`��
	//int meshNum = m_pFBX->GetMeshNum();
	//for (int i = 0; i < meshNum; ++i) {
	//	SHADER->SetWorld(
	//		XMMatrixScaling(m_size.x, m_size.y, m_size.z) *
	//		XMMatrixRotationY(-m_Angle.y) *
	//		XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

	//	SHADER->SetTexture(m_pObjectStageTex);

	//	m_pBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	//}

	StageObjectBase::Draw();
}

////====================================================================
////
////		�e�N�X�`���ǂݍ���
////
////====================================================================
//bool StageObject::LoadStageObject(const char* pFilePath)
//{
//	/* �ȉ��̓��f����������g�p */
//	HRESULT hr;
//	m_pFBX = new FBXPlayer;
//	hr = m_pFBX->LoadModel(pFilePath);
//	if (FAILED(hr))
//	{
//		return false;
//	}
//
//	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
//	int meshNum = m_pFBX->GetMeshNum();
//	m_pBuffer = new DrawBuffer[meshNum];
//	for (int i = 0; i < meshNum; i++)
//	{
//		//���b�V�����Ƃɒ��_�o�b�t�@�쐬
//		m_pBuffer[i].CreateVertexBuffer(
//			m_pFBX->GetVertexData(i),
//			m_pFBX->GetVertexSize(i),
//			m_pFBX->GetVertexCount(i)
//		);
//		//�C���f�b�N�X�o�b�t�@�쐬
//		m_pBuffer[i].CreateIndexBuffer(
//			m_pFBX->GetIndexData(i),
//			m_pFBX->GetIndexCount(i)
//		);
//
//	}
//	return true;
//
//}
