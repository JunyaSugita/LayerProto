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
	DrawBox(pos_.x - BLOCK_SIZE, pos_.y - BLOCK_SIZE, pos_.x + BLOCK_SIZE, pos_.y + BLOCK_SIZE, GetColor(255, 255, 255), true);
}
