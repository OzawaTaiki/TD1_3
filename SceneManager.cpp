#include "SceneManager.h"

int		SceneManager::existChangeRequest;		// シーン変更の要求が存在するか
int		SceneManager::isEndDraw;				// 描画処理が終了したかどうか
Scenes	SceneManager::scene_current;			// 現在のシーン
Scenes	SceneManager::scene_next;				// リクエストが来たら代入

int*	SceneManager::title;
int*	SceneManager::stageSelect;
int*	SceneManager::game;

void SceneManager::ChangeRequest(Scenes _nextScene)
{
	existChangeRequest = 1;
	scene_next = _nextScene;
}

void SceneManager::Update()
{
	switch (scene_current)
	{
	case Title:
		//if (title) title->Update();
		break;
	case StageSelect:
		//if (stageSelect) stageSelect->Update();
		break;
	case Game:
		//if (game) game->Update();
		break;

	default:
		break;
	}
}

void SceneManager::Draw()
{
	switch (scene_current)
	{
	case Title:
		//if (title) title->Draw();
		break;
	case StageSelect:
		//if (stageSelect) stageSelect->Draw();
		break;
	case Game:
		//if (game) game->Draw();
		break;

	default:
		break;
	}
}

void SceneManager::ChangeScene()
{
	/// シーンチェンジ要求が存在する場合...
	if (existChangeRequest)
	{
		/// 描画が終了しているなら...
		if (isEndDraw)
		{
			// シーンチェンジの演出があれば記述
			switch (scene_current)
			{
			case Title:
				delete title;
				title = nullptr;
				break;
			case StageSelect:
				delete stageSelect;
				stageSelect = nullptr;
				break;
			case Game:
				delete game;
				game = nullptr;
				break;
			default:
				break;
			}

			// インスタンスの作成
			switch (scene_next)
			{
			case Title:
				//title = new Title();
				break;
			case StageSelect:
				//stageSelect = new StageSelect();
				break;
			case Game:
				//game = new Game();
				break;
			default:
				break;
			}
		}
	}
}