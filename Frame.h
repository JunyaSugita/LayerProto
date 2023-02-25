#pragma once
#include"Layer.h"

class Frame
{
private:
	//大枠の縦と横の数（仮）
	static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;

	//マウス座標
	int MouseX;
	int MouseY;

	//選択した時のマウスの座標
	int oldMouseX;
	int oldMouseY;


	//選択しているかどうか
	bool isSelect = false;

public:
	void Initialize();
	void Update(char* keys, char* oldkeys);
	void Draw();

	~Frame();

	int GetLayerFrameWidth() { return layerFrameWidth; }
	int GetLayerFrameHeight() { return layerFrameHeight; }

	//フレームの中のレイヤーの配列
	std::list<Layer> layersInTheFrame[layerFrameHeight][layerFrameWidth] = {};
	//std::vector<Layer> layersInTheFrame[layerFrameHeight][layerFrameWidth] = {};
	std::vector<std::vector<std::unique_ptr <Layer>>> layers_;

public:

	void SetFreamLayerNum();

private:


	int button;
	int clickX;
	int clickY;
	int logType;


};

