//-----------------------------------------------------------------------------
//
// ポーズ画面の処理
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#ifndef _PAUSE_H_
#define _PAUSE_H_

#include "main.h"

//ポーズメニュー
typedef enum
{
	PAUSE_MENU_CONTINUE = 0,	//コンティニュー
	PAUSE_MENU_RETRY,			//リトライ
	PAUSE_MENU_STAGESELECT,		//ステージ選択画面
	PAUSE_MENU_QUIT,			//終了
	PAUSE_MENU_MAX
}PAUSE_MENU;

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
}PAUSE;
//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

HRESULT InitPause(void);
void UninitPause(void);
void UpdatePause(void);
void DrawPause(void);
void SetVertexPause(int nIdx);

#endif _PAUSE_H_
