#include "Layer.h"
#include "DxLib.h"

using BlockType = Block::BlockType;

const float Layer::layerWidth = Block::BLOCK_SIZE * layerBlockWidth;
const float Layer::layerHeight = Block::BLOCK_SIZE * layerBlockHeight;

Layer::Layer()
{
	freamNumX = 0;
	freamNumY = 0;
	layerPos = { 0,0 };
}

Layer::~Layer()
{

	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			blocks_[i][j].reset();
		}
	}
}

void Layer::Delete()
{

}


void Layer::Initialize(int heightNum, int widthNum)
{
	freamNumX = widthNum;
	freamNumY = heightNum;

	for (int i = 0; i < layerBlockWidth; i++)
	{
		//ブロック型を持てる空のベクタを追加(行列でいうi列)
		blocks_.push_back(std::vector<std::unique_ptr <Block>>());

		for (int j = 0; j < layerBlockWidth; j++)
		{
			std::unique_ptr <Block> block_;
			block_ = std::make_unique<Block>();
			block_->Initialize();
			//ブロックの要素を追加
			blocks_[i].push_back(std::move(block_));
		}
	}

	//座標の初期化
	for (int i = 0; i < layerBlockWidth; i++)
	{
		for (int j = 0; j < layerBlockHeight; j++)
		{
			Vector2 pos;
			//ブロックの座標を設定
			if (i >= 0)
			{
				pos.x = (i * Block::BLOCK_SIZE) + (widthNum * layerWidth);

			}
			if (j >= 0)
			{
				pos.y = (j * Block::BLOCK_SIZE) + (heightNum * layerWidth);
			}

			blocks_[i][j]->SetPos(pos);

			//形状の初期化(CSVファイルの読み込んだ形状をブロッククラスに渡す)
			BlockType blockType;
			if (i == j)
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

	movePos.x = 0;
	movePos.y = 0;
}

void Layer::Update(char* keys, char* oldkeys)
{
	oldMouseX = MouseX;
	oldMouseY = MouseY;

	// マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);

	if (keys[KEY_INPUT_0] == 1 && oldkeys[KEY_INPUT_0] == 0)
	{
		if (freamNumX < 2)
		{
			freamNumX++;
		}
		else
		{
			freamNumX = 0;
		}
	}

	//押されたら
	if ((button & MOUSE_INPUT_LEFT) != 0)
	{


	}

	//選択状態に
	//isSelect = true;

	// 左ボタンが押されたり離されたりしていたら描画するかどうかのフラグを立てて、座標も保存する
	if (GetMouseInputLog2(&button, &clickX, &clickY, &logType, TRUE) == 0)
	{
		/*if((button & MOUSE_INPUT_LEFT) != 0)
		{

		}*/

		isSelect = true;

	}

	if (isSelect == true)
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//マウスが押されている
			movePos.x = MouseX - oldMouseX;
			movePos.y = MouseY - oldMouseY;

			//layerPos += movePos;

			//ブロックの座標を設定

			for (int i = 0; i < layerBlockWidth; i++)
			{
				for (int j = 0; j < layerBlockHeight; j++)
				{
					blocks_[i][j]->SetMove(movePos);
				}
			}
		}
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{

		}
		else // 押されていない
		{
			movePos.x = 0;
			movePos.y = 0;

			for (int i = 0; i < layerBlockWidth; i++)
			{
				for (int j = 0; j < layerBlockHeight; j++)
				{
					blocks_[i][j]->SetMove(movePos);
				}
			}
		}
	}

	for (int i = 0; i < layerBlockWidth; i++)
	{
		for (int j = 0; j < layerBlockHeight; j++)
		{
			blocks_[i][j]->Update();
		}
	}
}

void Layer::Draw()
{
	DrawBox(layerPos.x, layerPos.y, layerPos.x + layerWidth, layerPos.y + layerHeight, GetColor(255, 255, 255), false);

	for (int i = 0; i < layerBlockWidth; i++)
	{
		for (int j = 0; j < layerBlockHeight; j++)
		{
			blocks_[i][j]->Draw();
		}
	}


}

//
//void Layer::SetBlock(int y, int x, BlockType block)
//{
//	this->blockTypes[y][x] = block;
//}
//
//BlockType Layer::GetBlock(int y, int x)
//{
//	return this->blockTypes[y][x];
//}




