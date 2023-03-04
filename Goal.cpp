#include "Goal.h"
#include "StageCSVManager.h"
#include <math.h>
#include "Field.h"

Goal& Goal::GetInstance()
{
	static Goal inst;
	return inst;
}

void Goal::Initialize()
{
	bool isGoalPos = false;

	for (int y = 0; y < Frame::GetLayerFrameHeight() * Layer::layerBlockHeight; y++)
	{
		for (int x = 0; x < Frame::GetLayerFrameWidth() * Layer::layerBlockWidth; x++)
		{
			int Y = y / Layer::layerBlockHeight;
			int X = x / Layer::layerBlockWidth;

			std::list<std::unique_ptr<Layer>>& layer = StageCSVManager::GetInstance().frameData.layersInTheFrame[Y][X];

			//�d�Ȃ肪����΂��̕����ǂݍ���
			for (auto itr = layer.begin(); itr != layer.end(); itr++) {
				if (layer.size())
				{
					Block::BlockType block = itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->GetType();
					//�v���C���[�̈ʒu���ǂݍ��܂�Ă�����
					if (block == map::GOAL)
					{
						SetMapPos({ (float)y,(float)x });
						isGoalPos = true;
						//�����Ƃ�
						itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->SetType(Block::NONE);
						break;
					}
				}
			}
			//�����ǂݍ��܂ꂽ��I���
			if (isGoalPos)
			{
				break;
			}
		}
	}
	//���W���ǂݍ��܂�Ȃ�������
	if (!isGoalPos)
	{
		SetMapPos({ 0,0 });
	}

	isOverlap = false;

	effectCount = 0;
}

Vector2 Goal::GetMapPos()
{
	return { (int)pos.x / Block::BLOCK_SIZE ,(int)pos.y / Block::BLOCK_SIZE  };
}

void Goal::SetMapPos(Vector2 mapPos)
{
	pos.y = (int)mapPos.x * Block::BLOCK_SIZE + Block::BLOCK_SIZE / 2;
	pos.x = (int)mapPos.y * Block::BLOCK_SIZE + Block::BLOCK_SIZE / 2;
}



void Goal::CheckOverlapBlock(Field* field)
{
	if (field->GetMap({ GetMapPos().x,GetMapPos().y }) == BLOCK)
	{
		this->isOverlap = true;
	}
	else
	{
		this->isOverlap = false;
	}
}

void Goal::Draw()
{
	effectCount++;

	int color = fabsf(sinf((float)effectCount * 0.05f)) * 155;

	float length = Block::BLOCK_SIZE / 2;

	if (this->isOverlap)
	{
		SetDrawBlendMode(DX_BLENDMODE_SUB, color);
		length *= sinf((float)effectCount * 0.04f);
	}

	DrawBox(pos.x - length, pos.y - length, pos.x + length, pos.y + length, GetColor(255, 255, 0), true);

	if (this->isOverlap) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}


