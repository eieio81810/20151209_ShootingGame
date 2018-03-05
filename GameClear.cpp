#include "GameClear.h"


void Clear(){
	InitGraph();//�ǂݍ��񂾉摜�����ׂĉ��

	StopMusic();//���܂ł̉��y���~����

	PlayMusic("game_maoudamashii_9_jingle06.mid", DX_PLAYTYPE_BACK);//�Q�[���N���A�[�Ȃ𗬂�

	//�I��p���̃O���t�B�b�N���[�h�����W�Z�b�g
	chooseGraph = LoadGraph("choose.bmp");
	chooseX = 350, chooseY = 450;

	//�Q�[���N���A�[����
	while (ProcessMessage == 0, state == CLEAR){

		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		char clearS[20];//�Q�O�����̃��b�Z�[�W(strings)
		char clearN[20];//20�����̃��b�Z�[�W(new game)
		char clearT[20];//20�����̃��b�Z�[�W(to title)
		unsigned int clearColor;//�����Ȃ������^�ϐ�COLOR
		clearColor = GetColor(255, 255, 255);//�F�̎擾

		//�����̕\��
		DrawFormatStringToHandle(200, 100, clearColor,BigHandle, "GAME CLEAR!!", clearS);


		//���j���[�̏�ɂ�����Ƃ���������
		DrawString(420, 400, "PUSH SPACE KEY", clearColor);

		sprintfDx(Scorestr, "YOUR SCORE %d", Score);
		DrawString(400, 300, Scorestr, clearColor);//�X�R�A�\��


		//���j���[����ň͂�
		DrawLine(320, 420, 320, 570, clearColor);//���c��
		DrawLine(320, 420, 640, 420, clearColor);//�㉡��
		DrawLine(640, 420, 640, 570, clearColor);//�E�c��
		DrawLine(320, 570, 640, 570, clearColor);//������


		DrawFormatStringToHandle(380, 450, clearColor, DefaultHandle, "NEW GAME", clearN);
		DrawFormatStringToHandle(380, 500, clearColor, DefaultHandle, "TO TITLE", clearT);

		// ���L�[�Ŗ�����Ɉړ�������
		keyU = CheckHitKey(KEY_INPUT_UP);
		if (UpTrigger() == TRUE) {
			chooseY -= 50;

			PlaySound("se_maoudamashii_system37.wav", DX_PLAYTYPE_BACK);
		}

		// ���L�[�Ŗ������Ɉړ�������
		keyD = CheckHitKey(KEY_INPUT_DOWN);
		if (DownTrigger() == TRUE) {
			chooseY += 50;

			PlaySound("se_maoudamashii_system37.wav", DX_PLAYTYPE_BACK);
		}

		//��֍s���߂���������ԉ���
		if (chooseY < 450) chooseY = 500;

		//���֍s���߂���������ԏ��
		if (chooseY > 500) chooseY = 450;

		//���̕\��
		DrawGraph(chooseX, chooseY, chooseGraph, TRUE);

		//�X�y�[�X�L�[����͂���ꏊ�ɂ���Ĉȉ��̏����i�X�y�[�X�L�[�`�F�b�N�֐��j
		keyS = CheckHitKey(KEY_INPUT_SPACE);
		switch (chooseY){
		case 450:
			if (SpaceTrigger() == TRUE) state = MAIN;//�Q�[���J�n
			break;
		case 500:
			if (SpaceTrigger() == TRUE) state = TITLE;//�Q�[�����I���֓���
			break;
		default:
			break;
		}



		//�ŏI�I�ȏ���
		ScreenFlip();
		if (ProcessMessage() < 0) break;

	}
	StopMusic();//���܂ł̉��y���~����
}