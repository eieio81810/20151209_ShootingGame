#include "Main.h"

#define E_HEIGHT 8
#define E_WIDTH 3
#define SHOT 1

//グローバル変数


int jetX, jetY, jetGraph, jW, jH;//ジェットの座標、グラフィック、サイズ
int SHOTX[SHOT], SHOTY[SHOT], SHOTFlag[SHOT], SHOTGraph;//ジェットの弾
int SHOTjetFlag;//ジェットの射撃判定
int jetDamageFlag, jetDamageCounter, jetDamageGraph;//ジェットのダメージ
int mutekiCounter;//ジェットの無敵時間計測（非無敵時カウント0）

int backX, backY, backGraph;//背景
int speedX[2], speedY[2], speedGraph[2], speedW[2], speedH[2];//スピード感の座標、画像、サイズ

int lifeX[3], lifeY[3], lifeGraph[3];//ハート(残機は3がMAX）
int lifeW[3], lifeH[3], lX, LP;//ハートサイズ、座標、残機
// Score変数はtitleクラスで定義されている

static int enemyX[E_HEIGHT][E_WIDTH], enemyY[E_HEIGHT][E_WIDTH], enemyMuki, enemyGraph[E_HEIGHT][E_WIDTH],//敵座標、グラフィック
enemyDamageFlag[E_HEIGHT][E_WIDTH], enemyDamageCounter[E_HEIGHT][E_WIDTH], enemyDamageGraph[E_HEIGHT][E_WIDTH],//敵のダメージ
enemyW[E_HEIGHT][E_WIDTH], enemyH[E_HEIGHT][E_WIDTH], SHOTW, SHOTH,//敵サイズ、自弾サイズ
EmutekiCounter[E_HEIGHT][E_WIDTH];
int ETamaX[20], ETamaY[20];//敵弾座標
int ETamaFlag[20];//敵弾判定
double ETamaEx, ETamaEy;//敵弾三角関数
int ETamaW, ETamaH, ETamaGraph;//敵弾グラフィック
int ETamaCounter[E_HEIGHT][E_WIDTH];

int h;//配列の添字（hはハート）
int i;//配列の添字(iはジェット)
int ii;//配列添え字（エネミーの）
int eH,eW,jj; //配列(eHはエネミーの数縦配列、eWは横配列、jjはスピード感)

int OnePoint;//エネミーやられ音

//エネミーの数を捉える
enemyData enemies[E_HEIGHT][E_WIDTH];


