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

	isOverlap = false;

	effectCount = 0;

	//ゴールに触れていると
	goalCount = 0;
	isGoal = false;
}

Vector2 Goal::GetMapPos()
{
	return { (int)pos.x / Block::BLOCK_SIZE ,(int)pos.y / Block::BLOCK_SIZE };
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

void Goal::CheckEnterGoal(const Vector2& pos, const Vector2& length)
{
	if (CheckHitBoxAndBox(pos, length, this->GetPos(), { Block::BLOCK_SIZE ,Block::BLOCK_SIZE })
		&& !isGoal)
	{
		goalCount++;

		if (goalCount >= goalCountMax )
		{
			isGoal = true;
		}
	}
	else
	{
		goalCount = 0;
	}
}

void Goal::Draw()
{
	effectCount++;

	//blendmode用の値
	int color = fabsf(sinf((float)effectCount * 0.05f)) * 155;

	float goalT = 1.0f + (float)this->goalCount / (float)goalCountMax;

	//当たっているときサイズを変更したり
	float length = (float)Block::BLOCK_SIZE / 2.0f * (goalT - sinf(goalCount * 0.3f));

	//ゴールに重なっているとき
	if (this->isOverlap)
	{
		SetDrawBlendMode(DX_BLENDMODE_SUB, color);
		length *= sinf((float)effectCount * 0.04f);
	}
	//描画
	DrawBox(pos.x - length, pos.y - length, pos.x + length, pos.y + length, GetColor(255* goalT, 255* goalT, 0), true);

	//ほかに影響しないように戻す
	if (this->isOverlap) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}


	//デバッグテキスト
	if (isGoal)
	{
		DrawFormatString(0, 200, GetColor(255, 255, 255), "CLEAR", 3.0f);
	}
}



