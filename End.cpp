#include "End.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int ComSelect[5];
extern int PlayerSelect[5];
extern int PlayerCount;
extern int PlayerScore[6];

static int WinnerCount = 0;   // 勝利者の人数
static int Winners[6];
static char WinnersName[6][8];    // 勝利者名を文字列で格納

static int mImageHandle;    //画像ハンドル格納用変数
static int Background;
static int Circle;
static int CircleSmall;
static int Ribbon;
static int RibbonSmall;
static int WinnerText;
static int Board;

static int PlayerNum;

static int Com[5]; // com参加者
static int ComNum = 0;
static int PlayerIconImg[5];
static int CompIconImg[5];
static int PlayerIconImgSmall[5];
static int CompIconImgSmall[5];

static int colWidth;
static int FontHandle30;
static int FontHandle45;
static int FontHandle60;

static int test = 1;
static int max;
static int win;
static int t;


// 勝利者の判定
void GetWinner(int *arr) {
	 max = arr[0];
	int flag = 0;

	// 最高点を求める
	for (int i = 1; i < 6; i++) {
		if (max < arr[i])
			max = arr[i];
	}

	// 勝利者名を配列に入れる
	// 勝利者数を設定
	for (int i = 0; i < 6; i++) {
		if (PlayerScore[i] == max) {
			if (i == 0)
				strcpy(WinnersName[WinnerCount], "PLAYER");
			else
				sprintf(WinnersName[WinnerCount], "COMP %d", i);
			Winners[WinnerCount] = i;
			WinnerCount++;
			win = Winners[WinnerCount-1];
		}
	}
	for (int i = 0; i < 6; i++) {
		if (Winners[0] == 1) {
			for (int j = 0; j < 6; j++) {
				if (ComSelect[j] == 1) {
					Winners[0] = j + 1;
					break;
				}
			}
		}
		else if (Winners[0] == 2) {
			for (int j = 0; j < 6; j++) {
				if (ComSelect[j] == 1) {
					flag++;
				}
				if (flag == 2 && ComSelect[test] == 1) {
					Winners[0] = j + 1;
					break;
				}
			}
		}
		else if (Winners[0] == 3) {
			for (test = 0; test < 6; test++) {
				if (ComSelect[test] == 1) {
					flag++;
				}
				if (flag == 3 && ComSelect[test] == 1) {
					Winners[0] = test + 1;
					t = Winners[0];
					break;
				}
			}
		}
		else if (Winners[0] == 4) {
			for (int j = 0; j < 6; j++) {
				if (ComSelect[j] == 1) {
					flag++;
				}
				if (flag == 4 && ComSelect[test] == 1) {
					Winners[0] = j + 1;
					break;
				}
			}
		}
	}

	//
	for (int i = 0; i < 6; i++) {
		if (Winners[1] == 1) {
			for (int j = 0; j < 6; j++) {
				if (ComSelect[j] == 1) {
					Winners[1] = j + 1;
					break;
				}
			}
		}
		else if (Winners[1] == 2) {
			for (int j = 0; j < 6; j++) {
				if (ComSelect[j] == 1) {
					flag++;
				}
				if (flag == 2 && ComSelect[test] == 1) {
					Winners[1] = j + 1;
					break;
				}
			}
		}
		else if (Winners[1] == 3) {
			for (test = 0; test < 6; test++) {
				if (ComSelect[test] == 1) {
					flag++;
				}
				if (flag == 3 && ComSelect[test] == 1) {
					Winners[0] = test + 1;
					t = Winners[1];
					break;
				}
			}
		}
		else if (Winners[1] == 4) {
			for (int j = 0; j < 6; j++) {
				if (ComSelect[j] == 1) {
					flag++;
				}
				if (flag == 4 && ComSelect[test] == 1) {
					Winners[1] = j + 1;
					break;
				}
			}
		}
	}
}

