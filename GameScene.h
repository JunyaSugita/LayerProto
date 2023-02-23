#pragma once
#include "DxLib.h"
#include "Player.h"
#include <memory>

class GameScene
{
public:
	GameScene();
	~GameScene();

	void Initialize();
	void Update();
	void Draw();

public:
	//1ブロックのサイズ(直径)
	const float BLOCK_SIZE = 50.0f;

	//プレイヤー
	std::unique_ptr<Player> player_;
};

