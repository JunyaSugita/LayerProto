#pragma once
#include "Vector2.h"
#include "DxLib.h"
#include "Field.h"
#include "Frame.h"

enum MapPos {
	LT,	//����
	RT,	//�E��
	LB,	//����
	RB,	//�E��
};

class Player
{
private:
	Player();
	~Player();

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// update
	/// </summary>
	/// <param name="windowX"> �E�B���h�E�T�C�Y(�c) </param>
	/// <param name="windowY"> �E�B���h�E�T�C�Y(��) </param>
	void Updata(float windowX,float windowY,Field* field,Frame* frame);

	/// <summary>
	/// draw
	/// </summary>
	void Draw();

	/// <summary>
	/// �v���C���[�̈ʒu�̎擾
	/// </summary>
	/// <returns> �v���C���[�̈ʒu </returns>
	Vector2 GetPos() {
		return pos_;
	}

	/// <summary>
	/// �v���C���[�̃}�b�v�`�b�v��̈ʒu�̎擾(�p)
	/// </summary>
	/// <param name="Num"> �ǂ̊p���I�� </param>
	/// <returns> �I�������p�̃}�b�v�`�b�v��̈ʒu </returns>
	Vector2 GetMapPos(int Num);

	/// <summary>
	/// �v���C���[�̃}�b�v�`�b�v��̈ʒu�̎擾(����)
	/// </summary>
	/// <returns> �v���C���[�����̃}�b�v�`�b�v��̈ʒu </returns>
	Vector2 GetMapPos();

	/// <summary>
	/// �v���C���[���W�̃Z�b�g(���[���h���W���Z)
	/// </summary>
	/// <param name="pos"> �Z�b�g���������W </param>
	void SetPlayerPos(Vector2 pos) {
		pos_ = pos;
	}

	/// <summary>
	/// �v���C���[���W�̃Z�b�g(�}�b�v�`�b�v���Z)
	/// </summary>
	/// <param name="gridPos"> �}�b�v�`�b�v��̍��W </param>
	void SetPlayerMapPos(Vector2 gridPos) {
		pos_.y = gridPos.x * SIZE + SIZE / 2;
		pos_.x = gridPos.y * SIZE + SIZE / 2;
	}

	static Player* GetInctance();

private:
	void CalcMapPos();

private:
	//�Œ�l
	const float SIZE = 30;			//�v���C���[�̒��a
	const float SPEED = 4.0f;		//���ړ����x
	const float GRAVITY = 22.5f;    //�v���C���[�̏d��
	const float MAX_JUMP = 30.0f;    //�ő�W�����v�� 
	float subJump_ = 0.8f;			//�W�����v�͌����l		

	//�ϐ�
	Vector2 pos_;
	bool isJump_;

	//�W�����v��
	float jumpPow_;
	
	//�v���C���[��4�p�̃}�b�v�`�b�v��̏ꏊ
	Vector2 LT_, RT_, LB_, RB_;
	//�v���C���[�̉��ړ��p
	Vector2 tempPos_ = pos_;

	static Player* player_;
};

