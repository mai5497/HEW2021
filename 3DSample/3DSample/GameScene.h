#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include"Texture.h"
#include "Scene.h"
#include "Bullet.h"

class GameScene :public Scene
{
public:
	GameScene(void);
	~GameScene(void);

	void Init(int StageNum);
	void Uninit();
	// 戻り値でシーンを移動するかどうか判定
	SCENE Update();
	void Draw();

private:
	int m_StageNum;			// 現在のステージ番号
	int m_NextStageNum;		// 次のステージ番号
	bool m_IsClear;			// クリアフラグ
		//ID3D11ShaderResourceView* m_pTexture[2];


		//bool m_isFadeOut;
};


#endif
