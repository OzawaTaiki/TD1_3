#include "CursorManager.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "JSON-Loader/JSON-Manager.h"
#include "SceneManager.h"

#include <time.h>
#include <Novice.h>
#include "playground.h"
#include "definition.h"
#include "Tutorial.h"

const char kWindowTitle[] = "1304_framy";

void ResourceRegist();
void JSONLoad();

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Tutorial* tutorial = nullptr;

	srand(unsigned int(time(nullptr)));

	JSONLoad();
	ResourceRegist();
	SceneManager::Init();
	int wndModeCnt = 0;

	Novice::SetMouseCursorVisibility(false);
	int mGH = ResourceManager::Handle("cursor");
	int mX = 0;
	int mY = 0;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);
		KeyManager::GetKeyState();

		///
		/// ↓更新処理ここから
		///

		CursorManager::UpdateCursorStatus();
		CursorManager::GetCursorPosX(&mX);
		CursorManager::GetCursorPosY(&mY);

		SceneManager::Update();

		// TODO: シーンマネージャにまとめる
		if (keys[DIK_TAB] && !preKeys[DIK_TAB] && !tutorial)
			tutorial = new Tutorial();

		if (keys[DIK_0] && !preKeys[DIK_0])
		{
			// シーンをセレクト画面に変更
			SceneManager::ChangeRequest(Scenes::SC_StageSelect);
		}

		if (keys[DIK_F11] && !preKeys[DIK_F11])
		{
			if (wndModeCnt == 0)
				Novice::SetWindowMode(WindowMode::kFullscreen);
			else Novice::SetWindowMode(WindowMode::kWindowed);
			wndModeCnt++;
			wndModeCnt %= 2;
		}

		if (tutorial)
		{
			tutorial->Update();
			if (tutorial->Deletable() == 1)
			{
				delete tutorial;
				tutorial = nullptr;
			}
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///


		if (tutorial) tutorial->Draw();

		SceneManager::Draw();

		Novice::DrawSpriteRect(mX, mY, CursorManager::GetClickFlag() ? 64 : 0, 0, 64, 64, mGH, 0.5f, 1, 0, WHITE);

		///
		/// ↑描画処理ここまで
		///

		// ゲームループの最後に配置してください↓
		SceneManager::ChangeScene();

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}

void ResourceRegist()
{
	ResourceManager::Regist("white1x1", "white1x1.png");
	ResourceManager::Regist("rule1", "./img/rule1.png");
	ResourceManager::Regist("rule2", "./img/rule2.png");
	ResourceManager::Regist("bubble", "./img/bubble.png");
	ResourceManager::Regist("foam", "./Resources/img/foam.png");
	ResourceManager::Regist("dekaP", "./img/dekaP.png");
	ResourceManager::Regist("stgNumElement", "./resources/img/stageNumBlock.png");
	ResourceManager::Regist("stgArrow", "./Resources/img/arrow.png");

	for (int i = 0; i < 1; i++)
	{
		char path[] = "./img/thumbnails/stg";
		char result[128]{};
		char name[32]{};
		sprintf_s(result, "%s%d%s", path, i, ".png");
		sprintf_s(name, "thmb_stg%d", i);

		ResourceManager::Regist(name, result);
	}

	/// オザワ追加分
	// テクスチャ
	ResourceManager::Regist("playerTex", "./Resources/img/player-sheet.png");
	ResourceManager::Regist("soapTex", "./Resources/img/soap.png");
	ResourceManager::Regist("pieceTex", "./Resources/img/pieceBlock.png");
	ResourceManager::Regist("goalTex", "./Resources/img/goal.png");
	ResourceManager::Regist("blockTex", "./Resources/img/block.png");
	ResourceManager::Regist("togeTex", "./Resources/img/toge.png");
	ResourceManager::Regist("backGround", "./Resources/img/stageBackGround.png");
	ResourceManager::Regist("cursor", "./Resources/img/cursor.png");

	//サウンド
	ResourceManager::Regist("titleBGM", "./Resources/sound/BGM/title.mp3", false);
	ResourceManager::Regist("selectBGM", "./Resources/sound/BGM/select.mp3", false);
	ResourceManager::Regist("gameBGM", "./Resources/sound/BGM/game.mp3", false);
	ResourceManager::Regist("piecePutDownSound", "./Resources/sound/SE/put.mp3", false);
	ResourceManager::Regist("piecePickUpSound", "./Resources/sound/SE/grip.mp3", false);
	/*
	ResourceManager::Regist("playerMoveSound", "./Resources/sound/SE/.mp3",false);
	ResourceManager::Regist("playerJumpSound", "./Resources/sound/SE/.mp3",false);
	ResourceManager::Regist("pieceMoveSound", "./Resources/sound/SE/.mp3",false);
	ResourceManager::Regist("boxMoveSound", "./Resources/sound/.SE/mp3",false);
	*/
}

void JSONLoad()
{
	JSON_Manager::LoadJSON("plygro-scroll", "./data/Playground/scroll.json");
	JSON_Manager::LoadJSON("stgSel-main", "./data/StageSelect/stageSelect.json");
	JSON_Manager::LoadJSON("stgSel-scroll", "./data/StageSelect/scroll.json");
	JSON_Manager::LoadJSON("stgSel-back", "./data/StageSelect/backButton.json");
	JSON_Manager::LoadJSON("fillWithPlayer", "./data/StageSelect/fillWithPlayer.json");
}
