#pragma once
#include"Layer.h"

class Frame
{
private:
	//��g�̏c�Ɖ��̐��i���j
	static const int layerFrameWidth = 3;
	static const int layerFrameHeight = 3;

	//�}�E�X���W
	int MouseX;
	int MouseY;

	//�I���������̃}�E�X�̍��W
	int oldMouseX;
	int oldMouseY;


	//�I�����Ă��邩�ǂ���
	bool isSelect = false;

public:
	void Initialize();
	void Update(char* keys, char* oldkeys);
	void Draw();

	~Frame();

	int GetLayerFrameWidth() { return layerFrameWidth; }
	int GetLayerFrameHeight() { return layerFrameHeight; }

	//�t���[���̒��̃��C���[�̔z��
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

