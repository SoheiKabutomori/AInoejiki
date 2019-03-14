#include "SelectCard.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg2;
extern int ButtonScoreHandle1, ButtonScoreHandle2;
extern int Deck1[15];
extern int Hand[15];//�J�[�h��݂���
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



static int GSizeX, GSizeY;  // �摜�T�C�Y
static int MouseX, MouseY;  // �}�E�X�ʒu
static int ButtonDecX = 1050, ButtonDecY = 570;
static int ButtonScoreX = 1100, ButtonScoreY = 30;
static int ButtonBackX = 20, ButtonBackY = 20;
extern int ButtonDec;
extern int ButtonDecHover;
static int ButtonBack;
static int ButtonBackHover;
static int ButtonScore;
static int ButtonScoreHover;
static int BDSizeX = 181, BDSizeY = 103;  // ButtonDec�T�C�Y
static int BSSizeX = 110, BSSizeY = 63;  // ButtonScore�T�C�Y
static int BBSizeX = 81, BBSizeY = 28;  // ButtonBack�T�C�Y
static int PointCardImg;

static int CardTest;


// ������
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

	// �摜�̃��[�h
	PointCardImg = PointCardSetImg[ScoreCard];
	ButtonBack = LoadGraph("data/img/Button/back.png");
	ButtonBackHover = LoadGraph("data/img/Button/back_hover.png");
	ButtonScore = LoadGraph("data/img/Button/score.png");
	ButtonScoreHover = LoadGraph("data/img/Button/score_hover.png");
}

// �I������
void SelectCard_Finalize() {
	// �摜�̉��
	DeleteGraph(ButtonBack);
	DeleteGraph(ButtonBackHover);
	DeleteGraph(ButtonScore);
	DeleteGraph(ButtonScoreHover);
}

// �X�V
void SelectCard_Update() {
	GetMousePoint(&MouseX, &MouseY);

	// �{�^�����N���b�N���ꂽ���̏���
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (PlayerSelectCard < 16) {
			if (ButtonDecX < MouseX && MouseX < (ButtonDecX + BDSizeX)) {          // ����{�^���N���b�N
				if (ButtonDecY < MouseY && MouseY < (ButtonDecY + BDSizeY)) {
					PlayerCard[PlayerSelectCard - 1] = 1;
					//Score[ScoreCard] = 1;
					SceneMgr_ChangeScene(eScene_CardOpen);   // �J�[�h�\����ʂɕύX
				}
			}
		}
		if (ButtonScoreX < MouseX && MouseX < (ButtonScoreX + BSSizeX)) {          // �X�R�A�{�^���N���b�N
			if (ButtonScoreY < MouseY && MouseY < (ButtonScoreY + BSSizeY)) {
				PlayerSelectCard = 16;
				SceneMgr_ChangeScene(eScene_Score);   // �X�R�A��ʂɕύX
			}
		}
		if (ButtonBackX < MouseX && MouseX < ButtonBackX + BBSizeX) {                // �߂�{�^���N���b�N
			if (ButtonBackY < MouseY && MouseY < ButtonBackY + BBSizeY) {
				SceneMgr_ChangeScene(eScene_Title);   // �^�C�g���ɖ߂�
			}
		}
	}
}


void CardPick(int cardx, int cardy, int x, int y, int Mouse, int Image, int num) {

	double size = 0.15;
	int Color = GetColor(255, 255, 255);
	Mouse = GetMouseInput();                //�}�E�X�̓��͏�Ԏ擾
	GetMousePoint(&x, &y);                //�}�E�X�̍��W�擾

										  //DrawFormatString(0, 40, Color, "���݂̒l�� %d �ł�", PlayerSelectCard);
	if (cardx - 50 < x && x < cardx + 50 && cardy - 70 < y && y < cardy + 70) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			PlayerSelectCard = num;
		}
	}
	if (num == PlayerSelectCard) { size = 0.2; }
	DrawRotaGraph(cardx, cardy, size, 0.0, Hand[num - 1], TRUE);  //�摜��x,y�̈ʒu�ɃT�C�Ysize�ŕ`��

}

