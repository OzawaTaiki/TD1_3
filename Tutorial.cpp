#include "Tutorial.h"
#include "KeyManager.h"
#include "PhilliaFunction/Phill.h"
#include "ResourceManager.h"
#include <Novice.h>

Tutorial::Tutorial()
{
	frameCount_current = 0;
	frameCount_next = 0;
	frameCount_close = 0;
	frameBuffer_next = 0;
	frameBuffer_close = 0;
	page_current = 0;
	page_previous = 0;
	turnDirection = 0;
	alphaValue_popup = 0;
	alphaValue_bg = 0;
	alphaValue_next = 0;
	alphaValue_close = 0;
	substract_next = 0;
	constantT_popup = 0.0f;
	constantT_next = 0.0f;
	constantT_close = 0.0f;
	easedT_next = 0.0f;
	deletable = 0;

	whiteHandle = ResourceManager::Handle("white1x1");
	handle[Page1] = ResourceManager::Handle("rule1");
	handle[Page2] = ResourceManager::Handle("rule2");
}

void Tutorial::Update()
{
	if (constantT_popup != 1.0f)
	{
		constantT_popup = float(frameCount_current) / float(targetFrame_popup);
		alphaValue_popup = int(0xff * constantT_popup);
		alphaValue_bg = int(0xff * constantT_popup);
	}

	if (KeyManager::GetKeys(DIK_TAB) && !KeyManager::GetPreKeys(DIK_TAB) && frameCount_current && frameBuffer_next == 0 && constantT_popup == 1.0f)
	{
		page_current = ImgName_Count;
		frameBuffer_next = frameCount_current;
	}

	//if (KeyManager::GetKeys(DIK_A) && !KeyManager::GetPreKeys(DIK_A))
	//{
	//	this->Prev();
	//}
	if (KeyManager::GetKeys(DIK_D) && !KeyManager::GetPreKeys(DIK_D) && frameBuffer_next == 0)
	{
		this->Next();
		frameBuffer_next = frameCount_current;
	}

	// ページを変更
	if (turnDirection != 0)
	{
		page_previous = page_current;
		page_current += turnDirection;
		turnDirection = 0;
		if (page_current < 0) page_current = 0;
	}

	if (page_previous != page_current)
	{
		if (frameBuffer_next != 0)
		{
			frameCount_next = frameCount_current - frameBuffer_next;
			constantT_next = float(frameCount_next) / float(targetFrame_turnPage);
			easedT_next = Phill::EaseOutQuart(constantT_next);
			substract_next = int(targetSubstract_close * easedT_next);
			alphaValue_next = int(0xff * constantT_next);
		}
		if (constantT_next == 1.0f)
		{
			if (page_current < ImgName_Count)
				page_previous = page_current;
			else deletable = 1;
		}
		if (page_current >= ImgName_Count)
		{
			alphaValue_bg = int((1.0f - constantT_next) * 0xff);
		}
	}
	else
	{
		// 事後処理
		if (constantT_next == 1.0f)
		{
			frameBuffer_next = 0;
			frameCount_next = 0;
			constantT_next = 0.0f;
			easedT_next = 0.0f;
			substract_next = 0;
			alphaValue_next = 0;
		}
	}

	



	// クローズスタート
	if (frameBuffer_close != 0 && constantT_close != 1.0f)
	{
		frameCount_close = frameCount_current - frameBuffer_close;

		constantT_close = float(frameCount_close) / float(targetFrame_close);
		alphaValue_close = int(0xff * constantT_close);
	}
	// クローズ終了
	if (constantT_close == 1.0f) deletable = 1;

	frameCount_current++;
}

void Tutorial::Next()
{
	turnDirection = 1;
}

void Tutorial::Prev()
{
	turnDirection = -1;
}

void Tutorial::Draw()
{
	Novice::DrawBox(0, 0, 1920, 1080, 0.0f, int(alphaValue_bg / 1.2f), kFillModeSolid);

	if (page_current < ImgName_Count)
	{
		Phill::DrawQuadPlus(
			960, 540,
			srcWidth, srcHeight,
			1.0f, 1.0f, 0.0f,
			0, 0,
			srcWidth, srcHeight,
			handle[page_current],
			0xffffff00 + alphaValue_popup,
			DrawMode_Center
		);
	}

	if (page_previous < ImgName_Count)
	{
		Phill::DrawQuadPlus(
			960 - substract_next, 540,
			srcWidth, srcHeight,
			1.0f, 1.0f, 0.0f,
			0, 0,
			srcWidth, srcHeight,
			handle[page_previous],
			0xffffff00 + alphaValue_popup - alphaValue_next,
			DrawMode_Center
		);
	}
	
	
}
