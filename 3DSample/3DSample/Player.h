#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "CharacterBase.h"
#include "Camera.h"
#include "TPSCamera.h"
#include "DwarfManager.h"
#include "Collision.h"
#include "Stage.h"

// モデル描画用
#include	"Texture.h"
#include	"FBX//FBXPlayer.h"
#include	"DrawBuffer.h"

class DwarfManager;

class Player : public CharacterBase
{
public:
	// ---コンストラクタ/デストラクタ
	Player();
	virtual ~Player();

	// ---4大処理
	bool Init();
	void Uninit();
	virtual void Update();
	void Draw();

	// ---エネミー追跡処理
	virtual void PlayerToEnemy(GameObject*);

	// ---カメラ関連
	void SetControllCamera(Camera *pCamera);
	void GetCameraPos(TPSCamera*);

	// ---プレイヤー関連
	ID3D11ShaderResourceView *m_pPlayerTex;			
	XMFLOAT3 GetPlayerPos();
	XMFLOAT3 GetPlayerAngle();


private:
	bool LoadPlayer(const char *pFilePath);


	Camera * m_pControllCamera;				// カメラ座標操作

	static DrawBuffer *m_pBuffer;			// バッファ情報操作
	static FBXPlayer *m_pFBX;				// FBXファイル操作クラス

	float m_DrawAngle;						// 描画角度
};

#endif // !_PLAYER_H_
