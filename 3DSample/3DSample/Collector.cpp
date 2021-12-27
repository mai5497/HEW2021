//****************************************************
//
//	������u
//	�쐬�ҁF�ɐ����P
//	
//	2021/12/21 : �쐬
//	2021/12/22 : �ړ������ǉ�
//	2021/12/25 : �萔�� / �R�����g�ǋL
//	2021/12/26 : ���f���ύX
//
//****************************************************

//========================= �C���N���[�h�� ===========================
#include "Collector.h"
#include "Texture.h"

#define ENEMY_SIZE (0.5f)

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define COLLECTOR_SIZE		(0.3f)
#define FPS					(60)					// �t���[����
#define WAIT_TIME			(10)					// �ҋ@����

#define START_POS_X			(22.0f)					// �J�n�n�_ X
#define START_POS_Y			(10.0f)					// �J�n�n�_ Y
#define COLLECT_POS_X		(0.0f)					// ����n�_ X
#define COLLECT_POS_Y		(1.0f)					// ����n�_ Y

Collector::Collector()
{
	LoadTextureFromFile("Assets/Model/tyoutingazou.png", &m_pCollectorTex);

//*******************************************************************************
// �O���[�o���錾
//*******************************************************************************
DrawBuffer* Collector::m_pBuffer = NULL;
FBXPlayer* Collector::m_pfbx = NULL;


//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
Collector::Collector()
{
	LoadTextureFromFile("Assets/Model/ufo.png", &m_pCollectorTex);

	m_pos = XMFLOAT3(START_POS_X, START_POS_Y, 0.0f);
	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Radius = XMFLOAT3(0.8f, 0.8f, 0.8f);

	m_timer = WAIT_TIME * FPS + 59;
	m_timeFlg = true;
	use = true;

	m_collisionType = COLLISION_DYNAMIC;
}


//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
Collector::~Collector()
{

}

//====================================================================
//
//		FBX�Ǎ�
//
//====================================================================
bool Collector::LoadFBX(const char* pFilePath)
{
	HRESULT hr;
	m_pfbx = new FBXPlayer;
	hr = m_pfbx->LoadModel(pFilePath);
	if (FAILED(hr)) {
		return false;
	}

	//���f���̃��b�V���̐��������_�o�b�t�@�쐬
	int meshNum = m_pfbx->GetMeshNum();
	m_pBuffer = new DrawBuffer[meshNum];
	for (int i = 0; i < meshNum; i++)
	{
		//���b�V�����Ƃɒ��_�o�b�t�@�쐬
		m_pBuffer[i].CreateVertexBuffer(
			m_pfbx->GetVertexData(i),
			m_pfbx->GetVertexSize(i),
			m_pfbx->GetVertexCount(i)
		);
		//�C���f�b�N�X�o�b�t�@�쐬
		m_pBuffer[i].CreateIndexBuffer(
			m_pfbx->GetIndexData(i),
			m_pfbx->GetIndexCount(i)
		);

	}
	return true;
}


//====================================================================
//
//		������
//
//====================================================================
bool Collector::Init()
{
	if (m_pBuffer == NULL)
	{
		Collector::LoadFBX("Assets/Model/tyoutinobake.fbx");
	}
	return true;
}


//====================================================================
//
//		�I������
//
//====================================================================
void Collector::Uninit()
{
	if (m_pBuffer != NULL) {
		delete[] m_pBuffer;
		m_pBuffer = NULL;
		delete m_pfbx;
		m_pfbx = NULL;
	}
}


//====================================================================
//
//		�X�V
//
//====================================================================
void Collector::Update()
{
	// �A�[�N�^���W�F���g(�t����)
	m_angle = atan2(m_move.z, m_move.x);
	m_angle -= DirectX::XM_PI * 0.5f;

	if (m_timeFlg) {
		// ��莞�ԑҋ@
		if (m_timer > 0) {
			m_timer--;
		}
		// ����n�_�ֈړ�
		else {
			m_move.x = -(MOVE_SPEED / FPS);
		}
		if (m_pos.x < COLLECT_POS_X) {
			m_move.x = 0;
			if (m_pos.y > COLLECT_POS_Y) {
				m_move.y = -(MOVE_SPEED / FPS);
			}
			else {
				m_move.y = 0;
				m_timeFlg = false;
				m_timer = WAIT_TIME * FPS + 59;
			}
		}
	}

	if (!m_timeFlg) {
		// ��莞�ԑҋ@
		if (m_timer > 0) {
			m_timer--;
		}
		// �J�n�n�_�֖߂�
		else {
			m_move.y = (MOVE_SPEED / FPS);
		}

		if (m_pos.y > START_POS_Y) {
			m_move.y = 0;
			if (m_pos.x < START_POS_X) {
				m_move.x = (MOVE_SPEED / FPS);
			}
			else {
				m_move.x = 0;
			}
		}
	}

	// �ړ�
	m_pos.x += m_move.x;
	m_pos.y += m_move.y;
	m_pos.z += m_move.z;
}


//====================================================================
//
//		�`��
//
//====================================================================
void Collector::Draw()
{
	int meshNum = m_pfbx->GetMeshNum();
	for (int i = 0; i < meshNum; ++i)
	{
		SHADER->SetWorld(
			DirectX::XMMatrixScaling(COLLECTOR_SIZE, COLLECTOR_SIZE, COLLECTOR_SIZE)
			* DirectX::XMMatrixRotationY(-m_angle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));

		SHADER->SetTexture(m_pCollectorTex);

		m_pBuffer[i].Draw(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);
	}
}

int Collector::GetTimer()
{
	return m_timer;
}
