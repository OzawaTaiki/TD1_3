#pragma once

#include "CursorManager.h"
#include "JSON-Loader/json.h"

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

	JsonL*		json;

	Size	srcSize;
	Size	elementSize;
	Size	targetElmSize;
	int		targetFrame_turn;
	int		thumbTargetAlpha;
	int		elementMargin;

	unsigned int bgColor;

	StageSelectElement elements[3][5];

	int		ssElementHandle;
	int		ssThumbHandle;

	//int		frameCount_current;
	int		frameCount_turn[3][5];
	
	float	constantT_turn[3][5];
	float	easedT_turn[3][5];

	Transform elementStandard = { 192,92 };
	Transform cur;

	void	EasingHover(int _row, int _col);
	void    LoadFromJSON();
	void	Calculation();
	void	Init();
public:
	StageSelect();

	void	Update();
	void	Draw();

};