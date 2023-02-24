#include "Player.h"

//無視
Player::Player(){}

//delete処理
Player::~Player()
{

}

//初期化
void Player::Initialize()
{
	pos_ = {25,425};
	isJump_ = false;
	jumpPow_ = 0;
}

//update
void Player::Updata(float windowX, float windowY)
{
#pragma region 操作
	//横移動(左)
	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT)) {
		pos_.x -= SPEED;
	}
	//横移動(右)
	if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT)) {
		pos_.x += SPEED;
	}
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
	//ジャンプと重力の移動
	pos_.y -= jumpPow_ - GRAVITY;

	//ジャンプ力の減少
	jumpPow_ -= subJump_;

	//ジャンプ力がマイナスだったら0にする
	if(jumpPow_ < 0){
		jumpPow_ = 0;
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
	//下(奈落判定にするならこの処理は消す)
	if (pos_.y + SIZE / 2 > windowY) {
		//押し戻し処理
		pos_.y = windowY - SIZE / 2;
		//床判定なのでジャンプフラグを解く
		isJump_ = false;
	}

#pragma endregion

	//
}

//draw
void Player::Draw()
{
	DrawBox(pos_.x - SIZE / 2, pos_.y - SIZE / 2, pos_.x + SIZE / 2, pos_.y + SIZE / 2, GetColor(100, 100, 200),true);
}

