#pragma once
#include"Layer.h"

class Frame
{
private:
	//大枠の縦と横の数（仮）
	static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;
	static const int layerFrameNum = layerFrameWidth * layerFrameHeight;

public:
	void Initialize();
	void Update(char* keys, char* oldkeys,int mouseX,int mouseY,int oldMouseX,int oldMouseY);
	void Draw();

	~Frame();

	static int GetLayerFrameWidth() { return layerFrameWidth; }
	static int GetLayerFrameHeight() { return layerFrameHeight; }

	//フレームの中のレイヤーの配列
	std::list<std::unique_ptr <Layer>> layersInTheFrame[layerFrameHeight][layerFrameWidth] = {};
	std::vector<std::vector<std::unique_ptr <Layer>>> layers_;

	//各枠の座標
	Vector2 freamPos[layerFrameHeight][layerFrameWidth] = {};
	
	//各レイヤーの座標
	Vector2 layerPos_[layerFrameHeight][layerFrameWidth] = {};
	//各レイヤーの時間
	float isLayerTimer[layerFrameHeight][layerFrameWidth] = {};

	//レイヤーを選んでいるかどうか
	bool isSelect_ = false;
	//レイヤーをはめたフラグ
	bool isSetLayer = false;
	
public:

	void SetFreamLayerNum();

	bool GetisSelect();


private:

	//マウス類の変数
	int button;
	int clickX;
	int clickY;
	int logType;
};

