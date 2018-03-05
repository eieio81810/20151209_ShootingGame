#include "GameOver.h"

//ゲームオーバー画面

void GameOver(){

	InitGraph();//読み込んだ画像をすべて解放

	StopMusic();//今までの音楽を停止する

	PlayMusic("game_maoudamashii_9_jingle07.mid", DX_PLAYTYPE_BACK);//ゲームオーバー曲を流す

	//選択用矢印のグラフィックロード＆座標セット
	chooseGraph = LoadGraph("choose.bmp");
	chooseX = 350, chooseY = 450;

	//ゲームオーバー処理
	while (ProcessMessage == 0,state==GAMEOVER){

		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		char endS[20];//２０文字のメッセージ
		char endN[20];//20文字のメッセージ(new game)
		char endT[20];//20文字のメッセージ(to title)
		unsigned int endColor;//符号なし整数型変数COLOR
		endColor = GetColor(255, 255, 255);//色の取得

		//文字の表示
		DrawFormatStringToHandle(260, 100, endColor,BigHandle, "GAME OVER", endS);

		sprintfDx(Scorestr, "YOUR SCORE %d", Score);
		DrawString(400, 300, Scorestr, endColor);//スコアを表示する


		//メニューの上にちょっとした説明を
		DrawString(420, 400, "PUSH SPACE KEY", endColor);

		//メニューを線で囲む
		DrawLine(320, 420, 320, 570, endColor);//左縦線
		DrawLine(320, 420, 640, 420, endColor);//上横線
		DrawLine(640, 420, 640, 570, endColor);//右縦線
		DrawLine(320, 570, 640, 570, endColor);//下横線


		DrawFormatStringToHandle(380, 450, endColor, DefaultHandle, "NEW GAME", endN);
		DrawFormatStringToHandle(380, 500, endColor, DefaultHandle, "TO TITLE", endT);

		// ↑キーで矢印を上に移動させる
		keyU = CheckHitKey(KEY_INPUT_UP);
		if (UpTrigger() == TRUE) {
			chooseY -= 50;

			PlaySound("se_maoudamashii_system37.wav", DX_PLAYTYPE_BACK);
		}

		// ↓キーで矢印を下に移動させる
		keyD = CheckHitKey(KEY_INPUT_DOWN);
		if (DownTrigger() == TRUE) {
			chooseY += 50;

			PlaySound("se_maoudamashii_system37.wav", DX_PLAYTYPE_BACK);
		}

		//上へ行き過ぎた矢印を一番下へ
		if (chooseY < 450) chooseY = 500;

		//下へ行き過ぎた矢印を一番上へ
		if (chooseY > 500) chooseY = 450;

		//矢印の表示
		DrawGraph(chooseX, chooseY, chooseGraph, TRUE);

		//スペースキーを入力する場所によって以下の処理（スペースキーチェック関数）
		keyS = CheckHitKey(KEY_INPUT_SPACE);
		switch (chooseY){
		case 450:
			if (SpaceTrigger() == TRUE) state = MAIN;//ゲーム開始
			break;
		case 500:
			if (SpaceTrigger() == TRUE) state = TITLE;//ゲームを終了へ導く
			break;
		default:
			break;
		}



		//最終的な処理
		ScreenFlip();
		if (ProcessMessage() < 0) break;

	}
	StopMusic();//今までの音楽を停止する
}