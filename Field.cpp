#include "Field.h"
#include "StageCSVManager.h"
#include <assert.h>
#include "Player.h"
#include "Goal.h"

//無視
Field::Field() {}

//delete処理
Field::~Field()
{

}

void Field::Initialize(int map)
{
	//マップの読み込み

	int mapTemp[MAX_OVERLAP][MAP_Y][MAP_X];


	for (int y = 0; y < Frame::GetLayerFrameHeight() * Layer::layerBlockHeight; y++)
	{
		for (int x = 0; x < Frame::GetLayerFrameWidth() * Layer::layerBlockWidth; x++)
		{
			int Y = y / Layer::layerBlockHeight;
			int X = x / Layer::layerBlockWidth;

			std::list<std::unique_ptr<Layer>>& layer = StageCSVManager::GetInstance().frameData.layersInTheFrame[Y][X];
			int count = 0;

			//重なりがあればその分も読み込み
			for (auto itr = layer.begin(); itr != layer.end(); itr++) {
				if (layer.size())
				{
					Block::BlockType block = itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->GetType();
					//マップをセット
					if (block == Block::PLAYER)
					{
						//playerの情報は入れない
						mapTemp[count][y][x] = Block::NONE;
					}
					else
					{
						mapTemp[count][y][x] = block;
					}
				}
				count++;
			}
		}
	}


	//代入
	for (int k = 0; k < MAX_OVERLAP; k++) {
		for (int i = 0; i < MAP_Y; i++) {
			for (int j = 0; j < MAP_X; j++) {
				map_[k][i][j] = mapTemp[k][i][j];
			}
		}
	}

	mouseStart = { -1,-1 };
	isSelect_ = false;
	isDraw_ = false;
}

void Field::Update(int mouseX, int mouseY, int windowWidth, int windowHeight)
{
	mouseX_ = mouseX;
	mouseY_ = mouseY;

	PreviewUpdate();

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (mouseStart.x == -1) {
			mouseStart = { (float)(mouseX / (windowWidth / Frame::GetLayerFrameWidth())),(float)(mouseY / (windowHeight / Frame::GetLayerFrameHeight())) };
		}
		isSelect_ = true;
	}
	else if (mouseStart.x != -1) {
		if (mouseStart.x >= 0 && mouseStart.x <= 2 && mouseStart.y >= 0 && mouseStart.y <= 2) {
			MoveLayer(mouseStart, { (float)(mouseX / (windowWidth / Frame::GetLayerFrameWidth())),(float)(mouseY / (windowHeight / Frame::GetLayerFrameHeight())) });
		}
		mouseStart = { -1,-1 };
		isSelect_ = false;
	}


}

void Field::Draw()
{
	for (int k = 0; k < MAX_OVERLAP; k++) {
		for (int i = 0; i < MAP_Y; i++) {
			for (int j = 0; j < MAP_X; j++) {
				int Light = GetLayerNum(j / 9, i / 9);
				//マップの数字によって描画する
				switch (map_[k][i][j])
				{
				case BLOCK:
					//ブロックなら白で描画
					if (k == Light) {
						DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(255, 255, 255), true);
					}
					else {
						DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(100, 100, 100), true);
					}
					break;

				//case GOAL:
				//	//ゴールなら赤で描画
				//	DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(200, 100, 100), true);
				//	break;

				case TRAP:
					//トゲを黄色で描画
					DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(250, 0, 0), true);

				//case NOLAYER:
				//	//レイヤーはないが、枠はある場所
				//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
				//	DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(100, 100, 10), true);
				//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
				//	break;

				case NONE:
				default:
					break;
				}

				if (k == 0) {
					if (map_[k][i][j] == NULL_BLOCK) {
						DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(0, 0, 0), true);

					}
				}
			}
		}
	}

	for (int i = 0; i < 27; i++) {
		for (int j = 0; j < 27; j++) {
			switch (GetMap({ (float)j,(float)i }))
			{
			case RAP_BLOCK:
				DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(50, 50, 0), true);
				break;
			default:
				break;
			}
		}
	}

	PreviewDraw();
}

int Field::GetMap(Vector2 pos)
{
	//ブロック同士の重なり確認用
	int blockRap = 0;

	if (map_[0][(int)pos.y][(int)pos.x] == NULL_BLOCK) {
		return NULL_BLOCK;
	}

	for (int i = MAX_OVERLAP - 1; i >= 0; i--) {
		switch (map_[i][(int)pos.y][(int)pos.x]) {
		case NONE:
			break;
		case BLOCK:
			blockRap++;
			break;
		case GOAL:
			if (blockRap == 0) {
				return GOAL;
			}
			break;
		case TRAP:
			if (blockRap == 0) {
				return TRAP;
			}
			break;
		}
	}

	if (blockRap == 1) {
		return BLOCK;
	}
	else if(blockRap == 2){
		return RAP_BLOCK;
	}

	return 0;
}

