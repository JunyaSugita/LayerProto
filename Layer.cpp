#include"Layer.h"


void Layer::SetBlock(int y, int x, Block block)
{
	this->blocks[y][x] = block;
}

Block Layer::GetBlock(int y, int x)
{
	return this->blocks[y][x];
}
