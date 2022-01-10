/**
 * @file Bullet.h
 * @Author	園田翔大
 * @Edit	吉原(2021/12/19)
 * @date 2021/11/29 作成
 *		 2021/12/19 赤青玉を判別する変数を追加
 *					赤青玉判別変数のゲッターセッターを追加
					フィールドと弾の当たり判定の処理を追加(吉原)
 * @brief			プレイヤーから発射される弾に関する処理
 */


 /* -----------------インクルードガード------------------ */
#ifndef __BULLET_H__
#define __BULLET_H__

 //*******************************************************************************
 // インクルード部
 //*******************************************************************************
#include "CharacterBase.h"
#include "Collision.h"

// ---モデル描画用の追加
#include	"FBX/FBXPlayer.h"
#include	"DrawBuffer.h"


 //*******************************************************************************
 // クラス定義
 //*******************************************************************************
class Bullet : public CharacterBase
{
public:

	Bullet(DirectX::XMFLOAT3 size);
	virtual ~Bullet();

	// ---4大処理関数
	bool Init();
	virtual void Uninit();
	virtual void Update();
	//virtual void Draw();

	// ---当たり判定処理
	virtual void OnCollision(GameObject*);
	void SetColFlg(bool flg);
	//void BulletCollision(bool Setflg);		// フィールドとの当たり判定

	// ---2色の弾の処理
	void SetRB(bool flg);						// 投げた弾が赤か青かセットする
	bool GetRB();

	// ---モデル描画用の追加
	ID3D11ShaderResourceView* m_pBulletTex;


private:
	// ---関数
	bool LoadBullet(const char* pFilePath);		// 　モデル読み込み

	// ---変数
	int m_sleep;
	int m_sleep2;
	float m_BulletAngle;						// 角度
	XMFLOAT3 m_dir;								// 向き

	bool m_rbFlg;								// true　→　赤			false　→　青
	bool m_ColFlg;								// true　→　接している		false → 接していない

	// ---モデル描画関連
	static DrawBuffer* m_pBuffer;				// バッファクラス
	static FBXPlayer* m_pFBX;					// FBXファイル操作くらす
};


#endif