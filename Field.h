#pragma once
#include "DxLib.h"
#include "Vector2.h"

enum map
{
	NONE,	//���
	BLOCK,	//�u���b�N
	GOAL,	//�S�[��
	TRAP,	//�g�Q
	NOLAYER,//���C���[�������Ȃ��g
	PLAYER,	//�v���C���[�̏ꏊ
	NOLAYER_PLAYER,	//���C���[�������ꏊ�ł̃v���C���[�̈ʒu
	NULL_BLOCK = -858993460, //�����͂̋��
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
	void Update(int mouseX, int mouseY,int windowWidth,int windowHeight);

	/// <summary>
	/// draw
	/// </summary>
	void Draw();

	/// <summary>
	/// �}�b�v���̎擾
	/// </summary>
	/// <param name="pos"> �擾���������W </param>
	/// <returns> �w����W�̃u���b�N�̎�ޔԍ� </returns>
	int GetMap(Vector2 pos);

	/// <summary>
	/// �w��̃��C���[�̏ꏊ�����w�ڂ��邩
	/// </summary>
	/// <param name="x"> ���C���[���W </param>
	/// <param name="y"> ���C���[���W </param>
	/// <returns> �w��̏ꏊ�Ƀ��C���[�����w���邩 </returns>
	int GetLayerNum(int x,int y);


	void MoveLayer(Vector2 start,Vector2 end);

	bool GetIsSelect() {
		return isSelect_;
	};

	/// <summary>
	/// �v���r���[�̃A�b�v�f�[�g
	/// </summary>
	void PreviewUpdate();

	/// <summary>
	/// �v���r���[��draw
	/// </summary>
	void PreviewDraw();

public:

	//�Œ�l
	static const int MAP_X = 27;	//�}�b�v�̉��u���b�N��
	static const int MAP_Y = 27;	//�}�b�v�̏c�u���b�N��
	static const int BLOCK_SIZE = 30;		//�u���b�N�T�C�Y
	static const int MAX_OVERLAP = 2;		//���C���[�����w�܂ŏd�˂��邩

private:
	//�}�b�v[y][x](���l�͉�)
	int map_[MAX_OVERLAP][MAP_Y][MAP_X];

	Vector2 mouseStart;
	bool isSelect_;

	//�v���r���[�֘A
	int preview_[9][9] = {};
	int mouseX_, mouseY_;
	int layerNum_;

};

