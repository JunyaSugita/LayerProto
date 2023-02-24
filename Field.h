#pragma once
#include "DxLib.h"

enum map
{
	NONE,	//空間
	BLOCK,	//ブロック
	GOAL,	//ゴール
};

class Field
{
public:
	Field();
	~Field();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="map"> マップcsv(未実装) </param>
	void Initialize(int map = 0);

	/// <summary>
	/// updata
	/// </summary>
	void Update();

	/// <summary>
	/// draw
	/// </summary>
	void Draw();

private:
	//固定値
	static const int MAP_X = 27;	//マップの横ブロック数
	static const int MAP_Y = 27;		//マップの縦ブロック数
	const int BLOCK_SIZE = 30;		//ブロックサイズ

	//マップ[y][x](数値は仮)
	int map_[MAP_Y][MAP_X];

};