//初期化
void End_Initialize() {
	mImageHandle = LoadGraph("images/Scene_Config.png");//画像のロード

	SetGraphMode(1280, 720, 32);
	FontHandle30 = CreateFontToHandle(NULL, 30, -1);
	FontHandle60 = CreateFontToHandle(NULL, 60, -1);
	FontHandle45 = CreateFontToHandle(NULL, 45, -1);
	WinnerCount = 0;   // 勝利者の人数
	WinnersName[6][8] = { 0 };
	//PlayerSelect[3] = 1;
	for (int i = 0; i < 5; i++) {
		if (PlayerSelect[i] == 1)
			PlayerNum = i;
	}
	/*
	ComSelect[0] = 1;
	ComSelect[1] = 1;
	ComSelect[2] = 1;
	ComSelect[3] = 1;
	PlayerScore[0] = 0;
	PlayerScore[1] = 0;
	PlayerScore[2] = 0;
	PlayerScore[3] = 40;
	PlayerScore[4] = 40;
	PlayerCount = 5;
	*/

	GetWinner(PlayerScore);

	Background = LoadGraph("data/img/BackgroundWinner.png");
	Circle = LoadGraph("data/img/circle.png");
	CircleSmall = LoadGraph("data/img/circle-small.png");
	Ribbon = LoadGraph("data/img/ribbon.png");
	RibbonSmall = LoadGraph("data/img/ribbon-small.png");
	WinnerText = LoadGraph("data/img/winnertext.png");
	Board = LoadGraph("data/img/scoreboard.png");

	LoadDivGraph("data/img/PlayerIcon/p-icon.png", 5, 5, 1, 312, 312, PlayerIconImg);
	LoadDivGraph("data/img/PlayerIcon/c-icon.png", 5, 5, 1, 312, 312, CompIconImg);
	LoadDivGraph("data/img/PlayerIcon/p-icon-small.png", 5, 5, 1, 230, 230, PlayerIconImgSmall);
	LoadDivGraph("data/img/PlayerIcon/c-icon-small.png", 5, 5, 1, 230, 230, CompIconImgSmall);
}

//終了処理
void End_Finalize() {
	DeleteGraph(mImageHandle);//画像の解放
}

//更新
void End_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Title);   //シーンをタイトルに変更
	}
}

// 枠内の文字列を中央に表示する
// 戻り値は描写するx座標 
int CalcCenterX(int x1, int x2, const char *str)
{
	int StrLen, StrWidth;
	StrLen = (int)strlen(str);
	StrWidth = GetDrawStringWidth(str, StrLen);
	return (int)((x1 + ((x2 - x1) / 2)) - (StrWidth / 2));
}


