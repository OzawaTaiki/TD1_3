#include "CursorManager.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "JSON-Loader/JSON-Manager.h"
#include "SceneManager.h"

#include <Novice.h>
#include "playground.h"
#include "definition.h"
#include "Tutorial.h"

const char kWindowTitle[] = "1304_がめちｔぇ";

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

	JSONLoad();
	ResourceRegist();
	SceneManager::Init();
	int wndModeCnt = 0;
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

	for (int i = 0; i < 1; i++)
	{
		char path[] = "./img/thumbnails/stg";
		char result[128]{};
		char name[32]{};
		sprintf_s(result, "%s%d%s", path, i, ".png");
		sprintf_s(name, "thmb_stg%d", i);

		ResourceManager::Regist(name, result);
	}
}

void JSONLoad()
{
	JSON_Manager::LoadJSON("stageSelect", "./data/stageSelect.json");
}