// �`��
void SelectCard_Draw() {
	DrawGraph(0, 0, BackgroundImg2, FALSE);

	int x, y, Mouse;
	double size = 1.0;
	Mouse = GetMouseInput();                //�}�E�X�̓��͏�Ԏ擾
	GetMousePoint(&x, &y);    //�}�E�X�̍��W�擾



	// �L�����[�I�[�o�[�̕\��
	int CarryOverNum = 0;
	int CarryOverX1 = 750, CarryOverY1 = 150;  // �\���͈́i������W�j
	int CarryOverX2 = 1050, CarryOverY2 = 270;     // �\���͈́i�E����W�j
	int j = 0, k = 0;
	for (int i = 0; i < 15; i++) {  // �L�����[�I�[�o�[�J�[�h�����v�Z
		if (CarryOverCard[i] == 1) {
			CarryOverNum++;
		}
	}
	if (CarryOverNum > 0) {
		DrawString(815, 120, "�y�L�����[�I�[�o�[�z", GetColor(255, 255, 255));
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
	if (0) {  // 1:�}�E�X�ʒu���W�\��, 0:��\��
		char StrBuf[128], StrBuf2[32];
		int MouseX, MouseY;
		GetMousePoint(&MouseX, &MouseY);
		lstrcpy(StrBuf, "���W �w");
		itoa(MouseX, StrBuf2, 10);
		lstrcat(StrBuf, StrBuf2);
		lstrcat(StrBuf, "�@�x ");
		itoa(MouseY, StrBuf2, 10);
		lstrcat(StrBuf, StrBuf2);
		DrawString(0, 0, StrBuf, GetColor(255, 255, 255));
	}

	

	//��D�̕\��
	for (int i = 1; i < 16; i++) {
		if (PlayerCard[i - 1] == 0) { //�J�[�h�����g�p�Ȃ�\��
			if (i < 11) {	//��̒i
				CardPick(100 + i * 100, 400, x, y, Mouse, Hand[i - 1], i);
			}
			else {	//���̒i
				CardPick(-650 + i * 100, 600, x, y, Mouse, Hand[i - 1], i);
			}
		}
	}


	//��D�̕\��
	DrawRotaGraph(640, 150, 0.27, 0.0, PointCardImg, TRUE);

	//���݂̓_����\��
	//DrawString(1100, 140, "���݂̓_��", GetColor(255, 255, 255));
	for (int i = 0; i < PlayerCount; i++) {
		if (i == 0)
			DrawFormatString(1100, 110 + 25 * i, GetColor(255, 255, 255), "P   �@ %d�_", PlayerScore[i]);
		else
			DrawFormatString(1100, 110 + 25 * i, GetColor(255, 255, 255), "C%d�@�@ %d�_", i, PlayerScore[i]);
	}

	// �߂�{�^��
	DrawGraph(ButtonBackX, ButtonBackY, ButtonBack, TRUE);
	if (ButtonBackX < MouseX && MouseX < ButtonBackX + BBSizeX) {                // �߂�{�^���N���b�N
		if (ButtonBackY < MouseY && MouseY < ButtonBackY + BBSizeY) {
			DrawGraph(ButtonBackX, ButtonBackY, ButtonBackHover, TRUE);
		}
	}

	// �X�R�A�{�^����`��
	DrawGraph(ButtonScoreX, ButtonScoreY, ButtonScore, TRUE);
	if (ButtonScoreX < MouseX && MouseX < (ButtonScoreX + BSSizeX)) {
		if (ButtonScoreY < MouseY && MouseY < (ButtonScoreY + BSSizeY)) {
			DrawGraph(ButtonScoreX, ButtonScoreY, ButtonScoreHover, TRUE);
		}
	}

	// ����{�^����`��
	if (PlayerSelectCard < 16) {
		DrawGraph(ButtonDecX, ButtonDecY, ButtonDec, TRUE);
		if (ButtonDecX < MouseX && MouseX < (ButtonDecX + BDSizeX)) {
			if (ButtonDecY < MouseY && MouseY < (ButtonDecY + BDSizeY)) {
				DrawGraph(ButtonDecX, ButtonDecY, ButtonDecHover, TRUE);
			}
		}
	}



}