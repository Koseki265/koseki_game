//-----------------------------------------------------------------------------
//
// リザルト画面の処理
// Author:KosekiYuto
//
//-----------------------------------------------------------------------------

#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//
typedef enum
{
	RESULT_CLEAR = 0,
	RESULT_GAMEOVER,
	RESULT_MAX
}RESULT_STATE;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetVertexResult(int nIdx);

#endif _RESULT_H_
