//-----------------------------------------------------------------------------
//
// 敵の処理
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------
#include "enemy.h"
#include "Player.h"
#include "input.h"
#include "block.h"
//#include "Explosion.h"
#include "score.h"
#include "sound.h"
#include "Bullet.h"
#include "fade.h"
#include <time.h>
#include <stdlib.h>

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureEnemy[MAX_ENEMY_TYPE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffEnemy = NULL;
ENEMY g_aEnemy[MAX_ENEMY];								//敵の情報
int g_nCounterAnimEnemy;								//アニメーションカウンター
int g_nPatternAnimEnemyU;								//アニメーションパターンNo.
int g_nPatternAnimEnemyV;
int g_Bulletfiring;
bool g_bFiring;
float g_fLength;
float g_fAngle;
int g_moveEnemy;
int g_nEnemyCount;
int g_FadeCount;
int g_EnemyCounter;


//-----------------------------------------------------------------------------
// 敵の頂点座標の設定
//-----------------------------------------------------------------------------
void SetVertexEnemy(int nIdx)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - g_aEnemy[nIdx].fWidth, g_aEnemy[nIdx].pos.y, 0);
	pVtx[1].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x - g_aEnemy[nIdx].fWidth, g_aEnemy[nIdx].pos.y - g_aEnemy[nIdx].fHeight, 0);
	pVtx[2].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + g_aEnemy[nIdx].fWidth, g_aEnemy[nIdx].pos.y, 0);
	pVtx[3].pos = D3DXVECTOR3(g_aEnemy[nIdx].pos.x + g_aEnemy[nIdx].fWidth, g_aEnemy[nIdx].pos.y - g_aEnemy[nIdx].fHeight, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();
}


//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitEnemy(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy000.png", &g_apTextureEnemy[0]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy001.png", &g_apTextureEnemy[1]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\enemy002.png", &g_apTextureEnemy[2]);

	//構造体初期化
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++)
	{
		g_aEnemy[nCntEnemy].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aEnemy[nCntEnemy].nType = 0;
		g_aEnemy[nCntEnemy].State = ENEMYSTATE_NORMAL;					//状態
		g_aEnemy[nCntEnemy].nCounterState = 0;							//状態カウンター
		g_aEnemy[nCntEnemy].nLife = 0;	
		g_aEnemy[nCntEnemy].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//体力
		g_aEnemy[nCntEnemy].bUse = false;
	}

	int g_nCounterAnimEnemy = 0;
	int g_nPatternAnimEnemyU = 0;
	int g_Bulletfiring = 0;
	bool g_bFiring = 0;
	float g_fLength = 0;
	float g_fAngle = 0;
	int g_moveEnemy = 0;
	int g_nEnemyCount = 0;
	int g_FadeCount = 0;
	int g_EnemyCounter = 0;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ENEMY, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffEnemy, NULL)))
	{
		return E_FAIL;
	}

	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pVtx += 4)
	{
		//頂点座標
		SetVertexEnemy(nCntEnemy);

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

	}
	//頂点バッファをアンロックする
	g_pVtxBuffEnemy->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//　終了処理
