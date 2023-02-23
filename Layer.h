#pragma once
#include<list>

enum Block
{
	LAYER_BLOCK = 1, //レイヤーと一緒に動くブロック
	FIXED_BLOCK, //固定ブロック
};

//一枚のレイヤー
class Layer
{
public:
	//一枚のレイヤーのブロック数
	static const int layerBlockWidth = 9;
	static const int layerBlockHeight = 9;

private:
	//ブロックの状態9x9
	Block blocks[layerBlockHeight][layerBlockWidth] = {};

public:
	//ブロックの状態をセット
	void SetBlock(int y, int x, Block block);
	//ブロックの状態をゲット
	Block GetBlock(int y, int x);
};


