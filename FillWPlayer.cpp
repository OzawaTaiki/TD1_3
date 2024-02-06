#include "FillWPlayer.h"
#include "PhilliaFunction/Phill.h"
#include <Novice.h>

void FillWithPlayer::LoadFromJSON()
{
	fcountData = JSON_Manager::GetJSON("fillWithPlayer");

	targetFrame_fill			= atoi((*fcountData)["targetFrame_fill"]);
	targetFrame_end				= atoi((*fcountData)["targetFrame_end"]);
	targetPosition_fill[0].x	= atoi((*fcountData)["target_0X"]);
	targetPosition_fill[0].y	= atoi((*fcountData)["target_0Y"]);
	targetPosition_fill[1].x	= atoi((*fcountData)["target_1X"]);
	targetPosition_fill[1].y	= atoi((*fcountData)["target_1Y"]);
	targetPosition_fill[2].x	= atoi((*fcountData)["target_2X"]);
	targetPosition_fill[2].y	= atoi((*fcountData)["target_2Y"]);
}

FillWithPlayer::FillWithPlayer()
{
	this->LoadFromJSON();
	frameCount = 0;
	frameBuffer_end = 0;
	fillCount = 0;
}

void FillWithPlayer::Update()
{
	if (frameCount < targetFrame_fill * (fillCount + 1))
	{
		constantT = Phill::ConstantT(targetFrame_fill * (fillCount + 1), frameCount);
		easedT = Phill::EaseOutQuart(constantT);
		if (fillCount == 0)
		{
			p.x = Phill::Lerp(1920, targetPosition_fill[fillCount].x, easedT);
			p.y = Phill::Lerp(0, targetPosition_fill[fillCount].y, easedT);
		}
		else
		{
			p.x = Phill::Lerp(targetPosition_fill[fillCount - 1].x, targetPosition_fill[fillCount].x, easedT);
			p.y = Phill::Lerp(targetPosition_fill[fillCount - 1].y, targetPosition_fill[fillCount].y, easedT);
		}

	}
	if (frameCount == targetFrame_fill)
	{
		fillCount++;
		frameCount = 0;
	}
	if (fillCount == 3)
	{
		isChangeTiming = 1;
	}

	frameCount++;
}

void FillWithPlayer::Draw()
{
	if (isChangeTiming == 0)
		Novice::DrawEllipse(p.x, p.y, 15, 15, 0.0f, 0x0000ffff,kFillModeSolid);
}
