#include "Player.h"
#include <assert.h>
#include "StageCSVManager.h"
#include "Goal.h"

Player* Player::player_ = nullptr;

//無視
Player::Player() {}

//delete処理
Player::~Player()
{

}

//初期化
void Player::Initialize()
{
	bool playerPos = false;

	for (int y = 0; y < Frame::GetLayerFrameHeight() * Layer::layerBlockHeight; y++)
	{
		for (int x = 0; x < Frame::GetLayerFrameWidth() * Layer::layerBlockWidth; x++)
		{
			int Y = y / Layer::layerBlockHeight;
			int X = x / Layer::layerBlockWidth;

			std::list<std::unique_ptr<Layer>>& layer = StageCSVManager::GetInstance().frameData.layersInTheFrame[Y][X];

			//重なりがあればその分も読み込み
			for (auto itr = layer.begin(); itr != layer.end(); itr++) {
				if (layer.size())
				{
					Block::BlockType block = itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->GetType();
					//プレイヤーの位置が読み込まれていたら
					if (block == Block::PLAYER)
					{
						SetPlayerMapPos({ (float)y,(float)x });
						playerPos = true;
						//消しとく
						itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->SetType(Block::NONE);
						break;
					}
				}
			}
			//もう読み込まれたら終わる
			if (playerPos)
			{
				break;
			}
		}
	}
	//座標が読み込まれなかったら
	if (!playerPos)
	{
		SetPlayerMapPos({ 0,0 });
	}

	isJump_ = false;
	jumpPow_ = 0;
	isInvincible_ = false;
}

//update
void Player::Updata(float windowX, float windowY, Field* field, Frame* frame)
{
	//フレームを動かしている間は処理を全て飛ばす
	if (frame->GetisSelect()) {
		return;
	}
	if (field->GetIsSelect()) {
		return;
	}

#pragma region 操作

	//ジャンプ
	if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP)) {
		//すでにジャンプしていないかチェック
		if (!isJump_) {
			//ジャンプ力を最大に
			jumpPow_ = MAX_JUMP;
			//ジャンプフラグを立てる
			isJump_ = true;
		}
	}

#pragma endregion

#pragma region ジャンプ関係

	//ジャンプ力の減少
	jumpPow_ -= subJump_;

	//ジャンプ力がマイナスだったら0にする
	if (jumpPow_ < 0) {
		jumpPow_ = 0;
	}

#pragma endregion

#pragma region ブロックとの当たり判定と移動
	//プレイヤーの仮移動用
	tempPos_ = pos_;

	//ジャンプと重力の移動
	float tempMove = jumpPow_ - GRAVITY;
	for (int i = 0; i < 20; i++) {
		tempPos_.y -= tempMove / 20;
		CalcMapPos();

		//ブロックなどと当たっているか
		if (field->GetMap(LB_) == BLOCK || field->GetMap(RB_) == BLOCK) {
			//着地なのでジャンプフラグを回復させる
			isJump_ = false;
			break;
		}
		else if (field->GetMap(LB_) == GOAL || field->GetMap(RB_) == GOAL) {
			//ブロックでは無いので移動させる
			pos_.y = tempPos_.y;

			//当たっているならゴール(未実装)

		}
		else if (field->GetMap(LT_) == BLOCK || field->GetMap(RT_) == BLOCK) {
			//天井ごっつんこの処理
			jumpPow_ = 0;
			break;
		}
		else {
			//それ以外なら移動させ続ける
			//ジャンプせずに空中に行った場合、プレイヤーの動きを自然にするため、jumpPowを少し追加
			if (isJump_ == false) {
				jumpPow_ = GRAVITY - 0.1f;

				//再計算
				tempMove = jumpPow_ - GRAVITY;
				tempPos_.y -= tempMove / 10;
				CalcMapPos();
			}

			pos_.y = tempPos_.y;
			//空中でジャンプ出来ないようにする
			isJump_ = true;
		}
	}

	tempPos_ = pos_;
	tempMove = 0;
	//横移動(左)
	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT)) {
		tempMove -= SPEED;
	}
	//横移動(右)
	if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT)) {
		tempMove += SPEED;
	}
	for (int i = 0; i < 10; i++) {
		tempPos_.x += tempMove / 10;
		CalcMapPos();

		//ブロックなどと当たっているか
		if (field->GetMap(LT_) == BLOCK || field->GetMap(LB_) == BLOCK) {

		}
		else if (field->GetMap(RT_) == BLOCK || field->GetMap(RB_) == BLOCK) {

		}
		else {
			//それ以外なら移動させる
			pos_.x = tempPos_.x;
		}
	}

	//トゲに当たったら死ぬ！！
	if (field->GetMap(LT_) == TRAP || field->GetMap(RT_) == TRAP || field->GetMap(LB_) == TRAP || field->GetMap(RB_) == TRAP) {
		if (isInvincible_ == false) {
			StageCSVManager::GetInstance().LoadStageCSV(StageCSVManager::GetInstance().selectNum);
			player_->Initialize();
			field->Initialize();
		}
	}

	//レイヤー外ブロックに当たったら死ぬ！！
	if (field->GetMap(LT_) == NULL_BLOCK || field->GetMap(RT_) == NULL_BLOCK || field->GetMap(LB_) == NULL_BLOCK || field->GetMap(RB_) == NULL_BLOCK) {
		if (isInvincible_ == false) {
			StageCSVManager::GetInstance().LoadStageCSV(StageCSVManager::GetInstance().selectNum);
			player_->Initialize();
			field->Initialize();
		}
	}


