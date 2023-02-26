#include "Layer.h"
#include "DxLib.h"

using BlockType = Block::BlockType;

const float Layer::layerWidth = Block::BLOCK_SIZE * layerBlockWidth;
const float Layer::layerHeight = Block::BLOCK_SIZE * layerBlockHeight;

Layer::Layer()
{
	freamNumX = 0;
	freamNumY = 0;
	layerPos = { 0,0 };
}

Layer::~Layer()
{

	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			blocks_[i][j].reset();
		}
	}
}

void Layer::Delete()
{

}


void Layer::Initialize(int heightNum, int widthNum)
{
	freamNumX = widthNum;
	freamNumY = heightNum;

	for (int i = 0; i < layerBlockWidth; i++)
	{
		//�u���b�N�^�����Ă��̃x�N�^��ǉ�(�s��ł���i��)
		blocks_.push_back(std::vector<std::unique_ptr <Block>>());

		for (int j = 0; j < layerBlockWidth; j++)
		{
			std::unique_ptr <Block> block_;
			block_ = std::make_unique<Block>();
			block_->Initialize();
			//�u���b�N�̗v�f��ǉ�
			blocks_[i].push_back(std::move(block_));
		}
	}

	//���W�̏�����
	for (int i = 0; i < layerBlockWidth; i++)
	{
		for (int j = 0; j < layerBlockHeight; j++)
		{
			Vector2 pos;
			//�u���b�N�̍��W��ݒ�
			if (i >= 0)
			{
				pos.y = (i * Block::BLOCK_SIZE) + (heightNum * layerWidth);

			}
			if (j >= 0)
			{
				pos.x = (j * Block::BLOCK_SIZE) + (widthNum * layerWidth);
			}

			blocks_[i][j]->SetPos(pos);

			//�`��̏�����(CSV�t�@�C���̓ǂݍ��񂾌`����u���b�N�N���X�ɓn��)
			BlockType blockType;
			if (i == 0 || j == 0)
			{
				blockType = BlockType::NOLAYER_BLOCK;
				blocks_[i][j]->SetType(blockType);
			}
			/*else if(i == layerBlockWidth - 1 || j == layerBlockHeight - 1)
			{
				blockType = BlockType::NOLAYER_BLOCK;
				blocks_[i][j]->SetType(blockType);
			}*/
			else if(i == j)
			{
				blockType = BlockType::FIXED_BLOCK;
				blocks_[i][j]->SetType(blockType);
			}
			else
			{
				blockType = BlockType::NONE;
				blocks_[i][j]->SetType(blockType);
			}

		}
	}

	movePos.x = 0;
	movePos.y = 0;

	layerCenterPos.x = layerPos.x + (layerWidth / 2);
	layerCenterPos.y= layerPos.y + (layerHeight / 2);

}

void Layer::Update(char* keys, char* oldkeys,int mouseX, int mouseY, int oldMouseX, int oldMouseY)
{
	layerCenterPos.x = layerPos.x + (layerWidth / 2);
	layerCenterPos.y = layerPos.y + (layerHeight / 2);

	//�����I�����ꂽ��
	if (isSelect == true)
	{
		//���N���b�N�������ꑱ���Ă���Ƃ�
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			//�ړ��ʂ��v�Z
			movePos.x = mouseX - oldMouseX;
			movePos.y = mouseY - oldMouseY;

			//���C���[���ړ�
			layerPos += movePos;

			//�u���b�N�̈ړ��ʂ�ݒ�
			for (int i = 0; i < layerBlockWidth; i++)
			{
				for (int j = 0; j < layerBlockHeight; j++)
				{
					blocks_[i][j]->SetMove(movePos);
				}
			}
		}
		else // ������Ă��Ȃ���
		{
			//�ړ��ʂ�0��
			movePos.x = 0;
			movePos.y = 0;
			
			for (int i = 0; i < layerBlockWidth; i++)
			{
				for (int j = 0; j < layerBlockHeight; j++)
				{
					blocks_[i][j]->SetMove(movePos);
				}
			}
			//�I��������
			isSelect = false;
		}
	}

	//�u���b�N�̍X�V
	for (int i = 0; i < layerBlockWidth; i++)
	{
		for (int j = 0; j < layerBlockHeight; j++)
		{
			blocks_[i][j]->Update();
		}
	}
}

void Layer::Draw()
{
	DrawBox(layerPos.x, layerPos.y, layerPos.x + layerWidth, layerPos.y + layerHeight, GetColor(255, 255, 255), false);

	for (int i = 0; i < layerBlockWidth; i++)
	{
		for (int j = 0; j < layerBlockHeight; j++)
		{
			blocks_[i][j]->Draw();
		}
	}
}

void Layer::SerchFrame(int frameWidthNum, Vector2 freamPos[][3])
{
	for(int i = 0; i < frameWidthNum; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			//�e�t���[���͈͓̔��ɂ��邩�ǂ����𔻒肷��
			if(layerCenterPos.x > freamPos[i][j].x && layerCenterPos.x < freamPos[i][j].x + Layer::layerWidth)
			{
				if(layerCenterPos.y > freamPos[i][j].y && layerCenterPos.y < freamPos[i][j].y + Layer::layerHeight)
				{
					//�����Ă��郌�C���[��g�ɂ͂߂�
					layerPos = freamPos[i][j];

				
				}
			}
		}
	}

	for(int i = 0; i < layerBlockWidth; i++)
	{
		for(int j = 0; j < layerBlockHeight; j++)
		{
			Vector2 pos;

			//�u���b�N�̍��W��ݒ�
			if(i >= 0)
			{
				pos.y = (i * Block::BLOCK_SIZE) + layerPos.y;

			}
			if(j >= 0)
			{
				pos.x = (j * Block::BLOCK_SIZE) + layerPos.x;
			}

			blocks_[i][j]->SetPos(pos);
		}
	}
}

Vector2 Layer::CheckHasFream(int frameWidthNum, Vector2 freamPos[][3])
{
	for(int i = 0; i < frameWidthNum; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			//�e�t���[���͈͓̔��ɂ��邩�ǂ����𔻒肷��
			if(layerCenterPos.x > freamPos[i][j].x && layerCenterPos.x < freamPos[i][j].x + Layer::layerWidth)
			{
				if(layerCenterPos.y > freamPos[i][j].y && layerCenterPos.y < freamPos[i][j].y + Layer::layerHeight)
				{
					Vector2 freamArray;
					freamArray.x = i;
					freamArray.y = j;

					return freamArray;
				}
			}
		}
	}
}

//
//void Layer::SetBlock(int y, int x, BlockType block)
//{
//	this->blockTypes[y][x] = block;
//}
//
//BlockType Layer::GetBlock(int y, int x)
//{
//	return this->blockTypes[y][x];
//}




