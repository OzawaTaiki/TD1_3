#include "Bubble.h"

Bubble::Bubble()
{
	sprData.srcPos = Transform(0, 0);
	sprData.srcSize = Size(1, 1);
	sprData.textureHandle = ResourceManager::Handle("white");
}

void Bubble::Update()
{
}

void Bubble::Draw()
{

}
