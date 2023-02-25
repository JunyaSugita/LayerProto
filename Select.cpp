#include "Select.h"
#include "DxLib.h"

void Select::Initialize(Layer* layer)
{
	layer_ = layer;
}

void Select::Update()
{
	// マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);

	//レイヤーの右上
	float layerX = Layer::layerWidth * layer_->GetFrameNumX();
	float layerY = Layer::layerHeight * layer_->GetFrameNumY();

	//もしマウスがいる位置にレイヤーがあるなら選択する
	//レイヤーの範囲内にいるかどうか
	if(MouseX >= layerX && MouseX <= layerX + Layer::layerWidth)
	{
		isSelect = true;
	}
}

bool Select::Search()
{
	//マウスが現在いるフレームの数
	frameNumX = MouseX / Layer::layerWidth;
	frameNumY = MouseY / Layer::layerHeight;

	return true;
}

void Select::Draw()
{

}