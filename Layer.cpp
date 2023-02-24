#include "Layer.h"
#include "DxLib.h"

using BlockType = Block::BlockType;

Layer::Layer() 
{
	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			blocks_[i][j] = new Block;
		}
	}

	freamNum = 0;
	waitTimer = 20;
}

Layer::~Layer()
{
	//ブロックの削除
	/*blocks_.clear();
	block_.release();*/

	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			delete blocks_[i][j];
		}
	}
}

void Layer::Initialize()
{
	//初期化
	//for(int i = 0; i < layerBlockWidth; i++)
	//{
	//	//ブロック型を持てる空のベクタを追加(行列でいうi列)
	//	blocks_.push_back(std::vector<std::unique_ptr <Block>>());

	//	for(int j = 0; j < layerBlockWidth; j++)
	//	{
	//		block_ = std::make_unique<Block>();
	//		block_->Initialize();
	//		//ブロックの要素を追加
	//		blocks_[i].push_back(std::move(block_));
	//	}
	//}

	//座標の初期化
	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			Vector2 pos;
			//ブロックの座標を設定
			if(i >= 0)
			{
				pos.x = i * blocks_[i][j]->BLOCK_SIZE;
				
			}
			if(j >= 0)
			{
				pos.y = j * blocks_[i][j]->BLOCK_SIZE;
			}

			blocks_[i][j]->SetPos(pos);

			//形状の初期化
			//blocks_[i][j]->SetType(blockTypes)
		}
	}
}

void Layer::Update(char* keys,char* oldkeys)
{
	if(keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
	{
		/*if(freamNum < 3)
		{
			if(waitTimer > 0)
			{
				waitTimer--;
				if(waitTimer <= 0)
				{
					freamNum++;
					waitTimer = 5;
				}
			}
		}*/

		if(freamNum < 2)
		{
			freamNum++;
		}
		else
		{
			freamNum = 0;
		}
	}
	
	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			Vector2 pos;
			//ブロックの座標を設定
			if(i >= 0)
			{
				pos.x = i * blocks_[i][j]->BLOCK_SIZE + (layerBlockWidth * blocks_[i][j]->BLOCK_SIZE * freamNum);

			}
			if(j >= 0)
			{
				pos.y = j * blocks_[i][j]->BLOCK_SIZE;
			}

			blocks_[i][j]->SetPos(pos);
		}
	}
}

void Layer::Draw()
{
	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			blocks_[i][j]->Draw();
		}
	}
}

void Layer::SetBlock(int y, int x, BlockType block)
{
	this->blockTypes[y][x] = block;
}

BlockType Layer::GetBlock(int y, int x)
{
	return this->blockTypes[y][x];
}



