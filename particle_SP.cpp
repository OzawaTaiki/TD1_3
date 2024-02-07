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

		newPati->pos.x = _pos.x;
		newPati->pos.y = _pos.y;

		newPati->drawTime = float(rand() % 20 / 10 + 1);
		newPati->currentTime = 0;

		newPati->maxSize = rand() % 3 * 50 + 50;
		newPati->size = (float)newPati->maxSize;

		newPati->veloX = float(rand() % 27 / 9) - 1.0f;
		newPati->veloY = float(rand() % 5 / 2.0f + 2) * -1.0f;

		newPati->color = 0xffffff00;

		p.push_back(newPati);
	}

	GHsize = { 64,64 };
	pGH = rand() % 2;
	pGH = pGH ? ResourceManager::Handle("bubble") : ResourceManager::Handle("foam");
}

bool particle_SP::Update(int _areaWidth)
{
	for (int i = 0; i < p.size(); i++)
	{
		p[i]->pos.x += p[i]->veloX;
		p[i]->pos.y += p[i]->veloY;

		float val = float(p[i]->currentTime) / ((float)p[i]->drawTime * 60.0f);

		if (p[i]->pos.x < -p[i]->size || p[i]->pos.x > _areaWidth + p[i]->size)
			val = 0;

			if (val < 0.6f)
				val /= 0.6f;
			else if (val > 0.9f)
			{
				val = (1.0f - val) / 0.2f;
				p[i]->size += 2.0f;
			}
			else if (val > 0.97f)
				val = 0;
			else
				val = 1;

		p[i]->color = unsigned int(96.0f * val) + 0xffffff00;


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

#ifdef _DEBUG
void particle_SP::a(int i)
{
	//for (int j = 0; j < p.size(); j++)
		//Novice::ScreenPrintf(i * 100, 20 * j, "%x", p[j]->color);
}
#endif //_DEBUG