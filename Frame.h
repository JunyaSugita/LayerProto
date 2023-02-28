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

	Vector2 freamPos[layerFrameHeight][layerFrameWidth] = {};
	//int isLayer[layerFrameHeight][layerFrameWidth] = {};
	Vector2 layerPos_[layerFrameHeight][layerFrameWidth] = {};
	float isLayerTimer[layerFrameHeight][layerFrameWidth] = {};
	float safeLayerTime[layerFrameHeight] = {0,0,0};

	//Vector2 safeSelectNum;
	bool isSelect_ = false;

	bool isSetLayer = false;
	
public:

	void SetFreamLayerNum();

	bool GetisSelect();


private:

	int FrameHasLayer[layerFrameWidth][layerFrameHeight];

	//bool isFrontSet[layerFrameWidth][layerFrameHeight];
	
	int button;
	int clickX;
	int clickY;
	int logType;

	bool isFrontLayer = false;

	Vector2 frontVec;
	Vector2 checkNum;

	Vector2 compareNum = { -1,-1 };
	Vector2 compareNum2 = { -1,-1 };
	Vector2 compareNum3 = { -1,-1 };

	//Vector2 compareNum[layerFrameNum] = {};

	bool isFreamDepth[layerFrameNum] = { false,false,false };
	bool isFrameMax = false;

};

