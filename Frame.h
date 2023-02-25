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

	int GetLayerFrameWidth() { return layerFrameWidth; }
	int GetLayerFrameHeight() { return layerFrameHeight; }

	//フレームの中のレイヤーの配列
	//std::list<Layer> layersInTheFrame[layerFrameHeight][layerFrameWidth] = {};

public:

	void SetFreamLayerNum();
};

