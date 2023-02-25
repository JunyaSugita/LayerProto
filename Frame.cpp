#include "Frame.h"

void Frame::Initialize()
{
	for (int i = 0; i < this->GetLayerFrameHeight(); i++)
	{
		for (int j = 0; j < this->GetLayerFrameWidth(); j++)
		{
			this->layersInTheFrame[i][j].clear();
		}
	}

	for(int i = 0; i < layerFrameWidth; i++)
	{
		//�u���b�N�^�����Ă��̃x�N�^��ǉ�(�s��ł���i��)
		layers_.push_back(std::vector<std::unique_ptr <Layer>>());

		for(int j = 0; j < layerFrameHeight; j++)
		{
			std::unique_ptr <Layer> layer_;
			layer_ = std::make_unique<Layer>();
			layer_->Initialize();
			//�u���b�N�̗v�f��ǉ�
			layers_[i].push_back(std::move(layer_));
		}
	}

	//���W�̏�����
	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			Vector2 pos;
			//�u���b�N�̍��W��ݒ�
			if(i >= 0)
			{
				pos.x = i * Layer::layerWidth;

			}
			if(j >= 0)
			{
				pos.y = j * Layer::layerHeight;
			}

			layers_[i][j]->SetPos(pos);

		}
	}
}

void Frame::Update()
{


}

void Frame::Draw()
{
	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			layers_[i][j]->Draw();
		}
	}

}

Frame::~Frame()
{
	//for(int i = 0; i < this->GetLayerFrameHeight(); i++)
	//{
	//	for(int j = 0; j < this->GetLayerFrameWidth(); j++)
	//	{
	//		//���C���[�̃C�e���[�^
	//		std::list<Layer>::iterator it;
	//		it = layersInTheFrame[i][j].begin();
	//		//�f�X�g���N�^���Ăяo��
	//		it->~Layer();
	//		//���ɐi�߂�
	//		it++;
	//	}
	//}
}