//描画
void End_Draw() {
	DrawGraph(0, 0, mImageHandle, FALSE);
	/*DrawString(0, 0, "終了画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));*/

	/* debug用
	WinnerCount = 2;
	Winners[0] = 0;
	
	Winners[1] = 1;
	Winners[2] = 2;
	strcpy(WinnersName[0], "PLAYER");
	strcpy(WinnersName[1], "COMP 1");
	strcpy(WinnersName[2], "COMP 2");
	*/

	// 背景
	DrawGraph(0, 0, Background, FALSE);

	/*DrawFormatString(0, 0, GetColor(255, 255, 255), "Winners[0]: %d", Winners[0]);
	DrawFormatString(0, 20, GetColor(255, 255, 255), "WinnerCount: %d", WinnerCount);
	DrawFormatString(0, 40, GetColor(255, 255, 255), "test: %d", test);
	DrawFormatString(0, 60, GetColor(255, 255, 255), "max: %d", max);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "win: %d", win);
	DrawFormatString(0, 100, GetColor(255, 255, 255), "playerNum: %d", PlayerNum);
	*/

	if (WinnerCount == 1) {
		DrawGraph(340, 8, Circle, TRUE);
		if (Winners[0] == 0) { // if winner is player
			DrawGraph(482, 138, PlayerIconImg[PlayerNum], TRUE);
		}
		else {
			DrawGraph(482, 138, CompIconImg[Winners[0]-1], TRUE);
		}

		DrawGraph(430, 405, Ribbon, TRUE);
		DrawFormatStringToHandle(570, 415, GetColor(255, 255, 255), FontHandle45, WinnersName[0]);

	}
	else if (WinnerCount == 2) {
		DrawGraph(30, 7, Circle, TRUE);
		DrawGraph(660, 7, Circle, TRUE);
		if (Winners[0] == 0) {
			DrawGraph(170, 140, PlayerIconImg[PlayerNum], TRUE);
		}
		else {
			DrawGraph(170, 140, CompIconImg[Winners[0]-1], TRUE);
		}

		if (Winners[1] == 0) {
			DrawGraph(800, 140, PlayerIconImg[PlayerNum], TRUE);
		}
		else {
			DrawGraph(800, 140, CompIconImg[Winners[1]-1], TRUE);
		}
		
		DrawGraph(120, 400, Ribbon, TRUE);
		DrawGraph(750, 400, Ribbon, TRUE);

		DrawFormatStringToHandle(260, 410, GetColor(255, 255, 255), FontHandle45, WinnersName[0]);
		DrawFormatStringToHandle(890, 410, GetColor(255, 255, 255), FontHandle45, WinnersName[1]);

	}
	else if (WinnerCount == 3) {
		DrawGraph(97, 6, CircleSmall, TRUE);
		DrawGraph(737, 6, CircleSmall, TRUE);
		DrawGraph(412, 162, CircleSmall, TRUE);
		if (Winners[0] == 0) {
			DrawGraph(200, 105, PlayerIconImgSmall[PlayerNum], TRUE);
		}
		else {
			DrawGraph(200, 105, CompIconImgSmall[Winners[0]], TRUE);
		}

		if (Winners[1] == 0) {
			DrawGraph(840, 105, PlayerIconImgSmall[PlayerNum], TRUE);
		}
		else {
			DrawGraph(840, 105, CompIconImgSmall[Winners[1]], TRUE);
		}

		if (Winners[2] == 0) {
			DrawGraph(517, 260, PlayerIconImgSmall[PlayerNum], TRUE);
		}
		else {
			DrawGraph(517, 260, CompIconImgSmall[Winners[2]], TRUE);
		}

		DrawGraph(164, 300, RibbonSmall, TRUE);
		DrawGraph(805, 300, RibbonSmall, TRUE);
		DrawGraph(481, 458, RibbonSmall, TRUE);

		DrawFormatStringToHandle(266, 308, GetColor(255, 255, 255), FontHandle30, WinnersName[0]);
		DrawFormatStringToHandle(909, 308, GetColor(255, 255, 255), FontHandle30, WinnersName[1]);
		DrawFormatStringToHandle(585, 466, GetColor(255, 255, 255), FontHandle30, WinnersName[2]);

	}
	else {
		for (int i = 0; i < WinnerCount; i++)
			DrawFormatStringToHandle(550, 200 + i * 60, GetColor(0, 0, 0), FontHandle45, WinnersName[i]);
	}

	DrawGraph(300, 0, WinnerText, TRUE);
	DrawGraph(15, 558, Board, TRUE);

	// 点数を描画
	colWidth = 1248 / PlayerCount;
	for (int i = 0; i < PlayerCount; i++) {
		if (i == 0) {
			DrawFormatStringToHandle(CalcCenterX(colWidth*i, colWidth*(i + 1), "Player"), 580, GetColor(255, 255, 255), FontHandle30, "Player");
		}
		else {
			DrawFormatStringToHandle(CalcCenterX(colWidth*i, colWidth*(i + 1), "Comp 0"), 580, GetColor(255, 255, 255), FontHandle30, "Comp %d", i);
		}

		DrawFormatStringToHandle(CalcCenterX(colWidth*i, colWidth*(i + 1), "00"), 630, GetColor(255, 255, 255), FontHandle60, "%d", PlayerScore[i]);
	}

}
