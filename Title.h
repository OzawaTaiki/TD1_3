#pragma once
#include "JSON-Loader/JSON-Manager.h"

class Title
{
private:
	JsonL*	startup;
	
	// JSONでロード
	int		targetFrame_startup;

	// 初期化必要
	int		framecount;
	int		alpha_startup;

	void	LoadFromJSON();
public:
	Title();

	void	Update();
	void	Draw();

};