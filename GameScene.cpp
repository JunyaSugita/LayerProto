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
	//インスタンスの生成
	layer_ = std::make_unique<Layer>();
	fream_ = std::make_unique<Frame>();

	//仮で読み込み
	//StageCSVManager::GetInstance().LoadStageCSV(1);
	
	//初期化
	layer_->Initialize();
	fream_->Initialize();
}


void GameScene::Update(char* keys, char* oldkeys)
{
	//キー入力のやり方忘れてたからお試し
	if (CheckHitKey(KEY_INPUT_SPACE)) {
	}

	layer_->Update(keys, oldkeys);
}

void GameScene::Draw()
{
	layer_->Draw();

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
}
