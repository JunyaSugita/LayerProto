#pragma once
#include "Frame.h"

class Select
{
public:
	
	void Initialize(Layer* layer);
	void Update();
	void Draw();

	bool Search();

private:

	//�}�E�X���W
	int MouseX;
	int MouseY;

	//���C���[���Ǘ����Ă���t���[��
	Layer* layer_ = nullptr;

	//�}�E�X�����݂���t���[���̐�
	int frameNumX;
	int frameNumY;

	bool isSelect = false;

public:

	void SetSelectLayer();


};

