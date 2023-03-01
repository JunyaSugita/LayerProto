#pragma once

#include"Frame.h"
#include<functional>


//�ǂݍ��ݗp�̃N���X
class StageCSVManager final
{//�ϐ�
private:
	int layersIntheFrameY;
	int layersIntheFrameX;


public:
	//�X�e�[�W�f�[�^
	Frame frameData;
	int selectNum = 1;

private://�֐�

	StageCSVManager() { ; }
	~StageCSVManager() { ; }

public:
	//�R�s�[�R���X�g���N�^�𖳌�
	StageCSVManager(const StageCSVManager& obj) = delete;
	//������Z�q��
	StageCSVManager& operator=(const StageCSVManager& obj) = delete;

	static StageCSVManager& GetInstance();

	//�X�e�[�W�ǂݍ���
	void LoadStageCSV(int stageNum);

	//�������ԍ��ɂ���ăX�e�[�W�ǂݍ���
	void UpdateLoadStage(std::function<void()>f);
};

