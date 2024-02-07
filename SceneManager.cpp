#include "SceneManager.h"
#include "KeyManager.h"

#include <Novice.h>

int		SceneManager::existChangeRequest;		// シーン変更の要求が存在するか
int		SceneManager::isEndDraw;				// 描画処理が終了したかどうか
Scenes	SceneManager::scene_current;			// 現在のシーン
Scenes	SceneManager::scene_next;				// リクエストが来たら代入
char* SceneManager::preKeys;
char* SceneManager::keys;
int		SceneManager::ableSceneChange;
int		SceneManager::stageNum;

Title* SceneManager::title;
StageSelect* SceneManager::stageSelect;
Playground* SceneManager::game;
BackGround* SceneManager::backGround;

TileChange* SceneManager::tileChange;

Sound* SceneManager::titleBGM;
Sound* SceneManager::selectBGM;
Sound* SceneManager::gameBGM;

void SceneManager::ChangeRequest(Scenes _nextScene)
{
	existChangeRequest = 1;
	scene_next = _nextScene;
}

void SceneManager::ChangeRequest(Scenes _nextScene, int _stage)
{
	existChangeRequest = 1;
	scene_next = _nextScene;
	stageNum = _stage;
}

void SceneManager::Init()
{

	Scenes initialScene = SC_Title;
	existChangeRequest = 0;
	isEndDraw = 0;
	scene_current = initialScene;
	scene_next = scene_current;
	title = initialScene == SC_Title ? new Title : nullptr;
	stageSelect = initialScene == SC_StageSelect ? new StageSelect() : nullptr;
	game = initialScene == SC_Game ? new Playground() : nullptr;
  
	backGround = initialScene == SC_Title ? new BackGround(0xcadde9f0, kWindowWidth, kWindowHeight) :
		(initialScene == SC_Game ? new BackGround(0xcadde9f0) : nullptr);
	ableSceneChange = 0;
	tileChange = nullptr;
	stageNum = 0;
	if (game) game->Init(0);

	titleBGM = new Sound(ResourceManager::Handle("titleBGM"), 0.5f, true);
	selectBGM = new Sound(ResourceManager::Handle("selectBGM"), 0.5f, true);
	gameBGM = new Sound(ResourceManager::Handle("gameBGM"), 0.5f, true);
	switch (initialScene)
	{
	case SC_Title:
		if (titleBGM) titleBGM->SoundEnable();
		break;
	case SC_StageSelect:
		if (selectBGM) selectBGM->SoundEnable();
		break;
	case SC_Game:
		if (gameBGM) gameBGM->SoundEnable();
		break;
	}
}

void SceneManager::Update()
{
	keys = KeyManager::GetKeysPtr();
	preKeys = KeyManager::GetpreKeysPtr();

	switch (scene_current)
	{
	case SC_Title:
		if (title) title->Update();
		if (backGround)backGround->Update();
		break;

	case SC_StageSelect:
		if (backGround)backGround->Update();
		if (stageSelect) stageSelect->Update();
		break;

	case SC_Game:
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
		if (backGround)backGround->Update();
		if (game) game->Update(keys, preKeys);
		break;

	default:
		break;
	}

	/// シーン遷移演出
	if (existChangeRequest || tileChange)
	{
		switch (scene_next)
		{
		case SC_StageSelect:
			ableSceneChange = 1;
			break;

		case SC_Game:
			if (!tileChange)
			{
				tileChange = new TileChange();
				ableSceneChange = 0;
			}
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
		if (backGround)backGround->Draw();
		if (title) title->Draw();
		if (titleBGM)titleBGM->PlayAudio(true, 120);
		break;
	case SC_StageSelect:
		if (backGround)backGround->Draw();
		if (stageSelect) stageSelect->Draw();
		if (selectBGM)selectBGM->PlayAudio(true, 120);
		break;
	case SC_Game:
		if (backGround)backGround->Draw();
		if (game) game->Draw();
		if (gameBGM)gameBGM->PlayAudio(true, 120);
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
					delete backGround;
					backGround = nullptr;
					if (titleBGM) titleBGM->StopAudio(true, 120);
					break;
				case SC_StageSelect:
					delete stageSelect;
					stageSelect = nullptr;
					delete backGround;
					backGround = nullptr;
					if (selectBGM) selectBGM->StopAudio(true, 120);
					break;
				case SC_Game:
					delete game;
					game = nullptr;
					delete backGround;
					backGround = nullptr;
					if (gameBGM) gameBGM->StopAudio(true, 120);
					break;
				default:
					break;
				}

				// インスタンスの作成
				switch (scene_next)
				{
				case SC_Title:
					title = new Title();
					backGround = new BackGround(0xcadde9f0, kWindowWidth, kWindowHeight);
					if (titleBGM) titleBGM->SoundEnable();
					break;
				case SC_StageSelect:
					backGround = new BackGround(0xcadde9f0, kWindowWidth, kWindowHeight);
					stageSelect = new StageSelect();
					if (selectBGM) selectBGM->SoundEnable();
					break;
				case SC_Game:
					backGround = new BackGround(0xcadde9f0);
					game = new Playground();
					game->Init(stageNum);
					if (gameBGM) gameBGM->SoundEnable();
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