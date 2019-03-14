#include "SelectCard.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg2;
extern int ButtonScoreHandle1, ButtonScoreHandle2;
extern int Deck1[15];
extern int Hand[15];//カードよみこみ
extern int PointCardSetImg[15];
extern int PlayerCard[15];
extern int Score[15];
extern int PlayerSelectCard;
extern int ScoreCard;
extern int PlayerCount;
extern int PlayerScore[6];
extern int DeckSelect;
extern int CarryOverCard[15];
extern int ScoreCard;



static int GSizeX, GSizeY;  // 画像サイズ
static int MouseX, MouseY;  // マウス位置
static int ButtonDecX = 1050, ButtonDecY = 570;
static int ButtonScoreX = 1100, ButtonScoreY = 30;
static int ButtonBackX = 20, ButtonBackY = 20;
extern int ButtonDec;
extern int ButtonDecHover;
static int ButtonBack;
static int ButtonBackHover;
static int ButtonScore;
static int ButtonScoreHover;
static int BDSizeX = 181, BDSizeY = 103;  // ButtonDecサイズ
static int BSSizeX = 110, BSSizeY = 63;  // ButtonScoreサイズ
static int BBSizeX = 81, BBSizeY = 28;  // ButtonBackサイズ
static int PointCardImg;

static int CardTest;


// 初期化
void SelectCard_Initialize() {

	
	//GetGraphSize(ButtonDec, &GSizeX, &GSizeY);
	PlayerSelectCard = 16;
	//int a = 0;
	if (DeckSelect == 0) {
		ScoreCard = GetRand(14);
		//a++;
		//if(a < 15){
		while (Score[ScoreCard] > 0) {
			ScoreCard = GetRand(14);
			//}
		}
	}

	// 画像のロード
	PointCardImg = PointCardSetImg[ScoreCard];
	ButtonBack = LoadGraph("data/img/Button/back.png");
	ButtonBackHover = LoadGraph("data/img/Button/back_hover.png");
	ButtonScore = LoadGraph("data/img/Button/score.png");
	ButtonScoreHover = LoadGraph("data/img/Button/score_hover.png");
}

// 終了処理
void SelectCard_Finalize() {
	// 画像の解放
	DeleteGraph(ButtonBack);
	DeleteGraph(ButtonBackHover);
	DeleteGraph(ButtonScore);
	DeleteGraph(ButtonScoreHover);
}

// 更新
void SelectCard_Update() {
	GetMousePoint(&MouseX, &MouseY);

	// ボタンがクリックされた時の処理
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (PlayerSelectCard < 16) {
			if (ButtonDecX < MouseX && MouseX < (ButtonDecX + BDSizeX)) {          // 決定ボタンクリック
				if (ButtonDecY < MouseY && MouseY < (ButtonDecY + BDSizeY)) {
					PlayerCard[PlayerSelectCard - 1] = 1;
					//Score[ScoreCard] = 1;
					SceneMgr_ChangeScene(eScene_CardOpen);   // カード表示画面に変更
				}
			}
		}
		if (ButtonScoreX < MouseX && MouseX < (ButtonScoreX + BSSizeX)) {          // スコアボタンクリック
			if (ButtonScoreY < MouseY && MouseY < (ButtonScoreY + BSSizeY)) {
				PlayerSelectCard = 16;
				SceneMgr_ChangeScene(eScene_Score);   // スコア画面に変更
			}
		}
		if (ButtonBackX < MouseX && MouseX < ButtonBackX + BBSizeX) {                // 戻るボタンクリック
			if (ButtonBackY < MouseY && MouseY < ButtonBackY + BBSizeY) {
				SceneMgr_ChangeScene(eScene_Title);   // タイトルに戻る
			}
		}
	}
}


void CardPick(int cardx, int cardy, int x, int y, int Mouse, int Image, int num) {

	double size = 0.15;
	int Color = GetColor(255, 255, 255);
	Mouse = GetMouseInput();                //マウスの入力状態取得
	GetMousePoint(&x, &y);                //マウスの座標取得

										  //DrawFormatString(0, 40, Color, "現在の値は %d です", PlayerSelectCard);
	if (cardx - 50 < x && x < cardx + 50 && cardy - 70 < y && y < cardy + 70) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			PlayerSelectCard = num;
		}
	}
	if (num == PlayerSelectCard) { size = 0.2; }
	DrawRotaGraph(cardx, cardy, size, 0.0, Hand[num - 1], TRUE);  //画像をx,yの位置にサイズsizeで描画

}

