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

			//重なりがあればその分も読み込み
			for (auto itr = layer.begin(); itr != layer.end(); itr++) {
				if (layer.size())
				{
					Block::BlockType block = itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->GetType();
					//プレイヤーの位置が読み込まれていたら
					if (block == map::GOAL)
					{
						SetMapPos({ (float)y,(float)x });
						isGoalPos = true;
						//消しとく
						itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->SetType(Block::NONE);
						break;
					}
				}
			}
			//もう読み込まれたら終わる
			if (isGoalPos)
			{
				break;
			}
		}
	}
	//座標が読み込まれなかったら
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



