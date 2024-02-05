#include "PhilliaFunction/Phill.h"
#include "StageSelect.h"
#include "ResourceManager.h"
#include <Novice.h>
#include "JSON-Loader/JSON-Manager.h"
#include "KeyManager.h"
#include "UI/UI_ToolKit.h"

StageSelect::StageSelect()
{
    LoadFromJSON();

    UI_Manager::Init();

    ed.position.x = 100;
    ed.position.y = 100;
    ed.size.width = 300;
    ed.size.height = 300;
    bubbleEmit = new BubbleEmitter(&ed);

    scrSpr.srcPos           = Transform(0, 0);
    scrSpr.srcSize          = Size(1, 1);
    scrSpr.trgSize          = Size(14,54);
    scrSpr.textureHandle    = ResourceManager::Handle("white1x1");

    scrollBar               = new Scroller(&scrSpr);
    
    cur					    = Transform(0, 0);
    frameBuffer_jump	    = 0;
    elmCnt_jump			    = 0;
    constantT_jump		    = 0.0f;
    easedT_jump			    = 0.0f;
    targetTheta_jump	    = 0.0f;
    isInterval			    = 0;

    ssElementHandle		    = ResourceManager::Handle("white1x1");

    Calculation();

    for (int index = 0; index < 15; index++)
    {
        frameCount_turn[index]		= 0;
        constantT_turn[index]		= 0.0f;
        easedT_turn[index]			= 0.0f;
        theta_jump[index]			= 0.0f;
        elements[index].pos.x       = elementStandard.x + elementSize.width / 2;
        elements[index].pos.y       = elementStandard.y + (elementSize.height + elementMargin) * index;
        elements[index].size.width	= elementSize.width;
        elements[index].size.height	= elementSize.height;
        elements[index].alpha		= 0;
        elements[index].fcStatus	= FCS_NONE;
    }
}

void StageSelect::ScrollCalc()
{
    float   scrT = scrollBar->GetValue();
    int     lerpValue = 1080 - (elementSize.height + elementMargin) * 15 - scrollMarginTop*2;
    for (int index = 0; index < 15; index++)
    {
        elements[index].pos.x = elementStandard.x + elementSize.width / 2;
        elements[index].pos.y = elementStandard.y + (elementSize.height + elementMargin) * index + int(lerpValue * scrT);
        elements[index].size.width = elementSize.width;
        elements[index].size.height = elementSize.height;
    }
}

StageSelect::~StageSelect()
{
    delete scrollBar;
    scrollBar = nullptr;
}

void StageSelect::Init()
{
    // 初期位置の算出
    for (int index = 0; index < 15; index++)
    {
        elements[index].pos.x       = elementStandard.x + elementSize.width / 2;
        elements[index].pos.y		= elementStandard.y + (elementSize.height + elementMargin) * index;
        elements[index].size.width	= elementSize.width;
        elements[index].size.height	= elementSize.height;
    }
}

void StageSelect::Update()
{
    // DEBUG 終わったら消す
    bubbleEmit->Update();

    CursorManager::GetCursorPos(&cur);
    scrollBar->UpdateStatus();
    ScrollCalc();
    for (int index = 0; index < 15; index++)
    {
        // 押印
        if (CursorManager::Pressing(&elements[index].pos, &elements[index].size) == 1)
        {
            elements[index].fcStatus = FCS_PRESS;
        }
        // ホバー
        else if (CursorManager::Hover(&elements[index].pos, &elements[index].size) == 1)
        {
            elements[index].fcStatus = FCS_HOVER;
        }
        // unpoint
        else elements[index].fcStatus = FCS_NONE;
        
        // それぞれの状態時の操作
        switch (elements[index].fcStatus)
        {
        case FCS_HOVER:
            EasingHover(index); // イージング
            if (frameCount_turn[index] < targetFrame_turn)
                frameCount_turn[index]++;
        case FCS_PRESS:
            break;
        case FCS_NONE:
            EasingHover(index);
            if (frameCount_turn[index] > 0) frameCount_turn[index]--;
        default:
            break;
        }
    }

    // 要素ジャンプ
    if (frameCount_current > frameOffset_jump)
    {
        // フレームカウントの一時保存
        if (frameBuffer_jump == 0) frameBuffer_jump = frameCount_current;
        frameCount_jump = frameCount_current - frameBuffer_jump;

        if (isInterval == 0)
        {
            if (frameCount_jump == targetFrame_jump / 2)
            {
                theta_jump[elmCnt_jump] = -0.1f * float(3.1415926535);
            }
            if (frameCount_jump == targetFrame_jump)
            {
                theta_jump[elmCnt_jump] = 0.0f;
            }
        }

        if (frameCount_jump == targetFrame_jump && isInterval == 0)
        {
            isInterval = 1;
            frameBuffer_jump = 0;
        }
        if (frameCount_jump == IntervalFrame_jump && isInterval == 1)
        {
            elmCnt_jump++;
            elmCnt_jump %= 15;
            frameBuffer_jump = 0;
            isInterval = 0;
        }
    }
    frameCount_current++;

    if (cur.x < 0) cur.x = 0;
    if (cur.y < 0) cur.y = 0;

    // ホットリロード
    if (KeyManager::GetKeys(DIK_F5) && !KeyManager::GetPreKeys(DIK_F5))
    {
        JSON_Manager::ReloadJSON(jsonName[0]);
        JSON_Manager::ReloadJSON(jsonName[1]);
        JSON_Manager::ReloadJSON(jsonName[2]);
        LoadFromJSON();
        Calculation();
        Init();
    }
}

