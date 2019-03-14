#include "CardOpen.h"
#include "SceneMgr.h"
#include "DxLib.h"

#define debug FALSE         // デバッグ用(TRUE：デバッグ)

int turn = 0;              // カードの裏返し
boolean doTrun = TRUE;     // 裏返り判定
boolean finTrun = FALSE;   // 裏返り終了判定
boolean MovedCard = FALSE; // カード移動完了:TRUE
static int GetPlayer = 0;   // 最大値を持つプレイヤー

//　画像ハンドル格納用変数
static int BackgroundImg;
static int CardBackImg;
static int PointCardImg;
static int PlayerCardImg;
static int Com1CardImg;
static int Com2CardImg;
static int Com3CardImg;
static int Com4CardImg;
static int Com5CardImg;
static int DrawTextImg;

// 共通変数
extern int PlayerCount;
extern int Score[15];
extern int ScoreCard;
extern int DeckSelect;
extern int PlayerScore[6];
extern int value[15];
extern int Deck2[15];
extern int PointCardSetImg[15];
extern int ComSelect[5];
extern int CarryOver;
extern int CarryOverCard[15];
extern int ComIcon[5];
extern int PlayerIcon[5];
extern int PlayerSelect[5];

// プレイヤーの所持カード
extern int PlayerCard[15];
extern int Com1Card[15];
extern int Com2Card[15];
extern int Com3Card[15];
extern int Com4Card[15];
extern int Com5Card[15];

// プレイヤーの選択カード
extern int PlayerSelectCard;
extern int Com1SelectCard;
extern int Com2SelectCard;
extern int Com3SelectCard;
extern int Com4SelectCard;
extern int Com5SelectCard;

// コンピュータ名
char Computer1Name[64] = "中野教授";
char Computer2Name[64] = "宮田助教";
char Computer3Name[64] = "若かりし頃";
char Computer4Name[64] = "似顔絵ver.1";
char Computer5Name[64] = "似顔絵ver.2";

static int fin = 0;
char Com1Name[64] = {};
char Com2Name[64] = {};
char Com3Name[64] = {};
char Com4Name[64] = {};
char Com5Name[64] = {};

// ネット情報
int AI1() {
	int n = 0;

	if (ScoreCard > 12) {  // 10, 9  =>  1, 2
		n = GetRand(1);
		while (Com1Card[n] > 0) {
			n = GetRand(1);
		}
		Com1Card[n] = 1;
	}
	else if (ScoreCard > 9) {  // 8, 7, 6  => 13, 14, 15
		n = GetRand(2) + 12;
		while (Com1Card[n] > 0) {
			n = GetRand(2) + 12;
		}
		Com1Card[n] = 1;
	}
	else if (ScoreCard > 6) {  // 5, 4, 3  => 8, 9, 10
		n = GetRand(2) + 7;
		while (Com1Card[n] > 0) {
			n = GetRand(2) + 7;
		}
		Com1Card[n] = 1;
	}
	else if (ScoreCard > 3) {  // 2, 1, -1  => 3, 4, 5
		n = GetRand(2) + 2;
		while (Com1Card[n] > 0) {
			n = GetRand(2) + 2;
		}
		Com1Card[n] = 1;
	}
	else if (ScoreCard > 1) {  // -2, -3  => 6, 7
		n = GetRand(1) + 5;
		while (Com1Card[n] > 0) {
			n = GetRand(1) + 5;
		}
		Com1Card[n] = 1;
	}
	else if (ScoreCard > -1) {  // -4, -5 => 11, 12
		n = GetRand(1) + 10;
		while (Com1Card[n] > 0) {
			n = GetRand(1) + 10;
		}
		Com1Card[n] = 1;
	}
	else {
		n = -1;
	}

	return n + 1;
}

// 得点に比例
int AI2() {
	int n;

	switch (ScoreCard) {
	case 0:
		n = 8;
		Com2Card[n] = 1;
		break;
	case 1:
		n = 6;
		Com2Card[n] = 1;
		break;
	case 2:
		n = 4;
		Com2Card[n] = 1;
		break;
	case 3:
		n = 2;
		Com2Card[n] = 1;
		break;
	case 4:
		n = 0;
		Com2Card[n] = 1;
		break;
	case 5:
		n = 1;
		Com2Card[n] = 1;
		break;
	case 6:
		n = 3;
		Com2Card[n] = 1;
		break;
	case 7:
		n = 5;
		Com2Card[n] = 1;
		break;
	case 8:
		n = 7;
		Com2Card[n] = 1;
		break;
	case 9:
		n = 9;
		Com2Card[n] = 1;
		break;
	case 10:
		n = 10;
		Com2Card[n] = 1;
		break;
	case 11:
		n = 11;
		Com2Card[n] = 1;
		break;
	case 12:
		n = 12;
		Com2Card[n] = 1;
		break;
	case 13:
		n = 13;
		Com2Card[n] = 1;
		break;
	case 14:
		n = 14;
		Com2Card[n] = 1;
		break;
	}

	return n + 1;
}

