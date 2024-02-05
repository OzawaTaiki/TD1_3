﻿#include "Bubble.h"
#include "PhilliaFunction/Phill.h"

Bubble::Bubble(ParticleData _pd)
{
	// 画像データ
	sprData.srcPos			= Transform(0, 0);
	sprData.srcSize			= Size(64, 64);
	sprData.textureHandle	= ResourceManager::Handle("bubble");
	sprData.trgSize			= Size(64, 64);
	sprData.drawMode		= DrawMode_Center;

	// エミッターから受け取る
	position				= _pd.zeroPosition;
	velocity				= _pd.zeroVelocity;
	acceleration			= _pd.zeroAcceleration;
	gravity					= _pd.zeroGravity;
	airResist				= _pd.zeroAirResistance;

	// 
	framecount = 0;
	scale					= 1.0f;
}

void Bubble::Update()
{
	velocity.x *= airResist;
	acceleration.y = gravity;

	// 座標に適用
	velocity += acceleration;
	position += velocity;
	if (framecount < targetFrame_erase)
		scale = 1.0f - Phill::ConstantT(targetFrame_erase, framecount);

	framecount++;
}

void Bubble::Draw()
{
	Phill::DrawQuadPlus(
		int(position.x), int(position.y),
		sprData.trgSize.width, sprData.trgSize.height,
		scale, scale, 0.0f,
		sprData.srcPos.x, sprData.srcPos.y,
		sprData.srcSize.width, sprData.srcSize.height,
		sprData.textureHandle,
		0xffffffff,
		DrawMode_Center
	);
}

void VECTOR2::operator+=(VECTOR2 _vec2)
{
	x += _vec2.x;
	y += _vec2.y;
	return;
}

void VECTOR2::operator=(Vector2 _vec2)
{
	x = _vec2.x;
	y = _vec2.y;
	return;
}