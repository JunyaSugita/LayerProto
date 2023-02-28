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

	static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;

	static const int depthLayerNum = 5;

	static const float layerWidth;
	static const float layerHeight;

public: //メンバ関数

	Layer();
	~Layer();
	void Initialize(int widthNum, int heightNum);
	void Update(char* keys, char* oldkeys, int mouseX, int mouseY, int oldMouseX, int oldMouseY, Vector2 freamPos[][layerFrameWidth]);
	void Draw();
	void Delete();

	void SerchFrame();

	//重なっている他のレイヤーがあるときに、自分の時間が他のレイヤーより小さいかどうか
	void CheckLayerDepth(float layerTime[][layerFrameHeight], Vector2 layerPos[][layerFrameHeight]);

private: //メンバ変数
	////ブロックの状態9x9
	//BlockType blockTypes[layerBlockHeight][layerBlockWidth] = {};
	////ブロックの座標
	//Vector2 blockPos[layerBlockHeight][layerBlockWidth] = {};

	//そのレイヤーがいるフレームの番号
	int freamNumX;
	int freamNumY;

	//レイヤーの座標
	Vector2 layerPos_;

	//選択されているかどうか
	bool isSelect = false;
	//移動量
	Vector2 movePos;

	//レイヤーの中心座標
	Vector2 layerCenterPos;

	//レイヤーの深さ
	int depthLayer;

	//最前面フラグ
	bool isFront_;
	//最前面のカウント
	int frontCount_;

	//枠にはめたフラグ
	bool isSetPos_;

	Vector2 freamPos_[layerFrameHeight][layerFrameWidth] = {};

	//レイヤーが置かれた時間
	float layerTimer_ = 0.99f;

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

	void SetPos(Vector2 pos) { layerPos_ = pos; };
	Vector2 GetLayerPos() { return  layerPos_; }

	bool GetIsSelect() { return isSelect; }
	void SetIsSelect(int isSelected) { isSelect = isSelected; }

	int GetFrameNumX() { return freamNumX; }
	int GetFrameNumY() { return freamNumY; }

	Vector2 GetLayerCenterPos() { return layerCenterPos; }

	bool GetIsFront() { return isFront_; }
	void SetIsFront(bool isFront) { isFront_ = isFront; }

	//セットされた時
	bool GetisSetPos() { return isSetPos_; }
	void SetisSetPos(bool isSetPos) {  isSetPos_ = isSetPos; }

	//深度
	int GetFrontCount() { return frontCount_; }
	void SetFrontCount(int frontCount) { frontCount_ = frontCount; }

	float GetLayerTimer() { return layerTimer_; }
	void SetLayerTimer(float layerTimer) { layerTimer_ = layerTimer; }
};


