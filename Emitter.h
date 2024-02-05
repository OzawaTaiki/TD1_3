#pragma once
#include "Bubble.h"

class Emitter
{
private:


public:
	static	void	Bubble();


	// mainに置くだけ。絶対に、複数回実行されることがないように。
	static	void	Update();
	static	void	Draw();
};