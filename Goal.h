#pragma once
#include "Vector2.h"
#include "DxLib.h"
#include "Field.h"
#include "Frame.h"
#include "Util.h"


class Goal final
{
private:
	Vector2 pos;
	//上にブロックがあるとき
	bool isOverlap = false;

	int effectCount = 0;

	//ゴールに触れていると
	int goalCount = 0;
	const int goalCountMax = 120;
	bool isGoal = false;

private:
	Goal() { ; }
	~Goal() { ; }

public:
	//コピーコンストラクタを無効
	Goal(const Goal& obj) = delete;
	//代入演算子も
	Goal& operator=(const Goal& obj) = delete;

	static Goal& GetInstance();

	void Initialize();

	//ゴールに重なってないか調べる
	void CheckOverlapBlock(Field* field);

	//ゴールに入ったか判定
	void CheckEnterGoal(const Vector2& pos, const Vector2& length);

	void Draw();

	void SetIsOverlap(bool is) { isOverlap = is; }
	void SetMapPos(Vector2 mapPos);

	Vector2 GetPos() { return pos; }
	Vector2 GetMapPos();
};

