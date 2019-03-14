#include "SelectPlayer.h"
#include "SceneMgr.h"
#include "DxLib.h"

extern int BackgroundImg2;
extern int ButtonDec, ButtonDecHover;
extern int PlayerIcon[5];
extern int PlayerSelect[5];
static int MouseCount = 0;
static int GSizeX, GSizeY;  // �摜�T�C�Y
static int MouseX, MouseY;  // �}�E�X�ʒu
static int ButtonX = 1050, ButtonY = 600;  // �{�^���ݒu�ʒu
static int iconY1 = 250, iconY2 = 500;
static int PlayerSelectText;  // �e�L�X�g�摜�n���h��
static int Count;
static int selected;


// ������
void SelectPlayer_Initialize() {
	// �摜�T�C�Y���擾
	GetGraphSize(ButtonDec, &GSizeX, &GSizeY);
	// �摜���[�h
	PlayerSelectText = LoadGraph("data/img/playericon_text_02.png");
	selected = 6;
	Count = 0;
}

// �I������
void SelectPlayer_Finalize() {
	// �摜�̉��
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

// �X�V
void SelectPlayer_Update() {
	GetMousePoint(&MouseX, &MouseY);

	if (CheckHitKey(KEY_INPUT_ESCAPE) != 0) {
		SceneMgr_ChangeScene(eScene_Title);   //�V�[�����^�C�g���ɕύX
	}
	if (selected < 6 ) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {
			if ((ButtonX - GSizeX / 2) < MouseX && MouseX < (ButtonX + GSizeX / 2)) {
				if ((ButtonY - GSizeY / 2) < MouseY && MouseY < (ButtonY + GSizeY / 2)) {
					PlayerSelect[selected] = 1;
					SceneMgr_ChangeScene(eScene_SelectCom);   // �J�[�h�I����ʂɕύX
				}
			}
		}
	}


}

//�`��
void SelectPlayer_Draw() {
	
	DrawString(0, 0, "�v���C���[�I����ʂł��B", GetColor(255, 255, 255));
	DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));
	DrawFormatString(0, 40, GetColor(255, 255, 255), "%d", Count);
	

	//�@�w�i�\��
	DrawGraph(0, 0, BackgroundImg2, FALSE);

	// �e�L�X�g�\��
	DrawGraph((1280 - 704) / 2, 50, PlayerSelectText, TRUE);

	// ����{�^����`��
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
				if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0) {//���N���b�N�������̂Ƃ�
					MouseCount++;
				}
				else {//���N���b�N������MouseCount���O�ɂȂ�
					MouseCount = 0;
				}
				if (MouseCount == 1) {//�N���b�N���ꂽ�Ƃ��j
					if (selected != i) {//�v���C���[���I������Ă��Ȃ��Ƃ�
						selected = i;//�I�����ꂽ���
					}
					else if (selected == i) {//�v���C�������łɑI������Ă���ꍇ
						selected = 6;//�I������
					}
				}
			}
		}
		if (selected == i) {//�v���C�����I������Ă���Ƃ�
			DrawBox(50 + 240 * i, iconY1- 10, 270 + 240 * i, iconY2 + 10, GetColor(0, 0, 255), TRUE);
		}
		DrawExtendGraph(60 + 240 * i, iconY1, 260 + 240 * i, iconY2, PlayerIcon[i], TRUE);
	}
	DrawFormatString(0, 600, GetColor(255, 255, 255), "%d", Count);
	
}