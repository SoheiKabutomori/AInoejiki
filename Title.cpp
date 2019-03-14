#include "Title.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg1;
extern int BackgroundImg2;
extern int ButtonDec;
extern int ButtonDecHover;
extern int ButtonScoreHandle1;
extern int ButtonScoreHandle2;
extern int Deck1[15], Deck2[15];
extern int Hand[15];
extern int PlayerIcon[5];
extern int ComIcon[5];
extern int Image1[16], Image2[16];
extern int PlayerCard[15];
extern int DeckSelect;
extern int PlayerScore[6];
extern int PointCardSetImg[15];

extern int PlayerCount;

extern int CarryOver;
extern int CarryOverCard[15];

extern int PlayerIcon[5];
extern int PlayerSelect[5];
extern int ComSelect[5];
// プレイヤーの所持カード
extern int PlayerCard[15];
extern int Com1Card[15];
extern int Com2Card[15];
extern int Com3Card[15];
extern int Com4Card[15];
extern int Com5Card[15];


// プレイヤーの選択カード
extern int PlayerSelectCard;

// 得点カードの所有者、現在の得点カード
extern int Score[15];
extern int ScoreCard;
extern int PlayerScore[6];

extern int DeckSelect;




static int ButtonStart;
static int ButtonStartHover;
static int ButtonTut;
static int ButtonTutHover;
static int GSizeX, GSizeY;
static int MouseX, MouseY;
static int ButtonStartX;
static int ButtonStartY;
static int ButtonTutX;
static int ButtonTutY;
static int BSSizeX;
static int BSSizeY;
static int BTSizeX;
static int BTSizeY;


// 初期化
void Title_Initialize() {
	SetGraphMode(1280, 720, 32);
	// 画像のロード
	for (int i = 0; i < 16; i++) {
		Score[i] = 0;
		Hand[i] = 0;
		PlayerCard[i] = 0;
		PlayerSelect[i] = 0;
		PlayerScore[i] = 0;
		CarryOverCard[i] = 0;
	}
	ScoreCard = 1;
	PlayerCount = 1;
	DeckSelect = 0;
	BackgroundImg1 = LoadGraph("data/img/TitleScreenBackground.png");
	BackgroundImg2 = LoadGraph("data/img/bgMainDark.png");
	PlayerIcon[0] = LoadGraph("data/img/PlayerIcon/icon1.png");
	PlayerIcon[1] = LoadGraph("data/img/PlayerIcon/icon2.png");
	PlayerIcon[2] = LoadGraph("data/img/PlayerIcon/icon3.png");
	PlayerIcon[3] = LoadGraph("data/img/PlayerIcon/icon4.png");
	PlayerIcon[4] = LoadGraph("data/img/PlayerIcon/icon5.png");
	ComIcon[0] = LoadGraph("data/img/PlayerIcon/nakano.jpg");
	ComIcon[1] = LoadGraph("data/img/PlayerIcon/hmiyata.jpg");
	ComIcon[2] = LoadGraph("data/img/PlayerIcon/nakano001001.jpg");
	ComIcon[3] = LoadGraph("data/img/PlayerIcon/nakano2010.jpg");
	ComIcon[4] = LoadGraph("data/img/PlayerIcon/nakanopic0910.jpg");
	ButtonDec = LoadGraph("data/img/Button/decision.png");
	ButtonDecHover = LoadGraph("data/img/Button/decision_hover.png");
	ButtonScoreHandle1 = LoadGraph("data/img/Button/score1.jpg");
	ButtonScoreHandle2 = LoadGraph("data/img/Button/score2.jpg");
	ButtonStart = LoadGraph("data/img/Button/start.png");
	ButtonStartHover = LoadGraph("data/img/Button/start_hover.png");
	ButtonTut = LoadGraph("data/img/Button/tut.png");
	ButtonTutHover = LoadGraph("data/img/Button/tut_hover.png");
	LoadDivGraph("data/img/CardSet/set-brown.png", 15, 5, 3, 600, 900, Hand);
	LoadDivGraph("data/img/CardSet108x162.png", 15, 5, 3, 108, 162, Deck1);
	LoadDivGraph("data/img/CardSet72x108.png", 15, 5, 3, 72, 108, Deck2);
	LoadDivGraph("data/img/CardSet/set-deck.png", 15, 5, 3, 600, 900, PointCardSetImg);
	BSSizeX = 125;
	BSSizeY = 50;
	BTSizeX = 170;
	BTSizeY = 50;

	//全ての変数・配列の初期化

	// プレイ人数

	CarryOver = 0;

	// プレイヤーの所持カード
	for (int i = 0; i < 15; i++) {
		PlayerCard[i] = 0;
		Com1Card[i] = 0;
		Com2Card[i] = 0;
		Com3Card[i] = 0;
		Com4Card[i] = 0;
		Com5Card[i] = 0;
		Score[i] = 0;

	};
	// プレイヤーの選択カード
	PlayerSelectCard = 16;


	// 得点カードの所有者、現在の得点カード
	for (int i = 0; i<6; i++) {
		PlayerScore[i] = 0;
	};

	DeckSelect = 0;



}

// 終了処理
void Title_Finalize() {
	// 画像の解放
	//DeleteGraph(BackgroundImg1);
}

// 更新
void Title_Update() {
	GetMousePoint(&MouseX, &MouseY);

	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if ((ButtonStartX < MouseX) && ((ButtonStartX + BSSizeX) > MouseX)) {
			if ((ButtonStartY < MouseY) && ((ButtonStartY + BSSizeY) > MouseY)) {
				SceneMgr_ChangeScene(eScene_SelectPlayer);   // プレイヤー選択画面に変更
			}
		}
		if ((ButtonTutX < MouseX) && ((ButtonTutX + BTSizeX) > MouseX)) {
			if ((ButtonTutY < MouseY) && ((ButtonTutY + BTSizeY) > MouseY)) {
				SceneMgr_ChangeScene(eScene_Tutorial);   // チュートリアル画面に変更
			}
		}
		if ((1000 < MouseX) && (1280 > MouseX)) {
			if ((0 < MouseY) && (200 > MouseY)) {
				SceneMgr_ChangeScene(eScene_End);
			}
		}

	}

}

// 描画
void Title_Draw() {
	ButtonStartX = 1280 / 2 - 125 / 2;
	ButtonStartY = 500;
	ButtonTutX = 1280 / 2 - 170 / 2;
	ButtonTutY = 600;

	GetMousePoint(&MouseX, &MouseY);

	// 背景
	DrawGraph(0, 0, BackgroundImg1, FALSE);

	// startボタン
	DrawGraph(ButtonStartX, ButtonStartY, ButtonStart, TRUE);
	if ((ButtonStartX < MouseX) && ((ButtonStartX + BSSizeX) > MouseX)) {
		if ((ButtonStartY < MouseY) && ((ButtonStartY + BSSizeY) > MouseY)) {
			DrawGraph(ButtonStartX, ButtonStartY, ButtonStartHover, TRUE);
		}
	}

	// tutorialボタン
	DrawGraph(ButtonTutX, ButtonTutY, ButtonTut, TRUE);
	if ((ButtonTutX < MouseX) && ((ButtonTutX + BTSizeX) > MouseX)) {
		if ((ButtonTutY < MouseY) && ((ButtonTutY + BTSizeY) > MouseY)) {
			DrawGraph(ButtonTutX, ButtonTutY, ButtonTutHover, TRUE);
		}
	}

}