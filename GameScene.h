#pragma once
#include "DxLib.h"
#include <memory>

#include "Player.h"
#include "Field.h"
#include "StageCSVManager.h"
#include "Layer.h"
#include "Frame.h"
#include "Goal.h"

class GameScene
{
public:
	GameScene();
	~GameScene();

	void Initialize();
	void Update(char* oldkey,char* key);
	void Draw();

public:
	//ブロックの大きさ
	const float BLOCK_SIZE = 30.0f;

	//マウス座標
	int MouseX;
	int MouseY;
	
	//選択した時のマウスの座標
	int oldMouseX;
	int oldMouseY;

	//プレイヤー
	Player* player_;
	//フィールド
	std::unique_ptr<Field> field_;
private:
	//std::unique_ptr<Layer> layer_ = nullptr;
	std::unique_ptr<Frame> fream_ = nullptr;
};

