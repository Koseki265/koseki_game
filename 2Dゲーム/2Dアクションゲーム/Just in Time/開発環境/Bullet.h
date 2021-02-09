
#ifndef _BULLET_H_
#define _BULLET_H_

#pragma once
#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//---------------------------------------------------------------------------
#define MOVE_BULLET (5)				//弾の速度
#define BULLET_SIZE (12)			//弾の大きさ
#define BULLET_SIZE_TYPE1 (30)		//弾の大きさ
#define MAX_BULLET (256)			//弾の上限
#define MAX_BULLET_TYPE (2)			//弾の種類
#define ENEMY_BULLET_1 (1)
#define ENEMY_BULLET_0 (0)

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType);
void SetVertexBullet(int nIdx);

#endif _BULLET_H_