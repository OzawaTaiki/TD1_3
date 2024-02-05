#pragma once
#include "BaseEmitter.h"

class BubbleEmitter : public Emitter
{
private:
	EmitterData* pEd;

public:
	BubbleEmitter(EmitterData* _ed);
	void	Update() override;
	void	Draw() override;
};