#include "playground.h"

#include "CSVLoader.h"
#include <Novice.h>

Playground::Playground()
{

}

void Playground::Init(int _stageNo)
{

	CSV_Loader::LoadFromCSV_s(stageFilePath[_stageNo], '\n');
	selectStage = _stageNo;

	field = CSV_Loader::GetPointerMapchip();
}

void Playground::Draw()
{

}
