#pragma once

#include"Frame.h"
#include<functional>


//読み込み用のクラス
class StageCSVManager final
{//変数
private:
	int layersIntheFrameY;
	int layersIntheFrameX;


public:
	//ステージデータ
	Frame frameData;
	int selectNum = 1;

private://関数

	StageCSVManager() { ; }
	~StageCSVManager() { ; }

public:
	//コピーコンストラクタを無効
	StageCSVManager(const StageCSVManager& obj) = delete;
	//代入演算子も
	StageCSVManager& operator=(const StageCSVManager& obj) = delete;

	static StageCSVManager& GetInstance();

	//ステージ読み込み
	void LoadStageCSV(int stageNum);

	//押した番号によってステージ読み込む
	void UpdateLoadStage(std::function<void()>f);
};

