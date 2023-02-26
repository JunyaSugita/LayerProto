#include "Player.h"
#include <assert.h>

//無視
Player::Player() {}

//delete処理
Player::~Player()
{

}

//初期化
void Player::Initialize()
{
	pos_ = { 15,15 };
	isJump_ = false;
	jumpPow_ = 0;
}

//update
void Player::Updata(float windowX, float windowY, Field* field)
{
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
	//if (pos_.y + SIZE / 2 > 270) {
	//	//押し戻し処理
	//	pos_.y = 255;
	//	//床判定なのでジャンプフラグを解く
	//	isJump_ = false;
	//}

#pragma endregion

#pragma region ブロックとの当たり判定と移動
	//プレイヤーの仮移動用
	tempPos_ = pos_;

	//ジャンプと重力の移動
	float tempMove = jumpPow_ - GRAVITY;
	for (int i = 0; i < 10; i++) {
		tempPos_.y -= tempMove / 10;
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
		else if(field->GetMap(LT_) == BLOCK || field->GetMap(RT_) == BLOCK){
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

#pragma endregion

}

//draw
void Player::Draw()
{
	DrawBox(pos_.x - SIZE / 2, pos_.y - SIZE / 2, pos_.x + SIZE / 2, pos_.y + SIZE / 2, GetColor(100, 100, 200), true);
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
	else if(Num == RB){
		return RB_;
	}
}

void Player::CalcMapPos()
{
	//マップチップ上の場所を計算
	LT_ = { (tempPos_.x - SIZE / 2) / SIZE,(tempPos_.y - SIZE / 2) / SIZE };
	RT_ = { (tempPos_.x + SIZE / 2 - 1) / SIZE,(tempPos_.y - SIZE / 2) / SIZE };
	LB_ = { (tempPos_.x - SIZE / 2) / SIZE,(tempPos_.y + SIZE / 2 - 1) / SIZE };
	RB_ = { (tempPos_.x + SIZE / 2 - 1) / SIZE,(tempPos_.y + SIZE / 2 - 1) / SIZE };

}



