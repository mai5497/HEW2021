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
	TitleScene *m_pTitle;		// �^�C�g���̏����S��
	GameScene *m_pGame;			// �Q�[���V�[��
	SelectScene *m_pSelect;
	//TitleSceneMenu m_titleMenu;	// �^�C�g�����j���[
	//ScenePause m_pause;			// �|�[�Y���
	ResultScene *m_pResult;		// ���U���g���
	//Fade m_fade;				// �t�F�[�h����
	//Tutorial m_tutorial;		// �`���[�g���A��

	int m_StageNum;				// �Z���N�g�V�[���őI�����ꂽ�X�e�[�W�ԍ�
};
#endif // !__SCENE_MANEGER_H__


