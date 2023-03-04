#pragma once
#include "DxLib.h"
#include "Vector2.h"

enum map
{
	NONE,	//空間
	BLOCK,	//ブロック
	GOAL,	//ゴール
	TRAP,	//トゲ
	NOLAYER,//レイヤーが何もない枠
	PLAYER,	//プレイヤーの場所
	NOLAYER_PLAYER,	//レイヤーが無い場所でのプレイヤーの位置
	NULL_BLOCK = -858993460, //未入力の空間
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
	void Update(int mouseX, int mouseY,int windowWidth,int windowHeight);

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


	void MoveLayer(Vector2 start,Vector2 end);

	bool GetIsSelect() {
		return isSelect_;
	};

	/// <summary>
	/// プレビューのアップデート
	/// </summary>
	void PreviewUpdate();

	/// <summary>
	/// プレビューのdraw
	/// </summary>
	void PreviewDraw();

public:

	//固定値
	static const int MAP_X = 27;	//マップの横ブロック数
	static const int MAP_Y = 27;	//マップの縦ブロック数
	static const int BLOCK_SIZE = 30;		//ブロックサイズ
	static const int MAX_OVERLAP = 2;		//レイヤーを何層まで重ねられるか

private:
	//マップ[y][x](数値は仮)
	int map_[MAX_OVERLAP][MAP_Y][MAP_X];

	Vector2 mouseStart;
	bool isSelect_;

	//プレビュー関連
	int preview_[9][9] = {};
	int mouseX_, mouseY_;
	int layerNum_;

};

