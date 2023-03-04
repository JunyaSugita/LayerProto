#include "Field.h"
#include "StageCSVManager.h"
#include <assert.h>
#include "Player.h"
#include "Goal.h"

//����
Field::Field() {}

//delete����
Field::~Field()
{

}

void Field::Initialize(int map)
{
	//�}�b�v�̓ǂݍ���

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
					if (block == Block::PLAYER)
					{
						//player�̏��͓���Ȃ�
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

				case TRAP:
					//�g�Q�����F�ŕ`��
					DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(200, 200, 0), true);

				case NOLAYER:
					//���C���[�͂Ȃ����A�g�͂���ꏊ
					SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
					DrawBox(j * BLOCK_SIZE, i * BLOCK_SIZE, j * BLOCK_SIZE + BLOCK_SIZE, i * BLOCK_SIZE + BLOCK_SIZE, GetColor(100, 100, 10), true);
					SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 100);
					break;

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
}

int Field::GetMap(Vector2 pos)
{
	if (map_[0][(int)pos.y][(int)pos.x] == NULL_BLOCK) {
		return NULL_BLOCK;
	}

	for (int i = MAX_OVERLAP - 1; i >= 0; i--) {
		switch (map_[i][(int)pos.y][(int)pos.x]) {
		case NONE:
			break;
		case BLOCK:
			return BLOCK;
			break;
		case GOAL:
			return GOAL;
			break;
		case TRAP:
			return TRAP;
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
	int i;
	for (i = MAX_OVERLAP - 1; i >= 0; i--) {
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
	return i;
}

void Field::MoveLayer(Vector2 start, Vector2 end)
{
	Player* player = Player::GetInctance();

	//�v���C���[��g���ɓ����
	player->SetPlayerMapPos({ (float)(int)player->GetMapPos().y, (float)(int)player->GetMapPos().x });

	//�A�T�[�g
	assert("start.x��0~2�ȊO�̐����������Ă��܂�", start.x >= 0 && start.x <= 2);
	assert("start.y��0~2�ȊO�̐����������Ă��܂�", start.y >= 0 && start.y <= 2);
	assert("end.x��0~2�ȊO�̐����������Ă��܂�", end.x >= 0 && end.x <= 2);
	assert("end.y��0~2�ȊO�̐����������Ă��܂�", end.y >= 0 && end.y <= 2);

	//�g���Ȃ�������ړ������Ȃ�
	if (GetLayerNum(end.x, end.y) < 0)
	{
		return;
	}

	//���t���[���̑w���o��
	int tempMap[9][9];
	int tempS = GetLayerNum(start.x, start.y);	//�n�_�̃t���[���̍őO��
	int tempE = GetLayerNum(end.x, end.y);		//�I�_�̃t���[���̍őO��

	//�N���b�N�����Ƃ��낪���C���[�Ȃ��g��������I���
	if (map_[tempS][(int)start.y * 9][(int)start.x * 9] == NOLAYER)
	{
		return;
	}

	//�v���C���[�̏����Ƃ�
	//�n�_�Ƀv���C���[�����鎞
	if (start.x * 270 <= player->GetPos().x && (start.x + 1) * 270 >= player->GetPos().x && start.y * 270 <= player->GetPos().y && (start.y + 1) * 270 >= player->GetPos().y) {
		map_[tempS][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = PLAYER;
	}
	//�I�_�Ƀv���C���[�����鎞
	else if(end.x * 270 <= player->GetPos().x && (end.x + 1) * 270 >= player->GetPos().x && end.y * 270 <= player->GetPos().y && (end.y + 1) * 270 >= player->GetPos().y) {
		if (map_[tempE][(int)player->GetMapPos().y][(int)player->GetMapPos().x] == NOLAYER) {
			//���C���[���������Ƀv���C���[�����鎞�A�߂����̂��߂�NOLAYER_PLAYER�ɂ���
			map_[tempE][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = NOLAYER_PLAYER;
		}
		else {
			map_[tempE][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = PLAYER;
		}
	}

	//�u���b�N���m���d�Ȃ��Ă��܂��Ă�����ړ������Ȃ�
	for (int k = GetLayerNum(end.x, end.y); k >= 0; k--) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				//�u���b�N���m
				if (map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] == BLOCK && map_[k][i + (int)end.y * 9][j + (int)end.x * 9] == BLOCK) {
					return;
				}
				//�v���C���[�ƃu���b�N
				if (map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] == PLAYER && map_[k][i + (int)end.y * 9][j + (int)end.x * 9] == BLOCK) {
					map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] = NONE;
					return;
				}
				//�u���b�N�ƃv���C���[
				if (map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] == BLOCK && map_[k][i + (int)end.y * 9][j + (int)end.x * 9] == PLAYER) {
					map_[k][i + (int)end.y * 9][j + (int)end.x * 9] = NONE;
					return;
				}
				//����Ă��邱�Ƃ͏�Ɠ��������ύX����u���b�N�悪�ς��
				if (map_[GetLayerNum(start.x, start.y)][i + (int)start.y * 9][j + (int)start.x * 9] == BLOCK && map_[k][i + (int)end.y * 9][j + (int)end.x * 9] == NOLAYER_PLAYER) {
					map_[k][i + (int)end.y * 9][j + (int)end.x * 9] = NOLAYER;
					return;
				}
			}
		}
	}

	//����Ă����v���C���[�̏�������
	if (end.x * 270 <= player->GetPos().x && (end.x + 1) * 270 >= player->GetPos().x && end.y * 270 <= player->GetPos().y && (end.y + 1) * 270 >= player->GetPos().y) {
		map_[tempE][(int)player->GetMapPos().y][(int)player->GetMapPos().x] = NONE;
	}

	//�����Ȃ���tempMap�ɏ����ڂ�
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			tempMap[i][j] = map_[tempS][i + (int)start.y * 9][j + (int)start.x * 9];
			//���C���[���ꖇ�ŁA�ړ��������烌�C���[�Ȃ��g�ɂ���i���C���[���ړ��ł���ꏊ�j
			if (tempS == 0)
			{
				map_[tempS][i + (int)start.y * 9][j + (int)start.x * 9] = NOLAYER;
			}
			//���Ƀ��C���[������ꍇ�͏���
			else
			{
				map_[tempS][i + (int)start.y * 9][j + (int)start.x * 9] = NULL_BLOCK;
			}
		}
	}

	//�őO�ʂ�T��
	tempS = GetLayerNum(end.x, end.y);
	assert("���C���[�̏d�Ȃ�ő�l10�𒴂��Ă��܂�", tempS < MAX_OVERLAP);
	//tempMap��������ڂ�
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			//�g�Ȃ����C���[�ɏd�˂��炻��������ď㏑��
			if (map_[tempS][i + (int)end.y * 9][j + (int)end.x * 9] == NOLAYER)
			{
				map_[tempS][i + (int)end.y * 9][j + (int)end.x * 9] = tempMap[i][j];
				if (map_[tempS][i + (int)end.y * 9][j + (int)end.x * 9] == PLAYER) {
					player->SetPlayerMapPos({ (float)(i + (int)end.y * 9), (float)(j + (int)end.x * 9) });
					map_[tempS][i + (int)end.y * 9][j + (int)end.x * 9] = NONE;
				}
			}
			//�ʏ펞�͏d�˂Ă���
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

	//�ړ���������ɃS�[���ɏd�Ȃ��Ă邩���ׂ�
	Goal::GetInstance().CheckOverlapBlock(this);
}


