#pragma once
#include "JSON-Loader/JSON-Manager.h"
#include "UI/UI_ToolKit_Defines.h"

class Title
{
private:
	JsonL*	startup;
	
	// JSONでロード
	int		targetFrame_startup;

	// ResourceManagerからロード
	int		handle_player;
	int		handle_soap;
	int		handle_title;
	int		handle_click2start;

	// 初期化必要
	int		framecount;
	int		alpha_startup;
	int		isReturn;

	Transform	tfTitle;
	Size		szTitle;

	void	LoadFromResMg();
	void	LoadFromJSON();
public:
	Title();

	void	Update();
	void	Draw();

};