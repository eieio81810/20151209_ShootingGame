#include "Main.h"

#define E_HEIGHT 8
#define E_WIDTH 3
#define SHOT 1

//�O���[�o���ϐ�


int jetX, jetY, jetGraph, jW, jH;//�W�F�b�g�̍��W�A�O���t�B�b�N�A�T�C�Y
int SHOTX[SHOT], SHOTY[SHOT], SHOTFlag[SHOT], SHOTGraph;//�W�F�b�g�̒e
int SHOTjetFlag;//�W�F�b�g�̎ˌ�����
int jetDamageFlag, jetDamageCounter, jetDamageGraph;//�W�F�b�g�̃_���[�W
int mutekiCounter;//�W�F�b�g�̖��G���Ԍv���i�񖳓G���J�E���g0�j

int backX, backY, backGraph;//�w�i
int speedX[2], speedY[2], speedGraph[2], speedW[2], speedH[2];//�X�s�[�h���̍��W�A�摜�A�T�C�Y

int lifeX[3], lifeY[3], lifeGraph[3];//�n�[�g(�c�@��3��MAX�j
int lifeW[3], lifeH[3], lX, LP;//�n�[�g�T�C�Y�A���W�A�c�@
// Score�ϐ���title�N���X�Œ�`����Ă���

static int enemyX[E_HEIGHT][E_WIDTH], enemyY[E_HEIGHT][E_WIDTH], enemyMuki, enemyGraph[E_HEIGHT][E_WIDTH],//�G���W�A�O���t�B�b�N
enemyDamageFlag[E_HEIGHT][E_WIDTH], enemyDamageCounter[E_HEIGHT][E_WIDTH], enemyDamageGraph[E_HEIGHT][E_WIDTH],//�G�̃_���[�W
enemyW[E_HEIGHT][E_WIDTH], enemyH[E_HEIGHT][E_WIDTH], SHOTW, SHOTH,//�G�T�C�Y�A���e�T�C�Y
EmutekiCounter[E_HEIGHT][E_WIDTH];
int ETamaX[20], ETamaY[20];//�G�e���W
int ETamaFlag[20];//�G�e����
double ETamaEx, ETamaEy;//�G�e�O�p�֐�
int ETamaW, ETamaH, ETamaGraph;//�G�e�O���t�B�b�N
int ETamaCounter[E_HEIGHT][E_WIDTH];

int h;//�z��̓Y���ih�̓n�[�g�j
int i;//�z��̓Y��(i�̓W�F�b�g)
int ii;//�z��Y�����i�G�l�~�[�́j
int eH,eW,jj; //�z��(eH�̓G�l�~�[�̐��c�z��AeW�͉��z��Ajj�̓X�s�[�h��)

int OnePoint;//�G�l�~�[���ꉹ

//�G�l�~�[�̐��𑨂���
enemyData enemies[E_HEIGHT][E_WIDTH];


