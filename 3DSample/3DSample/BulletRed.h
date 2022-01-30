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
	void Update();

private:
	//---関数
	bool LoadBullet(const char* pFilePath);

	//---変数
	ANIME_INDEX m_floweAnim[MAX_ANIME];
	FBXPlayer *m_pRedModel;
	DrawBuffer *m_pRedBuffer;

};
#endif