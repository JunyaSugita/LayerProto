#include "Block.h"
#include "DxLib.h"

const float Block::BLOCK_SIZE = 30.0f;

void Block::Initialize()
{
}

void Block::Update()
{
	pos_ += move_;
}


void Block::Draw()
{
	if(type_ == NONE)
	{

	}
	else if(type_ == NOLAYER_BLOCK)
	{
		DrawBox(pos_.x, pos_.y, pos_.x + BLOCK_SIZE, pos_.y + BLOCK_SIZE, GetColor(255, 255, 255), false);
	}
	else if(type_ == LAYER_BLOCK)
	{
		DrawBox(pos_.x, pos_.y, pos_.x + BLOCK_SIZE, pos_.y + BLOCK_SIZE, GetColor(255, 255, 255), true);
	}
	else if(type_ == FIXED_BLOCK)
	{
		DrawBox(pos_.x, pos_.y, pos_.x + BLOCK_SIZE, pos_.y + BLOCK_SIZE, GetColor(120, 0, 0), true);
	}
}
