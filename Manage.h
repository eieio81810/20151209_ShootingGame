#ifndef __MANAGE_H__//�����C���N���[�h��h�~����
#define __MANAGE_H__//�����C���N���[�h��h�~����

#include "DxLib.h"//���C�u�������C���N���[�h
//#include "loding.h"//�摜�Ǎ��֐����C���N���[�h�i�{���j�����s�B�Ȃ���DrawGraph���o���Ȃ������B
#include "titleclass.h"//�^�C�g���֐����C���N���[�h�i�����Y���j
#include "Main.h"//���C���֐����C���N���[�h�iWeb���j
#include "GameOver.h"
#include "GameClear.h"


//�Q�[����ԁi�萔�A�����t���j
enum GameState{
	TITLE, MAIN, GAMEOVER, CLEAR
};//0,1,2,3�Ɣԍ����^�����Ă���

//�֐��v���g�^�C�v�錾
BOOL SpaceTrigger();//�X�y�[�X�L�[�`�F�b�N�֐�
BOOL UpTrigger();//���L�[�`�F�b�N�֐�
BOOL DownTrigger();//���L�[�`�F�b�N�֐�


//extern�͐錾�ł���A��`�ł͂Ȃ�
//��`��Y���Ƙ_���G���[����������
//�����̃t�@�C�����ׂ��Ő��l�𗘗p����֐��͂����Ő錾���悤

extern int DefaultHandle,BigHandle;//�t�H���g�T�C�Y�p�ϐ�

extern int titleX, titleY, titleGraph;//�^�C�g�������ƃO���t�B�b�N�֘A
extern int chooseX, chooseY, chooseGraph;//�I��p���̃O���t�B�b�N�֘A

extern int jetX, jetY, jetGraph, jW, jH;//�W�F�b�g�̍��W�A�O���t�B�b�N�A�T�C�Y
extern int SHOTX[], SHOTY[], SHOTFlag[], SHOTGraph;//�W�F�b�g�̒e
extern int SHOTjetFlag;//�W�F�b�g�̎ˌ�����
extern int jetDamageFlag, jetDamageCounter, jetDamageGraph;//�W�F�b�g�̃_���[�W
extern int mutekiCounter;//�W�F�b�g�̖��G���Ԍv��

extern int backX, backY,backGraph;//�w�i
extern int speedX[], speedY[], speedGraph[],speedW[],speedH[];//�X�s�[�h��

extern int lifeX[3], lifeY[3], lifeGraph[3];//�n�[�g(�c�@��3��MAX�j
extern int lifeW[3], lifeH[3], lX, LP;//�n�[�g�T�C�Y�A���W�A�c�@

extern int Score;//�X�R�A�i�v���p�j
extern char Scorestr[];//�X�R�A�i�\���p�j

extern int h;//�z��̓Y���ih�̓n�[�g�j
extern int i, ii;//�z��̓Y��(i�̓W�F�b�g�e�Aii�̓G�l�~�[�e)
extern int eH,eW,jj; //�z��(eH�͓G�̏c�z��AeW�͉��z��Ajj�̓X�s�[�h��)

/*��قǒǉ������ϐ�	4���
�@�@int SHOTW,SHOTH,jetW,jetH*/


extern GameState state;//�Q�[���̃X�e�[�^�X��\��
extern int End;//�Q�[���I���̔����\���i0�͑��s�A-1�͏I���j

extern int keyS;//�X�y�[�X�L�[�`�F�b�N�ޗ�
extern int keyU;//���L�[�`�F�b�N�ޗ�
extern int keyD;//���L�[�`�F�b�N�ޗ�
extern BOOL Spaceprev;//�X�y�[�X�L�[�`�F�b�N
extern BOOL Upprev;//���L�[�`�F�b�N
extern BOOL Downprev;//���L�[�`�F�b�N



#endif//�����C���N���[�h��h��