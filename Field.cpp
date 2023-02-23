#include "Field.h"

//無視
Field::Field(){}

//delete処理
Field::~Field()
{

}

void Field::Initialize(int map)
{
	//マップの読み込み(未実装のためマジックナンバーを直入れ)
	int mapTemp[MAP_Y][MAP_X] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,0,1,0,0},
		{0,0,0,1,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
	};
	//代入
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			map_[i][j] = mapTemp[i][j];
		}
	}
}

void Field::Update()
{

}

void Field::Draw()
{
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			//マップの数字によって描画する
			switch (map_[i][j])
			{
			case BLOCK:
				//ブロックなら白で描画
				DrawBox(j * BLOCK_SIZE,i * BLOCK_SIZE,j * BLOCK_SIZE + BLOCK_SIZE,i * BLOCK_SIZE + BLOCK_SIZE,GetColor(255,255,255),true);
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


