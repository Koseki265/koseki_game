//-----------------------------------------------------------------------------
//
// 背景の処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#include "bg.h"

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureBg[MAX_BG] = {};	//テクスチャ
BG g_Bg[MAX_BG];
float g_fmoveBg;
int g_MoveCounter;

//-----------------------------------------------------------------------------
// 背景の初期化処理
//-----------------------------------------------------------------------------
HRESULT InitBg(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/sky000.jpg", &g_pTextureBg[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/mountain000.png", &g_pTextureBg[1]);

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		g_Bg[nCntBg].nType = 0;
	}

	g_fmoveBg = 0;
	g_MoveCounter = 0;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BG, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBg, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
	
		SetVertexBg(nCntBg);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点のカラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();

	return S_OK;
}
//-----------------------------------------------------------------------------
// 背景の終了処理
//-----------------------------------------------------------------------------
void UninitBg(void)
{
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		if (g_pTextureBg[nCntBg] != NULL)
		{
			g_pTextureBg[nCntBg]->Release();
			g_pTextureBg[nCntBg] = NULL;
		}
	}
}
//-----------------------------------------------------------------------------
// 背景の更新処理
//-----------------------------------------------------------------------------
void UpdateBg(void)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);
	
	g_fmoveBg += 0.00005f;


	//頂点の座標

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		SetVertexBg(nCntBg);

		if (nCntBg == 0)
		{
			//頂点の情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + g_fmoveBg, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f + g_fmoveBg, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.5f + g_fmoveBg, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(0.5f + g_fmoveBg, 0.0f);
		}
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();
}

//-----------------------------------------------------------------------------
// 背景の描画処理
//-----------------------------------------------------------------------------
void DrawBg(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_pTextureBg[nCntBg]);

		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBg * 4, 2);
	}
}

//頂点座標
void SetVertexBg(int nIdx)
{

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点の座標
	if (nIdx == 0)
	{
		pVtx[0].pos = D3DXVECTOR3(0, SCREEN_HEIGHT, 0);
		pVtx[1].pos = D3DXVECTOR3(0, 0, 0);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 0, 0);

		//頂点の情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);

	}

	if (nIdx == 1)
	{
		pVtx[0].pos = D3DXVECTOR3(0, 1080, 0);
		pVtx[1].pos = D3DXVECTOR3(0, 800, 0);
		pVtx[2].pos = D3DXVECTOR3(SCREEN_WIDTH, 1080, 0);
		pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, 800, 0);

		//頂点の情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBg->Unlock();

}
