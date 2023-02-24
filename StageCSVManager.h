#pragma once

#include"Frame.h"


//読み込み用のクラス
class StageCSVManager final
{//変数
private:
	Frame frameData;
	int layersIntheFrameY;
	int layersIntheFrameX;
	

public:


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
};

