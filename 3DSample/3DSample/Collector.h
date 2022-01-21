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

private:
	bool LoadFBX(const char* pFilePath);

	//---�ϐ�
public:
	ID3D11ShaderResourceView* m_pCollectorTex;

private:
	static DrawBuffer* m_pBuffer;
	static FBXPlayer* m_pfbx;		//FBX�t�@�C������N���X

	XMFLOAT3	m_dir;

	float	m_angle;
	int		m_timer;
	int		m_nowCollectTimer;
	bool	m_timeFlg;
	bool	m_nowCollectFlg;
};