// 得点に比例（バラツキ小）
int AI3() {
	int n;

	if (ScoreCard > 11) {  // 10,9,8  =>  15,14,13
		n = GetRand(2) + 12;
		while (Com3Card[n] > 0) {
			n = GetRand(2) + 12;
		}
		Com3Card[n] = 1;
	}
	else if (ScoreCard > 8) {  // 7,6,5  =>  12,11,10
		n = GetRand(2) + 9;
		while (Com3Card[n] > 0) {
			n = GetRand(2) + 9;
		}
		Com3Card[n] = 1;
	}
	else if (ScoreCard > 7 || ScoreCard < 2) {  // -5,4,-4  => 9,8,7
		n = GetRand(2) + 6;
		while (Com3Card[n] > 0) {
			n = GetRand(2) + 6;
		}
		Com3Card[n] = 1;
	}
	else if (ScoreCard > 5 || ScoreCard < 3) {  // 3,-3,2  => 6,5,4
		n = GetRand(2) + 3;
		while (Com3Card[n] > 0) {
			n = GetRand(2) + 3;
		}
		Com3Card[n] = 1;
	}
	else {  // -2,1,-1  => 3,2,1
		n = GetRand(2);
		while (Com3Card[n] > 0) {
			n = GetRand(2);
		}
		Com3Card[n] = 1;
	}

	return n + 1;
}

// 得点に比例（バラツキ大）
int AI4() {
	int n;

	if (ScoreCard > 9) {  // 10-6  =>  15-11
		n = GetRand(4) + 10;
		while (Com4Card[n] > 0) {
			n = GetRand(4) + 10;
		}
		Com4Card[n] = 1;
	}
	else if (ScoreCard > 7 || ScoreCard < 3) {  // -5, 5, -4, 4, -3  =>  10-6
		n = GetRand(4) + 5;
		while (Com4Card[n] > 0) {
			n = GetRand(4) + 5;
		}
		Com4Card[n] = 1;
	}
	else if (ScoreCard > 2) {  // 3, -2, 2, -1, 1  => 5-1
		n = GetRand(4);
		while (Com4Card[n] > 0) {
			n = GetRand(4);
		}
		Com4Card[n] = 1;
	}

	return n + 1;
}

// 手札温存
int AI5() {
	int n = 0;          // 選択したカード
	int turn = 0;       // ターン数
	int cardCount = 0;  // 残りカード数
	int a = 0, b = 0, c = 0;

	for (int i = 0; i < 15; i++) {
		turn += Score[i];          // ターン数計算
		cardCount += Com5Card[i];  // 残りカード数計算
	}

	if (turn < 4) {  // 3ターン目まで
		if (ScoreCard < 3) {  // -5,-4,-3のとき、所持カードの上から6番目を選択
			for (int i = 14; i > 0; i--) {
				if (Com5Card[i] == 0) {
					a++;
				}
				if (a == 6) {
					n = i;
					Com5Card[n] = 1;
					break;
				}
			}
		}
		else {  // 1,2,3から選択
			n = GetRand(2);
			while (Com5Card[n] > 0) {
				n = GetRand(2);
			}
			Com5Card[n] = 1;
		}
	}
	else if (turn < 13) {  //4~12ターン目まで
		if (CarryOver > 12) {  //キャリーオーバーが8以上のとき
			if (ScoreCard > 6) {
				for (int i = 14; i > -1; i--) {  //  最大のカードを選択
					if (Com5Card[i] == 0) {
						n = i;
						Com5Card[n] = 1;
						break;
					}
				}
			}
			else {
				for (int i = 14; i > 0; i--) {  // 所持カードの上から2番目を選択
					if (Com5Card[i] == 0) {
						a++;
					}
					if (a == 2) {
						n = i;
						Com5Card[n] = 1;
						break;
					}
				}
			}
		}
		else if (CarryOver > 6) {
			if (ScoreCard > 12) {
				for (int i = 14; i > -1; i--) {  //  最大のカードを選択
					if (Com5Card[i] == 0) {
						n = i;
						Com5Card[n] = 1;
						break;
					}
				}
			}
			else {
				for (int i = 14; i > 0; i--) {  // 所持カードの上から2番目を選択
					if (Com5Card[i] == 0) {
						a++;
					}
					if (a == 2) {
						n = i;
						Com5Card[n] = 1;
						break;
					}
				}
			}
		}
		else if (ScoreCard < 3) {  // -5,-4,-3のとき、所持カードの上から5番目を選択
			for (int i = 14; i > 0; i--) {
				if (Com5Card[i] == 0) {
					a++;
				}
				if (a == 5) {
					n = i;
					Com5Card[n] = 1;
					break;
				}
			}
			a = 0;
			if (n == 0) {
				for (int i = 14; i > 0; i--) {
					if (Com5Card[i] == 0) {
						a++;
					}
					if (a == 3) {
						n = i;
						Com5Card[n] = 1;
						break;
					}
				}
			}
		}
		else if (ScoreCard > 2 && ScoreCard < 7) { // -2,-1,1,2のとき、所持カードの最小値を選択
			for (int i = 0; i < 15; i++) {
				if (Com5Card[i] == 0) {
					n = i;
					Com5Card[n] = 1;
					break;
				}
			}
		}
		else {  // 3,4,5,6,7,8,9,10のとき、所持カードの上から3~5番目
			b = GetRand(2);
			for (int i = 14; i > 0; i--) {
				if (Com5Card[i] == 0) {
					a++;
				}
				if (a == (b + 3)) {
					n = i;
					Com5Card[n] = 1;
					break;
				}
			}
		}
	}
	else {  // 13ターン目以降
		int first = 0, second = 0, third;
		for (int i = 14; i >= 0; i--) {  // 残っている得点の最大、二番目を計算
			if (first > 0 && Score[i] == 0) {
				second = i;
			}
			else if (Score[i] == 0) {
				first = i;
			}
		}

		if (ScoreCard == first) {  // 最大カードを選択
			for (int i = 14; i >= 0; i--) {
				if (Com5Card[i] == 0) {
					n = i;
					Com5Card[n] = 1;
					break;
				}
			}
		}
		else if (ScoreCard == second) {  // 2番目のカードを選択
			for (int i = 14; i >= 0; i--) {
				if (Com5Card[i] == 0) {
					a++;
				}
				if (a == 1) {
					n = i;
					Com5Card[n] = 1;
					break;
				}
			}
		}
		else {
			for (int i = 0; i < 15; i++) {
				if (Com5Card[i] == 0) {
					n = i;
					Com5Card[n] = 1;
					break;
				}
			}
		}
	}

	return n + 1;
}

