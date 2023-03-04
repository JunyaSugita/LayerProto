#include "Goal.h"
#include "StageCSVManager.h"

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
}

Vector2 Goal::GetMapPos()
{
	return { (int)pos.x / Block::BLOCK_SIZE + Block::BLOCK_SIZE / 2,(int)pos.y / Block::BLOCK_SIZE + Block::BLOCK_SIZE / 2 };
}

void Goal::SetMapPos(Vector2 mapPos)
{
	pos.y = (int)mapPos.x * Block::BLOCK_SIZE + Block::BLOCK_SIZE / 2;
	pos.x = (int)mapPos.y * Block::BLOCK_SIZE + Block::BLOCK_SIZE / 2;
}



void Goal::Draw()
{
	DrawBox(pos.x - Block::BLOCK_SIZE / 2, pos.y - Block::BLOCK_SIZE / 2, pos.x + Block::BLOCK_SIZE / 2, pos.y + Block::BLOCK_SIZE / 2, GetColor(255, 255, 0), true);
}



