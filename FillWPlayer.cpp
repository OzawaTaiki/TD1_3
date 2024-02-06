#include "FillWPlayer.h"

void FillWithPlayer::LoadFromJSON()
{
	fcountData = JSON_Manager::GetJSON("fillWithPlayer");

	targetFrame_fill = atoi((*fcountData)["targetFrame_fill"]);
	targetFrame_end = atoi((*fcountData)["targetFrame_end"]);
}

FillWithPlayer::FillWithPlayer()
{
	this->LoadFromJSON();


}

void FillWithPlayer::Update()
{

}

void FillWithPlayer::Draw()
{

}
