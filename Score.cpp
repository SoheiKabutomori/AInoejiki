#include "Score.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg2;
static int GSizeX, GSizeY;  // 画像サイズ
static int MouseX, MouseY;  // マウス位置
static int ButtonX = 1000, ButtonY = 600;  // ボタン設置位置
extern int Deck1[15], Deck2[15];  //16個の画像を格納する配列
static unsigned int white = GetColor(255, 255, 255);    // 白色の値を取得
static int height;     // 一行の高さ
extern int PlayerScore[6];
extern int PlayerCount;
extern int Score[15];
extern int DeckSelect;
static int value[15] = { -5, -4, -3, -2, -1,1, 2, 3, 4, 5,6, 7, 8, 9, 10 };
static int FontHandle60;
static int FontHandle90;
static int MouseCount = 2;


// 初期化
void Score_Initialize() {
	// 画像のロード
	FontHandle60 = CreateFontToHandle(NULL, 60, -1);
	FontHandle90 = CreateFontToHandle(NULL, 90, -1);
	PlayerScore[0] = 0;
	PlayerScore[1] = 0;
	PlayerScore[2] = 0;
	PlayerScore[3] = 0;
	PlayerScore[4] = 0;
	PlayerScore[5] = 0;
	if (PlayerCount >= 1 && PlayerCount <= 4) {
		height = 180;
	}
	else {
		height = 120;
	}
	for (int i = 0; i < PlayerCount; i++) {
		for (int s = 0; s < 15; s++) {
			if (i + 1 == Score[s]) {
				PlayerScore[i] = PlayerScore[i] + value[s];        // スコアを計算・格納
			}
		}
	}
}

// 終了処理
void Score_Finalize() {
	// 画像の解放
	/*DeleteGraph(BackgroundImg2);
	DeleteGraph(ButtonDec);
	DeleteGraph(ButtonDecHover);*/
}

// 更新
void Score_Update() {
	GetMousePoint(&MouseX, &MouseY);
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Title);   // シーンをタイトルに変更
	}
	
	// 範囲内を左クリック時
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		MouseCount++;
		if (MouseCount == 1) {
			DeckSelect = 1;
			SceneMgr_ChangeScene(eScene_SelectCard);   // カード選択画面に変更
		}
	}
	else {
		MouseCount = 0;
	}
}

// 描画
void Score_Draw() {
	DrawGraph(0, 0, BackgroundImg2, FALSE);
	for (int i = 0; i < PlayerCount; i++) {
		// Player名
		if (PlayerCount > 4) {
			if (i == 0) {
				DrawFormatStringToHandle(20, (height*i) + (height*0.25), white, FontHandle60, "P");
			}
			else {
				DrawFormatStringToHandle(20, (height*i) + (height*0.25), white, FontHandle60, "C%d", i);
			}
		}
		else {
			if (i == 0) {
				DrawFormatStringToHandle(20, (height*i) + (height*0.25), white, FontHandle90, "P");
			}
			else {
				DrawFormatStringToHandle(20, (height*i) + (height*0.25), white, FontHandle90, "C%d", i);
			}
			
		}
		int cct = 0; //cardCount
		for (int s = 0; s < 15; s++) {
			if (i + 1 == Score[s]) {
				if ( PlayerCount >= 1 && PlayerCount <= 4) {
					DrawGraph(150 + 125 * cct, 13 + i * 180, Deck1[s], TRUE); // カードを描画する
				}
				else {
					DrawGraph(140 + 85 * cct, 8 + (i * 120), Deck2[s], TRUE);
				}
				cct++;
			}
		}
		if (PlayerCount > 4) {
			// スコアを描画
			DrawFormatStringToHandle(1100, (height*i) + (height*0.25), white, FontHandle60, "%d点", PlayerScore[i]);
		}
		else {
			DrawFormatStringToHandle(1100, (height*i) + (height*0.25), white, FontHandle90, "%d点", PlayerScore[i]);
		}
		// 区切り線を描画
		DrawLine(0, height*(i + 1), 1280, height*(i + 1), white);
	}
}