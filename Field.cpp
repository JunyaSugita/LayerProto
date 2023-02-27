#include "Field.h"
#include "StageCSVManager.h"
#include <assert.h>
#include "Player.h"

//無視
Field::Field() {}

//delete処理
Field::~Field()
{

}

void Field::Initialize(int map)
{
	//マップの読み込み(未実装のためマジックナンバーを直入れ)

	int mapTemp[MAX_OVERLAP][MAP_Y][MAP_X];


	for (int y = 0; y < Frame::GetLayerFrameHeight() * Layer::layerBlockHeight; y++)
	{
		for (int x = 0; x < Frame::GetLayerFrameWidth() * Layer::layerBlockWidth; x++)
		{
			int Y = y / Layer::layerBlockHeight;
			int X = x / Layer::layerBlockWidth;

			std::list<std::unique_ptr<Layer>>& layer = StageCSVManager::GetInstance().frameData.layersInTheFrame[Y][X];
			int count = 0;

			//重なりがあればその分も読み込み
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
	for (int k = 0; k < MAX_OVERLAP; k++) {
		for (int i = 0; i < MAP_Y; i++) {
			for (int j = 0; j < MAP_X; j++) {
				map_[k][i][j] = mapTemp[k][i][j];
			}
		}
	}

	mouseStart = { -1,-1 };
	isSelect_ = false;
}

void Field::Update(int mouseX, int mouseY, int windowWidth, int windowHeight)
{
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (mouseStart.x == -1) {
			mouseStart = { (float)(mouseX / (windowWidth / Frame::GetLayerFrameWidth())),(float)(mouseY / (windowHeight / Frame::GetLayerFrameHeight())) };
		}
		isSelect_ = true;
	}
	else if (mouseStart.x != -1) {
		if (mouseStart.x >= 0 && mouseStart.x <= 2 && mouseStart.y >= 0 && mouseStart.y <= 2) {
			MoveLayer(mouseStart, { (float)(mouseX / (windowWidth / Frame::GetLayerFrameWidth())),(float)(mouseY / (windowHeight / Frame::GetLayerFrameHeight())) });
		}
		mouseStart = { -1,-1 };
		isSelect_ = false;
	}


}

void Field::Draw()
{
	for (int k = 0; k < MAX_OVERLAP; k++) {
		for (int i = 0; i < MAP_Y; i++) {
			for (int j = 0; j < MAP_X; j++) {
				int Light = GetLayerNum(j / 9, i / 9);
				//マップの数字によって描画する
				switch (map_[k][i][j])
				{
				case BLOCK:
					//ブロックなら白で描画
					if (k == Light) {
						DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(255, 255, 255), true);
					}
					else {
						DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(100, 100, 100), true);
					}
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
	assert("xに0~2以外の数字が入っています", x >= 0 && x <= 2);
	assert("yに0~2以外の数字が入っています", y >= 0 && y <= 2);

	//レイヤーの層(最前面から)
	for (int i = MAX_OVERLAP - 1; i >= 0; i--) {
		//レイヤーYから
		for (int j = y * 9; j < 9 * (y + 1); j++) {
			//レイヤーXから
			for (int k = x * 9; k < 9 * (x + 1); k++) {
				if (map_[i][j][k] != -858993460) {
					//1つでも0以外があればレイヤーがある層を返す
					return i;
				}
			}
		}

	}
	//無ければ0層を返す
	return 0;
}

void Field::MoveLayer(Vector2 start, Vector2 end)
{
	Player* player = Player::GetInctance();

	//アサート
	assert("start.xに0~2以外の数字が入っています", start.x >= 0 && start.x <= 2);
	assert("start.yに0~2以外の数字が入っています", start.y >= 0 && start.y <= 2);
	assert("end.xに0~2以外の数字が入っています", end.x >= 0 && end.x <= 2);
	assert("end.yに0~2以外の数字が入っています", end.y >= 0 && end.y <= 2);

	//取るフレームの層を出す
	int tempMap[9][9];
	int temp = GetLayerNum(start.x, start.y);

	//プレイヤーの情報をとる
	if (start.x * 270 <= player->GetPos().x && (start.x + 1) * 270 >= player->GetPos().x && start.y * 270 <= player->GetPos().y && (start.y + 1) * 270 >= player->GetPos().y) {
		map_[temp][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = 9;
	}
	//消しながらtempMapに情報を移す
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			tempMap[i][j] = map_[temp][i + (int)start.y * 9][j + (int)start.x * 9];
			map_[temp][i + (int)start.y * 9][j + (int)start.x * 9] = -858993460;
		}
	}

	//最前面を探す
	temp = GetLayerNum(end.x, end.y);
	assert("レイヤーの重なり最大値5を超えています", temp < MAX_OVERLAP);
	//tempMapから情報を移す
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			map_[temp + 1][i + (int)end.y * 9][j + (int)end.x * 9] = tempMap[i][j];
			if (map_[temp + 1][i + (int)end.y * 9][j + (int)end.x * 9] == 9) {
				player->SetPlayerMapPos({ (float)(i + (int)end.y * 9), (float)(j + (int)end.x * 9) });
				map_[temp + 1][i + (int)end.y * 9][j + (int)end.x * 9] = 0;
			}
		}
	}

}


