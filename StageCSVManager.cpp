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
			if (word == "false" && frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].size() == 0)
			{
				//�v�f���g�̎w��̏ꏊ�Ɋm��
				std::unique_ptr <Layer> layer = std::make_unique<Layer>();
				layer->Initialize(Layer::layerBlockWidth, Layer::layerBlockHeight);

				frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].push_back(std::move(layer));
				//���C���[�̃u���b�N�ɘg�Ȃ��Ɠ���āA���C���[�Ȃ��g�Ƃ킩��悤��
				for (int i = 0; i < Layer::layerBlockHeight; i++)
				{
					for (int j = 0; j < Layer::layerBlockWidth; j++)
					{
						frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].begin()->get()->blocks_[i][j]->SetType(BlockType::NOLAYER_BLOCK);
					}
				}
			}
		}

		//���C���[�̃u���b�N�z�u
		if (key == "layer")
		{
			//"layer"������s
			getline(file, line);
			// 1�s���̕�������X�g���[���ɕϊ����ĉ�͂��₷������
			std::istringstream line_stream(line);

			//�v�f���g�̎w��̏ꏊ�Ɋm�ۂ��邽�߂ɕϐ��p��
			std::unique_ptr< Layer> layer = std::make_unique<Layer>();
			layer->Initialize(Layer::layerBlockWidth, Layer::layerBlockHeight);

			//�z��w��p�̃J�E���g
			int x = 0;
			int y = 0;
			//���C���[�̃u���b�N���ׂēǂݍ���
			while (1)
			{
				//�󔒂��ƂɃ��C���[�̃u���b�N���擾
				getline(line_stream, word, ' ');
				//�u���b�N���Z�b�g
				layer->blocks_[y][x]->SetType(BlockType((int)std::atoi(word.c_str())));

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
					//�l����ꂽ���̂����X�g�ɓ����
					frameData.layersInTheFrame[layersIntheFrameY][layersIntheFrameX].push_back(std::move(layer));
					break;
				}
			}
		}
	}

	//�t�@�C������
	file.close();
}


