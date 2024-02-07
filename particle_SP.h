#pragma once
#include <Vector2.h>
#include <vector>

class particle_SP
{
	struct pati
	{
		Vector2			pos;
		int				size;
		int				maxSize;
		float			theta;
		unsigned int	color;
		int				drawTime;
		int				currentTime;
		int				veloY;
	};

	std::vector<pati*> p;

	Vector2			GHsize;
	int				pGH;
	const int		posRange = 64;

public:
	particle_SP(Vector2 _pos, int _num);

	bool Update();
	void Draw();

	void a(int i);

};