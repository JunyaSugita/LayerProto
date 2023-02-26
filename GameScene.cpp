#include "GameScene.h"

//無視
GameScene::GameScene(){}

//delete処理
GameScene::~GameScene()
{

}

//初期化
void GameScene::Initialize()
{
	//プレイヤーの生成と初期化
	player_ = std::make_unique<Player>();
	player_->Initialize();

	//ステージ読み込み
	StageCSVManager::GetInstance().LoadStageCSV(1);

	//フィールドの生成と初期化
	field_ = std::make_unique<Field>();
	field_->Initialize();
  
	//インスタンスの生成
	//layer_ = std::make_unique<Layer>();
	fream_ = std::make_unique<Frame>();
	
	//初期化
	//layer_->Initialize();
	fream_->Initialize();
	
}


void GameScene::Update(char* keys, char* oldkeys)
{
	//プレイヤー
	player_->Updata(810, 810,field_.get());

	//リセット&ホットリロード
	if (CheckHitKey(KEY_INPUT_R)) {
		//
		player_->Initialize();
		StageCSVManager::GetInstance().LoadStageCSV(1);
		field_->Initialize();
	}

	fream_->Update(keys, oldkeys);
	//layer_->Update(keys, oldkeys);
}

void GameScene::Draw()
{
	
	//グリッドの表示(横)
	for (int i = 1; i < 9 * 3; i++) {
		//境界線の描画(赤)
		if (i % 9 == 0) {
			DrawLine(0, i * BLOCK_SIZE, 810, i * BLOCK_SIZE, GetColor(150, 0, 0));
		}
		//それ以外(白)
		else {
			DrawLine(0, i * BLOCK_SIZE, 810, i * BLOCK_SIZE, GetColor(100, 100, 100));
		}
	}
	//グリッドの表示(縦)
	for (int i = 1; i < 9 * 3; i++) {
		//境界線の描画(赤)
		if (i % 9 == 0) {
			DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, 810, GetColor(150, 0, 0));
		}
		//それ以外(白)
		else{
			DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, 810, GetColor(100, 100, 100));
		}
	}

	//layer_->Draw();

	//プレイヤーの表示
	player_->Draw();

	//フィールドの表示
	field_->Draw();

	fream_->Draw();

	//コメント表示
	DrawFormatString(10, 0, GetColor(200, 200, 200), "R : reset & hotReload(coming soon)");
}
