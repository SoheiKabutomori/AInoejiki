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

static eScene mScene = eScene_Title;     // シーン管理変数
static eScene mNextScene = eScene_None;  // 次のシーン管理変数

static void SceneMgr_InitializeModule(eScene scene);  // 指定モジュールを初期化する
static void SceneMgr_FinalizeModule(eScene scene);    // 指定モジュールの終了処理を行う

// 初期化
void SceneMgr_Initialize() {
	SceneMgr_InitializeModule(mScene);
}

// 終了処理
void SceneMgr_Finalize() {
	SceneMgr_FinalizeModule(mScene);
}

// 更新
void SceneMgr_Update() {
	if (mNextScene != eScene_None) {          // 次のシーンがセットされていたら
		SceneMgr_FinalizeModule(mScene);      // 現在のシーンの終了処理を実行
		mScene = mNextScene;                  // 次のシーンを現在のシーンセット
		mNextScene = eScene_None;             // 次のシーン情報をクリア
		SceneMgr_InitializeModule(mScene);    // 現在のシーンを初期化
	}
	switch (mScene) {          // シーンによって処理を分岐
	case eScene_Title:         // 現在の画面がメニューなら
		Title_Update();        // メニュー画面の更新処理をする
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

// 描画
void SceneMgr_Draw() {
	switch (mScene) {      // シーンによって処理を分岐
	case eScene_Title:     // 現在の画面がメニュー画面なら
		Title_Draw();      // メニュー画面の描画処理をする
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

// 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene NextScene) {
	mNextScene = NextScene;    // 次のシーンをセットする
}

// 引数sceneモジュールを初期化する
static void SceneMgr_InitializeModule(eScene scene) {
	switch (scene) {          // シーンによって処理を分岐
	case eScene_Title:        // 指定画面がメニュー画面なら
		Title_Initialize();   // メニュー画面の初期化処理をする
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

// 引数sceneモジュールの終了処理を行う
static void SceneMgr_FinalizeModule(eScene scene) {
	switch (scene) {         // シーンによって処理を分岐
	case eScene_Title:       // 指定画面がメニュー画面なら
		Title_Finalize();    // メニュー画面の終了処理処理をする
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