// 描画
void SelectCard_Draw() {
	DrawGraph(0, 0, BackgroundImg2, FALSE);

	int x, y, Mouse;
	double size = 1.0;
	Mouse = GetMouseInput();                //マウスの入力状態取得
	GetMousePoint(&x, &y);    //マウスの座標取得



	// キャリーオーバーの表示
	int CarryOverNum = 0;
	int CarryOverX1 = 750, CarryOverY1 = 150;  // 表示範囲（左上座標）
	int CarryOverX2 = 1050, CarryOverY2 = 270;     // 表示範囲（右上座標）
	int j = 0, k = 0;
	for (int i = 0; i < 15; i++) {  // キャリーオーバーカード数を計算
		if (CarryOverCard[i] == 1) {
			CarryOverNum++;
		}
	}
	if (CarryOverNum > 0) {
		DrawString(815, 120, "【キャリーオーバー】", GetColor(255, 255, 255));
		if (CarryOverNum < 4) {
			for (int i = 0; i < 15; i++) {
				if (CarryOverCard[i] == 1) {
					DrawExtendGraph(CarryOverX1 + j*110, CarryOverY1, CarryOverX1 + 80 + j*110, CarryOverY2, PointCardSetImg[i], TRUE);
					j++;
				}
			}
		}
		else if (CarryOverNum < 16) {
			for (int i = 0; i < 15; i++) {
				if (CarryOverCard[i] == 1) {
					if (j > 5) {
						DrawExtendGraph(CarryOverX1 + k * 55, CarryOverY1 + 65, CarryOverX1 + 40 + k * 55, CarryOverY1 + 125, PointCardSetImg[i], TRUE);
						k++;
					}
					else {
						DrawExtendGraph(CarryOverX1 + j * 55, CarryOverY1, CarryOverX1 + 40 + j * 55, CarryOverY1 + 60, PointCardSetImg[i], TRUE);
						j++;
					}
				}
			}
		}
	}
	if (0) {  // 1:マウス位置座標表示, 0:非表示
		char StrBuf[128], StrBuf2[32];
		int MouseX, MouseY;
		GetMousePoint(&MouseX, &MouseY);
		lstrcpy(StrBuf, "座標 Ｘ");
		itoa(MouseX, StrBuf2, 10);
		lstrcat(StrBuf, StrBuf2);
		lstrcat(StrBuf, "　Ｙ ");
		itoa(MouseY, StrBuf2, 10);
		lstrcat(StrBuf, StrBuf2);
		DrawString(0, 0, StrBuf, GetColor(255, 255, 255));
	}

	

	//手札の表示
	for (int i = 1; i < 16; i++) {
		if (PlayerCard[i - 1] == 0) { //カードが未使用なら表示
			if (i < 11) {	//上の段
				CardPick(100 + i * 100, 400, x, y, Mouse, Hand[i - 1], i);
			}
			else {	//下の段
				CardPick(-650 + i * 100, 600, x, y, Mouse, Hand[i - 1], i);
			}
		}
	}


	//場札の表示
	DrawRotaGraph(640, 150, 0.27, 0.0, PointCardImg, TRUE);

	//現在の点数を表示
	//DrawString(1100, 140, "現在の点数", GetColor(255, 255, 255));
	for (int i = 0; i < PlayerCount; i++) {
		if (i == 0)
			DrawFormatString(1100, 110 + 25 * i, GetColor(255, 255, 255), "P   　 %d点", PlayerScore[i]);
		else
			DrawFormatString(1100, 110 + 25 * i, GetColor(255, 255, 255), "C%d　　 %d点", i, PlayerScore[i]);
	}

	// 戻るボタン
	DrawGraph(ButtonBackX, ButtonBackY, ButtonBack, TRUE);
	if (ButtonBackX < MouseX && MouseX < ButtonBackX + BBSizeX) {                // 戻るボタンクリック
		if (ButtonBackY < MouseY && MouseY < ButtonBackY + BBSizeY) {
			DrawGraph(ButtonBackX, ButtonBackY, ButtonBackHover, TRUE);
		}
	}

	// スコアボタンを描画
	DrawGraph(ButtonScoreX, ButtonScoreY, ButtonScore, TRUE);
	if (ButtonScoreX < MouseX && MouseX < (ButtonScoreX + BSSizeX)) {
		if (ButtonScoreY < MouseY && MouseY < (ButtonScoreY + BSSizeY)) {
			DrawGraph(ButtonScoreX, ButtonScoreY, ButtonScoreHover, TRUE);
		}
	}

	// 決定ボタンを描画
	if (PlayerSelectCard < 16) {
		DrawGraph(ButtonDecX, ButtonDecY, ButtonDec, TRUE);
		if (ButtonDecX < MouseX && MouseX < (ButtonDecX + BDSizeX)) {
			if (ButtonDecY < MouseY && MouseY < (ButtonDecY + BDSizeY)) {
				DrawGraph(ButtonDecX, ButtonDecY, ButtonDecHover, TRUE);
			}
		}
	}



}