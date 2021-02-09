//-----------------------------------------------------------------------------
//
// ダイレクトｘの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//-----------------------------------------------------------------------------
// 選択
//-----------------------------------------------------------------------------
typedef enum
{
	STAGE_1 = 0,
	STAGE_2,
	STAGE_MAX,
}STAGE;

//構造体
typedef struct
{
	STAGE stage;
}GAME;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void Stage1(void);
void Stage2(void);
GAME *GetGame(void);
void SetPause(bool bPause);

#endif