// デバッグ用：1から順番にカードを選択
int AI_debug() {
	int n, turnNum = 0;

	for (int i = 0; i < 15; i++) {
		if (Score[i] > 0) {
			turnNum++;
		}
	}
	n = turnNum;

	return n + 1;
}

// 初期化
void CardOpen_Initialize() {
	char Name[64] = {};
	extern int PlayerSelectCard;
	extern int Com1SelectCard;
	extern int Com2SelectCard;
	extern int Com3SelectCard;
	extern int Com4SelectCard;
	extern int Com5SelectCard;
	extern int ScoreCard;
	int j = 0;

	// AIの選択カード
	switch (PlayerCount) {
	case 4:
		for (int i = 0; i < 5; i++) {
			if (ComSelect[i] == 1) {
				if (i == 0) {
					Com1SelectCard = AI1();
					strcpy(Com1Name, Computer1Name);
					j++;
				}
				if (i == 1) {
					if (j < 1) {
						Com1SelectCard = AI2();
						strcpy(Com1Name, Computer2Name);
						j++;
					}
					else {
						Com2SelectCard = AI2();
						strcpy(Com2Name, Computer2Name);
						j++;
					}
				}
				if (i == 2) {
					if (j < 1) {
						Com1SelectCard = AI3();
						strcpy(Com1Name, Computer3Name);
						j++;
					}
					else if (j < 2) {
						Com2SelectCard = AI3();
						strcpy(Com2Name, Computer3Name);
						j++;
					}
					else {
						Com3SelectCard = AI3();
						strcpy(Com3Name, Computer3Name);
						j++;
					}
				}
				if (i == 3) {
					if (j < 2) {
						Com2SelectCard = AI4();
						strcpy(Com2Name, Computer4Name);
						j++;
					}
					else {
						Com3SelectCard = AI4();
						strcpy(Com3Name, Computer4Name);
						j++;
					}
				}
				if (i == 4) {
					Com3SelectCard = AI5();
					strcpy(Com3Name, Computer5Name);
				}
			}
		}
		break;
	case 5:
		for (int i = 0; i < 5; i++) {
			if (ComSelect[i] == 0) {
				j = i;
			}
		}
		if (j == 0) {
			Com1SelectCard = AI2();
			strcpy(Com1Name, Computer2Name);
			Com2SelectCard = AI3();
			strcpy(Com2Name, Computer3Name);
			Com3SelectCard = AI4();
			strcpy(Com3Name, Computer4Name);
			Com4SelectCard = AI5();
			strcpy(Com4Name, Computer5Name);
		}
		else if (j == 1) {
			Com1SelectCard = AI1();
			strcpy(Com1Name, Computer1Name);
			Com2SelectCard = AI3();
			strcpy(Com2Name, Computer3Name);
			Com3SelectCard = AI4();
			strcpy(Com3Name, Computer4Name);
			Com4SelectCard = AI5();
			strcpy(Com4Name, Computer5Name);
		}
		else if (j == 2) {
			Com1SelectCard = AI1();
			strcpy(Com1Name, Computer1Name);
			Com2SelectCard = AI2();
			strcpy(Com2Name, Computer2Name);
			Com3SelectCard = AI4();
			strcpy(Com3Name, Computer4Name);
			Com4SelectCard = AI5();
			strcpy(Com4Name, Computer5Name);
		}
		else if (j == 3) {
			Com1SelectCard = AI1();
			strcpy(Com1Name, Computer1Name);
			Com2SelectCard = AI2();
			strcpy(Com2Name, Computer2Name);
			Com3SelectCard = AI3();
			strcpy(Com3Name, Computer3Name);
			Com4SelectCard = AI5();
			strcpy(Com4Name, Computer5Name);
		}
		else if (j == 4) {
			Com1SelectCard = AI1();
			strcpy(Com1Name, Computer1Name);
			Com2SelectCard = AI2();
			strcpy(Com2Name, Computer2Name);
			Com3SelectCard = AI3();
			strcpy(Com3Name, Computer3Name);
			Com4SelectCard = AI4();
			strcpy(Com4Name, Computer4Name);
		}
		break;
	case 6:
		/*
		Com1SelectCard = AI1();
		strcpy(Com1Name, Computer1Name);
		Com2SelectCard = AI2();
		strcpy(Com2Name, Computer2Name);
		Com3SelectCard = AI3();
		strcpy(Com3Name, Computer3Name);
		Com4SelectCard = AI4();
		strcpy(Com4Name, Computer4Name);
		Com5SelectCard = AI5();
		strcpy(Com5Name, Computer5Name);
		*/
		
		Com1SelectCard = AI_debug();
		strcpy(Com1Name, Computer1Name);
		Com2SelectCard = AI_debug();
		strcpy(Com2Name, Computer2Name);
		Com3SelectCard = AI_debug();
		strcpy(Com3Name, Computer3Name);
		Com4SelectCard = AI_debug();
		strcpy(Com4Name, Computer4Name);
		Com5SelectCard = AI_debug();
		strcpy(Com5Name, Computer5Name);
		
		break;
	}

	BackgroundImg = LoadGraph("data/img/bgMainDark.png");
	CardBackImg = LoadGraph("data/img/cardBack.png");
	PointCardImg = PointCardSetImg[ScoreCard];
	sprintf(Name, "data/img/PlayerCards/b%d.png", PlayerSelectCard);   // 選択カード名取得
	PlayerCardImg = LoadGraph(Name);
	sprintf(Name, "data/img/PlayerCards/g%d.png", Com1SelectCard);  // 選択カード名取得
	Com1CardImg = LoadGraph(Name);
	sprintf(Name, "data/img/PlayerCards/m%d.png", Com2SelectCard);  // 選択カード名取得
	Com2CardImg = LoadGraph(Name);
	sprintf(Name, "data/img/PlayerCards/o%d.png", Com3SelectCard);  // 選択カード名取得
	Com3CardImg = LoadGraph(Name);
	sprintf(Name, "data/img/PlayerCards/p%d.png", Com4SelectCard);  // 選択カード名取得
	Com4CardImg = LoadGraph(Name);
	sprintf(Name, "data/img/PlayerCards/r%d.png", Com5SelectCard);  // 選択カード名取得
	Com5CardImg = LoadGraph(Name);
	DrawTextImg = LoadGraph("data/img/draw.png");


}

