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
	void Update();


private:

	//---変数
	ANIME_INDEX m_floweAnim[MAX_BULLET_ANIME];
	FBXPlayer *m_pBlueModel;
	DrawBuffer *m_pBlueBuffer;

};

