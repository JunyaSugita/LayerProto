#include "Layer.h"
#include "DxLib.h"

using BlockType = Block::BlockType;

const float Layer::layerWidth = Block::BLOCK_SIZE * layerBlockWidth;
const float Layer::layerHeight = Block::BLOCK_SIZE * layerBlockHeight;

Layer::Layer()
{
	freamNum = 0;
	layerPos = {0,0};
}

Layer::~Layer()
{
	/*for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			delete blocks_[i][j];
		}
	}*/
}

void Layer::Delete()
{
	
}


void Layer::Initialize()
{
	for(int i = 0; i < layerBlockWidth; i++)
	{
		//ブロック型を持てる空のベクタを追加(行列でいうi列)
		blocks_.push_back(std::vector<std::unique_ptr <Block>>());

		for(int j = 0; j < layerBlockWidth; j++)
		{
			std::unique_ptr <Block> block_;
			block_ = std::make_unique<Block>();
			block_->Initialize();
			//ブロックの要素を追加
			blocks_[i].push_back(std::move(block_));
		}
	}

	//座標の初期化
	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			Vector2 pos;
			//ブロックの座標を設定
			if(i >= 0)
			{
				pos.x = i * Block::BLOCK_SIZE;
				
			}
			if(j >= 0)
			{
				pos.y = j * Block::BLOCK_SIZE;
			}

			blocks_[i][j]->SetPos(pos);

			//形状の初期化(CSVファイルの読み込んだ形状をブロッククラスに渡す)
			BlockType blockType;
			if(i == j)
			{
				blockType = BlockType::NOLAYER_BLOCK;
				blocks_[i][j]->SetType(blockType);
			}
			else
			{
				blockType = BlockType::NONE;
				blocks_[i][j]->SetType(blockType);
			}
			
		}
	}
}

void Layer::Update(char* keys,char* oldkeys)
{
	if(keys[KEY_INPUT_0] == 1 && oldkeys[KEY_INPUT_0] == 0)
	{
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
				pos.x = i * Block::BLOCK_SIZE + (layerBlockWidth * Block::BLOCK_SIZE * freamNum);

			}
			if(j >= 0)
			{
				pos.y = j * Block::BLOCK_SIZE;
			}

			blocks_[i][j]->SetPos(pos);
		}
	}
}

void Layer::Draw()
{
	DrawBox(layerPos.x, layerPos.y, layerPos.x + layerWidth, layerPos.y + layerHeight, GetColor(255, 255, 255), false);

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



