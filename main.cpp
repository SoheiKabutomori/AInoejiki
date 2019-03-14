#include "DxLib.h"
#include "SceneMgr.h"

// プレイ人数
int PlayerCount = 0;
// キャリーオーバー
int CarryOver;
int CarryOverCard[15] = {};

int PlayerIcon[5] = {};
int PlayerSelect[5] = {};
int ComIcon[5] = {};
int ComSelect[5] = {};
// プレイヤーの所持カード
int PlayerCard[15] = {};
int Com1Card[15] = {};
int Com2Card[15] = {};
int Com3Card[15] = {};
int Com4Card[15] = {};
int Com5Card[15] = {};

// プレイヤーの選択カード
int PlayerSelectCard = 16;
int Com1SelectCard = 5;
int Com2SelectCard = 12;
int Com3SelectCard = 15;
int Com4SelectCard = 14;
int Com5SelectCard = 1;

// 得点カードの所有者、現在の得点カード
int Score[15] = {};
int ScoreCard = 1;
int PlayerScore[6] = {};

int DeckSelect = 0;

int BackgroundImg1;
int BackgroundImg2;
int ButtonDec;
int ButtonDecHover;
int ButtonScoreHandle1;
int ButtonScoreHandle2;
int Deck1[15];
int Deck2[15];
int Hand[15];
int PointCardSetImg[15];
int value[15] = { -5, -4, -3, -2, -1,1, 2, 3, 4, 5,6, 7, 8, 9, 10 };

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);   // ウィンドウモード変更と初期化と裏画面設定

	SceneMgr_Initialize();

	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0){  // 画面更新 & メッセージ処理 & 画面消去

		SceneMgr_Update();  // 更新
		SceneMgr_Draw();    // 描画

	}

	SceneMgr_Finalize();

	DxLib_End(); // DXライブラリ終了処理
	return 0;
}