#pragma once
#include "BaseEmitter.h"
#include "Bubble.h"
#include <vector>

class BubbleEmitter : public Emitter
{
private:
	EmitterData* pEd;
	std::vector<Bubble*> bubbles;

	int			framecount;
	int			spawnInterval;

public:
	BubbleEmitter(EmitterData* _ed);
	void	Update() override;
	void	Draw() override;

};