#ifndef _TITLE_SCENE_H_
#define _TITLE_SCENE_H_

#include "Scene.h"
#include	"FBX//FBXPlayer.h"
#include	"DrawBuffer.h"

class TitleScene :public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Init();
	void Uninit();
	SCENE Update();
	void Draw();

private:
	DrawBuffer *m_pTitleBuffer;			// �o�b�t�@��񑀍�
	FBXPlayer *m_pTitleFBX;				// FBX�t�@�C������N���X
	//ID3D11ShaderResourceView *m_pTitleModelTex;
	int m_SelectState;


	bool LoadTitleModel(const char *pFilePath);

};


#endif // _TITLE_SCENE_H_
