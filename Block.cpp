#include "Block.h"
#include "DxLib.h"

void Block::Initialize()
{

}

void Block::Update()
{
}

void Block::Draw()
{
	DrawBox(pos_.x, pos_.y, pos_.x, pos_.y, GetColor(255, 255, 255), true);
}
