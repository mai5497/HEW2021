#include "Stage.h"

Stage::Stage()
	:m_ppFields(NULL)
	,m_nFieldNum(0)
{
}
Stage::~Stage()
{
	Uninit();
}

bool Stage::Init()
{
	struct FieldSetting
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 size;
	};
	FieldSetting settings[] = {
		{ DirectX::XMFLOAT3(0,-0.5f,0),
		  DirectX::XMFLOAT3(100,1,100),},

		{ DirectX::XMFLOAT3(10,0.5f,10),
		DirectX::XMFLOAT3(10,1,10), },
	};

	//�����f�[�^����t�B�[���h�̐����v�Z
	m_nFieldNum = sizeof(settings) / sizeof(settings[0]);
	//�|�C���^���i�[����z����쐬
	m_ppFields = new Field *[m_nFieldNum];
	//���ꂼ��̔z��Ƀt�B�[���h���������m��
	for (int i = 0; i < m_nFieldNum; i++)
	{
		m_ppFields[i] = new Field(settings[i].size);
		m_ppFields[i]->SetPos(settings[i].pos);
		m_ppFields[i]->Init();
	}
	//���N���X��z��Ń������m�ۂ���ꍇ��
	//����̃R���X�g���N�^(�����̂Ȃ��R���X�g���N�^)
	//���K�v�B�ǂ����Ă������t���̃R���X�g���N�^��
	//�z��ŌĂяo�������Ƃ��́A�|�C���^���i�[����
	//�z����m�ۂ��A�z����̗v�f�Ƀ������m���
	//�s�����Ƃň����t���̃R���X�g���N�^��
	//�Ăяo������������B

	return true;

}
void Stage::Uninit()
{
	if (m_ppFields != NULL)
	{
		for (int i = 0; i < m_nFieldNum; i++)
		{
			//�ʂɍ폜
			delete m_ppFields[i];
		}
		//�z����폜
		delete[] m_ppFields;
		m_ppFields = NULL;
	}
}
void Stage::Update()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Update();
	}
}
void Stage::Draw()
{
	for (int i = 0; i < m_nFieldNum; ++i)
	{
		m_ppFields[i]->Draw();
	}
}
Field *Stage::GetField(int index)
{
	if (index < m_nFieldNum)
	{
		return m_ppFields[index];
	}
	return NULL;
}
int Stage::GetFieldNum()
{
	return m_nFieldNum;
}

