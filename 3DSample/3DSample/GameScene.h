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

	void Init();
	void Uninit();
	// �߂�l�ŃV�[�����ړ����邩�ǂ�������
	SCENE Update();
	void Draw();

	//private:
		//ID3D11ShaderResourceView* m_pTexture[2];


		//bool m_isFadeOut;
};


#endif
