#include "SceneManager.h"
#include "Scene.h"


// ���̊֐��͊e�V�[�����Ƃ̏������s���Ȃ��̂�
// �V�[���Ǘ��N���X���̂̏��������s���Ȃ�

SceneManager::SceneManager(void)
{
	m_scene = SCENE_TITLE;
	m_nextScene = SCENE_TITLE;
#ifdef _DEBUG
	m_scene = SCENE_GAME;
	m_nextScene = SCENE_GAME;

#endif
}

SceneManager::~SceneManager(void)
{

}

HRESULT SceneManager::Init()
{
	HRESULT hr = E_FAIL;
	switch (m_scene)
	{
	case SCENE_TITLE:
		// �^�C�g�����j���[�̏�����
		m_pTitle = new TitleScene;
		m_pTitle->Init();
		break;
	case SCENE_SELECT:
		m_pSelect = new SelectScene;
		m_pSelect->Init();
		break;
	case SCENE_GAME:
		//--- �Q�[�����̃I�u�W�F�N�g�̏����� ---
		m_pGame = new GameScene;
		m_pGame->Init(m_StageNum);
		break;

	case SCENE_RESULT:
		m_pResult = new ResultScene;
		m_pResult->Init();
		break;
	/*case SCENE_LOSE_RESULT1:
		m_loseresult1.Init();
		break;
	case SCENE_LOSE_RESULT2:
		m_loseresult2.Init();
		break;*/
	}
	return hr;
}
void SceneManager::Uninit()
{
	switch (m_scene)
	{
	case SCENE_TITLE:
		m_pTitle->Uninit();
		break;
	case SCENE_SELECT:
		m_StageNum = m_pSelect->GetStageNum();
		m_pSelect->Uninit();
		break;
	case SCENE_GAME: 
		m_pGame->Uninit();
		break;
	case SCENE_RESULT:
		m_pResult->Uninit();
		break;
	/*case SCENE_LOSE_RESULT1:
		m_loseresult1.Uninit();
		break;
	case SCENE_LOSE_RESULT2:
		m_loseresult2.Uninit();
		break;*/
	}
}
bool SceneManager::Update()
{
	if (m_scene != m_nextScene)
	{
		SceneManager::Uninit();

		m_scene = m_nextScene;

		SceneManager::Init();

	}
	// ���ۂ̃Q�[������
	switch (m_scene)
	{
	case SCENE_TITLE:
		m_nextScene = m_pTitle->Update();
		break;
	case SCENE_SELECT:
		m_nextScene = m_pSelect->Update();
		break;
	case SCENE_GAME:
		m_nextScene = m_pGame->Update();
		break;
	case SCENE_RESULT:
		m_nextScene = m_pResult->Update();
		break;
	/*case SCENE_LOSE_RESULT1:
		m_nextScene = m_loseresult1.Update();
		break;
	case SCENE_LOSE_RESULT2:
		m_nextScene = m_loseresult2.Update();
		break;*/
	default:
		break;
	}
	return false;
}
void SceneManager::Draw()
{
	switch (m_scene)
	{
	case SCENE_TITLE:
		m_pTitle->Draw();
		break;
	case SCENE_SELECT:
		m_pSelect->Draw();
		break;
	case SCENE_GAME:
		m_pGame->Draw();
		break;
	case SCENE_RESULT:
		m_pResult->Draw();
		break;
	/*case SCENE_LOSE_RESULT1:
		m_loseresult1.Draw();
		break;
	case SCENE_LOSE_RESULT2:
		m_loseresult2.Draw();
		break;*/
	}

	// 
	//m_fade.Draw();
}