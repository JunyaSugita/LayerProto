#pragma once
#include "DxLib.h"
#include "Player.h"
#include <memory>
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
	//1�u���b�N�̃T�C�Y(���a)
	const float BLOCK_SIZE = 50.0f;

	//�v���C���[
	std::unique_ptr<Player> player_;
};

