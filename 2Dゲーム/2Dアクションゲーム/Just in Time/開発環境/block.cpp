//-----------------------------------------------------------------------------
//
// ブロックの処理
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#include "block.h"
#include "Player.h"

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;			//テクスチャ
BLOCK g_aBlock[MAX_BLOCK];

//-----------------------------------------------------------------------------
//初期化処理
//-----------------------------------------------------------------------------
HRESULT InitBlock(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Block000.jpg", &g_pTextureBlock);
	
	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBlock, NULL)))
	{
		return E_FAIL;
	}

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//位置
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量
		g_aBlock[nCntBlock].tex = D3DXVECTOR2(0.0f, 0.0f);			//テクスチャ
		g_aBlock[nCntBlock].fWidth = 0;								//幅
		g_aBlock[nCntBlock].fHeight = 0;							//高さ
		g_aBlock[nCntBlock].bUse = false;							//使用してるかどうか

	}

	VERTEX_2D *pVtx;

	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		SetVertexBlock(nCntBlock);

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

		//頂点の情報の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------------------
void UninitBlock(void)
{
	if (g_pVtxBuffBlock != NULL)
	{
		g_pVtxBuffBlock->Release();
		g_pVtxBuffBlock = NULL;
	}
	
	if (g_pTextureBlock != NULL)
	{
		g_pTextureBlock->Release();
		g_pTextureBlock = NULL;
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateBlock(void)
{

	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++,pBlock++)
	{
		if (pBlock->bUse == true)
		{

			pBlock->posOld = pBlock->pos;

			pBlock->pos += pBlock->move;

			if (pBlock->pos.x >= 1300 || pBlock->pos.x <= 1000)
			{
				pBlock->move.x *= -1;
			}
			
			if (pBlock->pos.y >= 800 || pBlock->pos.y <= 500)
			{
				pBlock->move.y *= -1;
			}

			
			SetVertexBlock(nCntBlock);
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawBlock(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureBlock);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{	
			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// ブロックの設定
//-----------------------------------------------------------------------------
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight)
{
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++,pBlock++)
	{
		if (pBlock->bUse == false)
		{
			//位置
			pBlock->pos = pos;

			//移動
			pBlock->move = move;

			//幅
			pBlock->fWidth = fWidth;

			//高さ
			pBlock->fHeight = fHeight;

			//頂点座標
			SetVertexBlock(nCntBlock);

			//テクスチャ横
			if (pBlock->fWidth >= 200 && pBlock->fWidth <= 500)
			{
				//頂点の情報の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(5.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(5.0f, 0.0f);
			}

			if (pBlock->fWidth >= 1650)
			{
				//頂点の情報の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(30.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(30.0f, 0.0f);
			}

			if (pBlock->fHeight >= 600 && pBlock->fHeight <= 900)
			{
				//頂点の情報の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 12.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 12.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			}
			if (pBlock->fHeight >= 1000)
			{
				//頂点の情報の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 20.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 20.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			}

			if (pBlock->fHeight >= 300 && pBlock->fHeight <= 600)
			{
				//頂点の情報の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 5.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 5.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			}
			if (pBlock->fHeight >= 100 && pBlock->fHeight <= 250)
			{
				//頂点の情報の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 3.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 3.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			}
			//使ってる状態に
			pBlock->bUse = true;

			break;
		}
		pVtx += 4;
	}
	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();

}

//頂点座標
void SetVertexBlock(int nIdx)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nIdx * 4);

	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y , 0);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffBlock->Unlock();
}

//-----------------------------------------------------------------------------
// ブロックの当たり判定
//-----------------------------------------------------------------------------
bool ColisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight,TOUCHING_BULOCK nType)
{
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	bool bLand = true;

	//当たり判定
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == true)
		{//プレイヤー敵の上下の当たり判定
			if (pBlock->pos.x <= pPos->x + (fWidth) && (pBlock->pos.x + pBlock->fWidth) >= pPos->x - (fWidth))
			{
				//ブロック上の当たり判定
				if (pBlock->pos.y >= pPosOld->y)
				{
					if (pBlock->pos.y <= pPos->y)
					{
						bLand = false;
						pPos->y = pBlock->pos.y;						
						pMove->y = 0;
						if (nType == TOUCHING_ENEMY)
						{				
							if (pBlock->pos.x >= pPos->x || pBlock->pos.x + pBlock->fWidth <= pPos->x)
							{
								pMove->x *= -1;
							}
						}
						if (pBlock->move.x != 0)
						{
							pPos->x += pBlock->move.x ;
						}

						if (pBlock->move.y != 0 && pBlock->move.y >= 0)
						{
							pPos->y += pBlock->move.y;	
						}			
					}
				}
				//移動床
				else if (pBlock->posOld.y >= pPos->y + pBlock->move.y)
				{
					if (pBlock->pos.y <= pPos->y)
					{
						bLand = false;
						pMove->y = 0;
						if (nType == TOUCHING_ENEMY)
						{
							if (pBlock->pos.x >= pPos->x || pBlock->pos.x + pBlock->fWidth <= pPos->x)
							{
								pMove->x *= -1;
							}
						}
						if (pBlock->move.y != 0)
						{
							pPos->y += pBlock->move.y;
							pPos->y = pBlock->pos.y;
						}
					}
				}
				//ブロック下の当たり判定
				else if (pBlock->pos.y + pBlock->fHeight <= pPosOld->y - fHeight)
				{
					if ((pBlock->pos.y + pBlock->fHeight) >= (pPos->y - fHeight))
					{
						pPos->y = (pBlock->pos.y + pBlock->fHeight +fHeight);
						pMove->y = GRAVITY;
						if (nType == TOUCHING_BULLET)
						{
							bLand = false;
						}
					}
				}
			}

			if (pPos->y != pBlock->pos.y && pPos->y - fHeight != (pBlock->pos.y + pBlock->fHeight) && (pBlock->pos.y + pBlock->fHeight) >= pPos->y - fHeight
				&& pBlock->pos.y <= pPos->y)
			{
				//ブロック左の当たり判定
				if (pBlock->pos.x >= pPosOld->x + fWidth)
				{
					if (pBlock->pos.x <= pPos->x + fWidth)
					{					
						pPos->x = pBlock->pos.x - fWidth; 

						if (nType == TOUCHING_ENEMY)
						{
							pMove->x *= -1;
						}

						if (nType == TOUCHING_BULLET)
						{
							bLand = false;
						}
					}
				}
				//移動床 (左)
				if (pBlock->posOld.x >= (pPosOld->x + fWidth))
				{
					if (pBlock->pos.x <= (pPos->x + fWidth))
					{
						if (pBlock->move.x != 0)
						{
							pPos->x = (pBlock->pos.x - fWidth);

							if (nType == TOUCHING_BULLET)
							{
								bLand = false;
							}
						}
					}
				}
				
				//ブロック右の当たり判定
				if (pBlock->pos.x + pBlock->fWidth <= (pPosOld->x - fWidth))
				{
					if ((pBlock->pos.x + pBlock->fWidth) >= (pPos->x - fWidth))
					{
						pPos->x = (pBlock->pos.x + pBlock->fWidth + fWidth);

						pMove->x *= -1;

						if (nType == TOUCHING_BULLET)
						{
							bLand = false;
						}

					}
				}
				//移動床(右)
				if (pBlock->posOld.x + pBlock->fWidth <= (pPosOld->x - fWidth))
				{
					if (pBlock->pos.x + pBlock->fWidth >= pPos->x - fWidth)
					{
						if (pBlock->move.x != 0)
						{
							pPos->x = (pBlock->pos.x + pBlock->fWidth + fWidth);

							if (nType == TOUCHING_BULLET)
							{
								bLand = false;
							}
						}

					}
				}
			}		
		}
	}
	return bLand;
}

//ブロックの情報
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}