#include "Field.h"
#include "StageCSVManager.h"
#include <assert.h>
#include "Player.h"

//����
Field::Field() {}

//delete����
Field::~Field()
{

}

void Field::Initialize(int map)
{
	//�}�b�v�̓ǂݍ���(�������̂��߃}�W�b�N�i���o�[�𒼓���)

	int mapTemp[MAX_OVERLAP][MAP_Y][MAP_X];


	for (int y = 0; y < Frame::GetLayerFrameHeight() * Layer::layerBlockHeight; y++)
	{
		for (int x = 0; x < Frame::GetLayerFrameWidth() * Layer::layerBlockWidth; x++)
		{
			int Y = y / Layer::layerBlockHeight;
			int X = x / Layer::layerBlockWidth;

			std::list<std::unique_ptr<Layer>>& layer = StageCSVManager::GetInstance().frameData.layersInTheFrame[Y][X];
			int count = 0;

			//�d�Ȃ肪����΂��̕����ǂݍ���
			for (auto itr = layer.begin(); itr != layer.end(); itr++) {
				if (layer.size())
				{
					Block::BlockType block = itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->GetType();
					//�}�b�v���Z�b�g
					mapTemp[count][y][x] = block;
				}
				else
				{
					mapTemp[count][y][x] = Block::BlockType::NOLAYER_BLOCK;
				}
				count++;
			}
		}
	}


	//���
	for (int k = 0; k < MAX_OVERLAP; k++) {
		for (int i = 0; i < MAP_Y; i++) {
			for (int j = 0; j < MAP_X; j++) {
				map_[k][i][j] = mapTemp[k][i][j];
			}
		}
	}

	mouseStart = { -1,-1 };
	isSelect_ = false;
}

void Field::Update(int mouseX, int mouseY, int windowWidth, int windowHeight)
{
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
				//�}�b�v�̐����ɂ���ĕ`�悷��
				switch (map_[k][i][j])
				{
				case BLOCK:
					//�u���b�N�Ȃ甒�ŕ`��
					if (k == Light) {
						DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(255, 255, 255), true);
					}
					else {
						DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(100, 100, 100), true);
					}
					break;

				case GOAL:
					//�S�[���Ȃ�Ԃŕ`��
					DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(200, 100, 100), true);
					break;

				case NONE:
				default:
					break;
				}
			}
		}
	}
}

int Field::GetMap(Vector2 pos)
{
	for (int i = 0; i < MAX_OVERLAP; i++) {
		switch (map_[i][(int)pos.y][(int)pos.x]) {
		case NONE:
			break;
		case BLOCK:
			return BLOCK;
			break;
		case GOAL:
			return GOAL;
			break;
		}

	}
	return 0;
}

int Field::GetLayerNum(int x, int y)
{
	assert("x��0~2�ȊO�̐����������Ă��܂�", x >= 0 && x <= 2);
	assert("y��0~2�ȊO�̐����������Ă��܂�", y >= 0 && y <= 2);

	//���C���[�̑w(�őO�ʂ���)
	for (int i = MAX_OVERLAP - 1; i >= 0; i--) {
		//���C���[Y����
		for (int j = y * 9; j < 9 * (y + 1); j++) {
			//���C���[X����
			for (int k = x * 9; k < 9 * (x + 1); k++) {
				if (map_[i][j][k] != -858993460) {
					//1�ł�0�ȊO������΃��C���[������w��Ԃ�
					return i;
				}
			}
		}

	}
	//�������0�w��Ԃ�
	return 0;
}

void Field::MoveLayer(Vector2 start, Vector2 end)
{
	Player* player = Player::GetInctance();

	//�A�T�[�g
	assert("start.x��0~2�ȊO�̐����������Ă��܂�", start.x >= 0 && start.x <= 2);
	assert("start.y��0~2�ȊO�̐����������Ă��܂�", start.y >= 0 && start.y <= 2);
	assert("end.x��0~2�ȊO�̐����������Ă��܂�", end.x >= 0 && end.x <= 2);
	assert("end.y��0~2�ȊO�̐����������Ă��܂�", end.y >= 0 && end.y <= 2);

	//���t���[���̑w���o��
	int tempMap[9][9];
	int temp = GetLayerNum(start.x, start.y);

	//�v���C���[�̏����Ƃ�
	if (start.x * 270 <= player->GetPos().x && (start.x + 1) * 270 >= player->GetPos().x && start.y * 270 <= player->GetPos().y && (start.y + 1) * 270 >= player->GetPos().y) {
		map_[temp][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = 9;
	}
	//�����Ȃ���tempMap�ɏ����ڂ�
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			tempMap[i][j] = map_[temp][i + (int)start.y * 9][j + (int)start.x * 9];
			map_[temp][i + (int)start.y * 9][j + (int)start.x * 9] = -858993460;
		}
	}

	//�őO�ʂ�T��
	temp = GetLayerNum(end.x, end.y);
	assert("���C���[�̏d�Ȃ�ő�l5�𒴂��Ă��܂�", temp < MAX_OVERLAP);
	//tempMap��������ڂ�
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			map_[temp + 1][i + (int)end.y * 9][j + (int)end.x * 9] = tempMap[i][j];
			if (map_[temp + 1][i + (int)end.y * 9][j + (int)end.x * 9] == 9) {
				player->SetPlayerMapPos({ (float)(i + (int)end.y * 9), (float)(j + (int)end.x * 9) });
				map_[temp + 1][i + (int)end.y * 9][j + (int)end.x * 9] = 0;
			}
		}
	}

}


