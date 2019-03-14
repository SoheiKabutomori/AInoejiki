#include "DxLib.h"
#include "Title.h"
#include "Tutorial.h"
#include "SelectPlayer.h"
#include "SelectCom.h"
#include "SelectCard.h"
#include "Score.h"
#include "CardOpen.h"
#include "End.h"
#include "SceneMgr.h"

static eScene mScene = eScene_Title;     // �V�[���Ǘ��ϐ�
static eScene mNextScene = eScene_None;  // ���̃V�[���Ǘ��ϐ�

static void SceneMgr_InitializeModule(eScene scene);  // �w�胂�W���[��������������
static void SceneMgr_FinalizeModule(eScene scene);    // �w�胂�W���[���̏I���������s��

// ������
void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

// �I������
void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

// �X�V
void SceneMgr_Update() {
	if (mNextScene != eScene_None) {          // ���̃V�[�����Z�b�g����Ă�����
		SceneMgr_FinalizeModule(mScene);      // ���݂̃V�[���̏I�����������s
		mScene = mNextScene;                  // ���̃V�[�������݂̃V�[���Z�b�g
		mNextScene = eScene_None;             // ���̃V�[�������N���A
		SceneMgr_InitializeModule(mScene);    // ���݂̃V�[����������
	}
	switch (mScene) {          // �V�[���ɂ���ď����𕪊�
	case eScene_Title:         // ���݂̉�ʂ����j���[�Ȃ�
		Title_Update();        // ���j���[��ʂ̍X�V����������
		break;
	case eScene_SelectPlayer:
		SelectPlayer_Update();
		break;
	case eScene_SelectCom:
		SelectCom_Update();
		break;
	case eScene_Tutorial:
		Tutorial_Update();
		break;
	case eScene_SelectCard:
		SelectCard_Update();
		break;
	case eScene_Score:
		Score_Update();
		break;
	case eScene_CardOpen:
		CardOpen_Update();
		break;
	case eScene_End:
		End_Update();
		break;
	}
}

// �`��
void SceneMgr_Draw() {
	switch (mScene) {      // �V�[���ɂ���ď����𕪊�
	case eScene_Title:     // ���݂̉�ʂ����j���[��ʂȂ�
		Title_Draw();      // ���j���[��ʂ̕`�揈��������
		break;
	case eScene_SelectPlayer:
		SelectPlayer_Draw();
		break;
	case eScene_SelectCom:
		SelectCom_Draw();
		break;
	case eScene_Tutorial:
		Tutorial_Draw();
		break;
	case eScene_SelectCard:
		SelectCard_Draw();
		break;
	case eScene_Score:
		Score_Draw();
		break;
	case eScene_CardOpen:
		CardOpen_Draw();
		break;
	case eScene_End:
		End_Draw();
		break;
	}
}

// ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene NextScene) {
	mNextScene = NextScene;    // ���̃V�[�����Z�b�g����
}

// ����scene���W���[��������������
static void SceneMgr_InitializeModule(eScene scene) {
	switch (scene) {          // �V�[���ɂ���ď����𕪊�
	case eScene_Title:        // �w���ʂ����j���[��ʂȂ�
		Title_Initialize();   // ���j���[��ʂ̏���������������
		break;
	case eScene_SelectPlayer:
		SelectPlayer_Initialize();
		break;
	case eScene_SelectCom:
		SelectCom_Initialize();
		break;
	case eScene_Tutorial:
		Tutorial_Initialize();
		break;
	case eScene_SelectCard:
		SelectCard_Initialize();
		break;
	case eScene_Score:
		Score_Initialize();
		break;
	case eScene_CardOpen:
		CardOpen_Initialize();
		break;
	case eScene_End:
		End_Initialize();
		break;
	}
}

// ����scene���W���[���̏I���������s��
static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene) {         // �V�[���ɂ���ď����𕪊�
	case eScene_Title:       // �w���ʂ����j���[��ʂȂ�
		Title_Finalize();    // ���j���[��ʂ̏I����������������
		break;
	case eScene_SelectPlayer:
		SelectPlayer_Finalize();
		break;
	case eScene_SelectCom:
		SelectCom_Finalize();
		break;
	case eScene_Tutorial:
		Tutorial_Finalize();
		break;
	case eScene_SelectCard:
		SelectCard_Finalize();
		break;
	case eScene_Score:
		Score_Finalize();
		break;
	case eScene_CardOpen:
		CardOpen_Finalize();
		break;
	case eScene_End:
		End_Finalize();
		break;
	}
}