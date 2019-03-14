#include "DxLib.h"
#include <iostream> 

void CardPick(int cardx, int cardy, int x, int y, int Mouse, int Image,int num);

int pick;




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	SetGraphMode(1280, 720, 16);

	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //ウィンドウモード変更,初期化,裏画面設定
	

	int x, y, Mouse, Wheel, Image;
	double size = 1.0;
	int kari = 0;
	int num = 1;
	int pick = 0;
	Image = LoadGraph("絵.bmp");//画像ロード
	Mouse = GetMouseInput();                //マウスの入力状態取得
											//Wheel = GetMouseWheelRotVol();  //ホイールの回転量取得
	GetMousePoint(&x, &y);    //マウスの座標取得

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		Mouse = GetMouseInput();                //マウスの入力状態取得
		GetMousePoint(&x, &y);
		CardPick(200, 400, x, y, Mouse, Image, 1);
		CardPick(400, 400, x, y, Mouse, Image, 2);
		
	}
	
	DxLib_End();
	return 0;
}



	//cardx,cardyはカードの座標
	//x,yはマウスの位置
	//Imageは画像　numはカードの番号
void CardPick(int cardx, int cardy, int x, int y, int Mouse, int Image, int num) {
	int kari=0;
	double size = 1.0;

	int Color = GetColor(255, 255, 255);
		Mouse = GetMouseInput();                //マウスの入力状態取得
		GetMousePoint(&x, &y);                //マウスの座標取得

		DrawFormatString(0, 0, Color, "現在の値は %d です", pick);
		if (cardx-50 < x && x < cardx + 50 && cardy - 70 < y && y < cardy + 70) {
			size = 1.2;
			if (MOUSE_INPUT_LEFT) {
				pick = num;
			}
		}
		else { size = 1; }
		//if (kari) { DrawRotaGraph(cardx, cardy, 1.2, 0.0, Image, TRUE); }
		 DrawRotaGraph(cardx, cardy, size, 0.0, Image, TRUE);  //画像をx,yの位置にサイズsizeで描画

}