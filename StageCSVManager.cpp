#include "StageCSVManager.h"
#include <fstream>
#include<cassert>
#include<string>
#include <sstream>
#include <iostream>

using BlockType = Block::BlockType;

StageCSVManager& StageCSVManager::GetInstance()
{
	static StageCSVManager instance;
	return instance;
}

void StageCSVManager::LoadStageCSV(int stageNum)
{
	//���Z�b�g
	frameData.Initialize();

	//�t�@�C���J��
	std::ifstream file;

	std::string filePath = "Resources/StageCSV/";
	std::string fileName = "stage";
	char stageNumC[7] = { 0 };
	//int�𕶎���ɕϊ�
	_itoa_s(stageNum, stageNumC, _countof(stageNumC) - 1);
	std::string numString = stageNumC;
	std::string fileCSV = ".csv";

	//�t�@�C���J��
	std::string fileFullPath = filePath + fileName + numString + fileCSV;
	file.open(fileFullPath.c_str());
	assert(file.is_open());

	// 1�s���ǂݍ���
	std::string line;
	while (getline(file, line)) {

		// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
		std::istringstream line_stream(line);

		// ���p�X�y�[�X��؂�ōs�̐擪��������擾
		std::string key;
		getline(line_stream, key, ' ');

		//[//]����n�܂�s�̓R�����g
		if (key.find("//") == 0)
		{
			continue;
		}

		//���������p
		std::string word;

		//��g�̒��̏ꏊ
		if (key == "layersInTheFrame")
		{
			//�c�Ɖ��̈ʒu
			getline(line_stream, word, ' ');
			layersIntheFrameY = (int)std::atoi(word.c_str());
			getline(line_stream, word, ' ');
			layersIntheFrameX = (int)std::atoi(word.c_str());

			//�g�͂��邯�ǃ��C���[�����Ȃ��ꏊ�p
			getline(line_stream, word, ' ');
			//false�Ƃ����āA�������C���[�ς܂�ĂȂ�������
			//if (word == "false" && frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].size() == 0)
			//{
			//	//�v�f���g�̎w��̏ꏊ�Ɋm��
			//	Layer layer;
			//	frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].push_back(layer);
			//	//���C���[��[0][0]��114514����āA���C���[�Ȃ��g�Ƃ킩��悤��
			//	frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].begin()->SetBlock(0, 0, BlockType::NOLAYER_BLOCK);
			//}
		}

		//���C���[�̃u���b�N�z�u
		if (key == "layer")
		{
			//"layer"������s
			getline(file, line);
			// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
			std::istringstream line_stream(line);

			//�v�f���g�̎w��̏ꏊ�Ɋm��
			Layer layer;
			//frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].push_back(layer);

			//�C�e���[�^
			std::list<Layer>::iterator itr =
				//frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].end();
			//end�͍ŏI�v�f�̈���Ȃ̂ł��ǂ�
			itr--;

			//�z��w��p�̃J�E���g
			int x = 0;
			int y = 0;
			//���C���[�̃u���b�N���ׂēǂݍ���
			while (1)
			{
				//�󔒂��ƂɃ��C���[�̃u���b�N���擾
				getline(line_stream, word, ' ');
				//�u���b�N���Z�b�g
				itr->SetBlock(y, x, BlockType((int)std::atoi(word.c_str())));

				//�J�E���g��i�߂�
				x++;
				//�����𒴂�����c��i�߂�
				if (x >= Layer::layerBlockWidth)
				{
					y++;
					x = 0;
					//���s
					getline(file, line);
					line_stream.str(line.c_str());
				}
				//�c���𒴂�����I���
				if (y >= Layer::layerBlockHeight)
				{
					break;
				}
			}
		}
	}
}


