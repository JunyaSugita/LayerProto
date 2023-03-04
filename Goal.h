#pragma once
#include "Vector2.h"
#include "DxLib.h"
#include "Field.h"
#include "Frame.h"


class Goal final
{
private:
	Vector2 pos;
	//��Ƀu���b�N������Ƃ�
	bool isOverlap = false;

	int effectCount = 0;

private:
	Goal() { ; }
	~Goal() { ; }

public:
	//�R�s�[�R���X�g���N�^�𖳌�
	Goal(const Goal& obj) = delete;
	//������Z�q��
	Goal& operator=(const Goal& obj) = delete;

	static Goal& GetInstance();

	void Initialize();

	//�S�[���ɏd�Ȃ��ĂȂ������ׂ�
	void CheckOverlapBlock(Field* field);

	void Draw();

	void SetIsOverlap(bool is) { isOverlap = is; }
	void SetMapPos(Vector2 mapPos);

	Vector2 GetPos() { return pos; }
	Vector2 GetMapPos();
};

