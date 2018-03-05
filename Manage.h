#ifndef __MANAGE_H__//無限インクルードを防止する
#define __MANAGE_H__//無限インクルードを防止する

#include "DxLib.h"//ライブラリをインクルード
//#include "loding.h"//画像読込関数をインクルード（本より）→失敗。なぜかDrawGraphが出来なかった。
#include "titleclass.h"//タイトル関数をインクルード（光太郎より）
#include "Main.h"//メイン関数をインクルード（Webより）
#include "GameOver.h"
#include "GameClear.h"


//ゲーム状態（定数連続名付け）
enum GameState{
	TITLE, MAIN, GAMEOVER, CLEAR
};//0,1,2,3と番号が与えられている

//関数プロトタイプ宣言
BOOL SpaceTrigger();//スペースキーチェック関数
BOOL UpTrigger();//↓キーチェック関数
BOOL DownTrigger();//↑キーチェック関数


//externは宣言であり、定義ではない
//定義を忘れると論理エラーが発生する
//複数のファイルを跨いで数値を利用する関数はここで宣言しよう

extern int DefaultHandle,BigHandle;//フォントサイズ用変数

extern int titleX, titleY, titleGraph;//タイトル処理とグラフィック関連
extern int chooseX, chooseY, chooseGraph;//選択用矢印のグラフィック関連

extern int jetX, jetY, jetGraph, jW, jH;//ジェットの座標、グラフィック、サイズ
extern int SHOTX[], SHOTY[], SHOTFlag[], SHOTGraph;//ジェットの弾
extern int SHOTjetFlag;//ジェットの射撃判定
extern int jetDamageFlag, jetDamageCounter, jetDamageGraph;//ジェットのダメージ
extern int mutekiCounter;//ジェットの無敵時間計測

extern int backX, backY,backGraph;//背景
extern int speedX[], speedY[], speedGraph[],speedW[],speedH[];//スピード感

extern int lifeX[3], lifeY[3], lifeGraph[3];//ハート(残機は3がMAX）
extern int lifeW[3], lifeH[3], lX, LP;//ハートサイズ、座標、残機

extern int Score;//スコア（計測用）
extern char Scorestr[];//スコア（表示用）

extern int h;//配列の添字（hはハート）
extern int i, ii;//配列の添字(iはジェット弾、iiはエネミー弾)
extern int eH,eW,jj; //配列(eHは敵の縦配列、eWは横配列、jjはスピード感)

/*後ほど追加される変数	4種類
　　int SHOTW,SHOTH,jetW,jetH*/


extern GameState state;//ゲームのステータスを表す
extern int End;//ゲーム終了の判定を表す（0は続行、-1は終了）

extern int keyS;//スペースキーチェック材料
extern int keyU;//↑キーチェック材料
extern int keyD;//↓キーチェック材料
extern BOOL Spaceprev;//スペースキーチェック
extern BOOL Upprev;//↑キーチェック
extern BOOL Downprev;//↓キーチェック



#endif//無限インクルードを防ぐ