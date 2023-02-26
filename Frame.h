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
	void Update(char* keys, char* oldkeys,int mouseX,int mouseY,int oldMouseX,int oldMouseY);
	void Draw();

	void FrameSerch();

	~Frame();

	static int GetLayerFrameWidth() { return layerFrameWidth; }
	static int GetLayerFrameHeight() { return layerFrameHeight; }

	//�t���[���̒��̃��C���[�̔z��
	std::list<std::unique_ptr <Layer>> layersInTheFrame[layerFrameHeight][layerFrameWidth] = {};
	std::vector<std::vector<std::unique_ptr <Layer>>> layers_;

	Vector2 freamPos[layerFrameHeight][layerFrameWidth] = {};

public:

	void SetFreamLayerNum();

private:

	int button;
	int clickX;
	int clickY;
	int logType;


};

