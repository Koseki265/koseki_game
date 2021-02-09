//-----------------------------------------------------------------------------
//
// ダイレクトｘの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#include "game.h"
#include "Player.h"
#include "bg.h"
#include "Bullet.h"
#include "Explosion.h"
#include "enemy.h"
#include "sound.h"
#include "score.h"
#include "fade.h"
#include "input.h"
//#include "Effect.h"
#include "pause.h"
#include "Time.h"
#include "block.h"
#include "item.h"
#include "goal.h"

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
bool g_bPause = false;
GAME g_Game;

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitGame(void)
{
	switch (g_Game.stage)
	{
	case STAGE_1:
		//背景の初期化
		InitBg();

		//プレイヤーの初期化処理
		InitPlayer();

		//ブロックの初期化処理
		InitBlock();

		//アイテムの初期化処理
		InitItem();

		//ゴールの初期化
		InitGoal();

		//弾の初期化処理
		InitBullet();

		//エフェクトの初期化処理
		//InitEffect();

		//敵の初期化処理
		InitEnemy();

		//スコアの初期化
		InitScore();

		//時間の初期化
		InitTime();

		//ポーズの初期化処理
		InitPause();

		//サウンドスタート
		//PlaySound(SOUND_LABEL_BGM002);
		Stage1();

		break;

		case STAGE_2:

			//背景の初期化
			InitBg();

			//プレイヤーの初期化処理
			InitPlayer();

			//ブロックの初期化処理
			InitBlock();

			//アイテムの初期化処理
			InitItem();

			//ゴールの初期化
			InitGoal();

			//弾の初期化処理
			InitBullet();

			//エフェクトの初期化処理
			//InitEffect();

			//敵の初期化処理
			InitEnemy();

			//スコアの初期化
			InitScore();

			//時間の初期化
			InitTime();

			//ポーズの初期化処理
			InitPause();

			//サウンドスタート
			//PlaySound(SOUND_LABEL_BGM002);

		Stage2();

		break;

	}

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitGame(void)
{
	switch (g_Game.stage)
	{
	case STAGE_1:
		//サウンドストップ
		StopSound();

		//ポーズの終了処理
		UninitPause();

		//時間の終了処理
		UninitTime();

		//敵の終了処理
		UninitEnemy();

		//エフェクトの終了処理
		//UninitEffect();

		//弾の終了処理
		UninitBullet();

		//ゴールの終了処理
		UninitGoal();

		//アイテムの終了処理
		UninitItem();

		//ブロックの終了処理
		UninitBlock();

		//プレイヤーの終了処理
		UninitPlayer();

		//背景の終了
		UninitBg();
		break;

	case STAGE_2:

		//サウンドストップ
		StopSound();

		//ポーズの終了処理
		UninitPause();

		//時間の終了処理
		UninitTime();

		//敵の終了処理
		UninitEnemy();

		//エフェクトの終了処理
		//UninitEffect();

		//弾の終了処理
		UninitBullet();

		//ゴールの終了処理
		UninitGoal();

		//アイテムの終了処理
		UninitItem();

		//ブロックの終了処理
		UninitBlock();

		//プレイヤーの終了処理
		UninitPlayer();

		//背景の終了
		UninitBg();

		break;
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateGame(void)
{

	FADE *pFade;
	pFade = GetFade();

	GOAL *pGoal;
	pGoal = GetGoal();

	if (GetKeyboardTrigger(DIK_P) == true)
	{
		if (*pFade == FADE_NONE)
		{
			g_bPause = g_bPause ? false : true;
		}
		if (g_bPause == true)
		{
			PlaySound(SOUND_LABEL_SE_MENU);
		}
		else if (g_bPause == false)
		{
			PlaySound(SOUND_LABEL_SE_MENUCLOSE);
		}
	}

	SetPause(g_bPause);

	if (g_bPause == true)
	{
		//ポーズの更新処理
		UpdatePause();
	}

	else if (g_bPause == false && *pFade == FADE_NONE)
	{
		switch (g_Game.stage)
		{
		case STAGE_1:
			if (pGoal->bUse == true)
			{

				//背景の更新処理
				UpdateBg();

				//プレイヤーの更新処理
				UpdatePlayer();

				//ブロックの更新処理
				UpdateBlock();

				//敵の更新処理
				UpdateEnemy();

				//アイテムの更新処理
				UpdateItem();

				//ゴールの更新処理
				UpdateGoal();

				//弾の更新処理
				UpdateBullet();

				//エフェクトの更新処理
				//UpdateEffect();

				//スコアの更新処理
				UpdateScore();
			}

			//時間の更新処理
			UpdateTime();
			break;

		case STAGE_2:
			if (pGoal->bUse == true)
			{

				//背景の更新処理
				UpdateBg();

				//プレイヤーの更新処理
				UpdatePlayer();

				//ブロックの更新処理
				UpdateBlock();

				//敵の更新処理
				UpdateEnemy();

				//アイテムの更新処理
				UpdateItem();

				//ゴールの更新処理
				UpdateGoal();

				//弾の更新処理
				UpdateBullet();

				//エフェクトの更新処理
				//UpdateEffect();

				//スコアの更新処理
				UpdateScore();
			}

			//時間の更新処理
			UpdateTime();
			break;
		}
	}

	/*if (GetKeyboardTrigger(DIK_L) == true)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}*/
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawGame(void)
{
	switch (g_Game.stage)
	{
	case STAGE_1:

		//背景の描画
		DrawBg();

		//ポリゴンの描画処理
		DrawPlayer();

		//ブロックの描画処理
		DrawBlock();

		//アイテムの描画処理
		DrawItem();

		//ゴールの描画処理
		DrawGoal();

		//弾の描画処理
		DrawBullet();

		//エフェクトの描画処理
		//DrawEffect();

		//敵の描画処理
		DrawEnemy();

		//スコアの描画処理
		DrawScore();

		//時間の描画処理
		DrawTime();

		break;

	case STAGE_2:

		//背景の描画
		DrawBg();

		//ポリゴンの描画処理
		DrawPlayer();

		//ブロックの描画処理
		DrawBlock();

		//アイテムの描画処理
		DrawItem();

		//ゴールの描画処理
		DrawGoal();

		//弾の描画処理
		DrawBullet();

		//エフェクトの描画処理
		//DrawEffect();

		//敵の描画処理
		DrawEnemy();

		//スコアの描画処理
		DrawScore();

		//時間の描画処理
		DrawTime();

		break;

	}

	if (g_bPause == true)
	{
		DrawPause();
	}

}

void Stage1(void)
{
	//サウンドスタート
	PlaySound(SOUND_LABEL_BGM000);

	//ブロック配置
	//床
	SetBlock(D3DXVECTOR3(0, 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1920, 50);

	//天井
	SetBlock(D3DXVECTOR3(0, -25, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1920, 50);
#if 1
	//左のブロック

	//下
	SetBlock(D3DXVECTOR3(50, 750, 0), D3DXVECTOR3(0, 0, 0.0f), 300, 50);

	//真ん中
	SetBlock(D3DXVECTOR3(225, 450, 0), D3DXVECTOR3(0, 0, 0.0f), 275, 50);

	//上
	SetBlock(D3DXVECTOR3(50, 130, 0), D3DXVECTOR3(0, 0, 0.0f), 275, 50);

#endif
	//真ん中のブロック

	//敵が乗ってるブロック上
	SetBlock(D3DXVECTOR3(550, 250, 0), D3DXVECTOR3(0, 0, 0.0f), 100, 50);

	//敵が乗ってるブロック真ん中
	SetBlock(D3DXVECTOR3(550, 500, 0), D3DXVECTOR3(0, 0, 0.0f), 100, 50);

	//敵が乗ってるブロック下
	SetBlock(D3DXVECTOR3(550, 750, 0), D3DXVECTOR3(0, 0, 0.0f), 100, 50);

	//上
	SetBlock(D3DXVECTOR3(1025, 150, 0), D3DXVECTOR3(0, 0, 0.0f), 75, 50);

	//真ん中
	SetBlock(D3DXVECTOR3(800, 350, 0), D3DXVECTOR3(0, 0, 0.0f), 75, 50);

	//真ん中下
	SetBlock(D3DXVECTOR3(1050, 600, 0), D3DXVECTOR3(0, 0, 0.0f), 70, 50);

	//下
	SetBlock(D3DXVECTOR3(800, 750, 0), D3DXVECTOR3(0, 0, 0.0f), 75, 50);

	//右ブロック
	//上
	SetBlock(D3DXVECTOR3(1150, 150, 0), D3DXVECTOR3(0, 0, 0.0f), 450, 50);

	//真ん中
	SetBlock(D3DXVECTOR3(1420, 400, 0), D3DXVECTOR3(0, 0, 0.0f), 500, 50);

	//下
	SetBlock(D3DXVECTOR3(1150, 650, 0), D3DXVECTOR3(0, 0, 0.0f), 500, 50);

#if 1
	//壁
	//左端
	SetBlock(D3DXVECTOR3(0, 130, 0), D3DXVECTOR3(0, 0, 0.0f), 50, 900);

	//真ん中左
	SetBlock(D3DXVECTOR3(500, 25, 0), D3DXVECTOR3(0, 0, 0.0f), 50, 900);

	//真ん中右
	SetBlock(D3DXVECTOR3(1100, 150, 0), D3DXVECTOR3(0, 0, 0.0f), 50, 900);

	//右端
	SetBlock(D3DXVECTOR3(1870, 25, 0), D3DXVECTOR3(0, 0, 0.0f), 50, 1005);

#endif
	//敵の配置
	//左のブロック
	//上の敵
	SetEnemy(D3DXVECTOR3(440, 400, 0.0f), D3DXVECTOR3(ENEMY_SPEED, 0, 0.0f), 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//下の敵
	SetEnemy(D3DXVECTOR3(300, 750, 0.0f), D3DXVECTOR3(ENEMY_SPEED, 0, 0.0f), 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//真ん中ブロック
	//下の敵
	SetEnemy(D3DXVECTOR3(600, 750, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//真ん中の敵
	SetEnemy(D3DXVECTOR3(600, 500, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//上の敵
	SetEnemy(D3DXVECTOR3(600, 250, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//右のブロック
	//敵
	SetEnemy(D3DXVECTOR3(1300, 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), RIGHT);

	//SetEnemy(D3DXVECTOR3(600, 900, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//アイテム
	//コイン
	//左下
	for (int nCount = 0; nCount < 5; nCount++)
	{
		SetItem(D3DXVECTOR3(80 + (nCount * 60.0f), 1030, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(80 + (nCount * 60.0f), 980, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(80 + (nCount * 60.0f), 930, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(80 + (nCount * 60.0f), 880, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	//真ん中
	//斜めコイン
	for (int nCount = 0; nCount < 4; nCount++)
	{
		SetItem(D3DXVECTOR3(700 + (nCount * 20.0f), 1030 - (nCount * 80.0f), 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(880 + (nCount * 30.0f), 710 - (nCount * 50.0f), 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(1000 - (nCount * 30.0f), 510 - (nCount * 50.0f), 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(880 + (nCount * 30.0f), 310 - (nCount * 40.0f), 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	for (int nCount = 0; nCount < 8; nCount++)
	{
		SetItem(D3DXVECTOR3(1150 + (nCount * 80.0f), 150, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(1290 + (nCount * 75.0f), 390, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(1175 + (nCount * 80.0f), 650, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	//時間延長アイテム
	SetItem(D3DXVECTOR3(525, 1030, 0.0f), ITEM_TIME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetItem(D3DXVECTOR3(1050, 150, 0.0f), ITEM_TIME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//ゴールの位置
	SetGoal(D3DXVECTOR3(1200, 1030, 0.0f));
}

void Stage2(void)
{

	//サウンドスタート
	PlaySound(SOUND_LABEL_BGM002);

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	//ブロック配置
	
	//天井
	SetBlock(D3DXVECTOR3(0, -25, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1920, 50);

	//壁
	SetBlock(D3DXVECTOR3(1870, 0, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 1080);
	
	//壁
	SetBlock(D3DXVECTOR3(220, 780, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 80, 400);

	//壁
	SetBlock(D3DXVECTOR3(220, 490, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 80, 155);

	//壁
	SetBlock(D3DXVECTOR3(220, 150, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 80, 250);

	//壁
	SetBlock(D3DXVECTOR3(300, 150, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 20, 1000);

	//壁
	SetBlock(D3DXVECTOR3(960, 25, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 800);

	//床スタート
	SetBlock(D3DXVECTOR3(70, 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);

	//床
	SetBlock(D3DXVECTOR3(70, 780, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 60, 50);
	
	//床
	SetBlock(D3DXVECTOR3(70, 490, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	
	//床
	SetBlock(D3DXVECTOR3(70, 200, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);

	//床
	SetBlock(D3DXVECTOR3(70, 200, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);

	//床
	SetBlock(D3DXVECTOR3(320, 250, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 500, 50);

	//床
	SetBlock(D3DXVECTOR3(460, 600, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 500, 50);

	//床
	SetBlock(D3DXVECTOR3(320, 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 100, 50);

	for (int nCount = 0; nCount < 4; nCount++)
	{	
		SetBlock(D3DXVECTOR3(640 + (nCount * 320), 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	}

	//床
	SetBlock(D3DXVECTOR3(1800, 750, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//床
	SetBlock(D3DXVECTOR3(1800, 470, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//床
	SetBlock(D3DXVECTOR3(1010, 660, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//床
	SetBlock(D3DXVECTOR3(1010, 360, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//床
	SetBlock(D3DXVECTOR3(1700, 190, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//床
	SetBlock(D3DXVECTOR3(1500, 360, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);

	SetBlock(D3DXVECTOR3(1250, 190, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);


	//敵
	SetEnemy(D3DXVECTOR3(260, 690, 0.0f), D3DXVECTOR3(0, 0, 0.0f),2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LEFT);

	//敵
	SetEnemy(D3DXVECTOR3(260, 390, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LEFT);

	//敵
	SetEnemy(D3DXVECTOR3(365, 250, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), RIGHT);

	//敵
	SetEnemy(D3DXVECTOR3(920, 350, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LEFT);

	//敵
	SetEnemy(D3DXVECTOR3(1040, 590, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), RIGHT);

	//敵
	SetEnemy(D3DXVECTOR3(1040, 200, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), RIGHT);

	//ゴールの位置
	SetGoal(D3DXVECTOR3(1100, 100, 0.0f));
}


GAME *GetGame(void)
{
	return &g_Game;
}

void SetPause(bool bpause)
{
	g_bPause = bpause;
}