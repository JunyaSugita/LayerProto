#include "Player.h"

//����
Player::Player() {}

//delete����
Player::~Player()
{

}

//������
void Player::Initialize()
{
	pos_ = { 15,135 };
	isJump_ = false;
	jumpPow_ = 0;
}

//update
void Player::Updata(float windowX, float windowY, Field* field)
{
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
	//��(�ޗ�����ɂ���Ȃ炱�̏����͏���)
	//if (pos_.y + SIZE / 2 > 270) {
	//	//�����߂�����
	//	pos_.y = 255;
	//	//������Ȃ̂ŃW�����v�t���O������
	//	isJump_ = false;
	//}

#pragma endregion

#pragma region �u���b�N�Ƃ̓����蔻��ƈړ�
	//�v���C���[�̉��ړ��p
	tempPos_ = pos_;

	//�W�����v�Əd�͂̈ړ�
	float tempMove = jumpPow_ - GRAVITY;
	for (int i = 0; i < 10; i++) {
		tempPos_.y -= tempMove / 10;
		CalcMapPos();

		//�u���b�N�ȂǂƓ������Ă��邩
		if (field->GetMap(LB_) == BLOCK || field->GetMap(RB_) == BLOCK) {
			//���n�Ȃ̂ŃW�����v�t���O���񕜂�����
			isJump_ = false;
			break;
		}
		else if (field->GetMap(LB_) == GOAL || field->GetMap(RB_) == GOAL) {
			//�������Ă���Ȃ�S�[��(������)
			break;
		}
		else if(field->GetMap(LT_) == BLOCK || field->GetMap(RT_) == BLOCK){
			//�V�䂲���񂱂̏���
			jumpPow_ = 0;
			break;
		}
		else {
			//����ȊO�Ȃ�ړ�����������
			pos_.y = tempPos_.y;
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


#pragma endregion

}

//draw
void Player::Draw()
{
	DrawBox(pos_.x - SIZE / 2, pos_.y - SIZE / 2, pos_.x + SIZE / 2, pos_.y + SIZE / 2, GetColor(100, 100, 200), true);
}

void Player::CalcMapPos()
{
	//�}�b�v�`�b�v��̏ꏊ���v�Z
	LT_ = { (tempPos_.x - SIZE / 2) / SIZE,(tempPos_.y - SIZE / 2) / SIZE };
	RT_ = { (tempPos_.x + SIZE / 2 - 1) / SIZE,(tempPos_.y - SIZE / 2) / SIZE };
	LB_ = { (tempPos_.x - SIZE / 2) / SIZE,(tempPos_.y + SIZE / 2 - 1) / SIZE };
	RB_ = { (tempPos_.x + SIZE / 2 - 1) / SIZE,(tempPos_.y + SIZE / 2 - 1) / SIZE };

}



