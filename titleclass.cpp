#include "titleclass.h"


int titleX, titleY, titleGraph;//タイトル処理とグラフィック関連
int Score;//スコア（計測用）
char Scorestr[20];//スコア（表示用）


//タイトル画面描画関数
void Title(){

		InitGraph();//読み込んだ画像をすべて解放

		StopMusic();//今までの音楽を停止する

		//BGMをループ再生（タイトルとメイン
		PlayMusic("game_maoudamashii_7_event44.mid", DX_PLAYTYPE_LOOP);


		//その他設定
		//タイトル画面のグラフィックロード＆座標セット
		titleGraph = LoadGraph("title.bmp");
		titleX = 0, titleY = 0;

		//選択用矢印のグラフィックロード＆座標セット
		chooseGraph = LoadGraph("choose.bmp");
		chooseX = 350, chooseY = 450;

		//スコアの初期化
		Score = 0;

		while (ProcessMessage() == 0, state == TITLE){
			// 画面を初期化(真っ黒にする)
			ClearDrawScreen();

			char titleS[20];//２０文字のメッセージ(start)
			char titleE[20];//20文字のメッセージその２(end)
			unsigned int Color;//符号なし整数型変数COLOR
			Color = GetColor(255, 255, 255);//色の取得

			//文字と画像の表示
			DrawGraph(titleX, titleY, titleGraph, FALSE);

			DrawFormatStringToHandle(380, 450, Color, DefaultHandle, "GAME START", titleS);
			DrawFormatStringToHandle(380, 500, Color, DefaultHandle, "EXIT", titleE);

			//メニューの上にちょっとした説明を
			DrawString(420,400,"PUSH SPACE KEY",Color);

			//メニューを線で囲む
			DrawLine(320, 420, 320, 570, Color);//左縦線
			DrawLine(320, 420, 640, 420, Color);//上横線
			DrawLine(640, 420, 640, 570, Color);//右縦線
			DrawLine(320, 570, 640, 570, Color);//下横線

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
				if (SpaceTrigger() == TRUE) End = -1;//ゲームを終了へ導く
				break;
			default:
				break;
			}
			

			//最終的な処理
			ScreenFlip();
			if (ProcessMessage() < 0) break;
			if (End == -1)break;
		}
}

