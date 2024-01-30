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
	Transform pos;
	Size size;
	ForCursorStatus fcStatus;
};

class StageSelect
{
private:
	JsonL*	json;
	const	int		targetFrame_turn	= 40;

	int		elementSize;
	int		targetElmSize;
	int		elementMargin;
	const	Size	srcSize				= Size(1, 1);

	StageSelectElement elements[3][5];

	int		ssElementHandle;

	//int		frameCount_current;
	int		frameCount_turn;
	
	float	constantT_turn;
	float	easedT_turn;

	Transform elementStandard = { 192,92 };
	Transform cur;


	void	Calculation();
public:
	StageSelect();

	void	Update();
	void	Draw();

};