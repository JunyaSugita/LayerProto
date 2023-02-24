#include "GameScene.h"

//
GameScene::GameScene(){}

//delete
GameScene::~GameScene()
{

}

//
void GameScene::Initialize()
{
	//プレイヤーの生成と初期化
	player_ = std::make_unique<Player>();
	player_->Initialize();

	//フィールドの生成と初期化
	field_ = std::make_unique<Field>();
	field_->Initialize();
  
	//インスタンスの生成
	layer_ = std::make_unique<Layer>();
	fream_ = std::make_unique<Frame>();

	//
	//StageCSVManager::GetInstance().LoadStageCSV(1);
	
	//初期化
	layer_->Initialize();
	fream_->Initialize();
	//StageCSVManager::GetInstance().LoadStageCSV(1);//
}


void GameScene::Update(char* keys, char* oldkeys)
{
	//
	player_->Updata(1350,450);

	//
	if (CheckHitKey(KEY_INPUT_R)) {
		//
		player_->Initialize();

	}

	layer_->Update(keys, oldkeys);
}

void GameScene::Draw()
{
	layer_->Draw();

	//
	for (int i = 1; i < 9; i++) {
		DrawLine(0,i * BLOCK_SIZE, 1350,i * BLOCK_SIZE,GetColor(100,100,100));
	}
	//
	for (int i = 1; i < 9 * 3; i++) {
		//
		if (i % 9 == 0) {
			DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, 450, GetColor(150, 0, 0));
		}
		//
		else{
			DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, 450, GetColor(100, 100, 100));
		}
	}

	//
	player_->Draw();

	//
	field_->Draw();

	//
	DrawFormatString(10, 0, GetColor(200, 200, 200), "R : reset & hotReload(coming soon)");
}
