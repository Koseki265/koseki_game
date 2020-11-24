

#pragma once

#ifndef _TIME_H_
#define _TIME_H_

#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define TIME_SIZEX (30)	//横幅
#define TIME_SIZEY (50)	//縦幅
#define MAX_TIME (2)	//スコアの桁
#define TIMER (40)

//-----------------------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;
}TIME;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitTime(void);
void UninitTime(void);
void UpdateTime(void);
void DrawTime(void);
int GetTime(void);
void SetTextureTime(int nIdx);

#endif _TIME_H_

