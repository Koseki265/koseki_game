//-----------------------------------------------------------------------------
//
// タイトルの処理
// Author:KosekiYuto
//
//-----------------------------------------------------------------------------

#ifndef _TITLE_H_
#define _TITLE_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;	//位置
	bool bDisp;			//表示ON/OFF

}TITLE;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

HRESULT InitTitle(void);
void UninitTitle(void);
void UpdateTitle(void);
void DrawTitle(void);
void SetVertexTitle(int nIdx);

#endif _TITLE_H_
