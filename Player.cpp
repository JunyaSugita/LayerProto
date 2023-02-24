#include "Player.h"

//����
Player::Player(){}

//delete����
Player::~Player()
{

}

//������
void Player::Initialize()
{
	pos_ = {25,425};
	isJump_ = false;
	jumpPow_ = 0;
}

//update
void Player::Updata(float windowX, float windowY)
{
#pragma region ����
	//���ړ�(��)
	if (CheckHitKey(KEY_INPUT_A) || CheckHitKey(KEY_INPUT_LEFT)) {
		pos_.x -= SPEED;
	}
	//���ړ�(�E)
	if (CheckHitKey(KEY_INPUT_D) || CheckHitKey(KEY_INPUT_RIGHT)) {
		pos_.x += SPEED;
	}
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
	//�W�����v�Əd�͂̈ړ�
	pos_.y -= jumpPow_ - GRAVITY;

	//�W�����v�͂̌���
	jumpPow_ -= subJump_;

	//�W�����v�͂��}�C�i�X��������0�ɂ���
	if(jumpPow_ < 0){
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
	if (pos_.y + SIZE / 2 > windowY) {
		//�����߂�����
		pos_.y = windowY - SIZE / 2;
		//������Ȃ̂ŃW�����v�t���O������
		isJump_ = false;
	}

#pragma endregion

	//
}

//draw
void Player::Draw()
{
	DrawBox(pos_.x - SIZE / 2, pos_.y - SIZE / 2, pos_.x + SIZE / 2, pos_.y + SIZE / 2, GetColor(100, 100, 200),true);
}

