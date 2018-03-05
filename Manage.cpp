#include "Manage.h"


GameState state = TITLE;
int End = 0;//�Q�[���I���̔����\���i0�͑��s�A-1�͏I���j

BOOL Upprev;//���L�[�`�F�b�N
BOOL Downprev;//���L�[�`�F�b�N
BOOL Spaceprev;//�X�y�[�X�L�[�`�F�b�N
int keyU;//���L�[�`�F�b�N�ޗ�
int keyD;//���L�[�`�F�b�N�ޗ�
int keyS;//�X�y�[�X�L�[�`�F�b�N�ޗ�
int DefaultHandle,BigHandle;//�t�H���g�T�C�Y�ϐ�

int chooseX, chooseY, chooseGraph;//�I��p���̃O���t�B�b�N�֘A


//winmain�֐�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdEhow)
{


	//�E�B���h�E���[�h�ύX
	ChangeWindowMode(TRUE);


	//��ʃT�C�Y�̐ݒ�
	 SetGraphMode(1000, 600, 16);

	// �c�w���C�u��������������
	if (DxLib_Init() == -1) return -1;

	//���ߐF�̐ݒ�
	SetTransColor(128, 128, 128);

	// �O���t�B�b�N�̕`���𗠉�ʂɃZ�b�g
	SetDrawScreen(DX_SCREEN_BACK);

	//�t�H���g�̒�`
	DefaultHandle = CreateFontToHandle(NULL, 40, 3, -1);//�f�t�H���g�t�H���g�A�T�C�Y�S�O�A�����R�A�f�t�H���g�t�H���g�^�C�v
	BigHandle = CreateFontToHandle(NULL, 100, 4, -1);

	
	while (ProcessMessage == 0 , CheckHitKey(KEY_INPUT_ESCAPE) == 0 && End == 0){

		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		//��ʕ`��֐��ɐ؂�ւ�
		switch (state){
		case TITLE:
			Title();
			break;
		case MAIN:
			Main();
			break;
		case GAMEOVER:
			GameOver();
			break;
		case CLEAR:
			Clear();
			break;
		default:
			break;
		}

		ScreenFlip();// ����ʂ̓��e��\��ʂɃR�s�[����

	}


	// �c�w���C�u�����g�p�̏I������
	DxLib_End();

	// �\�t�g�̏I��
	return 0;
}



//�X�y�[�X�L�[�`�F�b�N�֐�
BOOL SpaceTrigger(){
	if (keyS == 1){
		if (Spaceprev == FALSE){
			Spaceprev = TRUE;//Spaceprev�͂ƂĂ���؁I
			return TRUE;
		}
	}
	else{
		Spaceprev = FALSE;
	}
	return FALSE;
}

//���L�[�`�F�b�N�֐�
BOOL UpTrigger(){
	if (keyU == 1){
		if (Upprev == FALSE){
			Upprev = TRUE;//Upprev�͂ƂĂ���؁I
			return TRUE;
		}
	}
	else{
		Upprev = FALSE;
	}
	return FALSE;
}

//���L�[�`�F�b�N�֐�
BOOL DownTrigger(){
	if (keyD == 1){
		if (Downprev == FALSE){
			Downprev = TRUE;//Downprev�͂ƂĂ���؁I
			return TRUE;
		}
	}
	else{
		Downprev = FALSE;
	}
	return FALSE;
}