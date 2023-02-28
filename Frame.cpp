#include "Frame.h"
#include "DxLib.h"
#include "Player.h"

void Frame::Initialize()
{
	//�������
	for (int i = 0; i < this->GetLayerFrameHeight(); i++)
	{
		for(int j = 0; j < this->GetLayerFrameWidth(); j++)
		{
			this->layersInTheFrame[i][j].clear();

			if (layers_.size())
			{
				layers_[i].clear();
			}
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
			layer_->Initialize(i, j);
			//���C���[�̗v�f��ǉ�
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
				pos.y = i * Layer::layerWidth;

			}
			if(j >= 0)
			{
				pos.x = j * Layer::layerHeight;
			}

			layers_[i][j]->SetPos(pos);

		}
	}

	//�g�̒�����ݒ�
	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			if(i >= 0)
			{
				freamPos[i][j].y = (i * Layer::layerWidth);

			}
			if(j >= 0)
			{
				freamPos[i][j].x = (j * Layer::layerWidth);
			}
		}
	}

	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(i == j)
			{
				layers_[0][1]->blocks_[i][j]->SetType(Block::FIXED_BLOCK);
				layers_[0][2]->blocks_[i][j]->SetType(Block::NOLAYER_BLOCK);
				layers_[2][2]->blocks_[i][j]->SetType(Block::LAYER_BLOCK);
			}
		}
	}

}

