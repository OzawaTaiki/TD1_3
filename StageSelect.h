#pragma once

#include "CursorManager.h"

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
	const	int		targetFrame_turn	= 40;
	const	int		elementSize			= 196;
	const	int		targetElmSize		= 256;
	const	int		elementMargin		= 96;
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