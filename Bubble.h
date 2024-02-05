#pragma once
#include "ResourceManager.h"
#include "UI/UI_ToolKit_Defines.h"

class Bubble
{
private:
	SpriteData	sprData;
	Transform	position;

public:
	Bubble(Transform _pos);

	void	Update();
	void	Draw();

};
