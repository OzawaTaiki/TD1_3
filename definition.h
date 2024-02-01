#pragma once

enum BlockKinds
{
	AIR = 0,	//空気
	BLOCK,		//壁
	GOAL,		//ゴール
	HINDRANCE,	//お邪魔
	BOX,		//箱
	SPINE,		//棘

	kBlockKindsNum //カウント用
};


const int kTileSize = 64;
const int kStageAreaWidth = 1344;
const int kStageAreaHeight = 1024;
const int kWindowWidth = 1920;
const int kWindowHeight = 1080;
const int kTileKinds = kBlockKindsNum;