// 終了処理
void CardOpen_Finalize() {
	// 画像解放
	DeleteGraph(BackgroundImg);
	DeleteGraph(CardBackImg);
	DeleteGraph(PlayerCardImg);
	DeleteGraph(Com1CardImg);
	DeleteGraph(Com2CardImg);
	DeleteGraph(Com3CardImg);
	DeleteGraph(Com4CardImg);
	DeleteGraph(Com5CardImg);
	
	// スコア計算
	//score
	PlayerScore[GetPlayer] += value[ScoreCard];
	for (int i = 0; i < 15; i++) {
		if (CarryOverCard[i] == 1) {
			
			if (GetPlayer < 6) {
				PlayerScore[GetPlayer] += value[i];
				CarryOverCard[i] = 0;
				CarryOver = 0;
			}
		}
	}
	
	DeckSelect = 0;
}

// 更新
void CardOpen_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Title);   //シーンをタイトルに変更
	}
	DeckSelect = 0;

	fin = 0;

	for (int i = 0; i < 15; i++) {
		if (PlayerCard[i] != 0) {
			fin++;
		} 
	}

	if (fin == 15) {
		SceneMgr_ChangeScene(eScene_End);
	}
	else {
		SceneMgr_ChangeScene(eScene_SelectCard);
	}
	
}

