#include "DxLib.h"
#include "GameScene.h"

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LayerProto";

// �E�B���h�E����(��)
int WIN_WIDTH = 810;

// �E�B���h�E�c��(��)
int WIN_HEIGHT = 810;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);



	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0, 50, 0);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	GameScene* gameScene = new GameScene();
	gameScene->Initialize();

	//�E�C���h�E�T�C�Y�ݒ�
	WIN_WIDTH = gameScene->BLOCK_SIZE * 9 * 3;
	WIN_HEIGHT = gameScene->BLOCK_SIZE * 9 * 3;
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeChangeEnableFlag(FALSE, TRUE);

	//�t�H���g����
	SetFontSize(32);

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�//
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}

		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
		
		gameScene->Update(keys,oldkeys);
		
		
		// �`�揈��
		gameScene->Draw();

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		//WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}

	//delete����
	delete gameScene;

	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
