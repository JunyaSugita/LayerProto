#pragma once
#include "DxLib.h"
#include "StageCSVManager.h"

class GameScene
{
public:
	GameScene();
	~GameScene();

	void Initialize();
	void Update();
	void Draw();

public:
	const float BLOCK_SIZE = 50.0f;

private:
	std::unique_ptr<Layer> layer = nullptr;
};

