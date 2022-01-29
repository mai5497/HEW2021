#pragma once

//========================= �C���N���[�h�� ===========================
#include "GameObject.h"
#include "FBX/FBXPlayer.h"
#include "DrawBuffer.h"

//========================= �N���X��` ===========================
class Collector : public GameObject
{
	//---�֐�
public:
	Collector();
	~Collector();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

	int GetTimer();
	int GetnowCollectTimer();

	bool GetNowCollectFlg();
	void SetTargetPos(XMFLOAT3 pos);


private:
	bool LoadFBX(const char* pFilePath);

	//---�ϐ�
public:
	ID3D11ShaderResourceView* m_pCollectorTex;

private:
	DrawBuffer* m_pBuffer;
	FBXPlayer* m_pfbx;		//FBX�t�@�C������N���X

	XMFLOAT3	m_dir;

	float	m_angle;			// �`��p�x
	int		m_timer;			// �ҋ@����
	int		m_nowCollectTimer;	// ���������
	bool	m_collectFlg;		// ture�ŉ���ɍs��false�ŋA��
	bool	m_nowCollectFlg;	// ��������ǂ���
	bool	m_moveFlg;			// �ړ����t���O
	XMFLOAT3 m_targetPos;		// �ړI�n���W
};

