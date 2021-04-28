//-----------------------------------------------------------------------------
//
// タイトル画面の処理
// Author:KosekiYuto
//
//-----------------------------------------------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//マクロ定義
#define MAX_TITLE (3)				//タイトルの画像の数
#define TITLE_BG_SIZE_X (960)		//タイトル画面の横幅
#define TITLE_BG_SIZE_Y (540)		//タイトル画面の立幅
#define GAME_TITLE_SIZE_X (700)		//タイトルの横幅
#define GAME_TITLE_SIZE_Y (100)		//タイトルの立幅
#define ENTER_SIZE_X (400)			//プレスエンターの横幅
#define ENTER_SIZE_Y (75)			//プレスエンターの立幅
#define MOVE_TITLE (5)				//タイトルの移動速度

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE] = {};	//テクスチャ
TITLE g_aTitle[MAX_TITLE];
int g_nCounterTitle;
int g_FadeCounter;
int g_nCounter;
bool g_bEnter;

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	//サウンドスタート
	PlaySound(SOUND_LABEL_BGM003);

	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, NULL, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/game_title000.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &g_pTextureTitle[2]);

	g_bEnter = false;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].bDisp = true;
	}

	g_FadeCounter = 0;
	g_nCounterTitle = 30;

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{

		SetVertexTitle(nCntTitle);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点の情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		//頂点バッファをアンロックする
		g_pVtxBuffTitle->Unlock();

	}
	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitTitle(void)
{
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	FADE *pFade;
	pFade = GetFade();

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	g_nCounter++;		//表示カウンター

	if (g_aTitle[1].pos.y <= 300)
	{
		g_aTitle[1].pos.y += MOVE_TITLE;	//タイトル移動
	}
	
	if ((g_nCounter % g_nCounterTitle) == 0)
	{
		g_aTitle[2].bDisp = g_aTitle[2].bDisp ? false : true;	//プレスエンターの点滅
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{

		if (g_aTitle[1].pos.y < 300)
		{
			g_aTitle[1].pos.y = 300;
		}

		else if (g_aTitle[1].pos.y >= 300 && g_bEnter == false)
		{
			g_nCounterTitle -= 25;
			PlaySound(SOUND_LABEL_SE_DESICION);

			g_bEnter = true;
		}
	}

	if (g_bEnter == true)
	{
		if ((g_nCounter % 2) == 0)
		{
			
			g_FadeCounter++;

		}
	}
	if (g_FadeCounter == 30)
	{
		//サウンドストップ
		//StopSound();

		SetFade(FADE_OUT, MODE_TUTORIAL);
	}

	//頂点の座標
	pVtx[0].pos = D3DXVECTOR3(g_aTitle[1].pos.x - GAME_TITLE_SIZE_X, g_aTitle[1].pos.y + GAME_TITLE_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitle[1].pos.x - GAME_TITLE_SIZE_X, g_aTitle[1].pos.y - GAME_TITLE_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitle[1].pos.x + GAME_TITLE_SIZE_X, g_aTitle[1].pos.y + GAME_TITLE_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitle[1].pos.x + GAME_TITLE_SIZE_X, g_aTitle[1].pos.y - GAME_TITLE_SIZE_Y, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawTitle(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

		if (g_aTitle[nCntTitle].bDisp == true)
		{
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}

}

//-----------------------------------------------------------------------------
// タイトルの頂点座標の設定
//-----------------------------------------------------------------------------

void SetVertexTitle(int nIdx)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);


	pVtx += nIdx * 4;

	
	if (nIdx == 0)
	{
		g_aTitle[nIdx].pos = D3DXVECTOR3(960.0f, 540.0f, 0.0f);

		g_aTitle[nIdx].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);

		//頂点のカラー設定
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

	}
	else if (nIdx == 1)
	{
		g_aTitle[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, -300, 0);

		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - GAME_TITLE_SIZE_X, g_aTitle[nIdx].pos.y + GAME_TITLE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - GAME_TITLE_SIZE_X, g_aTitle[nIdx].pos.y - GAME_TITLE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + GAME_TITLE_SIZE_X, g_aTitle[nIdx].pos.y + GAME_TITLE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + GAME_TITLE_SIZE_X, g_aTitle[nIdx].pos.y - GAME_TITLE_SIZE_Y, 0.0f);

		//頂点のカラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else if (nIdx == 2)
	{
		g_aTitle[nIdx].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f);
		//頂点の座標
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - ENTER_SIZE_X, g_aTitle[nIdx].pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - ENTER_SIZE_X, g_aTitle[nIdx].pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + ENTER_SIZE_X, g_aTitle[nIdx].pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + ENTER_SIZE_X, g_aTitle[nIdx].pos.y - ENTER_SIZE_Y, 0.0f);

		//頂点のカラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffTitle->Unlock();

}
