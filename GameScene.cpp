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
	//ステージ読み込み
	StageCSVManager::GetInstance().LoadStageCSV(1);

	//プレイヤーの生成と初期化
	player_ = Player::GetInctance();
	player_->Initialize();

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
	//1フレーム前の座標を取得
	oldMouseX = MouseX;
	oldMouseY = MouseY;

	// マウスの位置を取得
	GetMousePoint(&MouseX, &MouseY);
	//
	field_->Update(MouseX, MouseY,810,810);

	//プレイヤー
	player_->Updata(810, 810,field_.get(), fream_.get());

	//リセット&ホットリロード
	if (CheckHitKey(KEY_INPUT_R)) {
		//
		player_->Initialize();
		StageCSVManager::GetInstance().LoadStageCSV(1);
		field_->Initialize();
	}

	fream_->Update(keys, oldkeys,MouseX,MouseY,oldMouseX,oldMouseY);
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



	//フィールドの表示
	field_->Draw();

	//プレイヤーの表示
	player_->Draw();

	//fream_->Draw();

	//コメント表示
	DrawFormatString(10, 0, GetColor(200, 200, 200), "R : reset & hotReload(coming soon)");
	/*DrawFormatString(0, 20, GetColor(200, 200, 200), "MouseX : %d", MouseX);
	DrawFormatString(0, 40, GetColor(200, 200, 200), "MouseY : %d", MouseY);*/

}
