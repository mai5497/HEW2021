//====================================================================
//
// 弾の落下地点[BulletTarget.h]
// 作成者:吉原飛鳥
// 
// 更新日:2022/01/15	作成
//====================================================================

/* -----------------インクルードガード------------------ */
#pragma once

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include	"GameObject.h"
#include	"MyVector.h"
#include	"TPScamera.h"


//---モデル描画用
#include	"Texture.h"
#include	"FBX/FBXPlayer.h"
#include	"DrawBuffer.h"

 //*******************************************************************************
 // クラス宣言
 //*******************************************************************************
class BulletTarget : public GameObject
{
public:
	BulletTarget();
	~BulletTarget();

	//---関数
	bool Init();
	void Uninit();
	virtual void Update();
	void Draw();

	void SetBulletTargetPos(XMFLOAT3 pos);	// ターゲット座標の設定
	XMFLOAT3 GetBulletTargetPos();			// ターゲット座標の取得

	//---てくすちゃ読み込み
	ID3D11ShaderResourceView	*m_pBulletTargetTex;

private:

	//---モデル読み込み
	static DrawBuffer* m_pBTBuffer;		// バッファ情報操作
	static FBXPlayer* m_pBTFBX;			// FBXファイル操作クラス

	Camera *m_pCamera;					// カメラ情報
	float m_DrawAngle;						// 描画角度
	float m_MoveSpeed;								// 移動速度
};



