#include "Player.h"
#include <assert.h>
#include "StageCSVManager.h"
#include "Goal.h"

Player* Player::player_ = nullptr;

//����
Player::Player() {}

//delete����
Player::~Player()
{

}

//������
void Player::Initialize()
{
	bool playerPos = false;

	for (int y = 0; y < Frame::GetLayerFrameHeight() * Layer::layerBlockHeight; y++)
	{
		for (int x = 0; x < Frame::GetLayerFrameWidth() * Layer::layerBlockWidth; x++)
		{
			int Y = y / Layer::layerBlockHeight;
			int X = x / Layer::layerBlockWidth;

			std::list<std::unique_ptr<Layer>>& layer = StageCSVManager::GetInstance().frameData.layersInTheFrame[Y][X];

			//�d�Ȃ肪����΂��̕����ǂݍ���
			for (auto itr = layer.begin(); itr != layer.end(); itr++) {
				if (layer.size())
				{
					Block::BlockType block = itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->GetType();
					//�v���C���[�̈ʒu���ǂݍ��܂�Ă�����
					if (block == Block::PLAYER)
					{
						SetPlayerMapPos({ (float)y,(float)x });
						playerPos = true;
						//�����Ƃ�
						itr->get()->blocks_[y % Layer::layerBlockHeight][x % Layer::layerBlockWidth].get()->SetType(Block::NONE);
						break;
					}
				}
			}
			//�����ǂݍ��܂ꂽ��I���
			if (playerPos)
			{
				break;
			}
		}
	}
	//���W���ǂݍ��܂�Ȃ�������
	if (!playerPos)
	{
		SetPlayerMapPos({ 0,0 });
	}

	isJump_ = false;
	jumpPow_ = 0;
	isInvincible_ = false;
}

//update
void Player::Updata(float windowX, float windowY, Field* field, Frame* frame)
{
	//�t���[���𓮂����Ă���Ԃ͏�����S�Ĕ�΂�
	if (frame->GetisSelect()) {
		return;
	}
	if (field->GetIsSelect()) {
		return;
	}

#pragma region ����

	//�W�����v
	if (CheckHitKey(KEY_INPUT_SPACE) || CheckHitKey(KEY_INPUT_W) || CheckHitKey(KEY_INPUT_UP)) {
		//���łɃW�����v���Ă��Ȃ����`�F�b�N
		if (!isJump_) {
			//�W�����v�͂��ő��
			jumpPow_ = MAX_JUMP;
			//�W�����v�t���O�𗧂Ă�
			isJump_ = true;
		}
	}

#pragma endregion

#pragma region �W�����v�֌W

	//�W�����v�͂̌���
	jumpPow_ -= subJump_;

	//�W�����v�͂��}�C�i�X��������0�ɂ���
	if (jumpPow_ < 0) {
		jumpPow_ = 0;
	}

#pragma endregion

#pragma region �u���b�N�Ƃ̓����蔻��ƈړ�
	//�v���C���[�̉��ړ��p
	tempPos_ = pos_;

	//�W�����v�Əd�͂̈ړ�
	float tempMove = jumpPow_ - GRAVITY;
	for (int i = 0; i < 20; i++) {
		tempPos_.y -= tempMove / 20;
		CalcMapPos();

		//�u���b�N�ȂǂƓ������Ă��邩
		if (field->GetMap(LB_) == BLOCK || field->GetMap(RB_) == BLOCK) {
			//���n�Ȃ̂ŃW�����v�t���O���񕜂�����
			isJump_ = false;
			break;
		}
		else if (field->GetMap(LB_) == GOAL || field->GetMap(RB_) == GOAL) {
			//�u���b�N�ł͖����̂ňړ�������
			pos_.y = tempPos_.y;

			//�������Ă���Ȃ�S�[��(������)

		}
		else if (field->GetMap(LT_) == BLOCK || field->GetMap(RT_) == BLOCK) {
			//�V�䂲���񂱂̏���
			jumpPow_ = 0;
			break;
		}
		else {
			//����ȊO�Ȃ�ړ�����������
			//�W�����v�����ɋ󒆂ɍs�����ꍇ�A�v���C���[�̓��������R�ɂ��邽�߁AjumpPow�������ǉ�
			if (isJump_ == false) {
				jumpPow_ = GRAVITY - 0.1f;

				//�Čv�Z
				tempMove = jumpPow_ - GRAVITY;
				tempPos_.y -= tempMove / 10;
				CalcMapPos();
			}

			pos_.y = tempPos_.y;
			//�󒆂ŃW�����v�o���Ȃ��悤�ɂ���
			isJump_ = true;
		}
	}

	tempPos_ = pos_;
	tempMove = 0;
	//���ړ�(��)
	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT)) {
		tempMove -= SPEED;
	}
	//���ړ�(�E)
	if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT)) {
		tempMove += SPEED;
	}
	for (int i = 0; i < 10; i++) {
		tempPos_.x += tempMove / 10;
		CalcMapPos();

		//�u���b�N�ȂǂƓ������Ă��邩
		if (field->GetMap(LT_) == BLOCK || field->GetMap(LB_) == BLOCK) {

		}
		else if (field->GetMap(RT_) == BLOCK || field->GetMap(RB_) == BLOCK) {

		}
		else {
			//����ȊO�Ȃ�ړ�������
			pos_.x = tempPos_.x;
		}
	}

	//�g�Q�ɓ��������玀�ʁI�I
	if (field->GetMap(LT_) == TRAP || field->GetMap(RT_) == TRAP || field->GetMap(LB_) == TRAP || field->GetMap(RB_) == TRAP) {
		if (isInvincible_ == false) {
			StageCSVManager::GetInstance().LoadStageCSV(StageCSVManager::GetInstance().selectNum);
			player_->Initialize();
			field->Initialize();
		}
	}

	//���C���[�O�u���b�N�ɓ��������玀�ʁI�I
	if (field->GetMap(LT_) == NULL_BLOCK || field->GetMap(RT_) == NULL_BLOCK || field->GetMap(LB_) == NULL_BLOCK || field->GetMap(RB_) == NULL_BLOCK) {
		if (isInvincible_ == false) {
			StageCSVManager::GetInstance().LoadStageCSV(StageCSVManager::GetInstance().selectNum);
			player_->Initialize();
			field->Initialize();
		}
	}


