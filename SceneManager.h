#pragma once

enum Scenes
{
	Title,
	StageSelect,
	Game,
	// リザルトはゲームシーンに組み込み
	// 全ステージクリア後はタイトルへ
};

class SceneManager
{
private:
	static	int		existChangeRequest;		// シーン変更の要求が存在するか
	static	int		isEndDraw;				// 描画処理が終了したかどうか
	static	Scenes	scene_current;			// 現在のシーン
	static	Scenes	scene_next;				// リクエストが来たら代入

	// TODO: 型を変更してください
	static	int*	title;					// タイトルシーン
	static	int*	stageSelect;			// ステージセレクトシーン
	static	int*	game;					// ゲームシーン

public:
	/// <summary>
	///	次のフレームからシーンを変更します。
	/// シーンチェンジの演出がある場合、演出が終わり次第変更します。
	/// </summary>
	/// <param name="_nextScene">次のシーン</param>
	void	ChangeRequest(Scenes _nextScene);

	// 更新処理
	void	Update();
	// 描画処理
	void	Draw();
	// ゲームループの最後に配置してください。※シーンチェンジ要求はChangeRequest関数を使用して下さい。
	void	ChangeScene();

};
