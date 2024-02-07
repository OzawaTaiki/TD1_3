#include "particle_SP.h"
#include "ResourceManager.h"
#include <Novice.h>
#include <stdlib.h>


particle_SP::particle_SP(Vector2 _pos, int _num)
{
	p.clear();

	for (int i = 0; i < _num; i++)
	{
		pati* newPati = new pati();

		newPati->pos.x = float(rand() % posRange + _pos.x);
		newPati->pos.y = float(rand() % posRange + _pos.y);

		newPati->theta = float(rand() % 100) / 100.0f * 6.14f;

		newPati->drawTime = rand() % 5 + 10;
		newPati->currentTime = 0;

		newPati->maxSize = rand() % 10 * 12;
		newPati->size = 4;

		newPati->veloY = (rand() % 3 + 1) * -1;

		newPati->color = 0xffffff40;

		p.push_back(newPati);
	}

	GHsize = { 64,64 };
	pGH = ResourceManager::Handle("bubble");
}

bool particle_SP::Update()
{
	for (int i = 0; i < p.size(); i++)
	{
		p[i]->pos.y += p[i]->veloY;

		float val = (float)p[i]->currentTime / float(p[i]->drawTime * 60) * 2 / 3;
		if (p[i]->currentTime > float(p[i]->drawTime * 60) * 2 / 3)
			val = 1.0f - val;

		p[i]->color = unsigned int(64.0f * val + 255.0f * val) + 0xffffff00;

		p[i]->size = int(4 * val + p[i]->maxSize * val);

		p[i]->currentTime++;

		if (p[i]->currentTime > p[i]->drawTime * 60)
		{
			p.erase(p.begin() + i);
		}
	}
	if (p.size() <= 0)
		return false;
	return true;
}

void particle_SP::Draw()
{
	for (int i = 0; i < p.size(); i++)
	{
		Novice::DrawQuad(
			int(p[i]->pos.x), int(p[i]->pos.y),
			int(p[i]->pos.x + p[i]->size), int(p[i]->pos.y),
			int(p[i]->pos.x), int(p[i]->pos.y + p[i]->size),
			int(p[i]->pos.x + p[i]->size), int(p[i]->pos.y + p[i]->size),
			0, 0, (int)GHsize.x, (int)GHsize.y,
			pGH, p[i]->color);
	}
}

void particle_SP::a(int i)
{
	for (int j = 0; j < p.size(); j++)
		Novice::ScreenPrintf(i * 100, 20 * j, "%x", p[j]->color);

}