#pragma endregion

#pragma region ��ʊO����

	//��
	if (pos_.x - SIZE / 2 < 0) {
		//�����߂�����
		pos_.x = 0 + SIZE / 2;
	}
	//�E
	else if (pos_.x + SIZE / 2 > windowX) {
		//�����߂�����
		pos_.x = windowX - SIZE / 2;
	}

#pragma endregion

	//���G��
	if (CheckHitKey(KEY_INPUT_0)) {
		isInvincible_ = true;
	}


#pragma region �S�[���Ƃ̔���
	
	Goal::GetInstance().CheckEnterGoal(pos_, { SIZE,SIZE });

#pragma endregion
}

//draw
void Player::Draw()
{
	DrawBox(pos_.x - SIZE / 2, pos_.y - SIZE / 2, pos_.x + SIZE / 2, pos_.y + SIZE / 2, GetColor(100, 100, 200), true);

	if (isInvincible_ == false) {
		DrawFormatString(0, 80, GetColor(200, 200, 200), " 0 : ���G��");
	}
	else {
		DrawFormatString(0, 80, GetColor(200, 200, 200), " ���G�����I");
	}
}

Vector2 Player::GetMapPos(int Num)
{
	//������0~3�ȊO�̒l�������Ă�����A�T�[�g
	assert(("GetMapPos()�̈�����0~3�ȊO�̒l�������Ă܂�", Num >= 0 && Num <= 3));

	//0(����)
	if (Num == LT) {
		return LT_;
	}
	//1(�E��)
	else if (Num == RT) {
		return RT_;
	}
	//2(����)
	else if (Num == LB) {
		return LB_;
	}
	//3(�E��)
	else if (Num == RB) {
		return RB_;
	}
}

Vector2 Player::GetMapPos()
{
	return Vector2(pos_.x / 30, pos_.y / 30);
}

void Player::CalcMapPos()
{
	//�}�b�v�`�b�v��̏ꏊ���v�Z
	LT_ = { (tempPos_.x - SIZE / 2) / SIZE,(tempPos_.y - SIZE / 2) / SIZE };
	RT_ = { (tempPos_.x + SIZE / 2 - 1) / SIZE,(tempPos_.y - SIZE / 2) / SIZE };
	LB_ = { (tempPos_.x - SIZE / 2) / SIZE,(tempPos_.y + SIZE / 2 - 1) / SIZE };
	RB_ = { (tempPos_.x + SIZE / 2 - 1) / SIZE,(tempPos_.y + SIZE / 2 - 1) / SIZE };

}

Player* Player::GetInctance()
{
	if (!player_) {
		player_ = new Player();
	}
	return player_;
}



