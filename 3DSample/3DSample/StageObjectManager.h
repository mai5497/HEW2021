//====================================================================
//
// ステージオブジェクト
// 作成者:吉原飛鳥
// 
// 更新日:20212/01/18	作成
//====================================================================
/* -----------------インクルードガード------------------ */
#pragma once

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"StageObjectBase.h"


 //*******************************************************************************
 // クラス宣言
 //*******************************************************************************
class StageObjectManager
{
public:
	StageObjectManager();
	~StageObjectManager();

	//---関数
	bool Init(int SelectStageNum);
	void Uninit();
	void Update();
	void Draw();

	//void CreateStageObject(int index, XMFLOAT3 pos, XMFLOAT3 size, LPCSTR TexPath, LPCSTR ModelPath);

private:
	StageObjectBase	**m_ppStageObject;		// ステージのオブジェクト
	int m_StageObjectNum;								// ステージのオブジェクトの最大数
	int m_SelectStageNm;								//　選択されているステージ番号
};