int Field::GetLayerNum(int x, int y)
{
	assert("xに0~2以外の数字が入っています", x >= 0 && x <= 2);
	assert("yに0~2以外の数字が入っています", y >= 0 && y <= 2);

	//レイヤーの層(最前面から)
	int i;
	for (i = MAX_OVERLAP - 1; i >= 0; i--) {
		//レイヤーYから
		for (int j = y * 9; j < 9 * (y + 1); j++) {
			//レイヤーXから
			for (int k = x * 9; k < 9 * (x + 1); k++) {
				if (map_[i][j][k] != -858993460) {
					//1つでも0以外があればレイヤーがある層を返す
					return i;
				}
			}
		}
	}
	//無ければ0層を返す
	return i;
}

void Field::MoveLayer(Vector2 start, Vector2 end)
{
	Player* player = Player::GetInctance();

	//プレイヤーを枠内に入れる
	player->SetPlayerMapPos({ (float)(int)player->GetMapPos().y, (float)(int)player->GetMapPos().x });

	//アサート
	assert("start.xに0~2以外の数字が入っています", start.x >= 0 && start.x <= 2);
	assert("start.yに0~2以外の数字が入っています", start.y >= 0 && start.y <= 2);
	assert("end.xに0~2以外の数字が入っています", end.x >= 0 && end.x <= 2);
	assert("end.yに0~2以外の数字が入っています", end.y >= 0 && end.y <= 2);

	//枠がなかったら移動させない
	if (GetLayerNum(end.x, end.y) < 0)
	{
		return;
	}

	//取るフレームの層を出す
	int tempMap[9][9];
	int tempS = GetLayerNum(start.x, start.y);	//始点のフレームの最前面
	int tempE = GetLayerNum(end.x, end.y);		//終点のフレームの最前面

	//クリックしたところがレイヤーなし枠だったら終わる
	if (map_[tempS][(int)start.y * 9][(int)start.x * 9] == NOLAYER)
	{
		return;
	}

	//終点にすでに2枚以上あったら終わる
	if (tempE >= 1) {
		return;
	}

	//プレイヤーの情報をとる
	//始点にプレイヤーが居る時
	if (start.x * 270 <= player->GetPos().x && (start.x + 1) * 270 >= player->GetPos().x && start.y * 270 <= player->GetPos().y && (start.y + 1) * 270 >= player->GetPos().y) {
		map_[tempS][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = PLAYER;
	}
	//終点にプレイヤーが居る時
	else if(end.x * 270 <= player->GetPos().x && (end.x + 1) * 270 >= player->GetPos().x && end.y * 270 <= player->GetPos().y && (end.y + 1) * 270 >= player->GetPos().y) {
		if (map_[tempE][(int)player->GetMapPos().y][(int)player->GetMapPos().x] == NOLAYER) {
			//レイヤーが無い所にプレイヤーが居る時、戻す時のためにNOLAYER_PLAYERにする
			map_[tempE][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = NOLAYER_PLAYER;
		}
		else {
			map_[tempE][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = PLAYER;
		}
	}

	//ブロック同士が重なってしまっていたら移動させない
	for (int k = GetLayerNum(end.x, end.y); k >= 0; k--) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				//ブロック同士(削除)
				//if (map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] == BLOCK && map_[k][i + (int)end.y * 9][j + (int)end.x * 9] == BLOCK) {
				//	return;
				//}
				//プレイヤーとブロック
				if (map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] == PLAYER && map_[k][i + (int)end.y * 9][j + (int)end.x * 9] == BLOCK) {
					map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] = NONE;
					return;
				}
				//ブロックとプレイヤー
				if (map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] == BLOCK && map_[k][i + (int)end.y * 9][j + (int)end.x * 9] == PLAYER) {
					map_[k][i + (int)end.y * 9][j + (int)end.x * 9] = NONE;
					return;
				}
				//やっていることは上と同じだが変更するブロック先が変わる
				if (map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] == BLOCK && map_[k][i + (int)end.y * 9][j + (int)end.x * 9] == NOLAYER_PLAYER) {
					map_[k][i + (int)end.y * 9][j + (int)end.x * 9] = NOLAYER;
					return;
				}
			}
		}
	}

	//取っていたプレイヤーの情報を消す
	if (end.x * 270 <= player->GetPos().x && (end.x + 1) * 270 >= player->GetPos().x && end.y * 270 <= player->GetPos().y && (end.y + 1) * 270 >= player->GetPos().y) {
		map_[tempE][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = NONE;
	}

	//消しながらtempMapに情報を移す
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			tempMap[i][j] = map_[tempS][i + (int)start.y * 9][j + (int)start.x * 9];
			//レイヤーが一枚で、移動させたらレイヤーなし枠にする（レイヤーが移動できる場所）
			if (tempS == 0)
			{
				map_[tempS][i + (int)start.y * 9][j + (int)start.x * 9] = NOLAYER;
			}
			//下にレイヤーがある場合は消す
			else
			{
				map_[tempS][i + (int)start.y * 9][j + (int)start.x * 9] = NULL_BLOCK;
			}
		}
	}

	//最前面を探す
	tempS = GetLayerNum(end.x, end.y);
	assert("レイヤーの重なり最大値10を超えています", tempS < MAX_OVERLAP);
	//tempMapから情報を移す
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			//枠なしレイヤーに重ねたらそれを消して上書き
			if (map_[tempS][i + (int)end.y * 9][j + (int)end.x * 9] == NOLAYER)
			{
				map_[tempS][i + (int)end.y * 9][j + (int)end.x * 9] = tempMap[i][j];
				if (map_[tempS][i + (int)end.y * 9][j + (int)end.x * 9] == PLAYER) {
					player->SetPlayerMapPos({ (float)(i + (int)end.y * 9), (float)(j + (int)end.x * 9) });
					map_[tempS][i + (int)end.y * 9][j + (int)end.x * 9] = NONE;
				}
			}
			//通常時は重ねていく
			else
			{
				map_[tempS + 1][i + (int)end.y * 9][j + (int)end.x * 9] = tempMap[i][j];
				if (map_[tempS + 1][i + (int)end.y * 9][j + (int)end.x * 9] == PLAYER) {
					player->SetPlayerMapPos({ (float)(i + (int)end.y * 9), (float)(j + (int)end.x * 9) });
					map_[tempS + 1][i + (int)end.y * 9][j + (int)end.x * 9] = NONE;
				}
			}
		}
	}

	//移動させた後にゴールに重なってるか調べる
	Goal::GetInstance().CheckOverlapBlock(this);
}

