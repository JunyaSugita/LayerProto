#pragma once

#include"Frame.h"


//�ǂݍ��ݗp�̃N���X
class StageCSVManager final
{//�ϐ�
private:
	Frame frameData;
	int layersIntheFrameY;
	int layersIntheFrameX;
	

public:
	



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
};
