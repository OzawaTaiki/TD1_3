﻿#pragma once
#include "JSON-Loader/JSON-Manager.h"
#include "UI/UI_ToolKit_Defines.h"
#include <vector>

class FillWithPlayer
{
private:
	JsonL*	fcountData;
	std::vector<Transform> bufferPos;
	// JSONで読み込むデータ
	int		targetFrame_fill;
	int		targetFrame_end;
	Transform targetPosition_fill[3];

	// 初期化必要
	int		frameCount;
	int		frameBuffer_end;
	int		isChangeTiming;
	int		fillCount;
	float	constantT;
	float	easedT;
	Transform	p;
	int		handle;


	void	LoadFromJSON();

public:
	FillWithPlayer();

	void	Update();
	void	Draw();

	int		IsChangeTiming() { return isChangeTiming; };

};
