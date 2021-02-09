//-----------------------------------------------------------------------------
//
// アイテムの処理
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#include "item.h"
#include "Player.h"
#include "score.h"
#include "time.h"
#include "sound.h"

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureItem[MAX_ITEM_TYPE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;
ITEM g_aItem[MAX_ITEM];								//アイテムの情報
int g_nCounterAnimItem;
int g_nPattenAnimItem;

//-----------------------------------------------------------------------------
// アイテムの頂点座標の設定
//-----------------------------------------------------------------------------
void SetVertexItem(int nIdx)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	if (g_aItem[nIdx].nType == ITEM_SCORE)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y, 0);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y, 0);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0);

		//テクスチャ座標
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nPattenAnimItem * 0.25f), 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0f + (g_nPattenAnimItem * 0.25f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f + (g_nPattenAnimItem * 0.25f), 1.0);
		pVtx[3].tex = D3DXVECTOR2(0.25f + (g_nPattenAnimItem * 0.25f), 0.0f);

	}

	else if (g_aItem[nIdx].nType == ITEM_TIME)
	{
		//頂点座標
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_TIME_SIZEX, g_aItem[nIdx].pos.y, 0);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_TIME_SIZEX, g_aItem[nIdx].pos.y - ITEM_TIME_SIZEY, 0);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_TIME_SIZEX, g_aItem[nIdx].pos.y, 0);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_TIME_SIZEX, g_aItem[nIdx].pos.y - ITEM_TIME_SIZEY, 0);

		//頂点の情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();
}


//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitItem(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\coin000.png", &g_apTextureItem[ITEM_SCORE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item.001.png", &g_apTextureItem[ITEM_TIME]);

	//構造体初期化
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
		g_aItem[nCntItem].nType = 0;
		g_aItem[nCntItem].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aItem[nCntItem].bUse = false;
	}

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pVtx += 4)
	{
		//頂点座標
		SetVertexItem(nCntItem);

		//rhwの設定
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//頂点のカラー設定
		pVtx[0].col = g_aItem[nCntItem].col;
		pVtx[1].col = g_aItem[nCntItem].col;
		pVtx[2].col = g_aItem[nCntItem].col;		
		pVtx[3].col = g_aItem[nCntItem].col;

	}
	//頂点バッファをアンロックする
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//　終了処理
//-----------------------------------------------------------------------------
void UninitItem(void)
{
	//バッファの開放
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
	//テクスチャの開放
	for (int nCntItemType = 0; nCntItemType < MAX_ITEM_TYPE; nCntItemType++)
	{
		if (g_apTextureItem[nCntItemType] != NULL)
		{
			g_apTextureItem[nCntItemType]->Release();
			g_apTextureItem[nCntItemType] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateItem(void)
{
	ITEM *pItem;
	pItem = &g_aItem[0];

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	TIMER *pTime;
	pTime = GetTime();

	g_nCounterAnimItem++;

	if ((g_nCounterAnimItem % 15) == 0)
	{
		g_nPattenAnimItem++;
	}

	//アイテムの効果
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{//当たり判定
			if (pItem->pos.y - ITEM_SIZEY < pPlayer->pos.y && pItem->pos.y > pPlayer->pos.y - pPlayer->fHeight &&
				pItem->pos.x < pPlayer->pos.x + pPlayer->fWidth && pItem->pos.x > pPlayer->pos.x - pPlayer->fWidth)
			{
				//スコアアップアイテムだったら
				if (pItem->nType == ITEM_SCORE)
				{
					PlaySound(SOUND_LABEL_SE_COIN);
					AddScore(100);
				}
				//時間延長アイテムだったら
				if (pItem->nType == ITEM_TIME)
				{
					pTime->nTime += 10;

					PlaySound(SOUND_LABEL_SE_ITEM);

					if (pTime->nTime > 60)
					{
						pTime->nTime = 60;
					}
				}

				pItem->bUse = false;
			}

		}

		//頂点座標
		SetVertexItem(nCntItem);

	}

}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawItem(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	ITEM *pItem;
	pItem = &g_aItem[0];

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureItem[pItem->nType]);

		if (pItem->bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}
//-----------------------------------------------------------------------------
// アイテムの設定
//-----------------------------------------------------------------------------
void SetItem(D3DXVECTOR3 pos, int nType,D3DXCOLOR col)
{

	ITEM *pItem;
	pItem = &g_aItem[0];

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++ , pItem++)
	{
		if (pItem->bUse == false)
		{

			//位置
			pItem->pos = pos;

			//頂点座標
			SetVertexItem(nCntItem);

			//タイプ
			pItem->nType = nType;

			//色
			pItem->col = col;
			pVtx[0].col = pItem->col;
			pVtx[1].col = pItem->col;
			pVtx[2].col = pItem->col;
			pVtx[3].col = pItem->col;

			//使っている状態に
			pItem->bUse = true;

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffItem->Unlock(); //アンロック
}
