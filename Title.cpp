#include "Title.h"

void Title::LoadFromJSON()
{
	targetFrame_startup = atoi((*startup)["target_turnLight"]);
}

Title::Title()
{
	framecount = 0;

}

void Title::Update()
{

}

void Title::Draw()
{

}

