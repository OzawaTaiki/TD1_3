﻿#include "PhilliaFunction/Phill.h"
#include "StageSelect.h"
#include "ResourceManager.h"
#include <Novice.h>
#include "JSON-Loader/JSON-Manager.h"
#include "KeyManager.h"

StageSelect::StageSelect()
{
    json = JSON_Manager::GetJSON(jsonName);

    LoadFromJSON();

    Calculation();

    cur					= Transform(0, 0);
    frameBuffer_jump	= 0;
    elmCnt_jump			= 0;
    constantT_jump		= 0.0f;
    easedT_jump			= 0.0f;
    targetTheta_jump	= 0.0f;
    ssElementHandle		= ResourceManager::Handle("white1x1");
    ssThumbHandle		= ResourceManager::Handle("thmb_stg0");
    isInterval			= 0;

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            frameCount_turn[row][col]		= 0;
            constantT_turn[row][col]		= 0.0f;
            easedT_turn[row][col]			= 0.0f;
            theta_jump[row][col]			= 0.0f;
            elements[row][col].pos.x		= elementStandard.x + (elementSize.width + elementMargin) * col;
            elements[row][col].pos.y		= elementStandard.y + (elementSize.height + elementMargin) * row;
            elements[row][col].size.width	= elementSize.width;
            elements[row][col].size.height	= elementSize.height;
            elements[row][col].alpha		= 0;
            elements[row][col].fcStatus		= FCS_NONE;
        }
    }
}

void StageSelect::Init()
{
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            elements[row][col].pos.x		= elementStandard.x + (elementSize.width + elementMargin) * col;
            elements[row][col].pos.y		= elementStandard.y + (elementSize.height + elementMargin) * row;
            elements[row][col].size.width	= elementSize.width;
            elements[row][col].size.height	= elementSize.height;
        }
    }
}

void StageSelect::Update()
{
    CursorManager::GetCursorPos(&cur);

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            // 押印
            if (CursorManager::Pressing(&elements[row][col].pos, &elements[row][col].size) == 1)
            {
                elements[row][col].fcStatus = FCS_PRESS;
            }
            // ホバー
            else if (CursorManager::Hover(&elements[row][col].pos, &elements[row][col].size) == 1)
            {
                elements[row][col].fcStatus = FCS_HOVER;
            }
            // unpoint
            else elements[row][col].fcStatus = FCS_NONE;
        
            // それぞれの状態時の操作
            switch (elements[row][col].fcStatus)
            {
            case FCS_HOVER:
                EasingHover(row, col); // イージング
                if (frameCount_turn[row][col] < targetFrame_turn)
                    frameCount_turn[row][col]++;
            case FCS_PRESS:
                break;
            case FCS_NONE:
                EasingHover(row, col);
                if (frameCount_turn[row][col] > 0) frameCount_turn[row][col]--;
            default:
                break;
            }
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
                theta_jump[elmCnt_jump / 5][elmCnt_jump % 5] = -0.1f * float(3.1415926535);
            }
            if (frameCount_jump == targetFrame_jump)
            {
                theta_jump[elmCnt_jump / 5][elmCnt_jump % 5] = 0.0f;
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

    // 要素
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 5; col++)
        {
            Phill::DrawQuadPlus(
                elements[row][col].pos.x, elements[row][col].pos.y,
                elements[row][col].size.width, elements[row][col].size.height,
                1.0f, 1.0f, theta_jump[row][col],
                0, 0,
                srcSize.width, srcSize.height,
                ssElementHandle,
                0xffffffff,
                DrawMode_Center
            );
            Phill::DrawQuadPlus(
                elements[row][col].pos.x, elements[row][col].pos.y,
                elements[row][col].size.width, elements[row][col].size.height,
                1.0f, 1.0f, theta_jump[row][col],
                0, 0,
                srcSize.width, srcSize.height,
                ssThumbHandle,
                0xffffff00+elements[row][col].alpha,
                DrawMode_Center
            );
        }
    }

    // !DEBUG
    Novice::ScreenPrintf(cur.x - 30, cur.y-15, "(%4d,%4d)", cur.x, cur.y);
    Novice::ScreenPrintf(15,35, "(%4d)", elmCnt_jump);
}

void StageSelect::EasingHover(int _row, int _col)
{
    constantT_turn[_row][_col]			= Phill::ConstantT(targetFrame_turn, frameCount_turn[_row][_col]);
    easedT_turn[_row][_col]				= Phill::EaseOutQuart(constantT_turn[_row][_col]);
    elements[_row][_col].size.width		= Phill::Lerp(elementSize.width, targetElmSize.width, easedT_turn[_row][_col]);
    elements[_row][_col].size.height	= Phill::Lerp(elementSize.height, targetElmSize.height, easedT_turn[_row][_col]);
    elements[_row][_col].alpha			= Phill::Lerp(0, thumbTargetAlpha, constantT_turn[_row][_col]);
}

void StageSelect::LoadFromJSON()
{
    elementSize.width		= atoi((*json)["elementWidth"].c_str());
    elementSize.height		= atoi((*json)["elementHeight"].c_str());
    targetElmSize.width		= atoi((*json)["targElementWidth"].c_str());
    targetElmSize.height	= atoi((*json)["targElementHeight"].c_str());
    srcSize.width			= atoi((*json)["srcWidth"].c_str());
    srcSize.height			= atoi((*json)["srcHeight"].c_str());
    thumbTargetAlpha		= atoi((*json)["targThmbAlpha"].c_str());

    frameOffset_jump		= atoi((*json)["frameOffset_jump"].c_str());
    IntervalFrame_jump		= atoi((*json)["intervalFrame_jump"].c_str());
    targetFrame_jump		= atoi((*json)["targetFrame_jump"].c_str());

    targetFrame_turn		= atoi((*json)["targFrame_turn"].c_str());
    elementMargin			= atoi((*json)["elementMargin"].c_str());
    bgColor					= UINT(strtoll((*json)["bgcolor"].c_str(), nullptr, 16));
}

void StageSelect::Calculation()
{

    // 基準点を算出する
    elementStandard.x = (1920 - (elementSize.width * 5 + elementMargin * 4)) / 2 + elementSize.width / 2;
    elementStandard.y = (1080 - (elementSize.height * 3 + elementMargin * 2)) / 2 + elementSize.height / 2;
}