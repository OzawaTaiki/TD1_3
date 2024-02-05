#pragma once
#include "ResourceManager.h"
#include "UI/UI_ToolKit_Defines.h"
#include "ParticleDefines.h"

struct VECTOR2
{
	float	x;
	float	y;
	VECTOR2& operator+=(VECTOR2 _vec2);
	VECTOR2& operator=(Vector2 _vec2);
};

class Bubble
{
private:
	SpriteData	sprData;
	VECTOR2		position;
	VECTOR2		velocity;
	VECTOR2		acceleration;
	float		gravity;
	float		airResist;

public:
	Bubble(ParticleData _pd);

	void	Update();
	void	Draw();

};
