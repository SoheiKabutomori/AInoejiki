#include "SelectPlayer.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg2;
extern int ButtonDec, ButtonDecHover;
extern int PlayerIcon[5];
extern int PlayerSelect[5];
static int MouseCount = 0;
static int GSizeX, GSizeY;  // 画像サイズ
static int MouseX, MouseY;  // マウス位置
static int ButtonX = 1050, ButtonY = 600;  // ボタン設置位置
static int iconY1 = 250, iconY2 = 500;
static int PlayerSelectText;  // テキスト画像ハンドル
static int Count;
static int selected;


// 初期化
void SelectPlayer_Initialize() {
	// 画像サイズを取得
	GetGraphSize(ButtonDec, &GSizeX, &GSizeY);
	// 画像ロード
	PlayerSelectText = LoadGraph("data/img/playericon_text_02.png");
	selected = 6;
	Count = 0;
}

// 終了処理
void SelectPlayer_Finalize() {
	// 画像の解放
	DeleteGraph(PlayerSelectText);
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
void SelectPlayer_Update() {
	GetMousePoint(&MouseX, &MouseY);

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Title);   //シーンをタイトルに変更
	}
	if (selected < 6 ) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if ((ButtonX - GSizeX / 2) < MouseX && MouseX < (ButtonX + GSizeX / 2)) {
				if ((ButtonY - GSizeY / 2) < MouseY && MouseY < (ButtonY + GSizeY / 2)) {
					PlayerSelect[selected] = 1;
					SceneMgr_ChangeScene(eScene_SelectCom);   // カード選択画面に変更
				}
			}
		}
	}


}

//描画
void SelectPlayer_Draw() {
	
	DrawString(0, 0, "プレイヤー選択画面です。", GetColor(255, 255, 255));
	DrawString(0, 20, "Escキーを押すとメニュー画面に戻ります。", GetColor(255, 255, 255));
	DrawFormatString(0, 40, GetColor(255, 255, 255), "%d", Count);
	

	//　背景表示
	DrawGraph(0, 0, BackgroundImg2, FALSE);

	// テキスト表示
	DrawGraph((1280 - 704) / 2, 50, PlayerSelectText, TRUE);

	// 決定ボタンを描画
	DrawGraph(ButtonX - GSizeX / 2, ButtonY - GSizeY / 2, ButtonDec, TRUE);
	if ((ButtonX - GSizeX / 2) < MouseX && MouseX < (ButtonX + GSizeX / 2)) {
		if ((ButtonY - GSizeY / 2) < MouseY && MouseY < (ButtonY + GSizeY / 2)) {
			if (Count < 6) {
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
					if (selected != i) {//プレイヤーが選択されていないとき
						selected = i;//選択された状態
					}
					else if (selected == i) {//プレイヤがすでに選択されている場合
						selected = 6;//選択解除
					}
				}
			}
		}
		if (selected == i) {//プレイヤが選択されているとき
			DrawBox(50 + 240 * i, iconY1- 10, 270 + 240 * i, iconY2 + 10, GetColor(0, 0, 255), TRUE);
		}
		DrawExtendGraph(60 + 240 * i, iconY1, 260 + 240 * i, iconY2, PlayerIcon[i], TRUE);
	}
	DrawFormatString(0, 600, GetColor(255, 255, 255), "%d", Count);
	
}