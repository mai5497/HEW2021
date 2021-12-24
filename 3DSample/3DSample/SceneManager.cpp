#include "SceneManager.h"
#include "Scene.h"


// 他の関数は各シーンごとの処理を行えないので
// シーン管理クラス自体の初期化が行えない

SceneManager::SceneManager(void) :m_scene(SCENE_TITLE), m_nextScene(SCENE_TITLE)
{

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
		// タイトルメニューの初期化
		m_title.Init();
		break;
	case SCENE_GAME:
		//--- ゲーム内のオブジェクトの初期化 ---
		m_game.Init();
		break;

	case SCENE_RESULT:
		m_result.Init();
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
		m_title.Uninit();
		break;
	case SCENE_GAME:
		m_game.Uninit();
		break;
	case SCENE_RESULT:
		m_result.Uninit();
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
	// 実際のゲーム処理
	switch (m_scene)
	{
	case SCENE_TITLE:
		m_nextScene = m_title.Update();
		break;
	case SCENE_GAME:
		m_nextScene = m_game.Update();
		break;
	case SCENE_RESULT:
		m_nextScene = m_result.Update();
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
		m_title.Draw();
		break;
	case SCENE_GAME:
		m_game.Draw();
		break;
	case SCENE_RESULT:
		m_result.Draw();
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