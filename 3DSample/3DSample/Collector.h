#pragma once

#include "GameObject.h"
#include "FBX/FBXPlayer.h"
#include "DrawBuffer.h"

class Collector : public GameObject
{
public:
	Collector();
	~Collector();

	bool Init();
	void Uninit();
	void Update();
	void Draw();

private:
	bool LoadFBX(const char* pFilePath);

public:
	ID3D11ShaderResourceView *m_pCollectorTex;

private:
	static DrawBuffer * m_pBuffer;
	static FBXPlayer *m_pfbx;	//FBXファイル操作クラス

	DirectX::XMFLOAT3 m_dir;
	float m_Angle;

	bool m_bTimeFlg;
	int m_Timer;
};

