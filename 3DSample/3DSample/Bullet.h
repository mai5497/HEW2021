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
	
	// ---関数
	Bullet(DirectX::XMFLOAT3 size);
	virtual ~Bullet();
	bool Init();
	void Uninit();

	virtual void OnCollision(GameObject*);
	virtual void Update();
	void SetRB(bool flg);								// 投げた弾が赤か青かセットする
	bool GetRB(); 
	void SetColFlg(bool flg);
	void BulletCollision(bool Setflg);				// フィールドとの当たり判定

	// ---変数
	// ---モデル描画用の追加
	ID3D11ShaderResourceView* m_pBulletTex;

private:
	// ---関数
	bool LoadBullet(const char* pFilePath);		// 　モデル読み込み

	// ---変数
	int m_sleep;
	int m_sleep2;
	bool m_rbFlg;	// true　→　赤			false　→　青
	bool m_ColFlg;	// true　→　接している		false → 接していない

	static DrawBuffer* m_pBuffer;					// バッファクラス
	static FBXPlayer* m_pFBX;						// FBXファイル操作くらす
};


#endif