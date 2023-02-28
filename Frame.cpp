#include "Frame.h"
#include "DxLib.h"
#include "Player.h"

void Frame::Initialize()
{
	//解放する
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
		//ブロック型を持てる空のベクタを追加(行列でいうi列)
		layers_.push_back(std::vector<std::unique_ptr <Layer>>());

		for(int j = 0; j < layerFrameHeight; j++)
		{
			std::unique_ptr <Layer> layer_;
			layer_ = std::make_unique<Layer>();
			layer_->Initialize(i, j);
			//レイヤーの要素を追加
			layers_[i].push_back(std::move(layer_));
		}
	}

	//座標の初期化
	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			Vector2 pos;
			//ブロックの座標を設定
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

	//枠の長さを設定
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
	//レイヤーを選択する処理
	if(GetMouseInputLog2(&button, &clickX, &clickY, &logType, TRUE) == 0)
	{
		if((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			for(int i = 0; i < layerFrameWidth; i++)
			{
				for(int j = 0; j < layerFrameHeight; j++)
				{
					//マウスとレイヤーの選択処理
					if(clickX > layers_[i][j]->GetLayerPos().x && clickX < layers_[i][j]->GetLayerPos().x + Layer::layerWidth)
					{
						if(clickY > layers_[i][j]->GetLayerPos().y && clickY < layers_[i][j]->GetLayerPos().y + Layer::layerHeight)
						{
							//もし選択されていないとき
							if(layers_[i][j]->GetIsSelect() == false && isSelect_ == false)
							{
								//最前面を選択した時の処理
								if(layers_[i][j]->GetFrontCount() == 1)
								{
									//レイヤーの選択フラグをONに
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
			//もしクリックされているとき
			if(layers_[i][j]->GetIsSelect() == true)
			{
				//左クリックが押され続けているとき
				if((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
				{
				}
				else
				{
					//押されていなければ
					//枠にフレームをはめる
					layers_[i][j]->SerchFrame();
				}
			}
		}
	}

	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			//各フレーム時間を取得
			isLayerTimer[i][j] = layers_[i][j]->GetLayerTimer();
		}
	}

	for(int i = 0; i < layerFrameWidth; i++)
	{
		for(int j = 0; j < layerFrameHeight; j++)
		{
			//どこか枠をはめたのなら
			//はめたフラグをONにする。
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
			//もしどこかのレイヤーを枠にはめたのなら
			if(isSetLayer == true)
			{
				//各レイヤーの深さを調整する
				layers_[i][j]->CheckLayerDepth(isLayerTimer, layerPos_);
				//最後のレイヤー処理が終わったなら
				if(i == layerFrameWidth - 1 && j == layerFrameHeight - 1)
				{
					//はめたフラグをOFFにする。
					isSetLayer = false;
				}
			}
		}
	}

	//レイヤーの更新(下に置いておかないとバグる)
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
	//解放する
	for (int i = 0; i < this->GetLayerFrameHeight(); i++)
	{
		for (int j = 0; j < this->GetLayerFrameWidth(); j++)
		{
			this->layersInTheFrame[i][j].clear();

			//std::list<std::unique_ptr<Layer>>& layer = layersInTheFrame[i][j];
			////重なりがあればその分も解放
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