#pragma endregion

#pragma region 画面外処理

	//左
	if (pos_.x - SIZE / 2 < 0) {
		//押し戻し処理
		pos_.x = 0 + SIZE / 2;
	}
	//右
	else if (pos_.x + SIZE / 2 > windowX) {
		//押し戻し処理
		pos_.x = windowX - SIZE / 2;
	}

#pragma endregion

	//無敵化
	if (CheckHitKey(KEY_INPUT_0)) {
		isInvincible_ = true;
	}


#pragma region ゴールとの判定
	
	Goal::GetInstance().CheckEnterGoal(pos_, { SIZE,SIZE });

#pragma endregion
}

//draw
void Player::Draw()
{
	DrawBox(pos_.x - SIZE / 2, pos_.y - SIZE / 2, pos_.x + SIZE / 2, pos_.y + SIZE / 2, GetColor(100, 100, 200), true);

	if (isInvincible_ == false) {
		DrawFormatString(0, 80, GetColor(200, 200, 200), " 0 : 無敵化");
	}
	else {
		DrawFormatString(0, 80, GetColor(200, 200, 200), " 無敵化中！");
	}
}

Vector2 Player::GetMapPos(int Num)
{
	//引数に0~3以外の値が入っていたらアサート
	assert(("GetMapPos()の引数に0~3以外の値が入ってます", Num >= 0 && Num <= 3));

	//0(左上)
	if (Num == LT) {
		return LT_;
	}
	//1(右上)
	else if (Num == RT) {
		return RT_;
	}
	//2(左下)
	else if (Num == LB) {
		return LB_;
	}
	//3(右下)
	else if (Num == RB) {
		return RB_;
	}
}

Vector2 Player::GetMapPos()
{
	return Vector2(pos_.x / 30, pos_.y / 30);
}

void Player::CalcMapPos()
{
	//マップチップ上の場所を計算
	LT_ = { (tempPos_.x - SIZE / 2) / SIZE,(tempPos_.y - SIZE / 2) / SIZE };
	RT_ = { (tempPos_.x + SIZE / 2 - 1) / SIZE,(tempPos_.y - SIZE / 2) / SIZE };
	LB_ = { (tempPos_.x - SIZE / 2) / SIZE,(tempPos_.y + SIZE / 2 - 1) / SIZE };
	RB_ = { (tempPos_.x + SIZE / 2 - 1) / SIZE,(tempPos_.y + SIZE / 2 - 1) / SIZE };

}

Player* Player::GetInctance()
{
	if (!player_) {
		player_ = new Player();
	}
	return player_;
}



