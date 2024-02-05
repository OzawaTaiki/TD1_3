#include "Bubble.h"

Bubble::Bubble(Transform _pos)
{
	sprData.srcPos = Transform(0, 0);
	sprData.srcSize = Size(1, 1);
	sprData.textureHandle = ResourceManager::Handle("white");
	sprData.trgSize = Size(30, 30);
	sprData.drawMode = DrawMode_Center;

	position = _pos;
}

void Bubble::Update()
{
}

void Bubble::Draw()
{

}
