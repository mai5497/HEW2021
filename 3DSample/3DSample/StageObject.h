//****************************************************
//
//	ステージオブジェクト[StageObject.h]
//	作成者：吉原飛鳥
//	
//	2022/01/18 :作成 
//
//****************************************************

/* -----------------インクルードガード------------------ */
#pragma once

//*******************************************************************************
// インクルード部
//*******************************************************************************
#include	"StageObjectBase.h"

#include	"FBX/FBXPlayer.h"
#include	"Texture.h"

//*******************************************************************************
// クラス宣言
//*******************************************************************************
class StageObject : public StageObjectBase
{
public:
	StageObject();
	~StageObject();

	//---関数
	bool Init();
	void Uninit();
	void Draw();

	//---変数
	//ID3D11ShaderResourceView	*m_pObjectStageTex;

private:

	//---関数
	//bool LoadStageObject(const char *pFilePath);

	//---変数
	//static DrawBuffer* m_pBuffer;
	//static FBXPlayer* m_pFBX;				// FBXファイル操作クラス
};

