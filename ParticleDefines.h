#pragma once
#include "UI/UI_ToolKit_Defines.h"
#include <Vector2.h>

struct VECTOR2
{
	float	x;
	float	y;
	void operator+=(VECTOR2 _vec2);
	void operator=(Vector2 _vec2);
	void operator=(Transform _tf);
};

struct ParticleData
{
	VECTOR2		zeroPosition;
	VECTOR2		zeroAcceleration;
	VECTOR2		zeroVelocity;
	Size		zeroSize;
	float		zeroTheta;
	float		zeroGravity;
	float		zeroAirResistance;
	SpriteData*	sprd;

};

struct EmitterData
{
	VECTOR2		position;
	VECTOR2		velocity;
	VECTOR2		acceleration;
	Size		size;
	SpriteData* sprd;
};