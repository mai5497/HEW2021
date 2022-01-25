//====================================================================
//
// 青弾[BulletBlue.h]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/09	作成
//====================================================================
/* -----------------インクルードガード------------------ */
#pragma once

//*******************************************************************************
// インクルード部
//*******************************************************************************
#include "BulletBase.h"
#include "FBX/FBXPlayer.h"

enum BULLETANIME {
	BLAST = 0,
};


//*******************************************************************************
// クラス宣言															
//*******************************************************************************
class BulletBlue : public BulletBase
{
public:
	BulletBlue();
	~BulletBlue();

	//---関数
	bool Init();
	virtual void Unint();
	void Draw();
	void AnimUpdate();

	//---変数
	ID3D11ShaderResourceView* m_pBulletBlueTex;

private:
	//---関数
	bool LoadBullet(const char* pFilePath);

	//---変数
	static DrawBuffer* m_pBuffer;
	static FBXPlayer* m_pFBX;		// FBXファイル操作クラス
	ANIME_INDEX m_floweAnim[MAX_ANIME];

};

