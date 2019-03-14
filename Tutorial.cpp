#include "Tutorial.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg2;
static int Tutorial[5];
static int MouseCount = 2;
static int MouseX, MouseY;  // �}�E�X�ʒu
static int TutoCount;

// ������
void Tutorial_Initialize() {
	//mImageHandle = LoadGraph("images/Scene_Config.png");//�摜�̃��[�h
	TutoCount = 0;
	Tutorial[0] = LoadGraph("data/img/tutorial1.png");
	Tutorial[1] = LoadGraph("data/img/tutorial2.png");
	Tutorial[2] = LoadGraph("data/img/tutorial3.png");
	Tutorial[3] = LoadGraph("data/img/tutorial4.png");

	Tutorial[4] = LoadGraph("data/img/TitleScreenBackground.png");
}

// �I������
void Tutorial_Finalize() {
	//DeleteGraph(mImageHandle);//�摜�̉��
	DeleteGraph(Tutorial[0]);
	DeleteGraph(Tutorial[1]);
	DeleteGraph(Tutorial[2]);
	DeleteGraph(Tutorial[3]);

	DeleteGraph(Tutorial[4]);
}

// �X�V
void Tutorial_Update() {
	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Title);   //�V�[�����^�C�g���ɕύX
	}
	else if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
		if (TutoCount == 4) {
			SceneMgr_ChangeScene(eScene_Title);
		}
	}
}

// �`��
void Tutorial_Draw() {
	DrawGraph(0, 0, Tutorial[TutoCount], FALSE);
	//DrawString(0, 0, "�`���[�g���A����ʂł��B", GetColor(255, 255, 255));
	//DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
	//DrawFormatString(0, 600, GetColor(255, 255, 255), "%d", TutoCount);
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {//���N���b�N�������̂Ƃ�
		MouseCount++;
	}
	else {//���N���b�N������MouseCount���O�ɂȂ�
		MouseCount = 0;
	}
	if (MouseCount == 1) {//�N���b�N���ꂽ�Ƃ�
		TutoCount++;
	}
}