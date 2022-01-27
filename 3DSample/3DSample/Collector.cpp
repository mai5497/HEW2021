//****************************************************
//
//	������u
//	�쐬�ҁF�ɐ����P
//	
//	2021/12/21 : �쐬
//	2021/12/22 : �ړ������ǉ�
//	2021/12/25 : �萔�� / �R�����g�ǋL
//	2021/12/26 : ���f���ύX
// 2022/01/17 : �d�l�ύX
//****************************************************

//========================= �C���N���[�h�� ===========================
#include "Collector.h"
#include "Texture.h"
#include "Sound.h"

//*******************************************************************************
// �萔�E�}�N����`
//*******************************************************************************
#define COLLECTOR_SIZE		(1.0f)
#define FPS					(60)					// �t���[����
#define START_WAIT_TIME			(5)					// �ҋ@����
#define COLLECT_WAIT_TIME			(2)					// �ҋ@����

#define START_POS_X			(46.0f)					// �J�n�n�_ X
#define START_POS_Z			(26.0f)					// �J�n�n�_ 
#define START_POS_Y			(17.0f)					// �J�n�n�_ Y
#define COLLECT_POS_X		(0.0f)					// ����n�_ X
#define COLLECT_POS_Y		(1.0f)					// ����n�_ Y

#define MOVE_SPEED			(1.5f)					// �ړ����x


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

	m_pos = XMFLOAT3(START_POS_X, START_POS_Y, START_POS_Z);
	m_move = XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Radius = XMFLOAT3(5.0f, 0.1f, 5.0f);

	m_nowCollectTimer = COLLECT_WAIT_TIME * FPS + 59;
	m_timer = START_WAIT_TIME * FPS + 59;
	m_collectFlg = true;
	use = true;
	m_nowCollectFlg = false;

	m_moveFlg = false;

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
		Collector::LoadFBX("Assets/Model/ufo.fbx");
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
	SAFE_RELEASE(m_pCollectorTex);
}


//====================================================================
//
//		�X�V
//
//====================================================================
void Collector::Update()
{
	XMFLOAT3 targetpos;

	//----- ������ҋ@�^�C�}�[�J�E���g�_�E�� -----
	if (m_nowCollectFlg) {
		m_nowCollectTimer--;
	}

	//----- ����֌����� -----
	if (m_collectFlg) {
		// ��莞�ԑҋ@
		if (m_timer > 0) {
			m_timer--;	// �X�^�[�g����̑ҋ@�^�C�}�[�J�E���g�_�E��
		} else {
			m_moveFlg = true;	// �ړ����t���O�𗧂Ă�
		}
		if (m_moveFlg) {
			// �Ǐ]����^�[�Q�b�g�̍��W
			targetpos = XMFLOAT3(m_targetPos.x, START_POS_Y, m_targetPos.z);	// Y�͈ړ������Ȃ�����X�^�[�g�˂�����ł�
			if (m_pos.x <= targetpos.x && m_pos.z <= targetpos.z) {	// �ړI�n�ɓ���
				m_nowCollectFlg = true;	// ������t���O�𗧂Ă�
				m_moveFlg = false;		// �ړ����������i���낵�Ă����Ɖ���Ԃ��Ղ�Ղ邵�Ȃ��j
				if (m_nowCollectTimer < 0) {	// ������̃^�C�}�[���O
					m_moveFlg = true;							// �ړ����𗧂Ă�
					m_collectFlg = false;						// �A�҂ɂ���̂�false
					m_nowCollectFlg = false;					// ������̃t���O������
					m_nowCollectTimer = COLLECT_WAIT_TIME * FPS + 59;	// ������^�C�}�[�̏�����
				}
			}
		}
	} 

	//----- �A�҂��� -----
	if (!m_collectFlg) {
		if(m_pos.x <= START_POS_X && m_pos.z <= START_POS_Z){	// �X�^�[�g�ʒu�ɋA���Ă��Ȃ�������
			targetpos = m_targetPos = XMFLOAT3(START_POS_X, START_POS_Y, START_POS_Z);	// �Ǐ]����^�[�Q�b�g�̍��W
		} else {
			m_moveFlg = false;				// �ړ��������낷
			m_collectFlg = true;			// ���͉���Ɍ������̂�ture
			m_timer = START_WAIT_TIME * FPS + 59;	// �X�^�[�g�ʒu�ł̑ҋ@�^�C�}�[�̏�����
		}
	}

	XMVECTOR m_vTarget = XMLoadFloat3(&targetpos);
	// ���̍��W
	XMVECTOR vCollectorPos = XMLoadFloat3(&m_pos);
	// �i�s����							�@�@���x�N�g���̈����Z
	XMVECTOR vDirection = XMVectorSubtract(m_vTarget, vCollectorPos);
	// ���̑��x�ɂ��邽�߂ɐ��K��
	// ���x��ς���Ȃ�vDirecton�ɑ��x��������B
	vDirection = XMVector3Normalize(vDirection);
	// ������֐�								  �������鐔
	if (m_collectFlg) {
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * 14);
	} else {
		vDirection = XMVectorScale(vDirection, (1.0f / 60) * 28);
	}
	// Float3�^�ɕϊ�
	XMStoreFloat3(&m_move, vDirection);


	// �A�[�N�^���W�F���g(�t����)
	m_angle = atan2(m_move.z, m_move.x);
	m_angle -= DirectX::XM_PI * 0.5f;



	if (m_moveFlg) {
		// �ړ�
		m_pos.x += m_move.x;
		m_pos.y += m_move.y;
		m_pos.z += m_move.z;
	}
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

	SHADER->SetTexture(NULL);
}

int Collector::GetTimer()
{
	return m_timer;
}


//====================================================================
//
//		������^�C���̎擾
//
//====================================================================
int Collector::GetnowCollectTimer() {
	return m_nowCollectTimer;
}



//====================================================================
//
//		������t���O�̎擾
//
//====================================================================
bool Collector::GetNowCollectFlg() {
	return m_nowCollectFlg;
}


//====================================================================
//
//		����ꏊ�̕ۑ�
//
//====================================================================
void Collector::SetTargetPos(XMFLOAT3 pos) {
	m_targetPos = pos;
}