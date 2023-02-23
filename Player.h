#pragma once
#include "Vector2.h"
#include "DxLib.h"

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
	void Updata(float windowX,float windowY);

	/// <summary>
	/// draw
	/// </summary>
	void Draw();

private:
	//固定値	//ジャンプ関係は一応、縦2マスジャンプ、横3マスジャンプに調整済み
	const float SIZE = 50;			//プレイヤーの直径
	const float SPEED = 4.0f;		//横移動速度
	const float GRAVITY = 10.0f;	//プレイヤーの重力
	const float MAX_JUMP = 24.0f;	//最大ジャンプ力
	float subJump_ = 0.8f;			//ジャンプ力減少値		

	//変数
	Vector2 pos_;
	bool isJump_;

	//ジャンプ力
	float jumpPow_;
	
	
};

