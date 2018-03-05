#include "Manage.h"


GameState state = TITLE;
int End = 0;//ゲーム終了の判定を表す（0は続行、-1は終了）

BOOL Upprev;//↑キーチェック
BOOL Downprev;//↓キーチェック
BOOL Spaceprev;//スペースキーチェック
int keyU;//↑キーチェック材料
int keyD;//↓キーチェック材料
int keyS;//スペースキーチェック材料
int DefaultHandle,BigHandle;//フォントサイズ変数

int chooseX, chooseY, chooseGraph;//選択用矢印のグラフィック関連


//winmain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdEhow)
{


	//ウィンドウモード変更
	ChangeWindowMode(TRUE);


	//画面サイズの設定
	 SetGraphMode(1000, 600, 16);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1) return -1;

	//透過色の設定
	SetTransColor(128, 128, 128);

	// グラフィックの描画先を裏画面にセット
	SetDrawScreen(DX_SCREEN_BACK);

	//フォントの定義
	DefaultHandle = CreateFontToHandle(NULL, 40, 3, -1);//デフォルトフォント、サイズ４０、太さ３、デフォルトフォントタイプ
	BigHandle = CreateFontToHandle(NULL, 100, 4, -1);

	
	while (ProcessMessage == 0 , CheckHitKey(KEY_INPUT_ESCAPE) == 0 && End == 0){

		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		//画面描画関数に切り替え
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

		ScreenFlip();// 裏画面の内容を表画面にコピーする

	}


	// ＤＸライブラリ使用の終了処理
	DxLib_End();

	// ソフトの終了
	return 0;
}



//スペースキーチェック関数
BOOL SpaceTrigger(){
	if (keyS == 1){
		if (Spaceprev == FALSE){
			Spaceprev = TRUE;//Spaceprevはとても大切！
			return TRUE;
		}
	}
	else{
		Spaceprev = FALSE;
	}
	return FALSE;
}

//↑キーチェック関数
BOOL UpTrigger(){
	if (keyU == 1){
		if (Upprev == FALSE){
			Upprev = TRUE;//Upprevはとても大切！
			return TRUE;
		}
	}
	else{
		Upprev = FALSE;
	}
	return FALSE;
}

//↓キーチェック関数
BOOL DownTrigger(){
	if (keyD == 1){
		if (Downprev == FALSE){
			Downprev = TRUE;//Downprevはとても大切！
			return TRUE;
		}
	}
	else{
		Downprev = FALSE;
	}
	return FALSE;
}