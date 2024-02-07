#pragma once
// シーンクラス
#include "StageSelect.h"
#include "playground.h"

enum Scenes
{
    SC_Title,
    SC_StageSelect,
    SC_Game,
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
    static  int     ableSceneChange;

    // TODO: 型を変更してください
    static	int*	title;					// タイトルシーン
    static	StageSelect*	stageSelect;	// ステージセレクトシーン
    static	Playground*	game;				// ゲームシーン

    static  char*   preKeys;
    static  char*   keys;

public:
    /// <summary>
    ///	次のフレームからシーンを変更します。
    /// シーンチェンジの演出がある場合、演出が終わり次第変更します。
    /// </summary>
    /// <param name="_nextScene">次のシーン</param>
    static  void	ChangeRequest(Scenes _nextScene);

    // 初期化処理
    static  void    Init();

    // 更新処理
    static  void	Update();

    // 描画処理
    static  void	Draw();

    // ゲームループの最後に配置してください。※シーンチェンジ要求はChangeRequest関数を使用して下さい。
    static  void	ChangeScene();

};
