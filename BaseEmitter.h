#pragma once
#include "Bubble.h"

class Emitter
{
private:
	EmitterData* pEd;

public:

	virtual void	Update();

	virtual void	Draw();
};