#pragma once
#include "Vector2.h"

//レイヤーの中の一個のブロック
class Block
{

public: //クラス内グローバル定数

	enum BlockType
	{
		NONE,        //なにもない
		LAYER_BLOCK, //レイヤーと一緒に動くブロック
		FIXED_BLOCK, //固定ブロック
		NOLAYER_BLOCK//枠はあるけどレイヤー無い用
	};

	//const float BLOCK_SIZE = 30.0f;
	static const float BLOCK_SIZE;
	const float BLOCK_RADIUS = BLOCK_SIZE / 2;

public: //メンバ関数
	void Initialize();
	void Update();
	void Draw();

private: //メンバ変数
	//形状
	BlockType type_;
	//座標
	Vector2 pos_;

	Vector2 move_;

public: //アクセッサ

	Vector2 GetPos() { return pos_; }

	//CSVファイル読み込みで得た、形状を各ブロックにセットする
	void SetType(BlockType type) { type_ = type; };

	void SetPos(Vector2 pos) { pos_ = pos; };

	void SetMove(Vector2 move) { move_ = move; }
};