#include "Field.h"
#include "StageCSVManager.h"

//無視
Field::Field() {}

//delete処理
Field::~Field()
{

}

void Field::Initialize(int map)
{
	//マップの読み込み(未実装のためマジックナンバーを直入れ)

	int mapTemp[MAX_OVERLAP][MAP_Y][MAP_X] /*= {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,0,1,0,0},
		{0,0,0,1,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	}*/;


	for (int y = 0; y < Frame::GetLayerFrameHeight() * Layer::layerBlockHeight; y++)
	{
		for (int x = 0; x < Frame::GetLayerFrameHeight() * Layer::layerBlockWidth; x++)
		{
			int Y = y / Layer::layerBlockHeight;
			int X = x / Layer::layerBlockWidth;

			std::list<std::unique_ptr<Layer>>& layer = StageCSVManager::GetInstance().frameData.layersInTheFrame[Y][X];
			auto itr = layer.begin();
			int count = 0;


			for (auto itr = layer.begin(); itr != layer.end(); itr++) {
				if (layer.size())
				{
					Block::BlockType block = itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->GetType();
					//マップをセット
					mapTemp[count][y][x] = block;
				}
				else
				{
					mapTemp[count][y][x] = Block::BlockType::NOLAYER_BLOCK;
				}
				count++;
			}
		}
	}


	//代入
	for (int k = 0; k < MAX_OVERLAP;k++) {
		for (int i = 0; i < MAP_Y; i++) {
			for (int j = 0; j < MAP_X; j++) {
				map_[k][i][j] = mapTemp[k][i][j];
			}
		}
	}
}

void Field::Update()
{

}

void Field::Draw()
{
	for (int k = 0; k < MAX_OVERLAP; k++) {
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
				//マップの数字によって描画する
				switch (map_[k][i][j])
				{
				case BLOCK:
					//ブロックなら白で描画
					DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(100, 100, 100), true);
					break;

				case GOAL:
					//ゴールなら赤で描画
					DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(200, 100, 100), true);
					break;

				case NONE:
				default:
					break;
				}
			}
		}
	}
}

int Field::GetMap(Vector2 pos)
{
	for (int i = 0; i < MAX_OVERLAP; i++) {
		switch (map_[i][(int)pos.y][(int)pos.x]) {
		case NONE:
			break;
		case BLOCK:
			return BLOCK;
			break;
		case GOAL:
			return GOAL;
			break;
		}

	}
	return 0;
}

int Field::GetLayerNum(int x, int y)
{
	//レイヤーの層(最前面から)
	for (int i = MAX_OVERLAP - 1; i >= 0; i--) {
		//レイヤーYから
		for (int j = y * 9; j < 9; j++) {
			//レイヤーXから
			for (int k = x * 9 ; k < 9; k++) {
				if (map_[i][j][k] != 0) {
					//1つでも0以外があればレイヤーがある層を返す
					return i;
				}
			}
		}

	}
	//無ければ0層を返す
	return 0;
}


