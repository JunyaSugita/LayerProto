#include "Select.h"
#include "DxLib.h"

void Select::Initialize(Layer* layer)
{
	layer_ = layer;
}

void Select::Update()
{
	// �}�E�X�̈ʒu���擾
	GetMousePoint(&MouseX, &MouseY);

	//���C���[�̉E��
	float layerX = Layer::layerWidth * layer_->GetFrameNumX();
	float layerY = Layer::layerHeight * layer_->GetFrameNumY();

	//�����}�E�X������ʒu�Ƀ��C���[������Ȃ�I������
	//���C���[�͈͓̔��ɂ��邩�ǂ���
	if(MouseX >= layerX && MouseX <= layerX + Layer::layerWidth)
	{
		isSelect = true;
	}
}

bool Select::Search()
{
	//�}�E�X�����݂���t���[���̐�
	frameNumX = MouseX / Layer::layerWidth;
	frameNumY = MouseY / Layer::layerHeight;

	return true;
}

void Select::Draw()
{

}