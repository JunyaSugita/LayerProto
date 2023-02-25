#include "Layer.h"
#include "DxLib.h"

using BlockType = Block::BlockType;

Layer::Layer() 
{
	freamNum = 0;
	waitTimer = 20;
}

Layer::~Layer()
{
	
}

void Layer::Initialize()
{
	//������
	for(int i = 0; i < layerBlockWidth; i++)
	{
		//�u���b�N�^�����Ă��̃x�N�^��ǉ�(�s��ł���i��)
		blocks_.push_back(std::vector<std::unique_ptr <Block>>());

		for(int j = 0; j < layerBlockWidth; j++)
		{
			block_ = std::make_unique<Block>();
			block_->Initialize();
			//�u���b�N�̗v�f��ǉ�
			blocks_[i].push_back(std::move(block_));
		}
	}

	//���W�̏�����
	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			Vector2 pos;
			//�u���b�N�̍��W��ݒ�
			if(i >= 0)
			{
				pos.x = i * blocks_[i][j]->BLOCK_SIZE;
				
			}
			if(j >= 0)
			{
				pos.y = j * blocks_[i][j]->BLOCK_SIZE;
			}

			blocks_[i][j]->SetPos(pos);

			//�`��̏�����
			//blocks_[i][j]->SetType(blockTypes)
		}
	}
}

void Layer::Update(char* keys,char* oldkeys)
{
	if(keys[KEY_INPUT_SPACE] == 1 && oldkeys[KEY_INPUT_SPACE] == 0)
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
			//�u���b�N�̍��W��ݒ�
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



