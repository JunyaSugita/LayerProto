#pragma once
#include"Layer.h"

class Frame
{
private:
	//��g�̏c�Ɖ��̐��i���j
	static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;

	
public:
	void Initialize();

	int GetLayerFrameWidth() { return layerFrameWidth; }
	int GetLayerFrameHeight() { return layerFrameHeight; }

	//�t���[���̒��̃��C���[�̔z��
	//std::list<Layer> layersInTheFrame[layerFrameHeight][layerFrameWidth] = {};

public:

	void SetFreamLayerNum();
};

