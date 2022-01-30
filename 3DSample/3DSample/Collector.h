#pragma once

//========================= インクルード部 ===========================
#include "GameObject.h"
#include "FBX/FBXPlayer.h"
#include "DrawBuffer.h"

enum UFOCOLLOR {
	RED_UFO = 0,
	BLUE_UFO,
	REDBLUE_UFO,

	MAX_UFO
};

//========================= クラス定義 ===========================
class Collector : public GameObject
{
	//---関数
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

	//---変数
public:
	ID3D11ShaderResourceView* m_pCollectorTex[MAX_UFO];

private:
	DrawBuffer *m_pBuffer[MAX_UFO];
	FBXPlayer *m_pfbx[MAX_UFO];		//FBXファイル操作クラス

	XMFLOAT3	m_dir;

	float	m_angle;			// 描画角度
	int		m_timer;			// 待機時間
	int		m_nowCollectTimer;	// 回収中時間
	bool	m_collectFlg;		// tureで回収に行くfalseで帰還
	bool	m_nowCollectFlg;	// 回収中かどうか
	bool	m_moveFlg;			// 移動許可フラグ
	XMFLOAT3 m_targetPos;		// 目的地座標
	int m_nowColorNum;				// ゆーふぉーの今の色
	int m_nextColorNum;				// ゆーふぉーの前の色
};

