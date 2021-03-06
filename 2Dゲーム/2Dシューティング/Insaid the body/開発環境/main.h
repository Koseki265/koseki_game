//-----------------------------------------------------------------------------
//
// ダイレクトｘの処理
// Author:KosekiYuto
//
//-----------------------------------------------------------------------------

#ifndef _MAIN_H_
#define _MAIN_H_

#pragma once
#define DIRECTINPUT_VERSION (0x800)
#include "dinput.h"										//入力処理に必要
#include <windows.h>
#include "d3dx9.h"
#include "xaudio2.h"									//サウンド再生に必要			

#pragma comment(lib,"dinput8.lib")						//入力処理に必要
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")

//マクロ定義
#define CLASS_NAME "WindowClass"						//ウインドウクラスの名前
#define WINDOW_NAME "INSAID THE BODY"					//ウインドウの名前
#define SCREEN_WIDTH (1920)								//スクリーンの幅
#define SCREEN_HEIGHT (1080)							//スクリーンの高さ
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//構造体
typedef struct
{
	D3DXVECTOR3 pos;	//位置
	float rhw;
	D3DCOLOR col;		//色
	D3DXVECTOR2 tex;	//テクスチャ
}VERTEX_2D;

//モードの種類
typedef enum
{
	MODE_TITLE = 0,	//タイトル画面
	MODE_TUTORIAL,	//チュートリアル画面
	MODE_GAME,		//ゲーム画面
	MODE_RESULT,	//リザルト画面
	MODE_MAX
}MODE;

//グローバル変数

//プロトタイプ宣言
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif