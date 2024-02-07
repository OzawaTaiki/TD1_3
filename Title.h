#pragma once
#include "JSON-Loader/JSON-Manager.h"

class Title
{
private:
	JsonL*	startup;
	
	int		targetFrame_startup;
	int		framecount;

	void	LoadFromJSON();
public:
	Title();

	void	Update();
	void	Draw();

};