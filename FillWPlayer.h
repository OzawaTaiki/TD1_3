#pragma once
#include "JSON-Loader/JSON-Manager.h"
#include "UI/UI_ToolKit_Defines.h"

class FillWithPlayer
{
private:
	JsonL*	fcountData;
	int		targetFrame_fill;
	int		targetFrame_end;
	Transform targetPosition_fill;
	Transform targetPosition_end;

	int		frameCount;
	int		frameBuffer_end;

	void	LoadFromJSON();

public:
	FillWithPlayer();
	~FillWithPlayer();

	void	Update();
	void	Draw();

	int		isChangeTiming;

};
