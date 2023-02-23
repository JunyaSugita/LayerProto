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
	//�v���C���[�̐����Ə�����
	player_ = std::make_unique<Player>();
	player_->Initialize();
}


void GameScene::Update()
{
	//�v���C���[
	player_->Updata(1350,450);
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

	//�v���C���[�̕\��
	player_->Draw();
}
