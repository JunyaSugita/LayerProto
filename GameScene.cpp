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
		DrawLine(0,i * 50, 1350,i * 50,GetColor(100,100,100));
	}
	//�O���b�h�̕\��(�c)
	for (int i = 1; i < 9 * 3; i++) {
		//���E���̕`��(��)
		if (i % 9 == 0) {
			DrawLine(i * 50, 0, i * 50, 450, GetColor(150, 0, 0));
		}
		//����ȊO(��)
		else{
			DrawLine(i * 50, 0, i * 50, 450, GetColor(100, 100, 100));
		}
	}
}