//メイン画面関数
void Main(){

	InitGraph();//読み込んだ画像をすべて解放
	InitSoundMem();//読み込んだ音をすべて解放

	//音楽が無い場合音楽再生（これがないとタイトルでも曲が切れる）
	if(CheckMusic()==0)	PlayMusic("game_maoudamashii_7_event44.mid", DX_PLAYTYPE_LOOP);

	//ジェット設定
	// 弾が画面上に存在しているか保持する変数に『存在していない』を意味する０を代入しておく
	for (i = 0; i < SHOT; i++)
	{
		SHOTFlag[i] = 0;
	}
	//数値の初期化処理
	SHOTjetFlag = 0;//ジェットが撃ったかどうか判定

	// ジェットのグラフィックをメモリにロード＆表示座標をセット
	jetGraph = LoadGraph("jet.bmp");
	jetX = 10; jetY = 260;
	GetGraphSize(jetGraph, &jW, &jH);// ジェットのサイズを得る
	jetDamageGraph = LoadGraph("bomb.bmp");//ダメージ時のグラフィックロード

	// ジェットが爆発しているかどうかの変数に『爆発していない』を表す０を代入
	jetDamageFlag = 0;

	//ジェットが無敵かどうかの変数に「無敵じゃない」を表す0を代入
	mutekiCounter = 0;

	//ジェット弾のグラフィックをメモリにロード
	SHOTGraph = LoadGraph("jetSHOT.bmp");

	//弾のグラフィックのサイズを得る
	GetGraphSize(SHOTGraph, &SHOTW, &SHOTH);


	//エネミー設定

	// エネミーの移動方向をセット
	enemyMuki = 1;
	
	for (eH = 0; eH < E_HEIGHT; eH++){
		for (eW = 0; eW < E_WIDTH; eW++){
			//エネミーを8*3体出現させたい
			enemies[eH][eW].living = TRUE;
			enemyGraph[eH][eW] = LoadGraph("enemy.bmp");//通常時のグラフィックロード
			enemyDamageGraph[eH][eW] = LoadGraph("enemyDamage.bmp");//ダメージ時のグラフィックロード
			// エネミーが顔を歪めているかどうかの変数に『歪めていない』を表す０を代入
			enemyDamageFlag[eH][eW] = 0;
			// 敵が弾を撃つタイミングを取るための計測用変数に０を代入
			ETamaCounter[eH][eW] = 0;

			// エネミーのグラフィックのサイズを得る
			GetGraphSize(enemyGraph[eH][eW], &enemyW[eH][eW], &enemyH[eH][eW]);

			lX = (eH + 1) * enemyW[eH][eW];//座標計算
			enemyX[eH][eW] = 750+eW*(enemyW[eH][eW]+10), enemyY[eH][eW] = lX + 15 * eH;//座標セット

			EmutekiCounter[eH][eW] = 0;//エネミーの点滅状態＝点滅していない
		}
	}

	// 敵の弾のグラフィックをロード
	ETamaGraph = LoadGraph("enemySHOT.bmp");

	// 敵の弾のグラフィックのサイズを得る
	GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

	// 敵の弾が飛んでいるかどうかを保持する変数に『飛んでいない』を表す０を代入
	for (ii = 0; ii < 20; ii++)
	{
		ETamaFlag[ii] = 0;
	}
	ii = 0; //配列の添字を初期化


	//その他設定
	//ハートの数だけハートを読み込む
	for (h = 0; h < 3; h++){
		lifeGraph[h] = LoadGraph("heart.bmp");//ハートのグラフィックロード
		GetGraphSize(lifeGraph[h], &lifeW[h], &lifeH[h]);//ハートグラフィックのサイズ取得
		lX = h * lifeW[h]+60;//座標計算
		lifeX[h] = lX + 10, lifeY[h] = 5;//座標セット

	}
	LP = 2;//残機数設定（数値＋１が残機）

	backGraph = LoadGraph("stage1.bmp");//背景をロード
	backX = 0, backY = 0;//背景の表示座標

	for (jj = 0; jj < 2; jj++){
		speedGraph[jj] = LoadGraph("speed.bmp");//スピード感をロード
		GetGraphSize(speedGraph[jj], &speedW[jj], &speedH[jj]);//サイズ取得
		speedX[jj] = jj*speedW[jj], speedY[jj] = 0;//座標設定
	}

	Score = 0;//スコアの初期化

	//エネミーのやられた時の音をロード
	OnePoint = LoadSoundMem("se_maoudamashii_onepoint20.wav");

	//移動ルーチン
	while (ProcessMessage() == 0,state==MAIN){

		// 画面を初期化(真っ黒にする)
		ClearDrawScreen();

		//背景を描画
		DrawGraph(backX, backY, backGraph, FALSE);

		//スピード感の描画と移動
		for (jj = 0; jj < 2; jj++){
			DrawGraph(speedX[jj], speedY[jj], speedGraph[jj], TRUE);//描画
			speedX[jj] -= 2;//2ビット左へ
			//左へある程度進んだら一番後ろへ送る
			if (speedX[jj] <= -speedW[jj])speedX[jj] = speedW[jj] * 1;
		}

		//ハートを描画(複数)
		for (h = 0; h < 3; h++){
			DrawGraph(lifeX[h], lifeY[h], lifeGraph[h], TRUE);
		}

		//スコアを描画（数値を文字列へ変換する必要あり）
		unsigned int mainColor = GetColor(0, 0, 0);
		char Scorestr[7] = { 0 };
		sprintfDx(Scorestr,"%d", Score);
		DrawString(650, 17, Scorestr, mainColor);

		Enemy();//エネミー関数
		


		// 爆発しているかどうかで処理を分岐
		if (jetDamageFlag == 1)
		{

			DeleteGraph(jetGraph);

			// 爆発している場合はダメージ時のグラフィックを描画する
			DrawGraph(jetX - 30, jetY - 20, jetDamageGraph, TRUE);

			// 爆発している時間を測るカウンターに１を加算する
			jetDamageCounter++;

			// もし爆発し初めて 60 フレーム経過していたら爆発した状態から
			// 元に戻してあげる
			if (jetDamageCounter > 60){	

				for (i = 0; i < SHOT; i++)SHOTFlag[i] = 0;

				jetGraph = LoadGraph("jet.bmp");//グラフィックロード
				jetX = 10, jetY = 260;//ジェットの位置を初期化			
				// 『爆発していない』を表す０を代入
				jetDamageFlag = 0;

				mutekiCounter = 80;//80フレームの間無敵状態

				DeleteGraph(lifeGraph[LP]);//ダメージを受けたのでlife減少
				LP--;//カウントダウン

				for (eH = 0; eH < E_HEIGHT; eH++){//エネミーを初期位置に復活させる
					for (eW = 0; eW < E_WIDTH; eW++){

						//エネミーを５体出現させたい
						enemies[eH][eW].living = TRUE;
						enemyGraph[eH][eW] = LoadGraph("enemy.bmp");//通常時のグラフィックロード
						enemyDamageGraph[eH][eW] = LoadGraph("enemyDamage.bmp");//ダメージ時のグラフィックロード
						// エネミーが顔を歪めているかどうかの変数に『歪めていない』を表す０を代入
						enemyDamageFlag[eH][eW] = 0;
						// 敵が弾を撃つタイミングを取るための計測用変数に０を代入
						ETamaCounter[eH][eW] = 0;
						// エネミーの移動方向をセット
						enemyMuki = 1;

						// エネミーのグラフィックのサイズを得る
						GetGraphSize(enemyGraph[eH][eW], &enemyW[eH][eW], &enemyH[eH][eW]);

						lX = (eH + 1) * enemyW[eH][eW];//座標計算
						enemyX[eH][eW] = 750 + eW*(enemyW[eH][eW] + 10), enemyY[eH][eW] = lX + 15 * eH;//座標セット

						EmutekiCounter[eH][eW] = 0;//エネミー＝点滅していない
					}
				}
			}
		}//爆発判定終了


		//無敵時ジェットを半透明にする処理
		if (mutekiCounter % 2 == 1 && LP>-1){
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 60);
			DrawGraph(jetX, jetY, jetGraph, TRUE);//ジェット描画
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
		else{
			if(LP > -1)DrawGraph(jetX, jetY, jetGraph, TRUE);// ジェットを描画
		}


		if (mutekiCounter > 0)mutekiCounter--;//無敵状態のときのみカウントダウン


		if (jetDamageFlag == 0){//ダメージを受けている間下記をスキップ
			// ↑キーでジェットを上に移動させる
			if (CheckHitKey(KEY_INPUT_UP) == 1) jetY -= 3;

			// ↓キーでジェットを下に移動させる
			if (CheckHitKey(KEY_INPUT_DOWN) == 1) jetY += 3;

			// ←キーでジェットを左に移動させる
			if (CheckHitKey(KEY_INPUT_LEFT) == 1) jetX -= 3;

			// →キーでジェットを右に移動させる
			if (CheckHitKey(KEY_INPUT_RIGHT) == 1) jetX += 3;


			// ジェットが画面左端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (jetX < 0) jetX = 0;

			// ジェットが画面右端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (jetX > 50) jetX = 50;

			// ジェットが画面上端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (jetY < 50) jetY = 50;

			// ジェットが画面下端からはみ出そうになっていたら画面内の座標に戻してあげる
			if (jetY > 570) jetY = 570;

			// スペースキーを押した場合は処理を分岐
			if (CheckHitKey(KEY_INPUT_SPACE))
			{

				// 前フレームでショットボタンを押したかが保存されている変数が0だったら弾を発射
				if (SHOTjetFlag == 0){

					// 画面上にでていない弾があるか、弾の数だけ繰り返して調べる
					for (i = 0; i < SHOT; i++){

						// 弾iが画面上にでていない場合はその弾を画面に出す
						if (SHOTFlag[i] == 0){

							int SHOTW, SHOTH;//ジェット弾のサイズ
							int jetW, jetH;//ジェットのサイズその2
							GetGraphSize(SHOTGraph, &SHOTW, &SHOTH);//弾のサイズを得る
							GetGraphSize(jetGraph, &jetW, &jetH);// ジェットのサイズを得る

							// 弾iの位置をセット、位置はジェットの中心にする
							SHOTX[i] = (jetW - SHOTW) / 2 + jetX;
							SHOTY[i] = (jetH - SHOTH) / 2 + jetY;

							//発射音
							PlaySoundFile("se_maoudamashii_battle_gun05.wav", DX_PLAYTYPE_BACK);

							// 弾iは現時点を持って存在するので、存在状態を保持する変数に１を代入する
							SHOTFlag[i] = 1;

							break;//抜け出す
						}
					}
				}
				// 前フレームでショットボタンを押されていたかを保存する変数に１(おされていた)を代入
				SHOTjetFlag = 1;
			}
			else{
				// ショットボタンが押されていなかった場合は
				// 前フレームでショットボタンが押されていたかを保存する変数に０(おされていない)を代入
				SHOTjetFlag = 0;
			}//スペースボタン判定終了	



			// 自弾の数だけ自弾を動かす処理を繰り返す
			for (i = 0; i < SHOT; i++)
			{
				// 自機の弾iの移動ルーチン( 存在状態を保持している変数の内容が１(存在する)の場合のみ行う )
				if (SHOTFlag[i] == 1)
				{
					// 弾iを１６ドット右に移動させる
					SHOTX[i] += 16;

					// 画面外に出てしまった場合は存在状態を保持している変数に０(存在しない)を代入する
					if (SHOTX[i] > 1000)
					{
						SHOTFlag[i] = 0;
					}

					// 画面に弾iを描画する
					DrawGraph(SHOTX[i], SHOTY[i], SHOTGraph, TRUE);
				}
			}//自弾移動処理終了

			if (mutekiCounter <= 0){//無敵時当たり判定スキップ
				// 敵弾と自分の当たり判定、敵弾の数だけ繰り返す
				for (ii = 0; ii < 20; ii++)
				{
					// 敵弾iiが存在している場合のみ次の処理に映る
					if (ETamaFlag[ii] == 1)
					{
						// 自分との当たり判定
						if (((ETamaX[ii] > jetX && ETamaX[ii] < jetX + jW) ||
							(jetX > ETamaX[ii] && jetX < ETamaX[ii] + ETamaW)) &&
							((ETamaY[ii] > jetY && ETamaY[ii] < jetY + jH) ||
							(jetY > ETamaY[ii] && jetY < ETamaY[ii] + ETamaH)))
						{
							// 接触している場合は当たった弾の存在を消す
							ETamaFlag[ii] = 0;

							//爆発音
							PlaySoundFile("se_maoudamashii_explosion06.wav", DX_PLAYTYPE_BACK);

							// 爆発しているかどうかを保持する変数に『爆発している』を表す１を代入
							jetDamageFlag = 1;

							// 爆発している時間を測るカウンタ変数に０を代入
							jetDamageCounter = 0;
						}
					}
				}//当たり判定閉じ
			}//無敵判定閉じ
		}//スキップ判定閉じ




		//LPが０になったらゲームオーバー
		if (LP < 0){
			state = GAMEOVER;
		}
		//敵が全滅すればゲームクリアー
		if (allkill() == FALSE)state = CLEAR;


		// 裏画面の内容を表画面にコピーする
		ScreenFlip();

		// Windows 特有の面倒な処理をＤＸライブラリにやらせる
		// -1 が返ってきたらループを抜ける
		if (ProcessMessage() < 0) break;

		// もしＥＳＣキーが押されていたらループから抜ける
		if (CheckHitKey(KEY_INPUT_ESCAPE)==1) break;

	}//移動ルーチンの閉じ括弧
}


