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
	int GetnowCollectTimer();

	bool GetNowCollectFlg();
	void SetTargetPos(XMFLOAT3 pos);


private:
	bool LoadFBX(const char* pFilePath);

	//---変数
public:
	ID3D11ShaderResourceView* m_pCollectorTex;

private:
	DrawBuffer* m_pBuffer;
	FBXPlayer* m_pfbx;		//FBXファイル操作クラス

	XMFLOAT3	m_dir;

	float	m_angle;			// 描画角度
	int		m_timer;			// 待機時間
	int		m_nowCollectTimer;	// 回収中時間
	bool	m_collectFlg;		// tureで回収に行くfalseで帰還
	bool	m_nowCollectFlg;	// 回収中かどうか
	bool	m_moveFlg;			// 移動許可フラグ
	XMFLOAT3 m_targetPos;		// 目的地座標
};

