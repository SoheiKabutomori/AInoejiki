#pragma once
extern int Score[15];
extern int ScoreCard;
extern int PlayerCount;
extern int PlayerSelect[5];
void Title_Initialize();  // 初期化
void Title_Finalize();    // 終了処理
void Title_Update();      // 更新
void Title_Draw();        // 描画