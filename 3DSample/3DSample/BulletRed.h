//====================================================================
//
// 赤弾[BulletRed.h]
// 作成者:伊地田真衣
// 
// 更新日:2022/01/08	作成
//====================================================================

/* -----------------インクルードガード------------------ */
#ifndef __BULLETRED_H__
#define __BULLETRED_H__

//*******************************************************************************
// インクルード部
//*******************************************************************************
#include "BulletBase.h"
#include "FBX/FBXPlayer.h"

//*******************************************************************************
// クラス宣言															
//*******************************************************************************
class BulletRed : public BulletBase
{
public:
	//---関数
	BulletRed();
	virtual ~BulletRed();
	bool Init();
	virtual void Unint();
	void Draw();

	//---変数
	ID3D11ShaderResourceView* m_pBulletRedTex;

private:
	//---関数
	bool LoadBullet(const char* pFilePath);

	//---変数
	static DrawBuffer* m_pBuffer;
	static FBXPlayer* m_pFBX;		// FBXファイル操作クラス
};
#endif