#pragma once
#include"Layer.h"

class Frame
{
private:
	//��g�̏c�Ɖ��̐��i���j
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

	//�t���[���̒��̃��C���[�̔z��
	std::list<std::unique_ptr <Layer>> layersInTheFrame[layerFrameHeight][layerFrameWidth] = {};
	std::vector<std::vector<std::unique_ptr <Layer>>> layers_;

	//�e�g�̍��W
	Vector2 freamPos[layerFrameHeight][layerFrameWidth] = {};
	
	//�e���C���[�̍��W
	Vector2 layerPos_[layerFrameHeight][layerFrameWidth] = {};
	//�e���C���[�̎���
	float isLayerTimer[layerFrameHeight][layerFrameWidth] = {};

	//���C���[��I��ł��邩�ǂ���
	bool isSelect_ = false;
	//���C���[���͂߂��t���O
	bool isSetLayer = false;
	
public:

	void SetFreamLayerNum();

	bool GetisSelect();


private:

	//�}�E�X�ނ̕ϐ�
	int button;
	int clickX;
	int clickY;
	int logType;
};

