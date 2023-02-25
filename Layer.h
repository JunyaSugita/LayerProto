#pragma once
#include<list>
#include"Block.h"
#include <memory>
#include <vector>

//enum BlockType
//{
//	NONE,        //�Ȃɂ��Ȃ�
//	LAYER_BLOCK, //���C���[�ƈꏏ�ɓ����u���b�N
//	FIXED_BLOCK, //�Œ�u���b�N
//};

//�ꖇ�̃��C���[
class Layer
{
	using BlockType = Block::BlockType;

public: //�N���X���O���[�o���萔

	//�ꖇ�̃��C���[�̃u���b�N��
	static const int layerBlockWidth = 9;
	static const int layerBlockHeight = 9;

	static const float layerWidth;
	static const float layerHeight;

public: //�����o�֐�

	Layer();
	~Layer();
	void Initialize(int widthNum ,int heightNum);
	void Update(char* keys, char* oldkeys);
	void Draw();
	void Delete();

private: //�����o�ϐ�
	////�u���b�N�̏��9x9
	//BlockType blockTypes[layerBlockHeight][layerBlockWidth] = {};
	////�u���b�N�̍��W
	//Vector2 blockPos[layerBlockHeight][layerBlockWidth] = {};

	//�}�E�X���W
	int MouseX;
	int MouseY;
	//�I���������̃}�E�X�̍��W
	int oldMouseX;
	int oldMouseY;

	//�u���b�N�̓񎟌��z��
	//Block* blocks_[layerBlockHeight][layerBlockWidth];
	std::vector<std::vector<std::unique_ptr <Block>>> blocks_;

	//���̃��C���[������t���[���̔ԍ�
	int freamNumX;
	int freamNumY;

	//���C���[�̍��W
	Vector2 layerPos;

	//�I������Ă��邩�ǂ���
	bool isSelect = false;
	//�ړ���
	Vector2 movePos;

	int button;
	int clickX;
	int clickY;
	int logType;


public: //�A�N�Z�b�T
	//�u���b�N�̏�Ԃ��Z�b�g
	void SetBlock(int y, int x, BlockType block);
	//�u���b�N�̏�Ԃ��Q�b�g
	BlockType GetBlock(int y, int x);

	void SetPos(Vector2 pos) { layerPos = pos; };
	Vector2 GetLayerPos() { return  layerPos; }

	bool GetSelect() { return isSelect; }
	void SetSelect(int isSelected) { isSelect = isSelected; }

	int GetFrameNumX() { return freamNumX; }
	int GetFrameNumY() { return freamNumY; }

};


