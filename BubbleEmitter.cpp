#include "BubbleEmitter.h"
#include <Novice.h>

BubbleEmitter::BubbleEmitter(EmitterData* _ed)
{
	pEd = _ed;
}

void BubbleEmitter::Update()
{
	
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
}
