//-----------------------------------------------------------------------------
//
// 敵の処理
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MAX_ENEMY_TYPE (3)
#define ENEMY_SIZE_TYPE0 (D3DXVECTOR3(50 , 60 , 0.0f))
#define ENEMY_SIZE_TYPE1 (D3DXVECTOR3(40 , 60 , 0.0f))
#define ENEMY_SIZE_TYPE2 (D3DXVECTOR3(40 , 90 , 0.0f))
#define ENEMY_SPEED (3)
#define MAX_ENEMY (256)			//敵の上限
#define PLAYER_HITAREA (5)
#define ENEMY_COUNT (45)
#define RIGHT (0)				//向き
#define LEFT (1)				//向き
#define	UP (2)					//向き
#define UNBER (3)				//向き
#define BULLETFIRING (100)

//-----------------------------------------------------------------------------
// 状態
//-----------------------------------------------------------------------------
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
}ENEMYSTATE;

//-----------------------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld;	//前回の位置
	D3DXVECTOR3 move;	//動く速度
	float fWidth;		//幅
	float fHeight;		//高さ
	int nType;			//種類
	ENEMYSTATE State;	//状態
	int nCounterState;	//状態カウンター
	int nLife;			//体力
	int g_nPatternAnimEnemyV;	
	D3DXCOLOR col;		//色
	bool bUse;			//使用状態
}ENEMY;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, D3DXCOLOR col, int nPatternAnimEnemyV);
void SetVertexEnemy(int nIdx);
bool HitEnemy(int nIdx, int nDamage);
ENEMY*GetEnemy(void);

#endif _ENEMY_H_
