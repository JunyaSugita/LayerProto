#pragma once
#include"Layer.h"

class Frame
{
private:
	//��g�̏c�Ɖ��̐��i���j
	int layerFrameWidth = 3;
	int layerFrameHeight = 1;

	
public:
	void Initialize();

	int GetLayerFrameWidth() { return layerFrameWidth; }
	int GetLayerFrameHeight() { return layerFrameHeight; }

	//�t���[���̒��̃��C���[�̔z��
	std::list<Layer> layersInTheFrame[3][3] = {};
};