//　アイコン・名前描画
void DrawIconName(char *name, int X, int Y, int IconNumber) {

	int iconNumCom[5] = {};
	int playerIconNum = 0;
	int j = 0;

	for (int i = 0; i < 5; i++) {
		if (ComSelect[i] > 0) {
			iconNumCom[j] = i;
			j++;
		}
	}
	for (int i = 0; i < 5; i++) {
		if (PlayerSelect[i] == 1) {
			playerIconNum = i;
		}
	}

	if (name == "Player") {
		DrawString(X + 100, Y - 16, name, GetColor(255, 255, 255));
		DrawExtendGraph(X + 100, Y, X + 200, Y + 120, PlayerIcon[playerIconNum], TRUE);
	}
	else if (name == "Computer1") {
		if (PlayerCount < 5) {
			DrawString(X - 200, Y - 100 - 16, Com1Name, GetColor(255, 255, 255));
			DrawExtendGraph(X - 200, Y - 100, X - 100, Y + 20, ComIcon[iconNumCom[0]], TRUE);
		}
		else {
			DrawString(X + 100, Y - 100 - 16,Com1Name, GetColor(255, 255, 255));
			DrawExtendGraph(X + 100, Y - 100, X + 200, Y + 20, ComIcon[iconNumCom[0]], TRUE);
		}
	}
	else if (name == "Computer2") {
		if (PlayerCount < 5) {
			DrawString(X + 100, Y - 100 - 16, Com2Name, GetColor(255, 255, 255));
			DrawExtendGraph(X + 100, Y - 100, X + 200, Y + 20, ComIcon[iconNumCom[1]], TRUE);
		}
		else {
			DrawString(X - 200, Y - 100 - 16, Com2Name, GetColor(255, 255, 255));
			DrawExtendGraph(X - 200, Y - 100, X - 100, Y + 20, ComIcon[iconNumCom[1]], TRUE);
		}
	}
	else if (name == "Computer3") {
		DrawString(X - 200, Y - 16, Com3Name, GetColor(255, 255, 255));
		DrawExtendGraph(X - 200, Y, X - 100, Y + 120, ComIcon[iconNumCom[2]], TRUE);
	}
	else if (name == "Computer4") {
		DrawString(X - 80, Y - 260 - 16, Com4Name, GetColor(255, 255, 255));
		DrawExtendGraph(X - 80, Y - 260, X + 20, Y - 140, ComIcon[iconNumCom[3]], TRUE);
	}
	else if (name == "Computer5") {
		DrawString(X, Y - 260 - 16, Com5Name, GetColor(255, 255, 255));
		DrawExtendGraph(X, Y - 260, X + 100, Y - 140, ComIcon[iconNumCom[4]], TRUE);
	}
	else {}

}

// 得点カードを描画
void cardPointDraw(int X, int Y, int cardSizeChange) {
	int GSizeX, GSizeY;

	// 画像サイズ入力
	GSizeX = 250;
	GSizeY = 375;

	// 画像表示
	DrawExtendGraph(X - GSizeX / cardSizeChange, Y - GSizeY / cardSizeChange,
		X + GSizeX / cardSizeChange, Y + GSizeY / cardSizeChange, PointCardImg, TRUE);
}

// カード裏面を描画
void cardDraw(char *name, int X, int Y, int cardSizeChange) {
	int GSizeX, GSizeY;

	// 画像サイズ入力
	GSizeX = 250;
	GSizeY = 375;

	// 画像表示
	DrawExtendGraph(X - GSizeX / cardSizeChange, Y - GSizeY / cardSizeChange,
		X + GSizeX / cardSizeChange, Y + GSizeY / cardSizeChange, CardBackImg, TRUE);
}

// カード裏返しを実行
void cardTrun(char *name, int SizeX, int SizeY, int GSizeX, int GSizeY, int GHandle, int cardSizeChange, int t) {
	// 画像描画
	GSizeX -= t;
	DrawExtendGraph(SizeX - GSizeX / cardSizeChange, SizeY - GSizeY / cardSizeChange,
		SizeX + GSizeX / cardSizeChange, SizeY + GSizeY / cardSizeChange, GHandle, TRUE);
}

