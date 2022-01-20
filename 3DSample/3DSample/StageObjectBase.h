//****************************************************
//
//	オブジェクトベース[ObjectBase.h]
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
#include	"GameObject.h"

#include	"Texture.h"
#include	"FBX/FBXPlayer.h"
#include	"MyVector.h"

//*******************************************************************************
// クラス宣言
//*******************************************************************************
class StageObjectBase : public GameObject
{	
public:
	StageObjectBase();
	virtual ~StageObjectBase();

	//---関数
	bool Init();
	void Uninit();
	virtual void Update();
	virtual void Draw();

	//---settet
	//void SetPos(XMFLOAT3 pos);
	//void SetSize(XMFLOAT3 size);
	void SetTexPath(LPCSTR pTexPath);
	void SetModelPath(LPCSTR pModelPath);

	//---getter
	//virtual XMFLOAT3 GerPos();
	//virtual XMFLOAT3 GetSize();
	LPCSTR GetTexPath();
	LPCSTR GetModelPath();

	//---関数
	bool LoadStageObject(const char *pFilePath);			//モデル読み込み

	//---生成
	void CreateStageObject(XMFLOAT3 pos, XMFLOAT3 size, LPCSTR TexPath, LPCSTR ModelPath);

	//---変数
	ID3D11ShaderResourceView *m_pStageObjectTex;

private:

	//---変数
	DrawBuffer *m_pBuffer;
	FBXPlayer *m_pFBX;


	LPCSTR m_TexPath;
	LPCSTR m_ModelPath;

};