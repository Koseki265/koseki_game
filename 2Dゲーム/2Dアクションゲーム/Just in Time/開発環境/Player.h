//-----------------------------------------------------------------------------
//
//プレイヤーの処理
//Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"


//-----------------------------------------------------------------------------
// マクロ定義
//-----------------------------------------------------------------------------
#define MOVE_SPEED (4)			//移動速度
#define GRAVITY		(2.6f)		//重力
#define PLAYER_SIZEX (35)		//プレイヤーの幅
#define PLAYER_SIZEY (75)		//プレイヤーの高さ
#define JAMP (42)				//ジャンプ力
#define ANIM_SPEED (5)			//アニメーションスピード
#define ANIM_SLOW_SPEED (20)	//遅いアニメーションスピード
#define LOW_JUMP (30)			//低いジャンプ
#define MOVE_SLOW_SPEED (1)		//遅い移動速度


//-----------------------------------------------------------------------------
//プレイヤーの状態
//-----------------------------------------------------------------------------
typedef enum
{
	PLAYERSTATE_NORMAL = 0,		//通常
	PLAYERSTATE_DAMAGE,			//ダメージ
	PLAYERSTATE_INVINCIBLE,		//無敵
	PLAYERSTATE_FREEZE,			//凍結
	PLAYERSTATE_SLOW,			//スロウ
	PLAYERSTATE_MAX,			
}PLAYERSTATE;

//-----------------------------------------------------------------------------
// 構造体
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//現在の位置
	D3DXVECTOR3 posOld;	//前回の位置
	D3DXVECTOR3 move;	//移動量
	PLAYERSTATE State;	//プレイヤーの状態
	float fWidth;		//幅
	float fHeight;		//高さ
	int Touchi;			//地面についたかどうか
	bool bDisp;			//表示してるかどうか
	bool bJump;			//ジャンプしてるかどうか
}PLAYER;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
bool HitPlayer(int nDamage);
void SetVertexPlayer(void);


#endif
