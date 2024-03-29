﻿#include "BubbleEmitter.h"
#include <Novice.h>

BubbleEmitter::BubbleEmitter(EmitterData* _ed)
{
	setting.velocityX_offset = 0.0f;
	setting.velocityX_range = 5.0f;
	setting.velocityY_offset = -1.0f;
	setting.velocityY_range = 1.0f;
	pEd = _ed;
	framecount = 0;
	spawnInterval = 3;
	ableGenerate = 1;
}

void BubbleEmitter::Update()
{
	if (framecount % spawnInterval == 0 && ableGenerate)
	{
		ParticleData pd{};
		pd.zeroPosition.x		= float(rand() % pEd->size.width + pEd->position.x);
		pd.zeroPosition.y		= float(rand() % pEd->size.height + pEd->position.y);
		pd.zeroVelocity.x		= 0;
		pd.zeroVelocity.x		= float(rand() % int(setting.velocityX_range * 10.0f)) / 10.0f + setting.velocityX_offset;
		pd.zeroVelocity.y		= float(rand() % int(setting.velocityY_range * 10.0f)) / 10.0f + setting.velocityY_offset;
		pd.zeroGravity			= setting.gravity;
		pd.zeroAirResistance	= 0.95f;
 		pd.sprd					= pEd->sprd;
		bubbles.push_back(new Bubble(pd));
	}

	for (int i = 0; i < bubbles.size(); i++)
	{
		bubbles[i]->Update();
		if (bubbles[i]->ableDelete())
		{
			delete bubbles[i];
			bubbles.erase(bubbles.begin() + i);
		}
	}

	framecount++;
}

void BubbleEmitter::Draw()
{
	Novice::DrawBox(
		int(pEd->position.x), int(pEd->position.y),
		pEd->size.width, pEd->size.height,
		0.0f,
		0xff000000,
		kFillModeSolid
	);
	for (Bubble* elm : bubbles)
	{
		elm->Draw();
	}
}

void BubbleEmitter::ChangeIsGenerate(bool _isGenerate)
{
	ableGenerate = _isGenerate;
}

void BubbleEmitter::SetParticleSetting(BubbleSetting* _bSetting)
{
	setting = (*_bSetting);
}