//-----------------------------------------------------------------------------
void UninitEnemy(void)
{
	//バッファの開放
	if (g_pVtxBuffEnemy != NULL)
	{
		g_pVtxBuffEnemy->Release();
		g_pVtxBuffEnemy = NULL;
	}
	//テクスチャの開放
	for (int nCntEnemyType = 0; nCntEnemyType < MAX_ENEMY_TYPE ; nCntEnemyType++)
	{
		if (g_apTextureEnemy[nCntEnemyType] != NULL)
		{
			g_apTextureEnemy[nCntEnemyType]->Release();
			g_apTextureEnemy[nCntEnemyType] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateEnemy(void)
{

	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	int nCounter = BULLETFIRING;

	g_nCounterAnimEnemy++;

	g_Bulletfiring++;

	g_EnemyCounter++;

	//アニメーション
	if ((g_nCounterAnimEnemy % (nCounter / 2)) == 0)
	{
		g_nPatternAnimEnemyU = (g_nPatternAnimEnemyU + 1) % 2;		//アニメーションパターンNo.更新
	}

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == true)
		{
			pEnemy->posOld = pEnemy->pos;

			//弾の発射
			if (pEnemy->nType == 1)
			{
				if ((g_Bulletfiring % nCounter) == 0)
				{
					if (pEnemy->g_nPatternAnimEnemyV == RIGHT)
					{
						SetBullet(D3DXVECTOR3(pEnemy->pos.x + pEnemy->fWidth, pEnemy->pos.y - pEnemy->fHeight + 35, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 10, 0);
					}
					else if (pEnemy->g_nPatternAnimEnemyV == LEFT)
					{
						SetBullet(D3DXVECTOR3(pEnemy->pos.x - pEnemy->fWidth, pEnemy->pos.y - pEnemy->fHeight + 35, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 10, 0);
					}
					else if (pEnemy->g_nPatternAnimEnemyV == UP)
					{
						SetBullet(D3DXVECTOR3(pEnemy->pos.x, pEnemy->pos.y - pEnemy->fHeight - 35, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), 10, 0);

					}
					else if (pEnemy->g_nPatternAnimEnemyV == UNBER)
					{
						SetBullet(D3DXVECTOR3(pEnemy->pos.x, pEnemy->pos.y - pEnemy->fHeight + 35, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 10, 0);
					}
				}
			}
			if (pEnemy->nType == 2)
			{
				if ((g_Bulletfiring % nCounter) == 0)
				{
					if (pEnemy->g_nPatternAnimEnemyV == RIGHT)
					{
						SetBullet(D3DXVECTOR3(pEnemy->pos.x + pEnemy->fWidth, pEnemy->pos.y - pEnemy->fHeight + 35, 0.0f), D3DXVECTOR3(10.0f, 0.0f, 0.0f), 10, 1);
					}
					else if (pEnemy->g_nPatternAnimEnemyV == LEFT)
					{
						SetBullet(D3DXVECTOR3(pEnemy->pos.x - pEnemy->fWidth, pEnemy->pos.y - pEnemy->fHeight + 35, 0.0f), D3DXVECTOR3(-10.0f, 0.0f, 0.0f), 10, 1);
					}
					else if (pEnemy->g_nPatternAnimEnemyV == UP)
					{
						SetBullet(D3DXVECTOR3(pEnemy->pos.x, pEnemy->pos.y - pEnemy->fHeight - 35, 0.0f), D3DXVECTOR3(0.0f, -10.0f, 0.0f), 10, 0);

					}
					else if (pEnemy->g_nPatternAnimEnemyV == UNBER)
					{
						SetBullet(D3DXVECTOR3(pEnemy->pos.x, pEnemy->pos.y - pEnemy->fHeight + 35, 0.0f), D3DXVECTOR3(0.0f, 10.0f, 0.0f), 10, 0);
					}

				}
			}

			//位置の更新
			pEnemy->pos.x += pEnemy->move.x;
			pEnemy->pos.y += pEnemy->move.y;

			pEnemy->move.y += GRAVITY;
			

			if (pEnemy->pos.x < 0 - pEnemy->fWidth)
			{
				pEnemy->bUse = false;
			}

			//敵の当たり判定
			if (pEnemy->pos.x - pEnemy->fWidth <= (pPlayer->pos.x + pPlayer->fWidth) && (pEnemy->pos.x + pEnemy->fWidth) >= (pPlayer->pos.x - pPlayer->fWidth))
			{
				//敵上の当たり判定
				if (pEnemy->pos.y - pEnemy->fHeight >= pPlayer->posOld.y)
				{
					if (pEnemy->pos.y - pEnemy->fHeight <= pPlayer->pos.y)
					{
						if (pEnemy->nType == 0)
						{
							pEnemy->bUse = false;

							pPlayer->Touchi += 1;

							if (GetKeyboardPress(DIK_SPACE) == true)
							{
								pPlayer->move.y = -40;
							}
							else
							{
								pPlayer->move.y = -30;
							}
							if (pPlayer->Touchi >= 1)
							{
								AddScore(300 * pPlayer->Touchi);
							}
							else
							{
								AddScore(300);
							}
							pPlayer->pos.y = pEnemy->pos.y - pEnemy->fHeight;
							
						}
						else
						{
							pPlayer->move.y = 0.0f;
							pPlayer->bJump = false;
							pPlayer->pos.y = pEnemy->pos.y - pEnemy->fHeight;
						}
					}
				}
				//敵下の当たり判定
				else if (pEnemy->pos.y <= pPlayer->posOld.y - pPlayer->fHeight)
				{
					if (pEnemy->pos.y >= (pPlayer->pos.y - pPlayer->fHeight))
					{
						pPlayer->move.y = GRAVITY;
						pPlayer->pos.y = pEnemy->pos.y + pPlayer->fHeight;
						AddScore(-100);
					}
				}
			}
			if (pEnemy->pos.y - pEnemy->fHeight != pPlayer->pos.y && pEnemy->pos.y >= pPlayer->pos.y - pPlayer->fHeight
				&& pEnemy->pos.y - pEnemy->fHeight <= pPlayer->pos.y)
			{
				//敵左の当たり判定
				if (pEnemy->pos.x - pEnemy->fWidth >= pPlayer->posOld.x + pPlayer->fWidth)
				{
					if (pEnemy->pos.x - pEnemy->fWidth <= pPlayer->pos.x + pPlayer->fWidth)
					{
						if (pPlayer->State == PLAYERSTATE_NORMAL)
						{
							if (pEnemy->nType == 0)
							{
								pPlayer->State = PLAYERSTATE_DAMAGE;
								pPlayer->move.x = -10;
								pPlayer->move.y = -10;
								AddScore(-100);
							}
						}
						if (pEnemy->nType != 0)
						{
							pPlayer->pos.x = pEnemy->pos.x - pEnemy->fWidth - pPlayer->fWidth;
						}
					}
				}
				//移動敵 (左)
				if (pEnemy->posOld.x >= pPlayer->posOld.x + pPlayer->fWidth)
				{
					if (pEnemy->pos.x - pEnemy->fWidth <= pPlayer->pos.x + pPlayer->fWidth)
					{
						if (pPlayer->State == PLAYERSTATE_NORMAL)
						{
							if (pEnemy->move != 0)
							{
							if (pEnemy->nType == 0)
							{
								pPlayer->State = PLAYERSTATE_DAMAGE;
								pPlayer->move.x = -10;
								pPlayer->move.y = -10;
								AddScore(-100);
							}
						}
						if (pEnemy->nType != 0)
						{
							pPlayer->pos.x = pEnemy->pos.x - pEnemy->fWidth - pPlayer->fWidth;
						}
						}
					}
				}

				//敵右の当たり判定
				if (pEnemy->pos.x + pEnemy->fWidth <= (pPlayer->posOld.x - pPlayer->fWidth))
				{
					if (pEnemy->pos.x + pEnemy->fWidth >= pPlayer->pos.x - pPlayer->fWidth)
					{
						if (pPlayer->State == PLAYERSTATE_NORMAL)
						{
							if (pEnemy->nType == 0)
							{
								pPlayer->State = PLAYERSTATE_DAMAGE;
								pPlayer->move.x = 10;
								pPlayer->move.y = -10;
								AddScore(-100);
							}
						}
						if (pEnemy->nType != 0)
						{
							pPlayer->pos.x = pEnemy->pos.x + pEnemy->fWidth + pPlayer->fWidth;
						}
					}

				}
				//移動敵
				if (pEnemy->posOld.x + pEnemy->fWidth <= pPlayer->posOld.x - pPlayer->fWidth)
				{
					if (pEnemy->pos.x + pEnemy->fWidth >= pPlayer->pos.x - pPlayer->fWidth)
					{
						if (pPlayer->State == PLAYERSTATE_NORMAL)
						{
							if (pEnemy->nType == 0)
							{
								pPlayer->State = PLAYERSTATE_DAMAGE;
								pPlayer->move.x = 10;
								pPlayer->move.y = -10;
								AddScore(-100);
							}
						}
						if (pEnemy->nType != 0)
						{
							pPlayer->pos.x = pEnemy->pos.x + pEnemy->fWidth + pPlayer->fWidth;
						}

					}
				}
				
			}

			if (pEnemy->move.x <= -1)
			{
				g_nPatternAnimEnemyV = 0;
			}
			else
			{
				g_nPatternAnimEnemyV = 1;
			}


			ColisionBlock(&pEnemy->pos, &pEnemy->posOld, &pEnemy->move, pEnemy->fWidth, pEnemy->fHeight, TOUCHING_ENEMY);
		}


		//頂点座標
		SetVertexEnemy(nCntEnemy);

		if (pEnemy->nType == 0)
		{
			//頂点の情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f + (0.5f * g_nPatternAnimEnemyV));
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f + (0.5f * g_nPatternAnimEnemyV));
			pVtx[2].tex = D3DXVECTOR2(1.0f, 0.5f + (0.5f * g_nPatternAnimEnemyV));
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f + (0.5f * g_nPatternAnimEnemyV));

		}

		if (pEnemy->nType == 2)
		{
			//頂点の情報の設定
			pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f * g_nPatternAnimEnemyU), 0.25f + (0.25f * pEnemy->g_nPatternAnimEnemyV));
			pVtx[1].tex = D3DXVECTOR2(0.0f + (0.5f * g_nPatternAnimEnemyU), 0.0f + (0.25f * pEnemy->g_nPatternAnimEnemyV));
			pVtx[2].tex = D3DXVECTOR2(0.5f + (0.5f * g_nPatternAnimEnemyU), 0.25f + (0.25f *pEnemy->g_nPatternAnimEnemyV));
			pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f * g_nPatternAnimEnemyU), 0.0f + (0.25f * pEnemy->g_nPatternAnimEnemyV));
		}
		pVtx += 4;
	}

	g_pVtxBuffEnemy->Unlock(); //アンロック

}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawEnemy(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffEnemy, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画
	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		//テクスチャの設定
		pDevice->SetTexture(0, g_apTextureEnemy[pEnemy->nType]);

		if (g_aEnemy[nCntEnemy].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntEnemy * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// 敵の設定
//-----------------------------------------------------------------------------
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, D3DXCOLOR col,int nPatternAnimEnemyV)
{
	ENEMY *pEnemy;
	pEnemy = &g_aEnemy[0];

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntEnemy = 0; nCntEnemy < MAX_ENEMY; nCntEnemy++, pEnemy++)
	{
		if (pEnemy->bUse == false)
		{
			//敵の数カウント
			//nCount++;

			//位置
			pEnemy->pos = pos;

			//移動
			pEnemy->move = move;

			//タイプ
			pEnemy->nType = nType;

			//敵の体力
			pEnemy->nLife = pEnemy->nType + 3;		

			//色
			pEnemy->col = col;
			pVtx[0].col = pEnemy->col;
			pVtx[1].col = pEnemy->col;
			pVtx[2].col = pEnemy->col;
			pVtx[3].col = pEnemy->col;
			
			if (nType == 0)
			{
				//幅
				pEnemy->fWidth = ENEMY_SIZE_TYPE0.x;

				//高さ
				pEnemy->fHeight = ENEMY_SIZE_TYPE0.y;

				//頂点の情報の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 0.5f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			}
			else if (nType == 1)
			{
				//幅
				pEnemy->fWidth = ENEMY_SIZE_TYPE1.x;

				//高さ
				pEnemy->fHeight = ENEMY_SIZE_TYPE1.y;

				//大砲の向き
				pEnemy->g_nPatternAnimEnemyV = nPatternAnimEnemyV;

			}
			else if (nType == 2)
			{
				//幅
				pEnemy->fWidth = ENEMY_SIZE_TYPE2.x;

				//高さ
				pEnemy->fHeight = ENEMY_SIZE_TYPE2.y;

				//大砲の向き
				pEnemy->g_nPatternAnimEnemyV = nPatternAnimEnemyV;

				//頂点の情報の設定
				pVtx[0].tex = D3DXVECTOR2(0.0f, 0.25f + (0.25f));
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f + (0.25f));
				pVtx[2].tex = D3DXVECTOR2(0.5f, 0.25f + (0.25f));
				pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f + (0.25f));

			}

			//頂点座標
			SetVertexEnemy(nCntEnemy);

			//使っている状態に
			pEnemy->bUse = true;

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffEnemy->Unlock(); //アンロック
}

//-----------------------------------------------------------------------------
// 弾が当たった時
//-----------------------------------------------------------------------------
bool HitEnemy(int nIdx, int nDamage)
{
	VERTEX_2D *pVtx;
	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffEnemy->Lock(0, 0, (void**)&pVtx, 0);

	//ダメージ計算
	g_aEnemy[nIdx].nLife -= nDamage;

	//体力が0の時
	if (g_aEnemy[nIdx].nLife <= 0)
	{		
		
		if (g_aEnemy[nIdx].nType == 2)
		{
			g_nEnemyCount += 2;
		}
		else
		{
			g_nEnemyCount++;
		}
		

		//SetExplosion(g_aEnemy[nIdx].pos, D3DXCOLOR(0.0f, 0.25f, 0.25f, 1.0f));

		g_aEnemy[nIdx].bUse = false;
		AddScore(100);

		return true;	
	}

	else
	{	
		PlaySound(SOUND_LABEL_SE_HIT);
		g_aEnemy[nIdx].State = ENEMYSTATE_DAMAGE;
		g_aEnemy[nIdx].nCounterState = 10;
		
		pVtx += nIdx * 4;
		
		pVtx[0].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 0, 0, 255);

		return false;
	}
	g_pVtxBuffEnemy->Unlock(); //アンロック
}

//-----------------------------------------------------------------------------
// 敵の情報の習得
//-----------------------------------------------------------------------------
ENEMY*GetEnemy(void)
{
	return &g_aEnemy[0];
}

//-----------------------------------------------------------------------------
// 敵の情報の習得
//-----------------------------------------------------------------------------
