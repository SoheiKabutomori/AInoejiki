#include "Score.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg2;
static int GSizeX, GSizeY;  // �摜�T�C�Y
static int MouseX, MouseY;  // �}�E�X�ʒu
static int ButtonX = 1000, ButtonY = 600;  // �{�^���ݒu�ʒu
extern int Deck1[15], Deck2[15];  //16�̉摜���i�[����z��
static unsigned int white = GetColor(255, 255, 255);    // ���F�̒l���擾
static int height;     // ��s�̍���
extern int PlayerScore[6];
extern int PlayerCount;
extern int Score[15];
extern int DeckSelect;
static int value[15] = { -5, -4, -3, -2, -1,1, 2, 3, 4, 5,6, 7, 8, 9, 10 };
static int FontHandle60;
static int FontHandle90;
static int MouseCount = 2;


// ������
void Score_Initialize() {
	// �摜�̃��[�h
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
				PlayerScore[i] = PlayerScore[i] + value[s];        // �X�R�A���v�Z�E�i�[
			}
		}
	}
}

// �I������
void Score_Finalize() {
	// �摜�̉��
	/*DeleteGraph(BackgroundImg2);
	DeleteGraph(ButtonDec);
	DeleteGraph(ButtonDecHover);*/
}

// �X�V
void Score_Update() {
	GetMousePoint(&MouseX, &MouseY);
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Title);   // �V�[�����^�C�g���ɕύX
	}
	
	// �͈͓������N���b�N��
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		MouseCount++;
		if (MouseCount == 1) {
			DeckSelect = 1;
			SceneMgr_ChangeScene(eScene_SelectCard);   // �J�[�h�I����ʂɕύX
		}
	}
	else {
		MouseCount = 0;
	}
}

// �`��
void Score_Draw() {
	DrawGraph(0, 0, BackgroundImg2, FALSE);
	for (int i = 0; i < PlayerCount; i++) {
		// Player��
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
					DrawGraph(150 + 125 * cct, 13 + i * 180, Deck1[s], TRUE); // �J�[�h��`�悷��
				}
				else {
					DrawGraph(140 + 85 * cct, 8 + (i * 120), Deck2[s], TRUE);
				}
				cct++;
			}
		}
		if (PlayerCount > 4) {
			// �X�R�A��`��
			DrawFormatStringToHandle(1100, (height*i) + (height*0.25), white, FontHandle60, "%d�_", PlayerScore[i]);
		}
		else {
			DrawFormatStringToHandle(1100, (height*i) + (height*0.25), white, FontHandle90, "%d�_", PlayerScore[i]);
		}
		// ��؂����`��
		DrawLine(0, height*(i + 1), 1280, height*(i + 1), white);
	}
}