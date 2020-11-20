#ifndef _MACHINE_H_
#define _MACHINE_H_

#pragma once
#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MACHINE_SIZE (20)
#define MOVE_MACHINE (3)
#define MAX_MACHINE (50) //子機の上限

//-----------------------------------------------------------------------------
// 状態
//-----------------------------------------------------------------------------
typedef enum
{
	MACHINESTATE_APPEAR = 0,
	MACHINESTATE_NORMAL,
	MACHINESTATE_BREAK,
	MACHINESTATE_MAX
}MACHINESTATE;

//-----------------------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//現在の位置
	D3DXVECTOR3 posDest;	//目的の位置
	D3DXVECTOR3 move;		//移動速度
	bool bUse;
	MACHINESTATE State;
}MACHINE;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitMachine(void);
void UninitMachine(void);
void UpdateMachine(void);
void DrawMachine(void);
MACHINE *GetMachine(void);
void SetPosMachine(int nIdx, D3DXVECTOR3 pos);
void SetBulletMachine(int nIdx);
void SetMachine(D3DXVECTOR3 pos);
void SetVertexMachine(int nIdx);


#endif _MACHINE_H_

