//-----------------------------------------------------------------------------
//
// ブロックの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MAX_BLOCK (128)
#define MOVE_BLOCK (2)

//----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
typedef enum
{
	TOUCHING_PLAYER = 0,
	TOUCHING_ENEMY,
	TOUCHING_BULLET,
	TOUCHING_BOLOCK_MAX,
}TOUCHING_BULOCK;
//-----------------------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	D3DXVECTOR3 posOld; //前の位置
	D3DXVECTOR3 move;	//移動量
	D3DXVECTOR2 tex;	//テクスチャ
	float fWidth;		//幅
	float fHeight;		//高さ
	bool bUse;			//使用してるかどうか
}BLOCK;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float Width, float fHeight);
void SetVertexBlock(int nIdx);
bool ColisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, TOUCHING_BULOCK nType);
BLOCK *GetBlock(void);


#endif _BLOCK_H_