// カードを裏返す描画
void cardOpen(char *name, int SizeX, int SizeY, int cardSizeChange) {
	// 画像情報
	int GHandleFront;
	int GSizeX, GSizeY;    // カードサイズ
	int speedTrun = 4;     // 裏返しのスピード
	char Name[64];

	// カードサイズ入力
	GSizeX = 250;
	GSizeY = 375;

	if (name == "Player") {
		GHandleFront = PlayerCardImg;
	}
	else if (name == "Computer1") {
		GHandleFront = Com1CardImg;
	}
	else if (name == "Computer2") {
		GHandleFront = Com2CardImg;
	}
	else if (name == "Computer3") {
		GHandleFront = Com3CardImg;
	}
	else if (name == "Computer4") {
		GHandleFront = Com4CardImg;
	}
	else if (name == "Computer5") {
		GHandleFront = Com5CardImg;
	}
	else {
		GHandleFront = PointCardImg;
	}

	if (debug) {
		char StrBuf[128];
		itoa(turn, StrBuf, 10);
		DrawBox(640, 0, 640 + 30, 16, GetColor(255, 255, 255), TRUE);
		DrawString(640, 0, StrBuf, GetColor(0, 0, 0));
	}

	// 画像表示
	if (turn < GSizeX & doTrun) {
		turn += speedTrun;
		cardTrun(name, SizeX, SizeY, GSizeX, GSizeY, CardBackImg, cardSizeChange, turn);
		if (debug) {
			DrawBox(630, 700, 650, 720, GetColor(255, 0, 0), TRUE);
		}
	}
	else if (turn >= 0) {
		doTrun = FALSE;
		cardTrun(name, SizeX, SizeY, GSizeX, GSizeY, GHandleFront, cardSizeChange, turn);
		turn -= speedTrun;
		if (debug) {
			DrawBox(630, 700, 650, 720, GetColor(0, 255, 0), TRUE);
		}
	}
	else {
		cardTrun(name, SizeX, SizeY, GSizeX, GSizeY, GHandleFront, cardSizeChange, turn);
		if (debug) {
			DrawBox(630, 700, 650, 720, GetColor(0, 0, 255), TRUE);
		}
		finTrun = TRUE;
	}
}

// 獲得者を判定
int GetCard() {
	extern int PlayerCount;
	extern int PlayerSelectCard;
	extern int Com1SelectCard;
	extern int Com2SelectCard;
	extern int Com3SelectCard;
	extern int Com4SelectCard;
	extern int Com5SelectCard;
	extern int ScoreCard;

	int a[15] = { PlayerSelectCard, Com1SelectCard, Com2SelectCard, Com3SelectCard, Com4SelectCard, Com5SelectCard };
	int max = 0, min = 16, maxIndex = 0;
	int i = 0, j = 0, pivot = 0;
	boolean nextTrun = TRUE;

	// 値が等しいとき
	for (i = 0; i < PlayerCount; i++) {
		pivot = a[i];
		for (j = i + 1; j < PlayerCount; j++) {
			if (pivot == a[j]) {
				if (ScoreCard + CarryOver < 5) {  // 得点が負のとき
					a[i] = 16;
					a[j] = 16;
				}
				else {               // 得点が正のとき
					a[i] = 0;
					a[j] = 0;
				}
			}
		}
	}

	// 全員カードがダブったら6を返す
	for (i = 0; i < PlayerCount; i++) {
		if (a[i] == 16 || a[i] == 0) {

		}
		else {
			nextTrun = FALSE;
		}
	}
	if (nextTrun) {
		return 6;
	}

	if (ScoreCard + CarryOver > 4) {   // 正の得点カード 
		for (i = 0; i < PlayerCount; i++) {
			if (max < a[i]) {
				max = a[i];
				maxIndex = i;
			}
		}
	}
	else {   // 負の得点カード
		for (i = 0; i < PlayerCount; i++) {
			if (min > a[i]) {
				min = a[i];
				maxIndex = i;
			}
		}
	}
	return maxIndex;
}

