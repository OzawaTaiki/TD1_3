#pragma once
#include "BaseEmitter.h"
#include "Bubble.h"
#include <vector>

struct BubbleSetting
{
	float	velocityX_offset;
	float	velocityX_range;
	float	velocityY_offset;
	float	velocityY_range;
	float	gravity;
};

class BubbleEmitter : public Emitter
{
private:
	EmitterData* pEd;
	BubbleSetting setting;
	std::vector<Bubble*> bubbles;

	int			ableGenerate;
	int			framecount;
	int			spawnInterval;

public:
	BubbleEmitter(EmitterData* _ed);
	void	Update() override;
	void	Draw() override;
	/// <summary>
	/// パーティクルを生成するかどうか
	/// </summary>
	/// <param name="_isGenerate">生成する->true</param>
	void	ChangeIsGenerate(bool _isGenerate);
	void	SetParticleSetting(BubbleSetting* _bSetting);

};