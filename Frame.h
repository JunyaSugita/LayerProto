#pragma once
#include"Layer.h"

class Frame
{
private:
	//大枠の縦と横の数（仮）
	int layerFrameWidth = 3;
	int layerFrameHeight = 1;

	
public:
	void Initialize();

	int GetLayerFrameWidth() { return layerFrameWidth; }
	int GetLayerFrameHeight() { return layerFrameHeight; }

	//フレームの中のレイヤーの配列
	std::list<Layer> layersInTheFrame[3][3] = {};
};

