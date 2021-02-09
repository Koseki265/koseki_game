//-----------------------------------------------------------------------------
//
// チュートリアルの処理
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
//
//
//
typedef enum
{
	SELECT_RETRY = 0,		//リトライ
	SELECT_STAGESELECT,		//ステージ選択画面
	SELECT_QUIT,			//終了
	SELECT_MAX
}SELECT;

//-----------------------------------------------------------------------------
// プロトタイプ宣言
//-----------------------------------------------------------------------------

HRESULT InitHighScore(void);
void UninitHighScore(void);
void UpdateHighScore(void);
void DrawHighScore(void);
void SetVertexHighScore(int nIdx,int nNumber);

#endif _RANKING_H_
