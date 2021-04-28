//-----------------------------------------------------------------------------
//
// チュートリアルの処理
// Author:KosekiYuto
//
//-----------------------------------------------------------------------------

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	bool bDisp;			//表示ON/OFF

}TUTORIAL;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetVertexTutorial(int nIdx);

#endif _TUTORIAL_H_

