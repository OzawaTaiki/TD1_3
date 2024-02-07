#include "backGround.h"
#include "definition.h"
#include <Novice.h>
#include "particle_SP.h"
#include <stdlib.h>

BackGround::BackGround(unsigned int _color)
{
	color = _color;
	width = kStageAreaWidth;
	height = kStageAreaHeight;

	pNumRange = 3;
	pPosXrange = kStageAreaWidth / kTileSize - 1;
	pPosYrange = kStageAreaHeight / kTileSize - 1;
	pPosMarginScale = kTileSize;

	randRange[0] = 100;
	randRange[1] = 150;
	randNum[0] = 0;
	randNum[1] = 0;

	particleMax = 4;
	particle.clear();
}

void BackGround::Update()
{
	randNum[0] = rand() % randRange[0];
	randNum[1] = rand() % randRange[1];

	if (randNum[0] == randNum[1])
	{
		int pNum = rand() % pNumRange + 2;
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
		if (!particle[i]->Update())
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
		particle[i]->a(i);
	}
}
