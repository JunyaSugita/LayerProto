#pragma once
#include"Layer.h"

class Frame
{
private:
	//大枠の縦と横の数（仮）
	static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;

	
public:
	void Initialize();
	void Update();
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
};

