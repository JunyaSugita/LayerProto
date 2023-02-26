#pragma once
#include "Vector2.h"
#include "DxLib.h"
#include "Field.h"
#include "Frame.h"

enum MapPos {
	LT,	//左上
	RT,	//右上
	LB,	//左下
	RB,	//右下
};

class Player
{
public:
	Player();
	~Player();

public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// update
	/// </summary>
	/// <param name="windowX"> ウィンドウサイズ(縦) </param>
	/// <param name="windowY"> ウィンドウサイズ(横) </param>
	void Updata(float windowX,float windowY,Field* field,Frame* frame);

	/// <summary>
	/// draw
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーの位置の取得
	/// </summary>
	/// <returns> プレイヤーの位置 </returns>
	Vector2 GetPos() {
		return pos_;
	}

	/// <summary>
	/// プレイヤーのマップチップ上の位置の取得
	/// </summary>
	/// <param name="Num"> どの角か選択 </param>
	/// <returns> 選択した角の位置 </returns>
	Vector2 GetMapPos(int Num);

	/// <summary>
	/// プレイヤー座標のセット(ワールド座標換算)
	/// </summary>
	/// <param name="pos"> セットしたい座標 </param>
	void SetPlayerPos(Vector2 pos) {
		pos_ = pos;
	}

	/// <summary>
	/// プレイヤー座標のセット(マップチップ換算)
	/// </summary>
	/// <param name="gridPos"> マップチップ上の座標 </param>
	void SetPlayerMapPos(Vector2 gridPos) {
		pos_.x = gridPos.x * SIZE + SIZE / 2;
		pos_.y = gridPos.y * SIZE + SIZE / 2;
	}

private:
	void CalcMapPos();

private:
	//固定値	//ジャンプ関係は一応、縦2マスジャンプ、横3マスジャンプに調整済み
	const float SIZE = 30;			//プレイヤーの直径
	const float SPEED = 4.0f;		//横移動速度
	const float GRAVITY = 10.0f;	//プレイヤーの重力
	const float MAX_JUMP = 24.0f;	//最大ジャンプ力
	float subJump_ = 0.8f;			//ジャンプ力減少値		

	//変数
	Vector2 pos_;
	bool isJump_;

	//ジャンプ力
	float jumpPow_;
	
	//プレイヤーの4つ角のマップチップ上の場所
	Vector2 LT_, RT_, LB_, RB_;
	//プレイヤーの仮移動用
	Vector2 tempPos_ = pos_;
};

