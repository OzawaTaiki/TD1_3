#include "Title.h"
#include "PhilliaFunction/Phill.h"
#include <Novice.h>
#include "KeyManager.h"
#include "CursorManager.h"
#include "SceneManager.h"

void Title::LoadFromResMg()
{
	using RM = ResourceManager;
	handle_player = RM::Handle("playerTex");
	handle_soap = RM::Handle("soapTex");
	handle_title;
	handle_click2start;
}

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
	using KM = KeyManager;
	using CM = CursorManager;
	using SM = SceneManager;
	if (framecount < targetFrame_startup)
	{
		float constantT = Phill::ConstantT(targetFrame_startup, framecount);
		alpha_startup = Phill::Lerp(0xff, 0, constantT);
	}

	if (KM::GetKeys(DIK_SPACE) and KM::GetPreKeys(DIK_SPACE) or
		KM::GetKeys(DIK_RETURN) and KM::GetPreKeys(DIK_RETURN) or
		CM::GetClickFlag())
	{
		isReturn = 1;
	}

	if (isReturn) SM::ChangeRequest(Scenes::SC_StageSelect);

	framecount++;
}

void Title::Draw()
{
	Novice::DrawBox(0, 0, 1920, 1080, 0.0f, alpha_startup, kFillModeSolid);

}