void Execution() {

	// 画面サイズの設定
	int SizeX = 1280;
	int SizeY = 720;

	// マウスの位置情報
	char StrBuf[128], StrBuf2[32];
	int MouseX, MouseY;

	// 背景色
	int backgroundCr = GetColor(20, 20, 20);

	// カードサイズ倍率
	int cardSizeChange = 3;

	// プレイヤーカード表示位置
	int PlayerCardX = SizeX * 11 / 16, PlayerCardY = SizeY * 4 / 5;
	int Com1CardX = SizeX * 5 / 16, Com1CardY = SizeY * 1 / 5;
	int Com2CardX = SizeX * 11 / 16, Com2CardY = SizeY * 1 / 5;
	int Com3CardX = SizeX * 5 / 16, Com3CardY = SizeY * 4 / 5;
	int Com4CardX = SizeX * 2 / 16, Com4CardY = SizeY * 1 / 2;
	int Com5CardX = SizeX * 14 / 16, Com5CardY = SizeY * 1 / 2;


	// 得点カードの移動
	int MoveX = SizeX / 2;
	int MoveY = SizeY / 2;

	// クリック判定
	boolean d1Click = FALSE;
	boolean d2Click = FALSE;

	// ループ
	while (1) {
		// 背景
		DrawGraph(0, 0, BackgroundImg, TRUE);

		// マウスの位置を表示（デバッグ用）
		if (debug) {
			GetMousePoint(&MouseX, &MouseY);
			lstrcpy(StrBuf, "座標 Ｘ");
			itoa(MouseX, StrBuf2, 10);
			lstrcat(StrBuf, StrBuf2);
			lstrcat(StrBuf, "　Ｙ ");
			itoa(MouseY, StrBuf2, 10);
			lstrcat(StrBuf, StrBuf2);
			DrawBox(0, 0, 200, 32, GetColor(0, 0, 0), TRUE);
			DrawString(0, 0, StrBuf, GetColor(255, 255, 255));
		}

		// アイコン・名前表示
		switch (PlayerCount) {
		case 2:
			DrawIconName("Player", PlayerCardX, PlayerCardY, 0);
			DrawIconName("Computer1", Com1CardX, Com1CardY, 0);
			break;
		case 3:
			DrawIconName("Player", PlayerCardX, PlayerCardY, 0);
			DrawIconName("Computer1", Com1CardX, Com1CardY, 0);
			DrawIconName("Computer2", Com2CardX, Com2CardY, 1);
			break;
		case 4:
			DrawIconName("Player", PlayerCardX, PlayerCardY, 0);
			DrawIconName("Computer1", Com1CardX, Com1CardY, 0);
			DrawIconName("Computer2", Com2CardX, Com2CardY, 1);
			DrawIconName("Computer3", Com3CardX, Com3CardY, 2);
			break;
		case 5:
			DrawIconName("Player", PlayerCardX, PlayerCardY, 0);
			DrawIconName("Computer1", Com1CardX, Com1CardY, 0);
			DrawIconName("Computer2", Com2CardX, Com2CardY, 1);
			DrawIconName("Computer3", Com3CardX, Com3CardY, 2);
			DrawIconName("Computer4", Com4CardX, Com4CardY, 3);
			break;
		case 6:
			DrawIconName("Player", PlayerCardX, PlayerCardY, 0);
			DrawIconName("Computer1", Com1CardX, Com1CardY, 0);
			DrawIconName("Computer2", Com2CardX, Com2CardY, 1);
			DrawIconName("Computer3", Com3CardX, Com3CardY, 2);
			DrawIconName("Computer4", Com4CardX, Com4CardY, 3);
			DrawIconName("Computer5", Com5CardX, Com5CardY, 4);
			break;
		}


		// プレイヤーカード表示
		if (d1Click) {   // カードを裏返す
			switch (PlayerCount) {
			case 2:
				cardOpen("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardOpen("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				break;
			case 3:
				cardOpen("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardOpen("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				cardOpen("Computer2", Com2CardX, Com2CardY, cardSizeChange);
				break;
			case 4:
				cardOpen("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardOpen("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				cardOpen("Computer2", Com2CardX, Com2CardY, cardSizeChange);
				cardOpen("Computer3", Com3CardX, Com3CardY, cardSizeChange);
				break;
			case 5:
				cardOpen("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardOpen("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				cardOpen("Computer2", Com2CardX, Com2CardY, cardSizeChange);
				cardOpen("Computer3", Com3CardX, Com3CardY, cardSizeChange);
				cardOpen("Computer4", Com4CardX, Com4CardY, cardSizeChange);
				break;
			case 6:
				cardOpen("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardOpen("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				cardOpen("Computer2", Com2CardX, Com2CardY, cardSizeChange);
				cardOpen("Computer3", Com3CardX, Com3CardY, cardSizeChange);
				cardOpen("Computer4", Com4CardX, Com4CardY, cardSizeChange);
				cardOpen("Computer5", Com5CardX, Com5CardY, cardSizeChange);
				break;
			}

			if (debug) {
				DrawBox(0, 700, 20, 720, GetColor(0, 0, 255), TRUE);
			}
		}
		else {   // カード裏面表示
			switch (PlayerCount) {
			case 2:
				cardDraw("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardDraw("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				break;
			case 3:
				cardDraw("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardDraw("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				cardDraw("Computer2", Com2CardX, Com2CardY, cardSizeChange);
				break;
			case 4:
				cardDraw("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardDraw("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				cardDraw("Computer2", Com2CardX, Com2CardY, cardSizeChange);
				cardDraw("Computer3", Com3CardX, Com3CardY, cardSizeChange);
				break;
			case 5:
				cardDraw("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardDraw("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				cardDraw("Computer2", Com2CardX, Com2CardY, cardSizeChange);
				cardDraw("Computer3", Com3CardX, Com3CardY, cardSizeChange);
				cardDraw("Computer4", Com4CardX, Com4CardY, cardSizeChange);
				break;
			case 6:
				cardDraw("Player", PlayerCardX, PlayerCardY, cardSizeChange);
				cardDraw("Computer1", Com1CardX, Com1CardY, cardSizeChange);
				cardDraw("Computer2", Com2CardX, Com2CardY, cardSizeChange);
				cardDraw("Computer3", Com3CardX, Com3CardY, cardSizeChange);
				cardDraw("Computer4", Com4CardX, Com4CardY, cardSizeChange);
				cardDraw("Computer5", Com5CardX, Com5CardY, cardSizeChange);
				break;
			}
		}

		// 得点カード表示
		if (d2Click) {   // 2回目の左クリック時
			
			// 得点獲得者にカードを配布
			GetPlayer = GetCard();
			Score[ScoreCard] = GetPlayer + 1;




			// キャリーオーバーを分配
			for (int i = 0; i < 15; i++) {
				if (CarryOverCard[i] == 1) {
					if (GetPlayer < 6) {
						Score[i] = GetPlayer + 1;
						//CarryOverCard[i] = 0;
						//CarryOver = 0;
					}
				}
			}

			if (debug) {
				DrawBox(20, 700, 40, 720, GetColor(64, 64, 255), TRUE);
				sprintf(StrBuf, "max%d", GetPlayer);
				DrawString(0, 700 - 16, StrBuf, GetColor(255, 255, 255));
			}

			switch (GetPlayer) {  // カードを獲得した人へ移動
			case 0:
				if (MoveX < PlayerCardX - 30) {
					MoveX += 8;
					MoveY += 7;
					if (debug) {
						DrawBox(40, 700, 60, 720, GetColor(128, 128, 255), TRUE);
					}
				}
				else {
					MovedCard = TRUE;
				}
				DrawBox(MoveX, MoveY, MoveX, MoveY, backgroundCr, TRUE);
				cardPointDraw(MoveX, MoveY, cardSizeChange);
				break;
			case 1:
				if (MoveX > Com1CardX + 30) {
					MoveX -= 8;
					MoveY -= 7;
					if (debug) {
						DrawBox(40, 700, 60, 720, GetColor(128, 128, 255), TRUE);
					}
				}
				else {
					MovedCard = TRUE;
				}
				DrawBox(MoveX, MoveY, MoveX, MoveY, backgroundCr, TRUE);
				cardPointDraw(MoveX, MoveY, cardSizeChange);
				break;
			case 2:
				if (MoveX < Com2CardX - 30) {
					MoveX += 8;
					MoveY -= 7;
					if (debug) {
						DrawBox(40, 700, 60, 720, GetColor(128, 128, 255), TRUE);
					}
				}
				else {
					MovedCard = TRUE;
				}
				DrawBox(MoveX, MoveY, MoveX, MoveY, backgroundCr, TRUE);
				cardPointDraw(MoveX, MoveY, cardSizeChange);
				break;
			case 3:
				if (MoveX > Com3CardX + 30) {
					MoveX -= 8;
					MoveY += 7;
					if (debug) {
						DrawBox(40, 700, 60, 720, GetColor(128, 128, 255), TRUE);
					}
				}
				else {
					MovedCard = TRUE;
				}
				DrawBox(MoveX, MoveY, MoveX, MoveY, backgroundCr, TRUE);
				cardPointDraw(MoveX, MoveY, cardSizeChange);
				break;
			case 4:
				if (MoveX > Com4CardX + 30) {
					MoveX -= 8;
					MoveY += 0;
					if (debug) {
						DrawBox(40, 700, 60, 720, GetColor(128, 128, 255), TRUE);
					}
				}
				else {
					MovedCard = TRUE;
				}
				DrawBox(MoveX, MoveY, MoveX, MoveY, backgroundCr, TRUE);
				cardPointDraw(MoveX, MoveY, cardSizeChange);
				break;
			case 5:
				if (MoveX < Com5CardX - 30) {
					MoveX += 8;
					MoveY += 0;
					if (debug) {
						DrawBox(40, 700, 60, 720, GetColor(128, 128, 255), TRUE);
					}
				}
				else {
					MovedCard = TRUE;
				}
				DrawBox(MoveX, MoveY, MoveX, MoveY, backgroundCr, TRUE);
				cardPointDraw(MoveX, MoveY, cardSizeChange);
				break;
			case 6:
				DrawExtendGraph(500, 520, 770, 620, DrawTextImg, TRUE);
				cardPointDraw(MoveX, MoveY, cardSizeChange);
				CarryOverCard[ScoreCard] = 1;
				CarryOver += ScoreCard + 1;
				MovedCard = TRUE;
				if (finTrun) {
					WaitKey();
				}
				break;
			}
		}
		else {
			cardPointDraw(SizeX / 2, SizeY / 2, cardSizeChange);
		}

		// メッセージ処理
		if (ProcessMessage() == -1)
		{
			break;    // エラーが起きたらループを抜ける
		}


		// リセットしループを抜ける
		if (finTrun & MovedCard & (GetMouseInput() & MOUSE_INPUT_LEFT)) {
			turn = 0;
			doTrun = TRUE;
			MovedCard = FALSE;
			finTrun = FALSE;

			break;
		}

		// 一定時間待つ
		WaitTimer(20);

		// 左クリック判定
		if (GetMouseInput() == MOUSE_INPUT_LEFT) {
			if (d1Click) {
				d2Click = TRUE;
			}
			else {
				d1Click = TRUE;
				WaitTimer(200);
			}
		}
	}
}

//描画
void CardOpen_Draw() {

	Execution();

	if (debug) {
		DrawBox(1250, 0, 1280, 30, GetColor(0, 255, 0), TRUE);
	}

}