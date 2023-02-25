#pragma once
#include "Vector2.h"

//���C���[�̒��̈�̃u���b�N
class Block
{

public: //�N���X���O���[�o���萔

	enum BlockType
	{
		NONE,        //�Ȃɂ��Ȃ�
		LAYER_BLOCK, //���C���[�ƈꏏ�ɓ����u���b�N
		FIXED_BLOCK, //�Œ�u���b�N
		NOLAYER_BLOCK//�g�͂��邯�ǃ��C���[�����p
	};

	//const float BLOCK_SIZE = 30.0f;
	static const float BLOCK_SIZE;
	const float BLOCK_RADIUS = BLOCK_SIZE / 2;

public: //�����o�֐�
	void Initialize();
	void Update();
	void Draw();

private: //�����o�ϐ�
	//�`��
	BlockType type_;
	//���W
	Vector2 pos_;

	Vector2 move_;

public: //�A�N�Z�b�T

	Vector2 GetPos() { return pos_; }

	//CSV�t�@�C���ǂݍ��݂œ����A�`����e�u���b�N�ɃZ�b�g����
	void SetType(BlockType type) { type_ = type; };

	void SetPos(Vector2 pos) { pos_ = pos; };

	void SetMove(Vector2 move) { move_ = move; }
};