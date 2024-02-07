#pragma once
#include <Vector2.h>
#include <vector>

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
	BackGround(unsigned int _color);

	void Update();
	void Draw();

};