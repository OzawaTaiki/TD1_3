#pragma once

#include "CursorManager.h"
#include "JSON-Loader/json.h"
#include "UI/UI_Manager.h"

enum ForCursorStatus
{
    FCS_NONE,
    FCS_HOVER,
    FCS_PRESS
};

struct StageSelectElement
{
    Transform		pos;
    Size			size;
    int				alpha;
    ForCursorStatus fcStatus;
};

class StageSelect
{
private:
    const char* jsonName = "stageSelect";
    const char* jsonName_scr = "scroll";

    JsonL*	json;
    JsonL*	json_scr;

    SpriteData  scrSpr;                         // スクロールデータ
    Scroller*   scrollBar;                      // スクロールバー実体

    Size	srcSize;                            // 画像解像度 (px)
    Size	elementSize;                        // 通常時の要素サイズ (px)
    int		targetFrame_turn;                   // 目標 ホバー時にかかるフレーム数 
    float   targetTheta_jump;                   // 目標 要素ジャンプの角度
    int		elementMargin;                      // 要素同士のマージン(px)

    int		IntervalFrame_jump;					// 要素のジャンプ間隔(f)
    int     targetFrame_jump;                   // 目標 要素のジャンプにかかるフレーム数
    int     isInterval;                         // インターバルかどうか
    float   theta_jump[15];                     // ジャンプ角度
    
    Size    scrollBarSize;                      // スクロールバーのサイズ
    Size    scrollboxSize;                      // スクロールボックスのサイズ
    int     scrollboxMargin;
    Transform scrollbarPosition;
    int     scrollMarginTop;                    // スクロール要素 上マージン

    unsigned int bgColor;                       // 背景色 (画像に差し替え予定)

    StageSelectElement elements[15];

    int		ssElementHandle;

    int		frameCount_current;                 // フレームカウント 総合
    int		frameCount_turn[15];                // フレームカウント ホバー時
    int     frameCount_jump;                    // フレームカウント ジャンプ

    int     elmCnt_jump;                        // 現在どの要素がジャンプしているか
    int     frameBuffer_jump;                   // フレームカウント一次保存用 要素ジャンプ
    int     frameOffset_jump;                   // ジャンプまでのオフセット値(f)
    
    float	constantT_turn[15];                 // 増加量一定 媒介変数_ホバー
    float   constantT_jump;                     // 増加量一定 媒介変数_要素ジャンプ

    float	easedT_turn[15];                    // 増加量不定 媒介変数_ホバー
    float   easedT_jump;                        // 増加量不定 媒介変数_要素ジャンプ

    Transform elementStandard = { 192,92 };     // 要素の基準座標
    Transform cur;                              // カーソル座標

    void	EasingHover(int _index);
    void    LoadFromJSON();
    void	Calculation();
    void	Init();
    void    ScrollCalc();

public:
    StageSelect();
    ~StageSelect();

    void	Update();
    void	Draw();

};