//���C����ʊ֐�
void Main(){

	InitGraph();//�ǂݍ��񂾉摜�����ׂĉ��
	InitSoundMem();//�ǂݍ��񂾉������ׂĉ��

	//���y�������ꍇ���y�Đ��i���ꂪ�Ȃ��ƃ^�C�g���ł��Ȃ��؂��j
	if(CheckMusic()==0)	PlayMusic("game_maoudamashii_7_event44.mid", DX_PLAYTYPE_LOOP);

	//�W�F�b�g�ݒ�
	// �e����ʏ�ɑ��݂��Ă��邩�ێ�����ϐ��Ɂw���݂��Ă��Ȃ��x���Ӗ�����O�������Ă���
	for (i = 0; i < SHOT; i++)
	{
		SHOTFlag[i] = 0;
	}
	//���l�̏���������
	SHOTjetFlag = 0;//�W�F�b�g�����������ǂ�������

	// �W�F�b�g�̃O���t�B�b�N���������Ƀ��[�h���\�����W���Z�b�g
	jetGraph = LoadGraph("jet.bmp");
	jetX = 10; jetY = 260;
	GetGraphSize(jetGraph, &jW, &jH);// �W�F�b�g�̃T�C�Y�𓾂�
	jetDamageGraph = LoadGraph("bomb.bmp");//�_���[�W���̃O���t�B�b�N���[�h

	// �W�F�b�g���������Ă��邩�ǂ����̕ϐ��Ɂw�������Ă��Ȃ��x��\���O����
	jetDamageFlag = 0;

	//�W�F�b�g�����G���ǂ����̕ϐ��Ɂu���G����Ȃ��v��\��0����
	mutekiCounter = 0;

	//�W�F�b�g�e�̃O���t�B�b�N���������Ƀ��[�h
	SHOTGraph = LoadGraph("jetSHOT.bmp");

	//�e�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(SHOTGraph, &SHOTW, &SHOTH);


	//�G�l�~�[�ݒ�

	// �G�l�~�[�̈ړ��������Z�b�g
	enemyMuki = 1;
	
	for (eH = 0; eH < E_HEIGHT; eH++){
		for (eW = 0; eW < E_WIDTH; eW++){
			//�G�l�~�[��8*3�̏o����������
			enemies[eH][eW].living = TRUE;
			enemyGraph[eH][eW] = LoadGraph("enemy.bmp");//�ʏ펞�̃O���t�B�b�N���[�h
			enemyDamageGraph[eH][eW] = LoadGraph("enemyDamage.bmp");//�_���[�W���̃O���t�B�b�N���[�h
			// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\���O����
			enemyDamageFlag[eH][eW] = 0;
			// �G���e�����^�C�~���O����邽�߂̌v���p�ϐ��ɂO����
			ETamaCounter[eH][eW] = 0;

			// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
			GetGraphSize(enemyGraph[eH][eW], &enemyW[eH][eW], &enemyH[eH][eW]);

			lX = (eH + 1) * enemyW[eH][eW];//���W�v�Z
			enemyX[eH][eW] = 750+eW*(enemyW[eH][eW]+10), enemyY[eH][eW] = lX + 15 * eH;//���W�Z�b�g

			EmutekiCounter[eH][eW] = 0;//�G�l�~�[�̓_�ŏ�ԁ��_�ł��Ă��Ȃ�
		}
	}

	// �G�̒e�̃O���t�B�b�N�����[�h
	ETamaGraph = LoadGraph("enemySHOT.bmp");

	// �G�̒e�̃O���t�B�b�N�̃T�C�Y�𓾂�
	GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

	// �G�̒e�����ł��邩�ǂ�����ێ�����ϐ��Ɂw���ł��Ȃ��x��\���O����
	for (ii = 0; ii < 20; ii++)
	{
		ETamaFlag[ii] = 0;
	}
	ii = 0; //�z��̓Y����������


	//���̑��ݒ�
	//�n�[�g�̐������n�[�g��ǂݍ���
	for (h = 0; h < 3; h++){
		lifeGraph[h] = LoadGraph("heart.bmp");//�n�[�g�̃O���t�B�b�N���[�h
		GetGraphSize(lifeGraph[h], &lifeW[h], &lifeH[h]);//�n�[�g�O���t�B�b�N�̃T�C�Y�擾
		lX = h * lifeW[h]+60;//���W�v�Z
		lifeX[h] = lX + 10, lifeY[h] = 5;//���W�Z�b�g

	}
	LP = 2;//�c�@���ݒ�i���l�{�P���c�@�j

	backGraph = LoadGraph("stage1.bmp");//�w�i�����[�h
	backX = 0, backY = 0;//�w�i�̕\�����W

	for (jj = 0; jj < 2; jj++){
		speedGraph[jj] = LoadGraph("speed.bmp");//�X�s�[�h�������[�h
		GetGraphSize(speedGraph[jj], &speedW[jj], &speedH[jj]);//�T�C�Y�擾
		speedX[jj] = jj*speedW[jj], speedY[jj] = 0;//���W�ݒ�
	}

	Score = 0;//�X�R�A�̏�����

	//�G�l�~�[�̂��ꂽ���̉������[�h
	OnePoint = LoadSoundMem("se_maoudamashii_onepoint20.wav");

	//�ړ����[�`��
	while (ProcessMessage() == 0,state==MAIN){

		// ��ʂ�������(�^�����ɂ���)
		ClearDrawScreen();

		//�w�i��`��
		DrawGraph(backX, backY, backGraph, FALSE);

		//�X�s�[�h���̕`��ƈړ�
		for (jj = 0; jj < 2; jj++){
			DrawGraph(speedX[jj], speedY[jj], speedGraph[jj], TRUE);//�`��
			speedX[jj] -= 2;//2�r�b�g����
			//���ւ�����x�i�񂾂��Ԍ��֑���
			if (speedX[jj] <= -speedW[jj])speedX[jj] = speedW[jj] * 1;
		}

		//�n�[�g��`��(����)
		for (h = 0; h < 3; h++){
			DrawGraph(lifeX[h], lifeY[h], lifeGraph[h], TRUE);
		}

		//�X�R�A��`��i���l�𕶎���֕ϊ�����K�v����j
		unsigned int mainColor = GetColor(0, 0, 0);
		char Scorestr[7] = { 0 };
		sprintfDx(Scorestr,"%d", Score);
		DrawString(650, 17, Scorestr, mainColor);

		Enemy();//�G�l�~�[�֐�
		


		// �������Ă��邩�ǂ����ŏ����𕪊�
		if (jetDamageFlag == 1)
		{

			DeleteGraph(jetGraph);

			// �������Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
			DrawGraph(jetX - 30, jetY - 20, jetDamageGraph, TRUE);

			// �������Ă��鎞�Ԃ𑪂�J�E���^�[�ɂP�����Z����
			jetDamageCounter++;

			// �������������߂� 60 �t���[���o�߂��Ă����甚��������Ԃ���
			// ���ɖ߂��Ă�����
			if (jetDamageCounter > 60){	

				for (i = 0; i < SHOT; i++)SHOTFlag[i] = 0;

				jetGraph = LoadGraph("jet.bmp");//�O���t�B�b�N���[�h
				jetX = 10, jetY = 260;//�W�F�b�g�̈ʒu��������			
				// �w�������Ă��Ȃ��x��\���O����
				jetDamageFlag = 0;

				mutekiCounter = 80;//80�t���[���̊Ԗ��G���

				DeleteGraph(lifeGraph[LP]);//�_���[�W���󂯂��̂�life����
				LP--;//�J�E���g�_�E��

				for (eH = 0; eH < E_HEIGHT; eH++){//�G�l�~�[�������ʒu�ɕ���������
					for (eW = 0; eW < E_WIDTH; eW++){

						//�G�l�~�[���T�̏o����������
						enemies[eH][eW].living = TRUE;
						enemyGraph[eH][eW] = LoadGraph("enemy.bmp");//�ʏ펞�̃O���t�B�b�N���[�h
						enemyDamageGraph[eH][eW] = LoadGraph("enemyDamage.bmp");//�_���[�W���̃O���t�B�b�N���[�h
						// �G�l�~�[�����c�߂Ă��邩�ǂ����̕ϐ��Ɂw�c�߂Ă��Ȃ��x��\���O����
						enemyDamageFlag[eH][eW] = 0;
						// �G���e�����^�C�~���O����邽�߂̌v���p�ϐ��ɂO����
						ETamaCounter[eH][eW] = 0;
						// �G�l�~�[�̈ړ��������Z�b�g
						enemyMuki = 1;

						// �G�l�~�[�̃O���t�B�b�N�̃T�C�Y�𓾂�
						GetGraphSize(enemyGraph[eH][eW], &enemyW[eH][eW], &enemyH[eH][eW]);

						lX = (eH + 1) * enemyW[eH][eW];//���W�v�Z
						enemyX[eH][eW] = 750 + eW*(enemyW[eH][eW] + 10), enemyY[eH][eW] = lX + 15 * eH;//���W�Z�b�g

						EmutekiCounter[eH][eW] = 0;//�G�l�~�[���_�ł��Ă��Ȃ�
					}
				}
			}
		}//��������I��


		//���G���W�F�b�g�𔼓����ɂ��鏈��
		if (mutekiCounter % 2 == 1 && LP>-1){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
			DrawGraph(jetX, jetY, jetGraph, TRUE);//�W�F�b�g�`��
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else{
			if(LP > -1)DrawGraph(jetX, jetY, jetGraph, TRUE);// �W�F�b�g��`��
		}


		if (mutekiCounter > 0)mutekiCounter--;//���G��Ԃ̂Ƃ��̂݃J�E���g�_�E��


		if (jetDamageFlag == 0){//�_���[�W���󂯂Ă���ԉ��L���X�L�b�v
			// ���L�[�ŃW�F�b�g����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_UP) == 1) jetY -= 3;

			// ���L�[�ŃW�F�b�g�����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) jetY += 3;

			// ���L�[�ŃW�F�b�g�����Ɉړ�������
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) jetX -= 3;

			// ���L�[�ŃW�F�b�g���E�Ɉړ�������
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) jetX += 3;


			// �W�F�b�g����ʍ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (jetX < 0) jetX = 0;

			// �W�F�b�g����ʉE�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (jetX > 50) jetX = 50;

			// �W�F�b�g����ʏ�[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (jetY < 50) jetY = 50;

			// �W�F�b�g����ʉ��[����͂ݏo�����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă�����
			if (jetY > 570) jetY = 570;

			// �X�y�[�X�L�[���������ꍇ�͏����𕪊�
			if (CheckHitKey(KEY_INPUT_SPACE))
			{

				// �O�t���[���ŃV���b�g�{�^���������������ۑ�����Ă���ϐ���0��������e�𔭎�
				if (SHOTjetFlag == 0){

					// ��ʏ�ɂłĂ��Ȃ��e�����邩�A�e�̐������J��Ԃ��Ē��ׂ�
					for (i = 0; i < SHOT; i++){

						// �ei����ʏ�ɂłĂ��Ȃ��ꍇ�͂��̒e����ʂɏo��
						if (SHOTFlag[i] == 0){

							int SHOTW, SHOTH;//�W�F�b�g�e�̃T�C�Y
							int jetW, jetH;//�W�F�b�g�̃T�C�Y����2
							GetGraphSize(SHOTGraph, &SHOTW, &SHOTH);//�e�̃T�C�Y�𓾂�
							GetGraphSize(jetGraph, &jetW, &jetH);// �W�F�b�g�̃T�C�Y�𓾂�

							// �ei�̈ʒu���Z�b�g�A�ʒu�̓W�F�b�g�̒��S�ɂ���
							SHOTX[i] = (jetW - SHOTW) / 2 + jetX;
							SHOTY[i] = (jetH - SHOTH) / 2 + jetY;

							//���ˉ�
							PlaySoundFile("se_maoudamashii_battle_gun05.wav", DX_PLAYTYPE_BACK);

							// �ei�͌����_�������đ��݂���̂ŁA���ݏ�Ԃ�ێ�����ϐ��ɂP��������
							SHOTFlag[i] = 1;

							break;//�����o��
						}
					}
				}
				// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂP(������Ă���)����
				SHOTjetFlag = 1;
			}
			else{
				// �V���b�g�{�^����������Ă��Ȃ������ꍇ��
				// �O�t���[���ŃV���b�g�{�^����������Ă�������ۑ�����ϐ��ɂO(������Ă��Ȃ�)����
				SHOTjetFlag = 0;
			}//�X�y�[�X�{�^������I��	



			// ���e�̐��������e�𓮂����������J��Ԃ�
			for (i = 0; i < SHOT; i++)
			{
				// ���@�̒ei�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e���P(���݂���)�̏ꍇ�̂ݍs�� )
				if (SHOTFlag[i] == 1)
				{
					// �ei���P�U�h�b�g�E�Ɉړ�������
					SHOTX[i] += 16;

					// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ��ɂO(���݂��Ȃ�)��������
					if (SHOTX[i] > 1000)
					{
						SHOTFlag[i] = 0;
					}

					// ��ʂɒei��`�悷��
					DrawGraph(SHOTX[i], SHOTY[i], SHOTGraph, TRUE);
				}
			}//���e�ړ������I��

			if (mutekiCounter <= 0){//���G�������蔻��X�L�b�v
				// �G�e�Ǝ����̓����蔻��A�G�e�̐������J��Ԃ�
				for (ii = 0; ii < 20; ii++)
				{
					// �G�eii�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
					if (ETamaFlag[ii] == 1)
					{
						// �����Ƃ̓����蔻��
						if (((ETamaX[ii] > jetX && ETamaX[ii] < jetX + jW) ||
							(jetX > ETamaX[ii] && jetX < ETamaX[ii] + ETamaW)) &&
							((ETamaY[ii] > jetY && ETamaY[ii] < jetY + jH) ||
							(jetY > ETamaY[ii] && jetY < ETamaY[ii] + ETamaH)))
						{
							// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
							ETamaFlag[ii] = 0;

							//������
							PlaySoundFile("se_maoudamashii_explosion06.wav", DX_PLAYTYPE_BACK);

							// �������Ă��邩�ǂ�����ێ�����ϐ��Ɂw�������Ă���x��\���P����
							jetDamageFlag = 1;

							// �������Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
							jetDamageCounter = 0;
						}
					}
				}//�����蔻���
			}//���G�����
		}//�X�L�b�v�����




		//LP���O�ɂȂ�����Q�[���I�[�o�[
		if (LP < 0){
			state = GAMEOVER;
		}
		//�G���S�ł���΃Q�[���N���A�[
		if (allkill() == FALSE)state = CLEAR;


		// ����ʂ̓��e��\��ʂɃR�s�[����
		ScreenFlip();

		// Windows ���L�̖ʓ|�ȏ������c�w���C�u�����ɂ�点��
		// -1 ���Ԃ��Ă����烋�[�v�𔲂���
		if (ProcessMessage() < 0) break;

		// �����d�r�b�L�[��������Ă����烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE)==1) break;

	}//�ړ����[�`���̕�����
}


