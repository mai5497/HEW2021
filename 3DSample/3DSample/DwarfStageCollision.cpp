//****************************************************
//
//	���l�̃X�e�[�W�̓����蔻��̂��߂̃u���b�N����
//	�쐬�ҁF�ɒn�c�^��
//	
//	2022/01/18 : �쐬
//
//****************************************************

//========================= �C���N���[�h�� ===========================
#include "DwarfStageCollision.h"


//====================================================================
//
//		�R���X�g���N�^
//
//====================================================================
DwarfStageCollision::DwarfStageCollision() {
	
}


//====================================================================
//
//		�f�X�g���N�^
//
//====================================================================
DwarfStageCollision::~DwarfStageCollision() {

}


//====================================================================
//
//		������
//
//====================================================================
void DwarfStageCollision::Init() {
	//----- �ݒ� -----
	struct StageSetting {
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};

	StageSetting settings[] =
	{
		// ��ԏ�
		{ XMFLOAT3(0.0f,1.0f, 15.5f),
		  XMFLOAT3(19.0f,1.0f,1.0f),
		},
		//�ォ��Q�Ԗ�
		{ XMFLOAT3(0.0f,1.0f, 14.5f),
		  XMFLOAT3(22.0f,1.0f,1.0f),
		},
		//�ォ��3�Ԗ�
		{ XMFLOAT3(0.0f,1.0f, 13.5f),
		  XMFLOAT3(25.0f,1.0f,1.0f),
		},
		//�ォ��4�Ԗ�
		{ XMFLOAT3(0.0f,1.0f, 12.0f),
		  XMFLOAT3(31.0f,1.0f,2.0f),
		},
		// �^��
		{ XMFLOAT3(0.0f,1.0f,10.0f),
		  XMFLOAT3(35.0f,1.0f,2.0f),
		},
		// ������S�Ԗ�
		{ XMFLOAT3(0.0f,1.0f,7.5f),
		  XMFLOAT3(40.0f,1.0f,3.0f),
		},
		// ������R�Ԗ�
		{ XMFLOAT3(0.0f,1.0f,4.0f),
		  XMFLOAT3(46.0f,1.0f,4.0f),
		},
		// �������Ԗ�
		{ XMFLOAT3(0.0f,1.0f,-1.5f),
		  XMFLOAT3(52.0f,1.0f,7.0f),
		},
		//��ԉ�
		{ XMFLOAT3(0.0f, 1.0f, -10.0f),
		  XMFLOAT3(56.0f, 1.0f,10.0f),
		},

	};

	//�����f�[�^����t�B�[���h�̐����v�Z
	m_DawarfStageNum = sizeof(settings) / sizeof(settings[0]);

	//�|�C���^���i�[����z����쐬
	m_ppDwarfStageCollision = new GameObject *[m_DawarfStageNum];

	//���ꂼ��̔z��Ƀt�B�[���h���������m��
	for (int i = 0; i < m_DawarfStageNum; i++) {
		m_ppDwarfStageCollision[i] = new GameObject;
		m_ppDwarfStageCollision[i]->SetSize(settings[i].size);
		m_ppDwarfStageCollision[i]->SetPos(settings[i].pos);
		m_ppDwarfStageCollision[i]->Init();
	}
}


//====================================================================
//
//		�I������
//
//====================================================================
void DwarfStageCollision::Uninit() {
	if (m_ppDwarfStageCollision != NULL) {
		for (int i = 0; i < m_DawarfStageNum; i++) {
			//�ʂɍ폜
			delete m_ppDwarfStageCollision[i];
		}
		//�z����폜
		delete[] m_ppDwarfStageCollision;
		m_ppDwarfStageCollision = NULL;
	}
}



//====================================================================
//
//		�`�揈��
//
//====================================================================
void DwarfStageCollision::Draw() {
	for (int i = 0; i < m_DawarfStageNum; ++i) {
		m_ppDwarfStageCollision[i]->Draw();
	}
}

//====================================================================
//
//		���l�̓����蔻��̃X�e�[�W�擾
//
//====================================================================
GameObject* DwarfStageCollision::GetDwarfStageCollision(int num) {
	if (num < m_DawarfStageNum) {
		return m_ppDwarfStageCollision[num];
	}
	return nullptr;
}

//====================================================================
//
//		�����������邩��Ԃ�
//
//====================================================================
int DwarfStageCollision::GetStageNum() {
	return m_DawarfStageNum;
}
