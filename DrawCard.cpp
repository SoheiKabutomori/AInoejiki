#include "DxLib.h"
#include <iostream> 

void CardPick(int cardx, int cardy, int x, int y, int Mouse, int Image,int num);

int pick;




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	SetGraphMode(1280, 720, 16);

	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX,������,����ʐݒ�
	

	int x, y, Mouse, Wheel, Image;
	double size = 1.0;
	int kari = 0;
	int num = 1;
	int pick = 0;
	Image = LoadGraph("�G.bmp");//�摜���[�h
	Mouse = GetMouseInput();                //�}�E�X�̓��͏�Ԏ擾
											//Wheel = GetMouseWheelRotVol();  //�z�C�[���̉�]�ʎ擾
	GetMousePoint(&x, &y);    //�}�E�X�̍��W�擾

	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen()) {
		Mouse = GetMouseInput();                //�}�E�X�̓��͏�Ԏ擾
		GetMousePoint(&x, &y);
		CardPick(200, 400, x, y, Mouse, Image, 1);
		CardPick(400, 400, x, y, Mouse, Image, 2);
		
	}
	
	DxLib_End();
	return 0;
}



	//cardx,cardy�̓J�[�h�̍��W
	//x,y�̓}�E�X�̈ʒu
	//Image�͉摜�@num�̓J�[�h�̔ԍ�
void CardPick(int cardx, int cardy, int x, int y, int Mouse, int Image, int num) {
	int kari=0;
	double size = 1.0;

	int Color = GetColor(255, 255, 255);
		Mouse = GetMouseInput();                //�}�E�X�̓��͏�Ԏ擾
		GetMousePoint(&x, &y);                //�}�E�X�̍��W�擾

		DrawFormatString(0, 0, Color, "���݂̒l�� %d �ł�", pick);
		if (cardx-50 < x && x < cardx + 50 && cardy - 70 < y && y < cardy + 70) {
			size = 1.2;
			if (MOUSE_INPUT_LEFT) {
				pick = num;
			}
		}
		else { size = 1; }
		//if (kari) { DrawRotaGraph(cardx, cardy, 1.2, 0.0, Image, TRUE); }
		 DrawRotaGraph(cardx, cardy, size, 0.0, Image, TRUE);  //�摜��x,y�̈ʒu�ɃT�C�Ysize�ŕ`��

}