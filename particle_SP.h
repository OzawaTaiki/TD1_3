#pragma once
#include <Vector2.h>
#include <vector>

class particle_SP
{
	struct pati
	{
		Vector2			pos;
		int				maxSize;
		float			size;
		unsigned int	color;
		float			drawTime;
		int				currentTime;
		float			veloX;
		float			veloY;
	};

	std::vector<pati*> p;

	Vector2			GHsize;
	int				pGH;
	const int		posRange = 64;

public:
	particle_SP(Vector2 _pos, int _num);

	bool Update(int _areaWidth);
	void Draw();

	void a(int i);

};