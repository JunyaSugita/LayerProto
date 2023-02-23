#include "Field.h"

//����
Field::Field(){}

//delete����
Field::~Field()
{

}

void Field::Initialize(int map)
{
	//�}�b�v�̓ǂݍ���(�������̂��߃}�W�b�N�i���o�[�𒼓���)
	int mapTemp[MAP_Y][MAP_X] = {
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0},
		{0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
		{0,0,0,1,0,0,1,0,0,0,0,0,0,1,0,1,0,0,0,0,1,1,1,0,1,0,0},
		{0,0,0,1,0,0,1,1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,2},
	};
	//���
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			map_[i][j] = mapTemp[i][j];
		}
	}
}

void Field::Update()
{

}

void Field::Draw()
{
	for (int i = 0; i < MAP_Y; i++) {
		for (int j = 0; j < MAP_X; j++) {
			//�}�b�v�̐����ɂ���ĕ`�悷��
			switch (map_[i][j])
			{
			case BLOCK:
				//�u���b�N�Ȃ甒�ŕ`��
				DrawBox(j * BLOCK_SIZE,i * BLOCK_SIZE,j * BLOCK_SIZE + BLOCK_SIZE,i * BLOCK_SIZE + BLOCK_SIZE,GetColor(255,255,255),true);
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


