#pragma once
#include "DxLib.h"
#include <memory>

#include "Player.h"
#include "Field.h"
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
	//1ブロックの直径
	const float BLOCK_SIZE = 50.0f;

	//プレイヤー
	std::unique_ptr<Player> player_;
	//フィールド
	std::unique_ptr<Field> field_;
};