void StageSelect::Draw()
{
    // 背景
    Novice::DrawBox(0, 0, 1920, 1080, 0.0f, bgColor, kFillModeSolid);

    // スクロールバー
    //Novice::DrawBox(1920 - );

    // 要素
    for (int index = 0; index < 15; index++)
    {
        Phill::DrawQuadPlus(
            elements[index].pos.x, elements[index].pos.y,
            elements[index].size.width, elements[index].size.height,
            1.0f, 1.0f, theta_jump[index],
            0, 0,
            srcSize.width, srcSize.height,
            ssElementHandle,
            0xffffffff,
            DrawMode_Center
        );
    }

    // 戻るボタン
    GUI_Toolkit::Button("stgSel-back", backPos.x, backPos.y, &backSpr);

    // !DEBUG
    Novice::ScreenPrintf(cur.x - 30, cur.y-15, "(%4d,%4d)", cur.x, cur.y);
    Novice::ScreenPrintf(15,35, "(%4d)", elmCnt_jump);

    scrollBar->Draw();

    // DEBUG 終わったら消す
    bubbleEmit->Draw();
}

void StageSelect::EasingHover(int _index)
{
    constantT_turn[_index]			= Phill::ConstantT(targetFrame_turn, frameCount_turn[_index]);
    easedT_turn[_index]				= Phill::EaseOutQuart(constantT_turn[_index]);
}

void StageSelect::LoadFromJSON()
{
    // データを取得
    json_main = JSON_Manager::GetJSON(jsonName[0]);
    json_scroll = JSON_Manager::GetJSON(jsonName[1]);
    json_back = JSON_Manager::GetJSON(jsonName[2]);

    elementSize.width		= atoi((*json_main)["elementWidth"]);
    elementSize.height		= atoi((*json_main)["elementHeight"]);
    srcSize.width			= atoi((*json_main)["srcWidth"]);
    srcSize.height			= atoi((*json_main)["srcHeight"]);
    
    frameOffset_jump		= atoi((*json_main)["frameOffset_jump"]);
    IntervalFrame_jump		= atoi((*json_main)["intervalFrame_jump"]);
    targetFrame_jump		= atoi((*json_main)["targetFrame_jump"]);

    targetFrame_turn		= atoi((*json_main)["targFrame_turn"]);
    elementMargin			= atoi((*json_main)["elementMargin"]);
    bgColor					= UINT(strtoll((*json_main)["bgcolor"], nullptr, 16));

    scrollBarSize.width     = atoi((*json_scroll)["scrollbarWidth"]);
    scrollBarSize.height    = atoi((*json_scroll)["scrollbarHeight"]);
    scrollboxSize.width     = atoi((*json_scroll)["scrollboxWidth"]);
    scrollboxSize.height    = atoi((*json_scroll)["scrollboxHeight"]);
    scrollboxMargin         = atoi((*json_scroll)["scrollboxMargin"]);
    scrollbarPosition.x     = atoi((*json_scroll)["scrollbarX"]);
    scrollbarPosition.y     = atoi((*json_scroll)["scrollbarY"]);
    scrollMarginTop         = atoi((*json_scroll)["scrollMarginTop"]);

    backSpr.srcPos.x        = atoi((*json_back)["srcX"]);
    backSpr.srcPos.y        = atoi((*json_back)["srcY"]);
    backSpr.srcSize.width   = atoi((*json_back)["srcWidth"]);
    backSpr.srcSize.height  = atoi((*json_back)["srcHeight"]);
    backSpr.trgSize.width   = atoi((*json_back)["width"]);
    backSpr.trgSize.height  = atoi((*json_back)["height"]);
    backSpr.textureHandle   = ResourceManager::Handle("white1x1");
    backSpr.drawMode        = DrawMode_Center;

    backPos.x               = atoi((*json_back)["x"]);
    backPos.y               = atoi((*json_back)["y"]);
}

void StageSelect::Calculation()
{
    // 基準点を算出する
    elementStandard.x = scrollbarPosition.x - elementSize.width - scrollBarSize.width / 2;
    elementStandard.y = elementSize.height / 2 + scrollMarginTop;

    // スクロールバー初期化
    scrollBar->SetBarSize(Size(scrollBarSize.width, scrollBarSize.height - scrollboxSize.height - scrollboxMargin)); // 54はスクロールボックスの縦幅 80は縦マージンx2
    scrollBar->SetBoxSize(scrollboxSize);
    scrollBar->SetPosition(Transform(scrollbarPosition.x, scrollbarPosition.y + scrollboxSize.height / 2 + scrollboxMargin / 2)); // 27はずらすため 40は縦マージン
}