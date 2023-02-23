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

	//フィールドの生成と初期化
	field_ = std::make_unique<Field>();
	field_->Initialize();
  
	//仮で読み込み
	StageCSVManager::GetInstance().LoadStageCSV(1);
}


void GameScene::Update()
{
	//プレイヤー
	player_->Updata(1350,450);

	//リセット&ホットリロード(未実装)
	if (CheckHitKey(KEY_INPUT_R)) {
		//プレイヤーの初期化
		player_->Initialize();

	}

}

void GameScene::Draw()
{
	//グリッドの表示(横)
	for (int i = 1; i < 9; i++) {
		DrawLine(0,i * BLOCK_SIZE, 1350,i * BLOCK_SIZE,GetColor(100,100,100));
	}
	//グリッドの表示(縦)
	for (int i = 1; i < 9 * 3; i++) {
		//境界線の描画(赤)
		if (i % 9 == 0) {
			DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, 450, GetColor(150, 0, 0));
		}
		//それ以外(白)
		else{
			DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, 450, GetColor(100, 100, 100));
		}
	}

	//プレイヤーの表示
	player_->Draw();

	//フィールドの表示
	field_->Draw();

	//コメント表示
	DrawFormatString(10, 0, GetColor(200, 200, 200), "R : reset & hotReload(coming soon)");
}
