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

	//マウス座標
	int MouseX;
	int MouseY;

	//レイヤーを管理しているフレーム
	Layer* layer_ = nullptr;

	//マウスが現在いるフレームの数
	int frameNumX;
	int frameNumY;

	bool isSelect = false;

public:

	void SetSelectLayer();


};

