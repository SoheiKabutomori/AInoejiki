#include "SelectCom.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg2;
extern int ButtonDec, ButtonDecHover;
extern int ComIcon[5];
extern int ComSelect[5];
static int MouseCount = 0;
static int GSizeX, GSizeY;  // 画像サイズ
static int MouseX, MouseY;  // マウス位置
static int ButtonX = 1050, ButtonY = 600;  // ボタン設置位置
static int iconY1 = 250, iconY2 = 500;
extern int PlayerCount;
static int SelectComText;

// 初期化
void SelectCom_Initialize() {
	// 画像サイズの取得
	GetGraphSize(ButtonDec, &GSizeX, &GSizeY);
	//画像ロード
	SelectComText = LoadGraph("data/img/aiicon_text_02.png");
}

// 終了処理
void SelectCom_Finalize() {
	// 画像の解放
	DeleteGraph(SelectComText);
	/*DeleteGraph(BackgroundImg2);
	DeleteGraph(ButtonHandle1);
	DeleteGraph(ButtonHandle2);
	DeleteGraph(PlayerIcon[1]);
	DeleteGraph(PlayerIcon[2]);
	DeleteGraph(PlayerIcon[3]);
	DeleteGraph(PlayerIcon[4]);
	DeleteGraph(PlayerIcon[5]);*/
}

// 更新
void SelectCom_Update() {
	GetMousePoint(&MouseX, &MouseY);

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Title);   //シーンをタイトルに変更
	}
	if (PlayerCount > 3) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if ((ButtonX - GSizeX / 2) < MouseX && MouseX < (ButtonX + GSizeX / 2)) {
				if ((ButtonY - GSizeY / 2) < MouseY && MouseY < (ButtonY + GSizeY / 2)) {
					SceneMgr_ChangeScene(eScene_SelectCard);   // カード選択画面に変更
				}
			}
		}
	}

	
}

//描画
void SelectCom_Draw() {
	/*
	DrawString(0, 0, "プレイヤー選択画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
	*/

	// 背景表示
	DrawGraph(0, 0, BackgroundImg2, FALSE);
	// テキスト表示
	DrawGraph((1280 - 704) / 2, 50, SelectComText, TRUE);

	// 決定ボタンを描画
	DrawGraph(ButtonX - GSizeX / 2, ButtonY - GSizeY / 2, ButtonDec, TRUE);
	if ((ButtonX - GSizeX / 2) < MouseX && MouseX < (ButtonX + GSizeX / 2)) {
		if ((ButtonY - GSizeY / 2) < MouseY && MouseY < (ButtonY + GSizeY / 2)) {
			if (PlayerCount > 3) {
				DrawGraph(ButtonX - GSizeX / 2, ButtonY - GSizeY / 2, ButtonDecHover, TRUE);
			}
		}
	}
	for (int i = 0; i < 5; i++) {
		if (60 + 240 * i < MouseX && MouseX < 260 + 240 * i) {
			if (iconY1 < MouseY && MouseY < iconY2) {
				if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {//左クリック長押しのとき
					MouseCount++;
				}
				else {//左クリック離すとMouseCountが０になる
					MouseCount = 0;
				}
				if (MouseCount == 1) {//クリックされたとき）
					if (ComSelect[i] == 0) {//プレイヤーが選択されていないとき
						ComSelect[i] = 1;//選択された状態
						PlayerCount += 1;//プレイヤ人数を１人増やす
					}
					else if (ComSelect[i] == 1) {//プレイヤがすでに選択されている場合
						ComSelect[i] = 0;//選択解除
						PlayerCount -= 1;//プレイヤ人数を１人減らす
					}
				}
			}
		}
		if (ComSelect[i] == 1) {//プレイヤが選択されているとき
			DrawBox(50 + 240 * i, iconY1 - 10, 270 + 240 * i, iconY2 + 10, GetColor(0, 0, 255), TRUE);
		}
		DrawExtendGraph(60 + 240 * i, iconY1, 260 + 240 * i, iconY2, ComIcon[i], FALSE);
	}
	DrawFormatString(0, 600, GetColor(255,255,255), "%d", PlayerCount);
}