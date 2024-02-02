#include "SceneManager.h"

int		SceneManager::existChangeRequest;		// シーン変更の要求が存在するか
int		SceneManager::isEndDraw;				// 描画処理が終了したかどうか
Scenes	SceneManager::scene_current;			// 現在のシーン
Scenes	SceneManager::scene_next;				// リクエストが来たら代入

int* SceneManager::title;
StageSelect* SceneManager::stageSelect;
int* SceneManager::game;

void SceneManager::ChangeRequest(Scenes _nextScene)
{
	existChangeRequest = 1;
	scene_next = _nextScene;
}

void SceneManager::Init()
{
	existChangeRequest	= 0;
	isEndDraw			= 0;
	scene_current		= SC_StageSelect;
	scene_next			= scene_current;
	title				= nullptr;
	stageSelect			= nullptr;
	game				= nullptr;
}

void SceneManager::Update()
{
	switch (scene_current)
	{
	case SC_Title:
		//if (title) title->Update();
		break;
	case SC_StageSelect:
		if (stageSelect) stageSelect->Update();
		break;
	case SC_Game:
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
	case SC_Title:
		//if (title) title->Draw();
		break;
	case SC_StageSelect:
		if (stageSelect) stageSelect->Draw();
		break;
	case SC_Game:
		//if (game) game->Draw();
		break;

	default:
		break;
	}
	isEndDraw = 1;
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
			case SC_Title:
				delete title;
				title = nullptr;
				break;
			case SC_StageSelect:
				delete stageSelect;
				stageSelect = nullptr;
				break;
			case SC_Game:
				delete game;
				game = nullptr;
				break;
			default:
				break;
			}

			// インスタンスの作成
			switch (scene_next)
			{
			case SC_Title:
				//title = new Title();
				break;
			case SC_StageSelect:
				stageSelect = new StageSelect();
				break;
			case SC_Game:
				//game = new Game();
				break;
			default:
				break;
			}
		}
		existChangeRequest = 0;
	}
}