void Frame::Update(char* keys, char* oldkeys, int mouseX, int mouseY, int oldMouseX, int oldMouseY)
{
	//���C���[��I�����鏈��
	if(GetMouseInputLog2(&button, &clickX, &clickY, &logType, TRUE) == 0)
	{
		if((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			for(int i = 0; i < layerFrameWidth; i++)
			{
				for(int j = 0; j < layerFrameHeight; j++)
				{
					//�}�E�X�ƃ��C���[�̑I������
					if(clickX > layers_[i][j]->GetLayerPos().x && clickX < layers_[i][j]->GetLayerPos().x + Layer::layerWidth)
					{
						if(clickY > layers_[i][j]->GetLayerPos().y && clickY < layers_[i][j]->GetLayerPos().y + Layer::layerHeight)
						{
							//�����I������Ă��Ȃ��Ƃ�
							if(layers_[i][j]->GetIsSelect() == false && isSelect_ == false)
							{
								//�őO�ʂ�I���������̏���
								if(layers_[i][j]->GetFrontCount() == 1)
								{
									//���C���[�̑I���t���O��ON��
									layers_[i][j]->SetIsSelect(true);
								}
							}
						}
					}
				}
			}
		}
	}

	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			//�����N���b�N����Ă���Ƃ�
			if(layers_[i][j]->GetIsSelect() == true)
			{
				//���N���b�N�������ꑱ���Ă���Ƃ�
				if((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
				{
				}
				else
				{
					//������Ă��Ȃ����
					//�g�Ƀt���[�����͂߂�
					layers_[i][j]->SerchFrame();
				}
			}
		}
	}

	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			//�e�t���[�����Ԃ��擾
			isLayerTimer[i][j] = layers_[i][j]->GetLayerTimer();
		}
	}

	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			//�ǂ����g���͂߂��̂Ȃ�
			//�͂߂��t���O��ON�ɂ���B
			if(layers_[i][j]->GetisSetPos() == true)
			{
				isSetLayer = true;
			}
		}
	}

	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			//�����ǂ����̃��C���[��g�ɂ͂߂��̂Ȃ�
			if(isSetLayer == true)
			{
				//�e���C���[�̐[���𒲐�����
				layers_[i][j]->CheckLayerDepth(isLayerTimer, layerPos_);
				//�Ō�̃��C���[�������I������Ȃ�
				if(i == layerFrameWidth - 1 && j == layerFrameHeight - 1)
				{
					//�͂߂��t���O��OFF�ɂ���B
					isSetLayer = false;
				}
			}
		}
	}

	//���C���[�̍X�V(���ɒu���Ă����Ȃ��ƃo�O��)
	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			layers_[i][j]->Update(keys, oldkeys, mouseX, mouseY, oldMouseX, oldMouseY, freamPos);
			layerPos_[i][j] = layers_[i][j]->GetLayerPos();
		}
	}
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


	/*DrawFormatString(0, 380, GetColor(255, 255, 255), "layers_[0][0] : %d", layers_[0][0]->GetIsSelect());
	DrawFormatString(0, 400, GetColor(255, 255, 255), "layers_[0][1] : %d", layers_[0][1]->GetIsSelect());
	DrawFormatString(0, 420, GetColor(255, 255, 255), "layers_[0][2] : %d", layers_[0][2]->GetIsSelect());

	DrawFormatString(0, 500, GetColor(255, 255, 255), "layers_[1][1] : %d", layers_[1][1]->GetIsSelect());

	DrawFormatString(0, 650, GetColor(255, 255, 255), "frontCount_[0][0] : %d", layers_[0][0]->GetFrontCount());
	DrawFormatString(0, 670, GetColor(255, 255, 255), "frontCount_[0][1] : %d", layers_[0][1]->GetFrontCount());
	DrawFormatString(0, 690, GetColor(255, 255, 255), "frontCount_[0][2] : %d", layers_[0][2]->GetFrontCount());
	DrawFormatString(0, 730, GetColor(255, 255, 255), "frontCount_[1][1] : %d", layers_[1][1]->GetFrontCount());
	DrawFormatString(0, 770, GetColor(255, 255, 255), "frontCount_[2][2] : %d", layers_[2][2]->GetFrontCount());*/
	/*DrawFormatString(0, 100, GetColor(255, 255, 255), "isLayerTimer[0][0] : %f", isLayerTimer[0][0]);
	DrawFormatString(0, 120, GetColor(255, 255, 255), "isLayerTimer[0][1] : %f", isLayerTimer[0][1]);
	DrawFormatString(0, 140, GetColor(255, 255, 255), "isLayerTimer[0][2] : %f", isLayerTimer[0][2]);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "isLayerTimer[1][0] : %f", isLayerTimer[1][0]);
	DrawFormatString(0, 180, GetColor(255, 255, 255), "isLayerTimer[1][1] : %f", isLayerTimer[1][1]);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "isLayerTimer[1][2] : %f", isLayerTimer[1][2]);
	DrawFormatString(0, 220, GetColor(255, 255, 255), "isLayerTimer[2][0] : %f", isLayerTimer[2][0]);
	DrawFormatString(0, 240, GetColor(255, 255, 255), "isLayerTimer[2][1] : %f", isLayerTimer[2][1]);
	DrawFormatString(0, 260, GetColor(255, 255, 255), "isLayerTimer[2][2] : %f", isLayerTimer[2][2]);

	DrawFormatString(0, 300, GetColor(255, 255, 255), "isSelect[0][0] : %d", layers_[0][0]->GetIsSelect());
	DrawFormatString(0, 320, GetColor(255, 255, 255), "isSelect[0][1] : %d", layers_[0][1]->GetIsSelect());
	DrawFormatString(0, 340, GetColor(255, 255, 255), "isSelect[0][2] : %d", layers_[0][2]->GetIsSelect());*/


}

Frame::~Frame()
{
	//�������
	for (int i = 0; i < this->GetLayerFrameHeight(); i++)
	{
		for (int j = 0; j < this->GetLayerFrameWidth(); j++)
		{
			this->layersInTheFrame[i][j].clear();

			//std::list<std::unique_ptr<Layer>>& layer = layersInTheFrame[i][j];
			////�d�Ȃ肪����΂��̕������
			//for (auto itr = layer.begin(); itr != layer.end(); itr++) {
			//	itr->reset();
			//}
			if (layers_.size())
			{
				layers_[i].clear();
			}
		}
	}
}

bool Frame::GetisSelect()
{
	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			if(layers_[i][j]->GetIsSelect())
			{
				return true;
			}
		}
	}
	return false;
}
