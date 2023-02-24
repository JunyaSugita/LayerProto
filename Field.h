#pragma once
#include "DxLib.h"

enum map
{
	NONE,	//���
	BLOCK,	//�u���b�N
	GOAL,	//�S�[��
};

class Field
{
public:
	Field();
	~Field();

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="map"> �}�b�vcsv(������) </param>
	void Initialize(int map = 0);

	/// <summary>
	/// updata
	/// </summary>
	void Update();

	/// <summary>
	/// draw
	/// </summary>
	void Draw();

private:
	//�Œ�l
	static const int MAP_X = 27;	//�}�b�v�̉��u���b�N��
	static const int MAP_Y = 27;		//�}�b�v�̏c�u���b�N��
	const int BLOCK_SIZE = 30;		//�u���b�N�T�C�Y

	//�}�b�v[y][x](���l�͉�)
	int map_[MAP_Y][MAP_X];

};

