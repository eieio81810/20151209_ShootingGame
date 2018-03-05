#include "GameOver.h"

//�Q�[���I�[�o�[���

void GameOver(){

	InitGraph();//�ǂݍ��񂾉摜�����ׂĉ��

	StopMusic();//���܂ł̉��y���~����

	PlayMusic("game_maoudamashii_9_jingle07.mid", DX_PLAYTYPE_BACK);//�Q�[���I�[�o�[�Ȃ𗬂�

	//�I��p���̃O���t�B�b�N���[�h�����W�Z�b�g
	chooseGraph = LoadGraph("choose.bmp");
	chooseX = 350, chooseY = 450;

	//�Q�[���I�[�o�[����
	while (ProcessMessage == 0,state==GAMEOVER){

		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		char endS[20];//�Q�O�����̃��b�Z�[�W
		char endN[20];//20�����̃��b�Z�[�W(new game)
		char endT[20];//20�����̃��b�Z�[�W(to title)
		unsigned int endColor;//�����Ȃ������^�ϐ�COLOR
		endColor = GetColor(255, 255, 255);//�F�̎擾

		//�����̕\��
		DrawFormatStringToHandle(260, 100, endColor,BigHandle, "GAME OVER", endS);

		sprintfDx(Scorestr, "YOUR SCORE %d", Score);
		DrawString(400, 300, Scorestr, endColor);//�X�R�A��\������


		//���j���[�̏�ɂ�����Ƃ���������
		DrawString(420, 400, "PUSH SPACE KEY", endColor);

		//���j���[����ň͂�
		DrawLine(320, 420, 320, 570, endColor);//���c��
		DrawLine(320, 420, 640, 420, endColor);//�㉡��
		DrawLine(640, 420, 640, 570, endColor);//�E�c��
		DrawLine(320, 570, 640, 570, endColor);//������


		DrawFormatStringToHandle(380, 450, endColor, DefaultHandle, "NEW GAME", endN);
		DrawFormatStringToHandle(380, 500, endColor, DefaultHandle, "TO TITLE", endT);

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