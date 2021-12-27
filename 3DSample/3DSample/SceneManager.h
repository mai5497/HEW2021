#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <windows.h>
#include "TitleScene.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "SelectScene.h"

// �V�[������������N���X
class SceneManager
{
public:
	SceneManager(void);
	~SceneManager(void);

	HRESULT Init();
	void Uninit();
	bool Update();
	void Draw();

private:
	SCENE m_scene;			// ���݂̃V�[��
	SCENE m_nextScene;		// ���̃V�[��(�\��)
	TitleScene m_title;		// �^�C�g���̏����S��
	GameScene m_game;			// �Q�[���V�[��
	SelectScene m_select;
	//TitleSceneMenu m_titleMenu;	// �^�C�g�����j���[
	//ScenePause m_pause;			// �|�[�Y���
	ResultScene m_result;		// ���U���g���
	//Fade m_fade;				// �t�F�[�h����
	//Tutorial m_tutorial;		// �`���[�g���A��
};
#endif // !__SCENE_MANEGER_H__


