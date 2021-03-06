//-----------------------------------------------------------------------------
//
// スコアの処理
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#include "score.h"
#include "game.h"
#include "Time.h"

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;
SCORE g_aScore[STAGE_SCORE];							//スコアの位置
D3DXVECTOR3 Scorepos[MAX_SCORE];										//スコア

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitScore(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//構造体初期化
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		Scorepos[MAX_SCORE] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//スコアの位置						
	}
	for (int nCntScore = 0; nCntScore < STAGE_SCORE; nCntScore++)
	{
		g_aScore[nCntScore].nScore = 0;
	}

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureScore);

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++, pVtx += 4)
	{
		//ポリゴンの位置
		Scorepos[nCntScore] = D3DXVECTOR3(1500.0f + nCntScore * 50, 50.0f, 0.0f);

		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(Scorepos[nCntScore].x - SCORE_SIZEX, Scorepos[nCntScore].y + SCORE_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Scorepos[nCntScore].x - SCORE_SIZEX, Scorepos[nCntScore].y - SCORE_SIZEY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Scorepos[nCntScore].x + SCORE_SIZEX, Scorepos[nCntScore].y + SCORE_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Scorepos[nCntScore].x + SCORE_SIZEX, Scorepos[nCntScore].y - SCORE_SIZEY, 0.0f);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点のカラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

		//頂点の情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

	}

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//　終了処理
//-----------------------------------------------------------------------------
void UninitScore(void)
{
	//バッファの開放
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
	//テクスチャの開放
	if (g_apTextureScore != NULL)
	{
		g_apTextureScore->Release();
		g_apTextureScore = NULL;
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateScore(void)
{
	
}
//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawScore(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_apTextureScore);

	//ポリゴンの描画
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//-----------------------------------------------------------------------------
// スコア換算
//-----------------------------------------------------------------------------
void AddScore(int nValue)
{
	GAME *pGame;
	pGame = GetGame();

	int aNumber[MAX_SCORE];
	if (pGame->stage == STAGE_1)
	{
		g_aScore[STAGE_1].nScore += nValue;

		if (g_aScore[STAGE_1].nScore >= 0)
		{
			for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
			{
				aNumber[nCntScore] = g_aScore[STAGE_1].nScore / powf(10.0f, 8.0f - (nCntScore + 1.0f));
				//テクスチャ座標の設定
				SetTextureScore(nCntScore, aNumber[nCntScore]);
			}
		}
		else
		{
			g_aScore[STAGE_1].nScore = 0;
		}
	}

	if (pGame->stage == STAGE_2)
	{
		g_aScore[STAGE_2].nScore += nValue;

		if (g_aScore[STAGE_2].nScore >= 0)
		{
			for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
			{
				aNumber[nCntScore] = g_aScore[STAGE_2].nScore / powf(10.0f, 8.0f - (nCntScore + 1.0f));
				//テクスチャ座標の設定
				SetTextureScore(nCntScore, aNumber[nCntScore]);
			}
		}
		else
		{
			g_aScore[STAGE_2].nScore = 0;
		}
	}

}

//-----------------------------------------------------------------------------
// テクスチャ頂点座標の更新
//-----------------------------------------------------------------------------
void SetTextureScore(int nIdx, int nNumber)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx += (nIdx * 4);

	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffScore->Unlock();
}

SCORE *GetScore(void)
{
	return &g_aScore[0];
}