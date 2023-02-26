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

	static const int depthLayerNum = 5;

	static const float layerWidth;
	static const float layerHeight;

public: //�����o�֐�

	Layer();
	~Layer();
	void Initialize(int widthNum, int heightNum);
	void Update(char* keys, char* oldkeys, int mouseX, int mouseY, int oldMouseX, int oldMouseY);
	void Draw();
	void Delete();

	void SerchFrame(int frameWidthNum, Vector2 freamPos[][3]);

	Vector2 CheckHasFream(int frameWidthNum, Vector2 freamPos[][3]);

private: //�����o�ϐ�
	////�u���b�N�̏��9x9
	//BlockType blockTypes[layerBlockHeight][layerBlockWidth] = {};
	////�u���b�N�̍��W
	//Vector2 blockPos[layerBlockHeight][layerBlockWidth] = {};

	//���̃��C���[������t���[���̔ԍ�
	int freamNumX;
	int freamNumY;

	//���C���[�̍��W
	Vector2 layerPos;

	//�I������Ă��邩�ǂ���
	bool isSelect = false;
	//�ړ���
	Vector2 movePos;

	//���C���[�̒��S���W
	Vector2 layerCenterPos;

	//���C���[�̐[��
	int depthLayer[depthLayerNum];

	//�őO�ʃt���O
	bool isfront;

	int button;
	int clickX;
	int clickY;
	int logType;


public: //�A�N�Z�b�T
	////�u���b�N�̏�Ԃ��Z�b�g
	//void SetBlock(int y, int x, BlockType block);
	////�u���b�N�̏�Ԃ��Q�b�g
	//BlockType GetBlock(int y, int x);

	std::vector<std::vector<std::unique_ptr <Block>>> blocks_;

	void SetPos(Vector2 pos) { layerPos = pos; };
	Vector2 GetLayerPos() { return  layerPos; }

	bool GetIsSelect() { return isSelect; }
	void SetIsSelect(int isSelected) { isSelect = isSelected; }

	int GetFrameNumX() { return freamNumX; }
	int GetFrameNumY() { return freamNumY; }

	Vector2 GetLayerCenterPos() { return layerCenterPos; }

	void SetIsFront() { isfront = true; }

};


