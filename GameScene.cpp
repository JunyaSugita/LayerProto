#include "GameScene.h"

//����
GameScene::GameScene(){}

//delete����
GameScene::~GameScene()
{

}

//������
void GameScene::Initialize()
{
	//���œǂݍ���
	StageCSVManager::GetInstance().LoadStageCSV(1);
}


void GameScene::Update()
{
	//�L�[���͂̂����Y��Ă����炨����
	if (CheckHitKey(KEY_INPUT_SPACE)) {
	}
}

void GameScene::Draw()
{
	//�O���b�h�̕\��(��)
	for (int i = 1; i < 9; i++) {
		DrawLine(0,i * BLOCK_SIZE, 1350,i * BLOCK_SIZE,GetColor(100,100,100));
	}
	//�O���b�h�̕\��(�c)
	for (int i = 1; i < 9 * 3; i++) {
		//���E���̕`��(��)
		if (i % 9 == 0) {
			DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, 450, GetColor(150, 0, 0));
		}
		//����ȊO(��)
		else{
			DrawLine(i * BLOCK_SIZE, 0, i * BLOCK_SIZE, 450, GetColor(100, 100, 100));
		}
	}
}
