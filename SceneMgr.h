#pragma once

typedef enum {
	eScene_Title,        // タイトル画面
	eScene_CardOpen,     // カード表示画面
	eScene_Tutorial,     // チュートリアル画面
	eScene_Score,        // スコア画面
	eScene_SelectPlayer, // プレイヤー選択画面
	eScene_SelectCom,    // コンピュータ選択画面
	eScene_SelectCard,   // カード選択画面
	eScene_End,          // 終了画面

	eScene_None,    //無し
} eScene;

void SceneMgr_Initialize();  // 初期化
void SceneMgr_Finalize();    // 終了処理
void SceneMgr_Update();      // 更新
void SceneMgr_Draw();        // 描画

// 引数 nextScene にシーンを変更する
void SceneMgr_ChangeScene(eScene nextScene);