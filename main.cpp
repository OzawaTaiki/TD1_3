#include "CursorManager.h"
#include "ResourceManager.h"
#include "KeyManager.h"
#include "StageSelect.h"
#include "JSON-Loader/JSON-Manager.h"

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

	Playground* pg = new Playground;
	Tutorial* tutorial = nullptr;

	pg->Init(1);
	StageSelect* stageSel = nullptr;

	JSONLoad();
	ResourceRegist();
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
		pg->Update(keys, preKeys);

		if (keys[DIK_TAB] && !preKeys[DIK_TAB] && !tutorial)
			tutorial = new Tutorial();

		if (keys[DIK_0] && !preKeys[DIK_0] && !stageSel)
		{
			stageSel = new StageSelect();
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

#ifdef _DEBUG
		if (keys[DIK_1]) pg->Init(0);
		if (keys[DIK_2]) pg->Init(1);
		if (keys[DIK_3]) pg->Init(2);
		if (keys[DIK_4]) pg->Init(3);
		if (keys[DIK_5]) pg->Init(4);
		if (keys[DIK_6]) pg->Init(5);
		if (keys[DIK_7]) pg->Init(6);
		if (keys[DIK_8]) pg->Init(7);
		if (keys[DIK_9]) pg->Init(8);
#endif // _DEBUG
		if (stageSel)
		{
			stageSel->Update();
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		pg->Draw();

		if (tutorial) tutorial->Draw();
		if (stageSel) stageSel->Draw();


		///
		/// ↑描画処理ここまで
		///

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
}

void JSONLoad()
{
	JSON_Manager::LoadJSON("stageSelect", "./data/stageSelect.json");
}
