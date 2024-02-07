#pragma once

#include "CursorManager.h"
#include "JSON-Loader/json.h"
#include "UI/UI_Manager.h"
#include "BubbleEmitter.h"

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
    // 

    std::vector<std::vector<int>>* field;
    int         blockHandle;
    int         goalHandle;
    int         togeHandle;
    int         boxHandle;

    //ファイル名一括管理 すべてここに入力
    const char* stageFilePath[64] = {
        "./data/stage1.csv",
        "./data/stage2.csv",
        "./data/stage3.csv",
        "./data/stage4.csv",
        "./data/stage5.csv",
        "./data/stage6.csv",
        "./data/stage7.csv",
        "./data/stage8.csv",
        "./data/stage9.csv",
        "./data/stage10.csv"
    };

    //

    static const int kMax = 8;
    const char* jsonName[3] = { 
        "stgSel-main", 
        "stgSel-scroll", 
        "stgSel-back"
    };

    JsonL*	json_main;
    JsonL*	json_scroll;
    JsonL*	json_back;

    EmitterData ed;
    BubbleEmitter*    bubbleEmit;

    Transform   cursor;

    // ステージ選択要素(15個のやつ)
    Size	    srcSize;                        // 画像解像度 (px)
    Size	    elementSize;                    // 通常時の要素サイズ (px)
    int		    targetFrame_turn;               // 目標 ホバー時にかかるフレーム数 
    float       targetTheta_jump;               // 目標 要素ジャンプの角度
    int		    elementMargin;                  // 要素同士のマージン(px)

    // フレーム系
    int		    IntervalFrame_jump;			    // 要素のジャンプ間隔(f)
    int         targetFrame_jump;               // 目標 要素のジャンプにかかるフレーム数
    int         isInterval;                     // インターバルかどうか
    float       theta_jump[kMax];                 // ジャンプ角度
    
    // スクロール系
    SpriteData  scrSpr;                         // スクロールデータ
    Scroller*   scrollBar;                      // スクロールバー実体
    Size        scrollBarSize;                  // スクロールバーのサイズ
    Size        scrollboxSize;                  // スクロールボックスのサイズ
    int         scrollboxMargin;
    Transform   scrollbarPosition;
    int         scrollMarginTop;                // スクロール要素 上マージン

    // 戻るボタン
    SpriteData  backSpr;                        // スクロールデータ
    Transform   backPos;                        // 戻るボタン座標

    int         thumbHandle[kMax];                // テクスチャハンドル
    Transform   thumbnailPos;                   // ステージサムネの座標
    Size        thumbnailSize;                  // ステージサムネのサイズ

    int         selectElm;                      // 現在選択中の要素
    int         selectElm_pre;                  // 選択してた要素

    unsigned int bgColor;                       // 背景色 (画像に差し替え予定)

    StageSelectElement elements[kMax];
    StageSelectElement screenElements[kMax];
    StageSelectElement defaultElm[kMax];

    int         clickCnt;

    int		    ssElementHandle;

    int		    frameCount_current;             // フレームカウント 総合
    int		    frameCount_turn[kMax];            // フレームカウント ホバー時
    int         frameCount_jump;                // フレームカウント ジャンプ

    int         elmCnt_jump;                    // 現在どの要素がジャンプしているか
    int         frameBuffer_jump;               // フレームカウント一次保存用 要素ジャンプ
    int         frameOffset_jump;               // ジャンプまでのオフセット値(f)
    
    float	    constantT_turn[kMax];             // 増加量一定 媒介変数_ホバー
    float       constantT_jump;                 // 増加量一定 媒介変数_要素ジャンプ

    float	    easedT_turn[kMax];                // 増加量不定 媒介変数_ホバー
    float       easedT_jump;                    // 増加量不定 媒介変数_要素ジャンプ

    Transform   elementStandard = { 192,92 };   // 要素の基準座標
    Transform   cur;                            // カーソル座標

    int         elm2barDiff;

    int         whiteHnd;

    void	    EasingHover(int _index);
    void        LoadFromJSON();
    void	    Calculation();
    void	    Init();
    void        ScrollCalc();
    void        LoadHandle();
public:
    StageSelect();
    ~StageSelect();

    void	Update();
    void	Draw();

};