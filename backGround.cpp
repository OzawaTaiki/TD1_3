#include "backGround.h"
#include <Novice.h>
#include "particle_SP.h"
#include <stdlib.h>

BackGround::BackGround(unsigned int _color, int _width, int _height)
{
	color = _color;
	width = _width;
	height = _height;

	pNumRange = 3;
	pPosXrange = kStageAreaWidth / kTileSize - 1;
	pPosYrange = kStageAreaHeight / kTileSize - 1;
	pPosMarginScale = kTileSize;

	randRange[0] = 100;
	randRange[1] = 100;
	randNum[0] = 0;
	randNum[1] = 0;

	particleMax = 1;
	particle.clear();
}

void BackGround::Update()
{
	randNum[0] = rand() % randRange[0];
	randNum[1] = rand() % randRange[1];

	if (randNum[0] == randNum[1])
	{
		int pNum = rand() % pNumRange + 1;
		Vector2 pos;
		pos.x = float(rand() % pPosXrange * pPosMarginScale + kTileSize / 2);
		pos.y = float(rand() % pPosYrange * pPosMarginScale + kTileSize / 2);

		if (particle.size() < particleMax)
			particle.push_back(new particle_SP(pos, pNum));
	}

	for (int i = 0; i < particle.size(); i++)
		//if(!particle.empty())
		//for (int i = 0; i < 1; i++)
	{
		if (!particle[i]->Update(width))
			particle.erase(particle.begin() + i);
	}
}

void BackGround::Draw()
{
	Novice::DrawBox(0, 0, width, height, 0, color, kFillModeSolid);

	for (int i = 0; i < particle.size(); i++)
		//if (!particle.empty())
		//for (int i = 0; i < 1; i++)
	{
		particle[i]->Draw();
#ifdef DEBUG
		particle[i]->a(i);
#endif // DEBUG
	}
}
