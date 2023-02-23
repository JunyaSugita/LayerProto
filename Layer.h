#pragma once
#include<list>

enum Block
{
	LAYER_BLOCK = 1, //���C���[�ƈꏏ�ɓ����u���b�N
	FIXED_BLOCK, //�Œ�u���b�N
};

//�ꖇ�̃��C���[
class Layer
{
public:
	//�ꖇ�̃��C���[�̃u���b�N��
	static const int layerBlockWidth = 9;
	static const int layerBlockHeight = 9;

private:
	//�u���b�N�̏��9x9
	Block blocks[layerBlockHeight][layerBlockWidth] = {};

public:
	//�u���b�N�̏�Ԃ��Z�b�g
	void SetBlock(int y, int x, Block block);
	//�u���b�N�̏�Ԃ��Q�b�g
	Block GetBlock(int y, int x);
};


