#include "Tutorial.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg2;
static int Tutorial[5];
static int MouseCount = 2;
static int MouseX, MouseY;  // マウス位置
static int TutoCount;

// 初期化
void Tutorial_Initialize() {
	//mImageHandle = LoadGraph("images/Scene_Config.png");//画像のロード
	TutoCount = 0;
	Tutorial[0] = LoadGraph("data/img/tutorial1.png");
	Tutorial[1] = LoadGraph("data/img/tutorial2.png");
	Tutorial[2] = LoadGraph("data/img/tutorial3.png");
	Tutorial[3] = LoadGraph("data/img/tutorial4.png");

	Tutorial[4] = LoadGraph("data/img/TitleScreenBackground.png");
}

// 終了処理
void Tutorial_Finalize() {
	//DeleteGraph(mImageHandle);//画像の解放
	DeleteGraph(Tutorial[0]);
	DeleteGraph(Tutorial[1]);
	DeleteGraph(Tutorial[2]);
	DeleteGraph(Tutorial[3]);

	DeleteGraph(Tutorial[4]);
}

// 更新
void Tutorial_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Title);   //シーンをタイトルに変更
	}
	else if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (TutoCount == 4) {
			SceneMgr_ChangeScene(eScene_Title);
		}
	}
}

// 描画
void Tutorial_Draw() {
	DrawGraph(0, 0, Tutorial[TutoCount], FALSE);
	//DrawString(0, 0, "チュートリアル画面です。", GetColor(255, 255, 255));
	//DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
	//DrawFormatString(0, 600, GetColor(255, 255, 255), "%d", TutoCount);
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {//左クリック長押しのとき
		MouseCount++;
	}
	else {//左クリック離すとMouseCountが０になる
		MouseCount = 0;
	}
	if (MouseCount == 1) {//クリックされたとき
		TutoCount++;
	}
}