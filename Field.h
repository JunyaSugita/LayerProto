#pragma once
#include "DxLib.h"
#include "Vector2.h"

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

	/// <summary>
	/// マップ情報の取得
	/// </summary>
	/// <param name="pos"> 取得したい座標 </param>
	/// <returns> 指定座標のブロックの種類番号 </returns>
	int GetMap(Vector2 pos);

	/// <summary>
	/// 指定のレイヤーの場所が何層目あるか
	/// </summary>
	/// <param name="x"> レイヤー座標 </param>
	/// <param name="y"> レイヤー座標 </param>
	/// <returns> 指定の場所にレイヤーが何層あるか </returns>
	int GetLayerNum(int x,int y);

public:

	//固定値
	static const int MAP_X = 27;	//マップの横ブロック数
	static const int MAP_Y = 27;	//マップの縦ブロック数
	const int BLOCK_SIZE = 30;		//ブロックサイズ
	static const int MAX_OVERLAP = 5;		//レイヤーを何層まで重ねられるか

private:
	//マップ[y][x](数値は仮)
	int map_[5][MAP_Y][MAP_X];



};

