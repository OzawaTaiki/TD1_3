#pragma once
#include <Vector2.h>
#include <vector>
#include "definition.h"

class particle_SP;

class BackGround
{
private:

	unsigned int color;
	int width;
	int height;

	int pNumRange;
	int pPosXrange;
	int pPosYrange;
	int pPosMarginScale;

	int randRange[2];
	int randNum[2];

	int particleMax;
	std::vector<particle_SP*> particle;

public:
	BackGround(unsigned int _color, int _width = kStageAreaWidth, int _height = kStageAreaHeight);

	void Update();
	void Draw();

};