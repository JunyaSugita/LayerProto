#include "Frame.h"
#include "DxLib.h"
#include "Player.h"

void Frame::Initialize()
{
	for (int i = 0; i < this->GetLayerFrameHeight(); i++)
	{
		for (int j = 0; j < this->GetLayerFrameWidth(); j++)
		{
			this->layersInTheFrame[i][j].clear();
		}
	}

	for (int i = 0; i < layerFrameWidth; i++)
	{
		//ブロック型を持てる空のベクタを追加(行列でいうi列)
		layers_.push_back(std::vector<std::unique_ptr <Layer>>());

		for (int j = 0; j < layerFrameHeight; j++)
		{
			std::unique_ptr <Layer> layer_;
			layer_ = std::make_unique<Layer>();
			layer_->Initialize(i, j);
			//レイヤーの要素を追加
			layers_[i].push_back(std::move(layer_));
		}
	}

	//座標の初期化
	for (int i = 0; i < layerFrameWidth; i++)
	{
		for (int j = 0; j < layerFrameHeight; j++)
		{
			Vector2 pos;
			//ブロックの座標を設定
			if (i >= 0)
			{
				pos.y = i * Layer::layerWidth;

			}
			if (j >= 0)
			{
				pos.x = j * Layer::layerHeight;
			}

			layers_[i][j]->SetPos(pos);

		}
	}

	//枠の長さを設定
	for (int i = 0; i < layerFrameWidth; i++)
	{
		for (int j = 0; j < layerFrameHeight; j++)
		{
			if (i >= 0)
			{
				freamPos[i][j].y = (i * Layer::layerWidth);

			}
			if (j >= 0)
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
	Player* player = Player::GetInctance();

	

	//レイヤーを選択する処理
	if (GetMouseInputLog2(&button, &clickX, &clickY, &logType, TRUE) == 0)
	{
		
		for (int i = 0; i < layerFrameWidth; i++)
		{
			for (int j = 0; j < layerFrameHeight; j++)
			{
				if(layers_[i][j]->GetIsFront() == true)
				{
					frontVec.x = i;
					frontVec.y = j;
				}

				if (clickX > layers_[i][j]->GetLayerPos().x && clickX < layers_[i][j]->GetLayerPos().x + Layer::layerWidth)
				{
					if (clickY > layers_[i][j]->GetLayerPos().y && clickY < layers_[i][j]->GetLayerPos().y + Layer::layerHeight)
					{
						if (layers_[i][j]->GetIsSelect() == false)
						{
							layers_[i][j]->SetIsSelect(true);
							layers_[i][j]->SetIsFront(true);


							layers_[(int)frontVec.x][int(frontVec.y)]->SetIsFront(false);
						}
					}
				}
			}
		}
	}

	for (int i = 0; i < layerFrameWidth; i++)
	{
		for (int j = 0; j < layerFrameHeight; j++)
		{
			if (layers_[i][j]->GetIsSelect() == true)
			{
				//左クリックが押され続けているとき
				if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
				{
				}
				else
				{
					layers_[i][j]->SerchFrame(layerFrameWidth, freamPos);
				}
			}
		}
	}

	//レイヤーの更新
	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			layers_[i][j]->Update(keys, oldkeys, mouseX, mouseY, oldMouseX, oldMouseY);
		}
	}
}


void Frame::Draw()
{
	for (int i = 0; i < layerFrameWidth; i++)
	{
		for (int j = 0; j < layerFrameHeight; j++)
		{
			layers_[i][j]->Draw();
		}
	}

	/*DrawFormatString(0, 100, GetColor(255, 255, 255), "isSelect : %d", isSelect);
	DrawFormatString(0, 200, GetColor(255, 255, 255), "MouseX : %d", MouseX);
	DrawFormatString(0, 300, GetColor(255, 255, 255), "MouseY : %d", MouseY);*/
	DrawFormatString(0, 300, GetColor(255, 255, 255), "layers_[0][0] : %d", layers_[0][0]->GetIsSelect());
	DrawFormatString(0, 400, GetColor(255, 255, 255), "layers_[0][1] : %d", layers_[0][1]->GetIsSelect());
	DrawFormatString(0, 500, GetColor(255, 255, 255), "layers_[1][1] : %d", layers_[1][1]->GetIsSelect());

}

Frame::~Frame()
{
	//for(int i = 0; i < this->GetLayerFrameHeight(); i++)
	//{
	//	for(int j = 0; j < this->GetLayerFrameWidth(); j++)
	//	{
	//		//レイヤーのイテレータ
	//		std::list<Layer>::iterator it;
	//		it = layersInTheFrame[i][j].begin();
	//		//デストラクタを呼び出す
	//		it->~Layer();
	//		//次に進める
	//		it++;
	//	}
	//}
}

bool Frame::GetisSelect()
{
	for (int i = 0; i < layerFrameWidth; i++) {
		for (int j = 0; j < layerFrameHeight; j++) {
			if (layers_[i][j]->GetIsSelect()) {
				return true;
			}
		}
	}
	return false;
}
