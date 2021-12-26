#ifndef __BULLET_H__
#define __BULLET_H__


#include "CharacterBase.h"
#include "Collision.h"

// ---モデル描画用の追加
#include	"FBX/FBXPlayer.h"
#include	"DrawBuffer.h"


class Bullet : public CharacterBase
{
public:
	
	// ---4大処理関数
	Bullet(DirectX::XMFLOAT3 size);
	virtual ~Bullet();
	bool Init();
	virtual void Uninit();
	virtual void Update();
	//virtual void Draw();
	void Draw();

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