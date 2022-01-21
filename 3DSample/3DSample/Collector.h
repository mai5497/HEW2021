#pragma once

//========================= インクルード部 ===========================
#include "GameObject.h"
#include "FBX/FBXPlayer.h"
#include "DrawBuffer.h"

//========================= クラス定義 ===========================
class Collector : public GameObject
{
	//---関数
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

	//---変数
public:
	ID3D11ShaderResourceView* m_pCollectorTex;

private:
	static DrawBuffer* m_pBuffer;
	static FBXPlayer* m_pfbx;		//FBXファイル操作クラス

	XMFLOAT3	m_dir;

	float	m_angle;
	int		m_timer;
	int		m_nowCollectTimer;
	bool	m_timeFlg;
	bool	m_nowCollectFlg;
};

