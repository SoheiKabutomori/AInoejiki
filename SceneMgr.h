#pragma once

typedef enum {
	eScene_Title,        // �^�C�g�����
	eScene_CardOpen,     // �J�[�h�\�����
	eScene_Tutorial,     // �`���[�g���A�����
	eScene_Score,        // �X�R�A���
	eScene_SelectPlayer, // �v���C���[�I�����
	eScene_SelectCom,    // �R���s���[�^�I�����
	eScene_SelectCard,   // �J�[�h�I�����
	eScene_End,          // �I�����

	eScene_None,    //����
} eScene;

void SceneMgr_Initialize();  // ������
void SceneMgr_Finalize();    // �I������
void SceneMgr_Update();      // �X�V
void SceneMgr_Draw();        // �`��

// ���� nextScene �ɃV�[����ύX����
void SceneMgr_ChangeScene(eScene nextScene);