#pragma once
#include "DxLib.h"
#include <memory>

#include "Player.h"
#include "Field.h"
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
	//1�u���b�N�̒��a
	const float BLOCK_SIZE = 50.0f;

	//プレイヤー
	std::unique_ptr<Player> player_;
	//フィールド
	std::unique_ptr<Field> field_;
private:
	std::unique_ptr<Layer> layer_ = nullptr;
	std::unique_ptr<Frame> fream_ = nullptr;
};

