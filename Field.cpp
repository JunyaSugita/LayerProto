#include "Field.h"
#include "StageCSVManager.h"

//����
Field::Field() {}

//delete����
Field::~Field()
{

}

void Field::Initialize(int map)
{
	//�}�b�v�̓ǂݍ���(�������̂��߃}�W�b�N�i���o�[�𒼓���)

	int mapTemp[MAX_OVERLAP][MAP_Y][MAP_X] /*= {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,0,1,0,0},
		{0,0,0,1,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	}*/;


	for (int y = 0; y < Frame::GetLayerFrameHeight() * Layer::layerBlockHeight; y++)
	{
		for (int x = 0; x < Frame::GetLayerFrameHeight() * Layer::layerBlockWidth; x++)
		{
			int Y = y / Layer::layerBlockHeight;
			int X = x / Layer::layerBlockWidth;

			std::list<std::unique_ptr<Layer>>& layer = StageCSVManager::GetInstance().frameData.layersInTheFrame[Y][X];
			auto itr = layer.begin();
			int count = 0;


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
	for (int k = 0; k < MAX_OVERLAP;k++) {
		for (int i = 0; i < MAP_Y; i++) {
			for (int j = 0; j < MAP_X; j++) {
				map_[k][i][j] = mapTemp[k][i][j];
			}
		}
	}
}

void Field::Update()
{

}

void Field::Draw()
{
	for (int k = 0; k < MAX_OVERLAP; k++) {
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
				//�}�b�v�̐����ɂ���ĕ`�悷��
				switch (map_[k][i][j])
				{
				case BLOCK:
					//�u���b�N�Ȃ甒�ŕ`��
					DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(100, 100, 100), true);
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
	//���C���[�̑w(�őO�ʂ���)
	for (int i = MAX_OVERLAP - 1; i >= 0; i--) {
		//���C���[Y����
		for (int j = y * 9; j < 9 + (y + 1); j++) {
			//���C���[X����
			for (int k = x * 9 ; k < 9 + (x + 1); k++) {
				if (map_[i][j][k] != 0) {
					//1�ł�0�ȊO������΃��C���[������w��Ԃ�
					return i;
				}
			}
		}

	}
	//�������0�w��Ԃ�
	return 0;
}


