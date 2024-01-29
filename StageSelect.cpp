#include "PhilliaFunction/Phill.h"
#include "StageSelect.h"
#include "ResourceManager.h"
#include <Novice.h>

StageSelect::StageSelect()
{
	Calculation();
	frameCount_turn = 0;
	constantT_turn = 0.0f;
	easedT_turn = 0.0f;
	cur = Transform(0, 0);
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			elements[row][col].pos.x = elementStandard.x + (elementSize + elementMargin) * col;
			elements[row][col].pos.y = elementStandard.y + (elementSize + elementMargin) * row;
			elements[row][col].size.width = elementSize;
			elements[row][col].size.height = elementSize;
			elements[row][col].fcStatus = FCS_NONE;
		}

	}
	ssElementHandle = ResourceManager::Handle("white1x1");
}

void StageSelect::Update()
{
	CursorManager::GetCursorPos(&cur);

	if (cur.x < 0) cur.x = 0;
	if (cur.y < 0) cur.y = 0;


}

void StageSelect::Draw()
{
	// 背景
	Novice::DrawBox(0, 0, 1920, 1080, 0.0f, 0x121212ff, kFillModeSolid);

	// サイズ確認用
	for (int row = 0; row < 3; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			//Novice::DrawBox(elements[row * 5 + col].pos.x, elements[row * 5 + col].pos.y, elements[row * 5 + col].size.width, elements[row * 5 + col].size.height, 0.0f, 0xcdcdcdff, kFillModeSolid);
			Phill::DrawQuadPlus(
				elements[row][col].pos.x, elements[row][col].pos.y,
				elements[row][col].size.width, elements[row][col].size.height,
				1.0f, 1.0f, 0.0f,
				0, 0,
				srcSize.width, srcSize.height,
				ssElementHandle,
				0xffffffff,
				DrawMode_Center
			);
		}
	}
	

	// !DEBUG
	Novice::ScreenPrintf(cur.x - 30, cur.y-12, "(%4d,%4d)", cur.x, cur.y);
}

void StageSelect::Calculation()
{
	// 基準点を算出する
	elementStandard.x = (1920 - (elementSize * 5 + elementMargin * 4)) / 2;
	elementStandard.y = (1080 - (elementSize * 3 + elementMargin * 2)) / 2;
}