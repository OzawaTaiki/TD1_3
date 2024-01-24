#pragma once

#include <vector>

enum ImgName : int
{
	Page1,
	Page2,
	ImgName_Count
};

class Tutorial
{
public:
	Tutorial();
	void	Update();
	void	Draw();
	void	Next();
	void	Prev();
	int		Deletable() const { return deletable; };

private:
	const	int		targetFrame_popup		= 40;
	const	int		targetFrame_turnPage	= 30;
	const	int		targetFrame_close		= 40;
	const	int		targetSubstract_close	= 100;

	int		frameCount_current;
	int		frameCount_next;
	int		frameCount_close;

	int		frameBuffer_next;
	int		frameBuffer_close;

	float	constantT_popup;
	float	constantT_next;
	float	constantT_close;

	float	easedT_next;

	int		alphaValue_popup;
	int		alphaValue_bg;
	int		alphaValue_next;
	int		alphaValue_close;
	int		substract_next;

	int		page_current;
	int		page_previous;

	int		turnDirection;
	int		deletable;

	// リソースデータ
	const	int		srcWidth	= 900;
	const	int		srcHeight	= 500;

	int		whiteHandle;
	int		handle[ImgName_Count];
};