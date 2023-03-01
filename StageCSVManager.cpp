#include "StageCSVManager.h"
#include <fstream>
#include<cassert>
#include<string>
#include <sstream>
#include <iostream>
#include <DxLib.h>

using BlockType = Block::BlockType;

StageCSVManager& StageCSVManager::GetInstance()
{
	static StageCSVManager instance;
	return instance;
}

void StageCSVManager::LoadStageCSV(int stageNum)
{
	//リセット
	frameData.Initialize();

	//ファイル開く
	std::ifstream file;

	std::string filePath = "Resources/StageCSV/";
	std::string fileName = "stage";
	char stageNumC[7] = { 0 };
	//intを文字列に変換
	_itoa_s(stageNum, stageNumC, _countof(stageNumC) - 1);
	std::string numString = stageNumC;
	std::string fileCSV = ".csv";

	//ファイル開く
	std::string fileFullPath = filePath + fileName + numString + fileCSV;
	file.open(fileFullPath.c_str());

	//開けなかったらそのままにする
	if (!file.is_open()) { return; }

	//選んだ番号を入れておく
	selectNum = stageNum;

	// 1行ずつ読み込む
	std::string line;
	while (getline(file, line)) {

		// 1行分の文字列をストリームに変換して解析しやすくする
		std::istringstream line_stream(line);

		// 半角スペース区切りで行の先頭文字列を取得
		std::string key;
		getline(line_stream, key, ' ');

		//[//]から始まる行はコメント
		if (key.find("//") == 0)
		{
			continue;
		}

		//数字入れる用
		std::string word;

		//大枠の中の場所
		if (key == "layersInTheFrame")
		{
			//縦と横の位置
			getline(line_stream, word, ' ');
			layersIntheFrameY = (int)std::atoi(word.c_str());
			getline(line_stream, word, ' ');
			layersIntheFrameX = (int)std::atoi(word.c_str());

			//枠はあるけどレイヤー何もない場所用
			getline(line_stream, word, ' ');
			//falseとあって、何もレイヤー積まれてなかったら
			if (word == "false" && frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].size() == 0)
			{
				//要素を大枠の指定の場所に確保
				std::unique_ptr <Layer> layer = std::make_unique<Layer>();
				layer->Initialize(Layer::layerBlockWidth, Layer::layerBlockHeight);

				frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].push_back(std::move(layer));
				//レイヤーのブロックに枠なしと入れて、レイヤーなし枠とわかるように
				for (int i = 0; i < Layer::layerBlockHeight; i++)
				{
					for (int j = 0; j < Layer::layerBlockWidth; j++)
					{
						frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].begin()->get()->blocks_[i][j]->SetType(BlockType::NOLAYER_BLOCK);
					}
				}
			}
		}

		//レイヤーのブロック配置
		if (key == "layer")
		{
			//"layer"から改行
			getline(file, line);
			// 1行分の文字列をストリームに変換して解析しやすくする
			std::istringstream line_stream(line);

			//要素を大枠の指定の場所に確保するために変数用意
			std::unique_ptr< Layer> layer = std::make_unique<Layer>();
			layer->Initialize(Layer::layerBlockWidth, Layer::layerBlockHeight);

			//配列指定用のカウント
			int x = 0;
			int y = 0;
			//レイヤーのブロックすべて読み込み
			while (1)
			{
				//空白ごとにレイヤーのブロックを取得
				getline(line_stream, word, ' ');
				//ブロックをセット

				if (word == "p")
				{
					//プレイヤーなら
					layer->blocks_[y][x]->SetType(BlockType::PLAYER);
				}
				else
				{
					layer->blocks_[y][x]->SetType(BlockType((int)std::atoi(word.c_str())));
				}

				//カウントを進める
				x++;
				//横幅を超えたら縦を進める
				if (x >= Layer::layerBlockWidth)
				{
					y++;
					x = 0;
					//改行
					getline(file, line);
					line_stream.str(line.c_str());
				}
				//縦幅を超えたら終わり
				if (y >= Layer::layerBlockHeight)
				{
					//値を入れたものをリストに入れる
					frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].push_back(std::move(layer));
					break;
				}
			}
		}
	}

	//ファイル閉じる
	file.close();
}

void StageCSVManager::UpdateLoadStage(std::function<void()>f)
{
	if (CheckHitKey(KEY_INPUT_1)) {
		this->LoadStageCSV(1); f();
	}
	if (CheckHitKey(KEY_INPUT_2)) {
		this->LoadStageCSV(2); f();
	}
	if (CheckHitKey(KEY_INPUT_3)) {
		this->LoadStageCSV(3); f();
	}
	if (CheckHitKey(KEY_INPUT_4)) {
		this->LoadStageCSV(4); f();
	}
	if (CheckHitKey(KEY_INPUT_5)) {
		this->LoadStageCSV(5); f();
	}
	if (CheckHitKey(KEY_INPUT_6)) {
		this->LoadStageCSV(6); f();
	}
	if (CheckHitKey(KEY_INPUT_7)) {
		this->LoadStageCSV(7); f();
	}
	if (CheckHitKey(KEY_INPUT_8)) {
		this->LoadStageCSV(8); f();
	}
	if (CheckHitKey(KEY_INPUT_9)) {
		this->LoadStageCSV(9); f();
	}
}


