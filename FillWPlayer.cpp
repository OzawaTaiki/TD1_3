﻿#include "FillWPlayer.h"
#include "PhilliaFunction/Phill.h"
#include <Novice.h>
#include "ResourceManager.h"


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
	constantT = 0.0f;
	easedT = 0.0f;
	handle = ResourceManager::Handle("dekaP");
}

void FillWithPlayer::Update()
{
	if (frameCount < targetFrame_fill)
	{
		Novice::ScreenPrintf(300, 15, "%d", frameCount);
		constantT = Phill::ConstantT(targetFrame_fill, frameCount);
		//easedT = Phill::EaseOutQuart(constantT);
		if (fillCount == 0)
		{
			p.x = Phill::Lerp(1920, targetPosition_fill[fillCount].x, constantT);
			p.y = Phill::Lerp(0, targetPosition_fill[fillCount].y, constantT);
		}
		else
		{
			p.x = Phill::Lerp(targetPosition_fill[fillCount - 1].x, targetPosition_fill[fillCount].x, constantT);
			p.y = Phill::Lerp(targetPosition_fill[fillCount - 1].y, targetPosition_fill[fillCount].y, constantT);
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
	if (isChangeTiming == 0)
	{
		bufferPos.push_back(p);
		if (frameCount % 20)
		{
			sprd.srcPos = 0;
			sprd.srcSize = 64;
			sprd.trgSize = 64;
			sprd.drawMode = DrawMode_Center;
			sprd.textureHandle = ResourceManager::Handle("bubble");
			bs.gravity = 0.01f;
			bs.velocityX_range = 4.0f;
			bs.velocityX_offset = -2.0f;
			bs.velocityY_range = 1.0f;
			EmitterData temp_ed{};
			temp_ed.position.x = p.x - 500.0f;
			temp_ed.position.y = p.y - 100.0f;
			temp_ed.size.width = 1000;
			temp_ed.size.height = 200;
			temp_ed.sprd = &sprd;
			ed.push_back(temp_ed);
			emitters.push_back(new BubbleEmitter(&ed.back()));
			emitters.back()->SetParticleSetting(&bs);
		}
	}

	for (auto& elm : emitters)
	{
		elm->Update();
	}

	frameCount++;
}

void FillWithPlayer::Draw()
{
	if (isChangeTiming == 0)
		Novice::DrawEllipse(p.x, p.y, 15, 15, 0.0f, 0x0000ffff,kFillModeSolid);
	for (auto& elm : bufferPos)
	{
		Phill::DrawQuadPlus(
			elm.x, elm.y,
			640, 680,
			1.0f, 1.0f,
			0.0f,
			0, 0, 640, 680,
			handle,
			0xffffffff,
			DrawMode_Center
		);
	}
	for (auto& elm : emitters)
	{
		elm->Draw();
	}
}