void Field::PreviewUpdate()
{
	int layerPosX = mouseX_ / 270;
	int layerPosY = mouseY_ / 270;
	
	//プレイヤーを枠内に入れる
	Player* player = Player::GetInctance();
	if (isSelect_) {
		player->SetPlayerMapPos({ (float)(int)player->GetMapPos().y, (float)(int)player->GetMapPos().x });
	}
	else
	{
		layerNum_ = GetLayerNum(layerPosX, layerPosY);
		clickX_ = layerPosX;
		clickY_ = layerPosY;

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				preview_[i][j] = map_[layerNum_][i + layerPosY * 9][j + layerPosX * 9];
			}
		}

		int a = player->GetMapPos().x / 9;
		int b = player->GetMapPos().y / 9;

		if (a == layerPosX && b == layerPosY) {
			preview_[(int)player->GetMapPos().y % 9][(int)player->GetMapPos().x % 9] = PLAYER;
		}
	}
}

void Field::PreviewDraw()
{
	int layerPosX = mouseX_ / 270;
	int layerPosY = mouseY_ / 270;

	//マウスをクリックしている時だけ描画
	if (isSelect_) {

		if (GetLayerNum(layerPosX, layerPosY) == 1) {
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					if (map_[0][i + layerPosY * 9][j + layerPosX * 9] == BLOCK && (clickX_ != layerPosX || clickY_ != layerPosY)) {
						DrawBox(layerPosX * 270, layerPosY * 270, (layerPosX + 1) * 270, (layerPosY + 1) * 270, GetColor(250, 0, 0), true);
						return;
					}
				}
			}
		}

		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
				switch (preview_[i][j])
				{
				case BLOCK:
					if (map_[0][i + layerPosY * 9][j + layerPosX * 9] == BLOCK && (clickX_ != layerPosX || clickY_ != layerPosY)) {
						DrawBox(layerPosX * 270 + j * BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE, layerPosX * 270 + j * BLOCK_SIZE + BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE + BLOCK_SIZE, GetColor(50, 50, 0), true);
					}
					else {
						DrawBox(layerPosX * 270 + j * BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE, layerPosX * 270 + j * BLOCK_SIZE + BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE + BLOCK_SIZE, GetColor(250, 250, 250), true);
					}
					break;
				case PLAYER:
					DrawBox(layerPosX * 270 + j * BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE, layerPosX * 270 + j * BLOCK_SIZE + BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE + BLOCK_SIZE, GetColor(150, 150, 250), true);
					break;
				case TRAP:
					DrawBox(layerPosX * 270 + j * BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE, layerPosX * 270 + j * BLOCK_SIZE + BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE + BLOCK_SIZE, GetColor(250, 0, 0), true);
					break;
				default:
					DrawBox(layerPosX * 270 + j * BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE, layerPosX * 270 + j * BLOCK_SIZE + BLOCK_SIZE, layerPosY * 270 + i * BLOCK_SIZE + BLOCK_SIZE, GetColor(50, 50, 50), true);
					break;
				}
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 50);
			}
		}
	}
}


