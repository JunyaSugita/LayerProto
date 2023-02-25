#pragma once
#include<list>
#include"Block.h"
#include <memory>
#include <vector>

//enum BlockType
//{
//	NONE,        //なにもない
//	LAYER_BLOCK, //レイヤーと一緒に動くブロック
//	FIXED_BLOCK, //固定ブロック
//};

//一枚のレイヤー
class Layer
{
	using BlockType = Block::BlockType;

public: //クラス内グローバル定数

	//一枚のレイヤーのブロック数
	static const int layerBlockWidth = 9;
	static const int layerBlockHeight = 9;

public: //メンバ関数

	Layer();
	~Layer();
	void Initialize();
	void Update(char* keys, char* oldkeys);
	void Draw();
	void Delete();

private: //メンバ変数
	//ブロックの状態9x9
	BlockType blockTypes[layerBlockHeight][layerBlockWidth] = {};
	//ブロックの座標
	Vector2 blockPos[layerBlockHeight][layerBlockWidth] = {};

	//ブロックの二次元配列
	Block* blocks_[layerBlockHeight][layerBlockWidth];
	//std::vector<std::vector<std::unique_ptr <Block>>> blocks_;

	//そのレイヤーがいるフレームの番号
	int freamNum;

	//キー入力の待ち時間
	int waitTimer = 20;

public: //アクセッサ
	//ブロックの状態をセット
	void SetBlock(int y, int x, BlockType block);
	//ブロックの状態をゲット
	BlockType GetBlock(int y, int x);
};