//エネミー関数
void Enemy(){

		// エネミーの移動ルーチン
		for (eH = 0; eH < E_HEIGHT; eH++){
			for (eW = 0; eW < E_WIDTH; eW++){
				if (enemies[eH][eW].living == FALSE)continue;

				for (eH = 0; eH < E_HEIGHT; eH++){
					for (eW = 0; eW < E_WIDTH; eW++){
						if (enemies[eH][eW].living == FALSE)continue;
						// 顔を歪めているかどうかで処理を分岐			
						if (enemyDamageFlag[eH][eW] == 1)
						{

							if (ETamaCounter[eH][eW] >= 299)ETamaCounter[eH][eW] = 0;//弾の発射を防ぐ
							// 顔を歪めている場合はダメージ時のグラフィックを描画する
							//30フレーム経過でグラフィック変化
							if (enemyDamageCounter[eH][eW]>30){
								enemyGraph[eH][eW] = enemyDamageGraph[eH][eW];//泣き顔
							}
							else{
								enemyGraph[eH][eW] = LoadGraph("bomb.bmp");//爆破エフェクト
							}

							enemyX[eH][eW] -= 1;//エネミーを前へ送る

							EmutekiCounter[eH][eW] = 1;

							// 顔を歪めている時間を測るカウンターに１を加算する
							enemyDamageCounter[eH][eW]++;

							// もし顔を歪め初めて 60 フレーム経過していたら顔の歪んだ状態から
							// 元に戻してあげる
							if (enemyDamageCounter[eH][eW] > 60){
								// 『歪んでいない』を表す０を代入
								enemyDamageFlag[eH][eW] = 0;

								enemies[eH][eW].living = FALSE;//ある程度前に下がってきたらエネミーを消す

								Score += 500;//スコアを500加算

							}

						}//表情判定終了
					}
				}

				// 歪んでいない場合は今まで通りの処理
				for (eH = 0; eH < E_HEIGHT; eH++){
					for (eW = 0; eW < E_WIDTH; eW++){
						if (enemies[eH][eW].living == FALSE)continue;
						// エネミーの座標を移動している方向に移動する
						if (enemyMuki == 1) enemyY[eH][eW] += 1;
						if (enemyMuki == 0) enemyY[eH][eW] -= 1;


						// 真ん中のエネミーが画面下端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
						if (enemyY[eH][eW] > 555)
						{
							enemyY[eH][eW] = 555;
							enemyMuki = 0;
						}

						// 真ん中のエネミーが画面上端からでそうになっていたら画面内の座標に戻してあげ、移動する方向も反転する
						if (enemyY[eH][eW] < 50)
						{
							enemyY[eH][eW] = 50;
							enemyMuki = 1;
						}
					}

				}



				//エネミーを描画
				for (eH = 0; eH < E_HEIGHT; eH++){//繰り返す
					for (eW = 0; eW < E_WIDTH; eW++){
						if (enemies[eH][eW].living == FALSE)continue;

						//やられた時エネミーを半透明にする処理
						if (EmutekiCounter[eH][eW] % 2 == 1 && enemyDamageCounter[eH][eW]>30){
							SetDrawBlendMode(DX_BLENDMODE_ALPHA, 140);
							DrawGraph(enemyX[eH][eW], enemyY[eH][eW], enemyGraph[eH][eW], TRUE);//エネミー描画
							SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
						}
						else{
							DrawGraph(enemyX[eH][eW], enemyY[eH][eW], enemyGraph[eH][eW], TRUE);// エネミー描画
						}


						if (EmutekiCounter[eH][eW] != 0)EmutekiCounter[eH][eW]--;//エネミー＝点滅していない


						// 敵弾を撃つタイミングを計測するためのカウンター
						ETamaCounter[eH][eW] = GetRand(300);

						// もしカウンター変数が299以上だった場合は弾を撃つ処理を行う
						if (ETamaCounter[eH][eW] >= 299)
						{
							// もし既に敵弾が『飛んでいない』状態だった場合のみ発射処理を行う
							for (ii = 0; ii < 20; ii++){
								if (ETamaCounter[eH][eW] == 0)break;
								if (ETamaFlag[ii] == 0)
								{
									//敵弾のサイズを得る
									GetGraphSize(ETamaGraph, &ETamaW, &ETamaH);

									// 弾の発射位置を設定する
									ETamaX[ii] = enemyX[eH][eW] + enemyW[eH][eW] / 2 - ETamaW / 2;
									ETamaY[ii] = enemyY[eH][eW] + enemyH[eH][eW] / 2 - ETamaH / 2;

									// 弾の状態を保持する変数に『飛んでいる』を示す１を代入する
									ETamaFlag[ii] = 1;

									// 弾を打つタイミングを計測するための変数に０を代入
									ETamaCounter[eH][eW] = 0;
								}
							}

						}
					}
				}//エネミー描画閉じ括弧
			}
		}//エネミールーチン閉じ括弧


		// 敵機の弾iiの移動ルーチン( 存在状態を保持している変数の内容が１(存在する)の場合のみ行う )
		for (ii = 0; ii < 20; ii++){
			if (ETamaFlag[ii] == 1)
			{
				// 弾iを8ドット左に移動させる
				ETamaX[ii] -= 8;

				// 画面外に出てしまった場合は存在状態を保持している変数に０(存在しない)を代入する
				if (ETamaX[ii] < 0)
				{
					ETamaFlag[ii] = 0;
				}
				// 画面に弾iを描画する
				DrawGraph(ETamaX[ii], ETamaY[ii], ETamaGraph, TRUE);
			}
		}


		
			// 弾と敵の当たり判定、弾の数だけ繰り返す
			for (i = 0; i < SHOT; i++)
			{
				// 弾iが存在している場合のみ次の処理に映る
				if (SHOTFlag[i] == 1)
				{
					for (eH = 0; eH < E_HEIGHT; eH++){
						for (eW = 0; eW < E_WIDTH; eW++){
							if (enemies[eH][eW].living == FALSE || enemyDamageFlag[eH][eW]==1)continue;
							// エネミーとの当たり判定
							if (((SHOTX[i] > enemyX[eH][eW] && SHOTX[i] < enemyX[eH][eW] + enemyW[eH][eW]) ||
								(enemyX[eH][eW] > SHOTX[i] && enemyX[eH][eW] < SHOTX[i] + SHOTW)) &&
								((SHOTY[i] > enemyY[eH][eW] && SHOTY[i] < enemyY[eH][eW] + enemyH[eH][eW]) ||
								(enemyY[eH][eW] > SHOTY[i] && enemyY[eH][eW] < SHOTY[i] + SHOTH)))
							{
								// 接触している場合は当たった弾の存在を消す
								SHOTFlag[i] = 0;

								// エネミーの顔を歪めているかどうかを保持する変数に『歪めている』を表す１を代入
								enemyDamageFlag[eH][eW] = 1;

								// エネミーの顔を歪めている時間を測るカウンタ変数に０を代入
								enemyDamageCounter[eH][eW] = 0;
								

								//やられた音
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
			if (enemies[eH][eW].living == TRUE)return TRUE;//敵はまだいる
		}
	}
	return FALSE;//敵は全滅した
}

