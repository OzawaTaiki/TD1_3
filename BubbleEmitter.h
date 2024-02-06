#pragma once
#include "BaseEmitter.h"
#include "Bubble.h"
#include <vector>

struct BubbleSetting
{
	float	velocityX_offset;
	float	velocityX_range;
	float	velocityY_offset;
	float	velocityY_range;
	float	gravity;
};

class BubbleEmitter : public Emitter
{
private:
	EmitterData* pEd;
	BubbleSetting setting;
	std::vector<Bubble*> bubbles;

	int			framecount;
	int			spawnInterval;

public:
	BubbleEmitter(EmitterData* _ed);
	void	Update() override;
	void	Draw() override;
	void	SetParticleSetting(BubbleSetting* _bSetting);

};