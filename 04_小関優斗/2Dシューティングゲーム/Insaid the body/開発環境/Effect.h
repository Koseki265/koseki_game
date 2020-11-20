#pragma once
#pragma once
#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//---------------------------------------------------------------------------		
#define EFFECT_SIZE (17)			//爆発の大きさ
#define MAX_EFFECT (10000)		//爆発の上限

//-----------------------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;						//位置
	D3DXCOLOR col;
	bool bUse;								//爆発の使用状況
}EFFECT;


//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitEffect(void);
void UninitEffect(void);
void UpdateEffect(void);
void DrawEffect(void);
void SetEffect(D3DXVECTOR3 pos, D3DXCOLOR col);
void SetVertexEffect(int nIdx);
EFFECT *GetEffect(void);

#endif _EFFECT_H_
