#include "Title.h"
#include "PhilliaFunction/Phill.h"
#include <Novice.h>

void Title::LoadFromJSON()
{
	startup = JSON_Manager::GetJSON("title-startup");
	targetFrame_startup = atoi((*startup)["target_turnLight"]);
}

Title::Title()
{
	framecount = 0;
	alpha_startup = 0;
	LoadFromJSON();
}

void Title::Update()
{
	if (framecount < targetFrame_startup)
	{
		float constantT = Phill::ConstantT(targetFrame_startup, framecount);
		alpha_startup = Phill::Lerp(0xff, 0, constantT);
	}
}

void Title::Draw()
{
	Novice::DrawBox(0, 0, 1920, 1080, 0.0f, alpha_startup, kFillModeSolid);

}

