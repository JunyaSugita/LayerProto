#pragma once
#include "DxLib.h"
#include "StageCSVManager.h"
#include "Layer.h"
#include "Frame.h"

class GameScene
{
public:
	GameScene();
	~GameScene();

	void Initialize();
	void Update(char* oldkey,char* key);
	void Draw();

public:
	const float BLOCK_SIZE = 50.0f;

private:
	std::unique_ptr<Layer> layer_ = nullptr;
	std::unique_ptr<Frame> fream_ = nullptr;
};