//�G�l�~�[�֐�
void Enemy(){

		// �G�l�~�[�̈ړ����[�`��
		for (eH = 0; eH < E_HEIGHT; eH++){
			for (eW = 0; eW < E_WIDTH; eW++){
				if (enemies[eH][eW].living == FALSE)continue;

				for (eH = 0; eH < E_HEIGHT; eH++){
					for (eW = 0; eW < E_WIDTH; eW++){
						if (enemies[eH][eW].living == FALSE)continue;
						// ���c�߂Ă��邩�ǂ����ŏ����𕪊�			
						if (enemyDamageFlag[eH][eW] == 1)
						{

							if (ETamaCounter[eH][eW] >= 299)ETamaCounter[eH][eW] = 0;//�e�̔��˂�h��
							// ���c�߂Ă���ꍇ�̓_���[�W���̃O���t�B�b�N��`�悷��
							//30�t���[���o�߂ŃO���t�B�b�N�ω�
							if (enemyDamageCounter[eH][eW]>30){
								enemyGraph[eH][eW] = enemyDamageGraph[eH][eW];//������
							}
							else{
								enemyGraph[eH][eW] = LoadGraph("bomb.bmp");//���j�G�t�F�N�g
							}

							enemyX[eH][eW] -= 1;//�G�l�~�[��O�֑���

							EmutekiCounter[eH][eW] = 1;

							// ���c�߂Ă��鎞�Ԃ𑪂�J�E���^�[�ɂP�����Z����
							enemyDamageCounter[eH][eW]++;

							// �������c�ߏ��߂� 60 �t���[���o�߂��Ă������̘c�񂾏�Ԃ���
							// ���ɖ߂��Ă�����
							if (enemyDamageCounter[eH][eW] > 60){
								// �w�c��ł��Ȃ��x��\���O����
								enemyDamageFlag[eH][eW] = 0;

								enemies[eH][eW].living = FALSE;//������x�O�ɉ������Ă�����G�l�~�[������

								Score += 500;//�X�R�A��500���Z

							}

						}//�\���I��
					}
				}

				// �c��ł��Ȃ��ꍇ�͍��܂Œʂ�̏���
				for (eH = 0; eH < E_HEIGHT; eH++){
					for (eW = 0; eW < E_WIDTH; eW++){
						if (enemies[eH][eW].living == FALSE)continue;
						// �G�l�~�[�̍��W���ړ����Ă�������Ɉړ�����
						if (enemyMuki == 1) enemyY[eH][eW] += 1;
						if (enemyMuki == 0) enemyY[eH][eW] -= 1;


						// �^�񒆂̃G�l�~�[����ʉ��[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
						if (enemyY[eH][eW] > 555)
						{
							enemyY[eH][eW] = 555;
							enemyMuki = 0;
						}

						// �^�񒆂̃G�l�~�[����ʏ�[����ł����ɂȂ��Ă������ʓ��̍��W�ɖ߂��Ă����A�ړ�������������]����
						if (enemyY[eH][eW] < 50)
						{
							enemyY[eH][eW] = 50;
							enemyMuki = 1;
						}
					}

				}



				//�G�l�~�[��`��
				for (eH = 0; eH < E_HEIGHT; eH++){//�J��Ԃ�
					for (eW = 0; eW < E_WIDTH; eW++){
						if (enemies[eH][eW].living == FALSE)continue;

						//���ꂽ���G�l�~�[�𔼓����ɂ��鏈��
						if (EmutekiCounter[eH][eW] % 2 == 1 && enemyDamageCounter[eH][eW]>30){
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 140);
							DrawGraph(enemyX[eH][eW], enemyY[eH][eW], enemyGraph[eH][eW], TRUE);//�G�l�~�[�`��
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}
						else{
							DrawGraph(enemyX[eH][eW], enemyY[eH][eW], enemyGraph[eH][eW], TRUE);// �G�l�~�[�`��
						}


						if (EmutekiCounter[eH][eW] != 0)EmutekiCounter[eH][eW]--;//�G�l�~�[���_�ł��Ă��Ȃ�


						// �G�e�����^�C�~���O���v�����邽�߂̃J�E���^�[
						ETamaCounter[eH][eW] = GetRand(300);

						// �����J�E���^�[�ϐ���299�ȏゾ�����ꍇ�͒e�����������s��
						if (ETamaCounter[eH][eW] >= 299)
						{
							// �������ɓG�e���w���ł��Ȃ��x��Ԃ������ꍇ�̂ݔ��ˏ������s��
							for (ii = 0; ii < 20; ii++){
								if (ETamaCounter[eH][eW] == 0)break;
								if (ETamaFlag[ii] == 0)
								{
									//�G�e�̃T�C�Y�𓾂�
									GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

									// �e�̔��ˈʒu��ݒ肷��
									ETamaX[ii] = enemyX[eH][eW] + enemyW[eH][eW] / 2 - ETamaW / 2;
									ETamaY[ii] = enemyY[eH][eW] + enemyH[eH][eW] / 2 - ETamaH / 2;

									// �e�̏�Ԃ�ێ�����ϐ��Ɂw���ł���x�������P��������
									ETamaFlag[ii] = 1;

									// �e��ł^�C�~���O���v�����邽�߂̕ϐ��ɂO����
									ETamaCounter[eH][eW] = 0;
								}
							}

						}
					}
				}//�G�l�~�[�`�������
			}
		}//�G�l�~�[���[�`��������


		// �G�@�̒eii�̈ړ����[�`��( ���ݏ�Ԃ�ێ����Ă���ϐ��̓��e���P(���݂���)�̏ꍇ�̂ݍs�� )
		for (ii = 0; ii < 20; ii++){
			if (ETamaFlag[ii] == 1)
			{
				// �ei��8�h�b�g���Ɉړ�������
				ETamaX[ii] -= 8;

				// ��ʊO�ɏo�Ă��܂����ꍇ�͑��ݏ�Ԃ�ێ����Ă���ϐ��ɂO(���݂��Ȃ�)��������
				if (ETamaX[ii] < 0)
				{
					ETamaFlag[ii] = 0;
				}
				// ��ʂɒei��`�悷��
				DrawGraph(ETamaX[ii], ETamaY[ii], ETamaGraph, TRUE);
			}
		}


		
			// �e�ƓG�̓����蔻��A�e�̐������J��Ԃ�
			for (i = 0; i < SHOT; i++)
			{
				// �ei�����݂��Ă���ꍇ�̂ݎ��̏����ɉf��
				if (SHOTFlag[i] == 1)
				{
					for (eH = 0; eH < E_HEIGHT; eH++){
						for (eW = 0; eW < E_WIDTH; eW++){
							if (enemies[eH][eW].living == FALSE || enemyDamageFlag[eH][eW]==1)continue;
							// �G�l�~�[�Ƃ̓����蔻��
							if (((SHOTX[i] > enemyX[eH][eW] && SHOTX[i] < enemyX[eH][eW] + enemyW[eH][eW]) ||
								(enemyX[eH][eW] > SHOTX[i] && enemyX[eH][eW] < SHOTX[i] + SHOTW)) &&
								((SHOTY[i] > enemyY[eH][eW] && SHOTY[i] < enemyY[eH][eW] + enemyH[eH][eW]) ||
								(enemyY[eH][eW] > SHOTY[i] && enemyY[eH][eW] < SHOTY[i] + SHOTH)))
							{
								// �ڐG���Ă���ꍇ�͓��������e�̑��݂�����
								SHOTFlag[i] = 0;

								// �G�l�~�[�̊��c�߂Ă��邩�ǂ�����ێ�����ϐ��Ɂw�c�߂Ă���x��\���P����
								enemyDamageFlag[eH][eW] = 1;

								// �G�l�~�[�̊��c�߂Ă��鎞�Ԃ𑪂�J�E���^�ϐ��ɂO����
								enemyDamageCounter[eH][eW] = 0;
								

								//���ꂽ��
								PlaySoundMem(OnePoint, DX_PLAYTYPE_BACK);
							}
						}
					}				
				}
			}
		
}

BOOL allkill(){
	for (eH = 0; eH < E_HEIGHT; eH++){
		for (eW = 0; eW < E_WIDTH; eW++){
			if (enemies[eH][eW].living == TRUE)return TRUE;//�G�͂܂�����
		}
	}
	return FALSE;//�G�͑S�ł���
}

