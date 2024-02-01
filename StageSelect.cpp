#include "PhilliaFunction/Phill.h"
#include "StageSelect.h"
#include "ResourceManager.h"
#include <Novice.h>
#include "JSON-Loader/JSON-Manager.h"
#include "KeyManager.h"

StageSelect::StageSelect()
{
    json = JSON_Manager::GetJSON(jsonName);

    LoadFromJSON();

    UI_Manager::Init();

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
    ssElementHandle		    = ResourceManager::Handle("white1x1");
    isInterval			    = 0;

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
        JSON_Manager::ReloadJSON(jsonName);
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

    // !DEBUG
    Novice::ScreenPrintf(cur.x - 30, cur.y-15, "(%4d,%4d)", cur.x, cur.y);
    Novice::ScreenPrintf(15,35, "(%4d)", elmCnt_jump);

    scrollBar->Draw();
}

void StageSelect::EasingHover(int _index)
{
    constantT_turn[_index]			= Phill::ConstantT(targetFrame_turn, frameCount_turn[_index]);
    easedT_turn[_index]				= Phill::EaseOutQuart(constantT_turn[_index]);
}

void StageSelect::LoadFromJSON()
{
    elementSize.width		= atoi((*json)["elementWidth"].c_str());
    elementSize.height		= atoi((*json)["elementHeight"].c_str());
    srcSize.width			= atoi((*json)["srcWidth"].c_str());
    srcSize.height			= atoi((*json)["srcHeight"].c_str());

    frameOffset_jump		= atoi((*json)["frameOffset_jump"].c_str());
    IntervalFrame_jump		= atoi((*json)["intervalFrame_jump"].c_str());
    targetFrame_jump		= atoi((*json)["targetFrame_jump"].c_str());

    targetFrame_turn		= atoi((*json)["targFrame_turn"].c_str());
    elementMargin			= atoi((*json)["elementMargin"].c_str());
    bgColor					= UINT(strtoll((*json)["bgcolor"].c_str(), nullptr, 16));

    scrollBarSize.width     = atoi((*json)["scrollbarWidth"].c_str());
    scrollBarSize.height    = atoi((*json)["scrollbarHeight"].c_str());
    scrollboxSize.width     = atoi((*json)["scrollboxWidth"].c_str());
    scrollboxSize.height    = atoi((*json)["scrollboxHeight"].c_str());
    scrollboxMargin         = atoi((*json)["scrollboxMargin"].c_str());
    scrollbarPosition.x     = atoi((*json)["scrollbarX"].c_str());
    scrollbarPosition.y     = atoi((*json)["scrollbarY"].c_str());
    scrollMarginTop         = atoi((*json)["scrollMarginTop"].c_str());
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