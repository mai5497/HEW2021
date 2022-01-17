#ifndef SCENE_MANAGER_H
#define SCENE_MANAGER_H

#include <windows.h>
#include "TitleScene.h"
#include "ResultScene.h"
#include "GameScene.h"
#include "SelectScene.h"

// シーンを完了するクラス
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
	SCENE m_scene;			// 現在のシーン
	SCENE m_nextScene;		// 次のシーン(予約)
	TitleScene *m_pTitle;		// タイトルの処理全般
	GameScene *m_pGame;			// ゲームシーン
	SelectScene *m_pSelect;
	//TitleSceneMenu m_titleMenu;	// タイトルメニュー
	//ScenePause m_pause;			// ポーズ画面
	ResultScene *m_pResult;		// リザルト画面
	//Fade m_fade;				// フェード処理
	//Tutorial m_tutorial;		// チュートリアル

	int m_StageNum;				// セレクトシーンで選択されたステージ番号
};
#endif // !__SCENE_MANEGER_H__


