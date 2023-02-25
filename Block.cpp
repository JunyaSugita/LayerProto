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
	if(type_ == NONE)
	{

	}
	else if(type_ == LAYER_BLOCK)
	{
		DrawBox(pos_.x - BLOCK_SIZE, pos_.y - BLOCK_SIZE, pos_.x + BLOCK_SIZE, pos_.y + BLOCK_SIZE, GetColor(255, 255, 255), true);
	}
	else if(type_ == FIXED_BLOCK)
	{
		DrawBox(pos_.x - BLOCK_SIZE, pos_.y - BLOCK_SIZE, pos_.x + BLOCK_SIZE, pos_.y + BLOCK_SIZE, GetColor(255, 255, 255), true);
	}
	else if(type_ == NOLAYER_BLOCK)
	{
		DrawBox(pos_.x, pos_.y, pos_.x + BLOCK_SIZE, pos_.y + BLOCK_SIZE, GetColor(255, 255, 255), false);
	}
	
}
