#include "SceneManager.h"
#include "KeyManager.h"

#include <Novice.h>

int		SceneManager::existChangeRequest;		// シーン変更の要求が存在するか
int		SceneManager::isEndDraw;				// 描画処理が終了したかどうか
Scenes	SceneManager::scene_current;			// 現在のシーン
Scenes	SceneManager::scene_next;				// リクエストが来たら代入
char*	SceneManager::preKeys;
char*	SceneManager::keys;
int		SceneManager::ableSceneChange;

int* SceneManager::title;
StageSelect* SceneManager::stageSelect;
Playground* SceneManager::game;

TileChange* SceneManager::tileChange;

void SceneManager::ChangeRequest(Scenes _nextScene)
{
	existChangeRequest = 1;
	scene_next = _nextScene;
}

void SceneManager::Init()
{
	Scenes initialScene = SC_StageSelect;
	existChangeRequest	= 0;
	isEndDraw			= 0;
	scene_current		= initialScene;
	scene_next			= scene_current;
	title				= initialScene == SC_Title ? new int : nullptr;
	stageSelect			= initialScene == SC_StageSelect ? new StageSelect() : nullptr;
	game				= initialScene == SC_Game ? new Playground() : nullptr;
	ableSceneChange		= 0;
	tileChange			= nullptr;
	if (game) game->Init(0);
}

void SceneManager::Update()
{
	keys = KeyManager::GetKeysPtr();
	preKeys = KeyManager::GetpreKeysPtr();

	switch (scene_current)
	{
	case SC_Title:
		//if (title) title->Update();
		break;

	case SC_StageSelect:
		if (stageSelect) stageSelect->Update();
		break;

	case SC_Game:
		// DEBUG: ステージを数字キーで変更
#ifdef _DEBUG
		if (KeyManager::GetKeys(DIK_1)) game->Init(0);
		if (KeyManager::GetKeys(DIK_2)) game->Init(1);
		if (KeyManager::GetKeys(DIK_3)) game->Init(2);
		if (KeyManager::GetKeys(DIK_4)) game->Init(3);
		if (KeyManager::GetKeys(DIK_5)) game->Init(4);
		if (KeyManager::GetKeys(DIK_6)) game->Init(5);
		if (KeyManager::GetKeys(DIK_7)) game->Init(6);
		if (KeyManager::GetKeys(DIK_8)) game->Init(7);
		if (KeyManager::GetKeys(DIK_9)) game->Init(8);
#endif // _DEBUG
		if (game) game->Update(keys, preKeys);
		break;

	default:
		break;
	}

	if (existChangeRequest || tileChange)
	{
		switch (scene_next)
		{
		case SC_Game:
			if (!tileChange) tileChange = new TileChange();
			if (tileChange) {
				tileChange->Update();
				if (tileChange->GetIsTileEnd())
				{
					ableSceneChange = 1;
				}
				if (tileChange->GetIsEnd())
				{
					delete tileChange;
					tileChange = nullptr;
				}
			}
			break;
		}
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
		if (game) game->Draw();
		break;

	default:
		break;
	}

	if (tileChange) tileChange->Draw();
	isEndDraw = 1;
}

void SceneManager::ChangeScene()
{
	/// シーンチェンジ要求が存在する場合...
	if (existChangeRequest)
	{
		if (ableSceneChange)
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
					game = new Playground();
					game->Init(0);
					break;
				default:
					break;
				}
			}
			scene_current = scene_next;
			existChangeRequest = 0;
		}
	}
}