#pragma once

//========================= �C���N���[�h�� ===========================
#include "GameObject.h"
#include "FBX/FBXPlayer.h"
#include "DrawBuffer.h"

enum UFOCOLLOR {
	RED_UFO = 0,
	BLUE_UFO,
	REDBLUE_UFO,

	MAX_UFO
};

//========================= �N���X��` ===========================
class Collector : public GameObject
{
	//---�֐�
public:
	Collector();
	~Collector();

	bool Init(int stagenum);
	void Uninit();
	void Update();
	void Draw();

	int GetTimer();
	int GetnowCollectTimer();
	bool GetNowCollectFlg();
	void SetTargetPos(XMFLOAT3 pos);
	void SetUFOColor(int color);

private:
	bool LoadFBX(const char* pFilePath,int index);

	//---�ϐ�
public:
	ID3D11ShaderResourceView* m_pCollectorTex[MAX_UFO];

private:
	DrawBuffer *m_pBuffer[MAX_UFO];
	FBXPlayer *m_pfbx[MAX_UFO];		//FBX�t�@�C������N���X

	XMFLOAT3	m_dir;

	float	m_angle;			// �`��p�x
	int		m_timer;			// �ҋ@����
	int		m_nowCollectTimer;	// ���������
	bool	m_collectFlg;		// ture�ŉ���ɍs��false�ŋA��
	bool	m_nowCollectFlg;	// ��������ǂ���
	bool	m_moveFlg;			// �ړ����t���O
	XMFLOAT3 m_targetPos;		// �ړI�n���W
	int m_nowColorNum;				// ��[�ӂ��[�̍��̐F
	int m_nextColorNum;				// ��[�ӂ��[�̑O�̐F
};

