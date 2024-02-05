#pragma once
#include "ResourceManager.h"
#include "UI/UI_ToolKit_Defines.h"
#include "ParticleDefines.h"

class Bubble
{
private:
	SpriteData	sprData;
	VECTOR2		position;
	VECTOR2		velocity;
	VECTOR2		acceleration;
	float		gravity;
	float		airResist;
	float		scale;

public:
	Bubble(ParticleData _pd);

	void	Update();
	void	Draw();

};
