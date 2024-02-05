#include "BubbleEmitter.h"
#include <Novice.h>

BubbleEmitter::BubbleEmitter(EmitterData* _ed)
{
	pEd = _ed;
	framecount = 0;
	spawnInterval = 3;
}

void BubbleEmitter::Update()
{
	if (framecount % spawnInterval == 0)
	{
		ParticleData pd{};
		pd.zeroPosition.x = float(rand() % pEd->size.width + pEd->position.x);
		pd.zeroPosition.y = float(rand() % pEd->size.height + pEd->position.y);
		pd.zeroVelocity.x = float(rand() % 50) / 10.0f;
		pd.zeroVelocity.y = float(rand() % 30 - 30) / 10.0f;
		pd.zeroGravity = 0.05f;
		pd.zeroAirResistance = 0.95f;
		
		bubbles.push_back(new Bubble(pd));
	}

	for (Bubble* elm : bubbles)
	{
		elm->Update();
	}

	framecount++;
}

void BubbleEmitter::Draw()
{
	Novice::DrawBox(
		int(pEd->position.x), int(pEd->position.y),
		pEd->size.width, pEd->size.height,
		0.0f,
		0xff000099,
		kFillModeSolid
	);
	for (Bubble* elm : bubbles)
	{
		elm->Draw();
	}
}
