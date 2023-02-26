#pragma once
#include "Vector2.h"
#include "DxLib.h"
#include "Field.h"

class Player
{
public:
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
	void Updata(float windowX,float windowY,Field* field);

	/// <summary>
	/// draw
	/// </summary>
	void Draw();

private:
	void CalcMapPos();

private:
	//�Œ�l	//�W�����v�֌W�͈ꉞ�A�c2�}�X�W�����v�A��3�}�X�W�����v�ɒ����ς�
	const float SIZE = 30;			//�v���C���[�̒��a
	const float SPEED = 4.0f;		//���ړ����x
	const float GRAVITY = 10.0f;	//�v���C���[�̏d��
	const float MAX_JUMP = 24.0f;	//�ő�W�����v��
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
};

