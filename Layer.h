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

	static const float layerWidth;
	static const float layerHeight;

public: //メンバ関数

	Layer();
	~Layer();
	void Initialize(int widthNum, int heightNum);
	void Update(char* keys, char* oldkeys, int mouseX, int mouseY, int oldMouseX, int oldMouseY);
	void Draw();
	void Delete();

private: //メンバ変数
	////ブロックの状態9x9
	//BlockType blockTypes[layerBlockHeight][layerBlockWidth] = {};
	////ブロックの座標
	//Vector2 blockPos[layerBlockHeight][layerBlockWidth] = {};

	//そのレイヤーがいるフレームの番号
	int freamNumX;
	int freamNumY;

	//レイヤーの座標
	Vector2 layerPos;

	//選択されているかどうか
	bool isSelect = false;
	//移動量
	Vector2 movePos;

	int button;
	int clickX;
	int clickY;
	int logType;


public: //アクセッサ
	////ブロックの状態をセット
	//void SetBlock(int y, int x, BlockType block);
	////ブロックの状態をゲット
	//BlockType GetBlock(int y, int x);

	std::vector<std::vector<std::unique_ptr <Block>>> blocks_;

	void SetPos(Vector2 pos) { layerPos = pos; };
	Vector2 GetLayerPos() { return  layerPos; }

	bool GetIsSelect() { return isSelect; }
	void SetIsSelect(int isSelected) { isSelect = isSelected; }

	int GetFrameNumX() { return freamNumX; }
	int GetFrameNumY() { return freamNumY; }

};


