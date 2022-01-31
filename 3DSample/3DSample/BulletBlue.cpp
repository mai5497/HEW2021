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
#include	"Sound.h"

//==============================================================
//
//	BlueBullet::�R���X�g���N�^
// 
//==============================================================
BulletBlue::BulletBlue()
{
	/* ���f���ǂݍ��� */
	m_pBlueModel = m_pBulletModel[BLUE_BULLET];
	m_pBlueBuffer = m_pBuffer[BLUE_BULLET];

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
	m_AliveTime = BULLET_DESTOROY_CNT;		// ��������

	return true;
}


//==============================================================
//
//	BlueBullet::�I������
// 
//==============================================================
void BulletBlue::Unint()
{

}

//==============================================================
//
//	BlueBullet::�X�V
// 
//==============================================================
void BulletBlue::Update() {

	// �e�̓������Ԃ�i�߂�(�萔�œ����I��鎞�Ԃ����߂��)
	m_ThrowTimer += 1.3f / BULLET_THROW_CNT;


	if (m_ThrowTimer <= 1.0f) {

		m_pos.x = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.x + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.x + m_ThrowTimer * m_ThrowTimer * m_EndPos.x;

		m_pos.y = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.y + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.y + m_ThrowTimer * m_ThrowTimer * m_EndPos.y;

		m_pos.z = (1.0f - m_ThrowTimer) * (1.0f - m_ThrowTimer) * m_StarPos.z + 2 * (1.0f - m_ThrowTimer) * m_ThrowTimer * m_CenterPos.z + m_ThrowTimer * m_ThrowTimer * m_EndPos.z;
	} else {
		m_ColFlg = true;
	}
	if (m_ColFlg) {
		if (m_AliveTime == BULLET_DESTOROY_CNT) {
			// �T�E���h
			CSound::Play(SE_BULLET_2);
			//m_pFBX->Play(0);
			m_LandingFlg = true;	// �e���n�ʂɂ����u��
		} else {
			m_LandingFlg = false;
		}

		// �e�̎��Ԍo�߂ł̔j�󏈗�
		m_AliveTime--;					// �������Ԃ̃J�E���g�_�E��
		//if (m_AliveTime < 25) {
		//	if (!m_pBlueModel->IsPlay()) {
		//		m_pBlueModel->Play(m_flowerAnim[BLUE_BLAST]);
		//	}
		//}
		if (m_AliveTime < 0) {			// 0�ȉ��ɂȂ�����
			use = false;					// �g�p�t���O��ύX
			Uninit();
		}
	}

	//if (m_pBlueModel->IsPlay()) {
	//	m_pBlueModel->Step();
	//}
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
	int meshNum = m_pBlueModel->GetMeshNum();
	for (int i = 0; i < meshNum; ++i) {

		SHADER->SetWorld(XMMatrixScaling(m_size.x, m_size.y, m_size.z)
			//* DirectX::XMMatrixRotationY(-m_DwarfAngle)
			* DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z));
		//SHADER->SetAnimation(m_pBlueModel->GetAnimeMatrix(i), m_pBlueModel->GetAnimeMatrixNum(i));
		SHADER->SetTexture(m_pBulletTex[BLUE_BULLET]);

		/*
		SHADER->SetTexture(m_fbx.GetTexture(i));
		*/

		m_pBlueBuffer[i].Draw(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}