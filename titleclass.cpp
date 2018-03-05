#include "titleclass.h"


int titleX, titleY, titleGraph;//�^�C�g�������ƃO���t�B�b�N�֘A
int Score;//�X�R�A�i�v���p�j
char Scorestr[20];//�X�R�A�i�\���p�j


//�^�C�g����ʕ`��֐�
void Title(){

		InitGraph();//�ǂݍ��񂾉摜�����ׂĉ��

		StopMusic();//���܂ł̉��y���~����

		//BGM�����[�v�Đ��i�^�C�g���ƃ��C��
		PlayMusic("game_maoudamashii_7_event44.mid", DX_PLAYTYPE_LOOP);


		//���̑��ݒ�
		//�^�C�g����ʂ̃O���t�B�b�N���[�h�����W�Z�b�g
		titleGraph = LoadGraph("title.bmp");
		titleX = 0, titleY = 0;

		//�I��p���̃O���t�B�b�N���[�h�����W�Z�b�g
		chooseGraph = LoadGraph("choose.bmp");
		chooseX = 350, chooseY = 450;

		//�X�R�A�̏�����
		Score = 0;

		while (ProcessMessage() == 0, state == TITLE){
			// ��ʂ�������(�^�����ɂ���)
			ClearDrawScreen();

			char titleS[20];//�Q�O�����̃��b�Z�[�W(start)
			char titleE[20];//20�����̃��b�Z�[�W���̂Q(end)
			unsigned int Color;//�����Ȃ������^�ϐ�COLOR
			Color = GetColor(255, 255, 255);//�F�̎擾

			//�����Ɖ摜�̕\��
			DrawGraph(titleX, titleY, titleGraph, FALSE);

			DrawFormatStringToHandle(380, 450, Color, DefaultHandle, "GAME START", titleS);
			DrawFormatStringToHandle(380, 500, Color, DefaultHandle, "EXIT", titleE);

			//���j���[�̏�ɂ�����Ƃ���������
			DrawString(420,400,"PUSH SPACE KEY",Color);

			//���j���[����ň͂�
			DrawLine(320, 420, 320, 570, Color);//���c��
			DrawLine(320, 420, 640, 420, Color);//�㉡��
			DrawLine(640, 420, 640, 570, Color);//�E�c��
			DrawLine(320, 570, 640, 570, Color);//������

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
				if (SpaceTrigger() == TRUE) End = -1;//�Q�[�����I���֓���
				break;
			default:
				break;
			}
			

			//�ŏI�I�ȏ���
			ScreenFlip();
			if (ProcessMessage() < 0) break;
			if (End == -1)break;
		}
}

