#include "machine.h"
#include "Player.h"
#include "sound.h"
#include "Bullet.h"
#include "input.h"

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureMachine = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMachine = NULL;
MACHINE g_aMachine[MAX_MACHINE];						//子機の情報
int nMachineCounter;

//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitMachine(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player000.png", &g_apTextureMachine);
	
	//構造体初期化
	for (int nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++)
	{
		g_aMachine[nCntMachine].pos = D3DXVECTOR3(1920.0f, 0.0f, 0.0f);
		g_aMachine[nCntMachine].move = D3DXVECTOR3(1920.0f, 0.0f, 0.0f);
		g_aMachine[nCntMachine].bUse = false;
		g_aMachine[nCntMachine].State = MACHINESTATE_APPEAR;
	}

	nMachineCounter = 0;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MACHINE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMachine, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++, pVtx += 4)
	{
		//頂点座標
		SetVertexMachine(nCntMachine);

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
	g_pVtxBuffMachine->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//　終了処理
//-----------------------------------------------------------------------------
void UninitMachine(void)
{
	//バッファの開放
	if (g_pVtxBuffMachine != NULL)
	{
		g_pVtxBuffMachine->Release();
		g_pVtxBuffMachine = NULL;
	}
	
	if (g_apTextureMachine != NULL)
	{
		g_apTextureMachine->Release();
		g_apTextureMachine = NULL;
	}
}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateMachine(void)
{
	MACHINE *pMachine;
	pMachine = &g_aMachine[0];

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++, pMachine++)
	{
		if (pMachine->bUse == true)
		{
			switch (pMachine->State)
			{
			case MACHINESTATE_APPEAR:
				//位置の更新
				pMachine->pos.y += 5;

				if (pMachine->pos.y > SCREEN_HEIGHT)
				{
					pMachine->State = MACHINESTATE_BREAK;
				}


				break;
			
			case MACHINESTATE_NORMAL:

				//慣性
				pMachine->pos.x += (pMachine->posDest.x - pMachine->pos.x) * 0.09f;
				pMachine->pos.y += (pMachine->posDest.y - pMachine->pos.y) * 0.09f;

				break;

			case MACHINESTATE_BREAK:

				pMachine->bUse = false;

				break;

			}
			SetVertexMachine(nCntMachine);
		}

		pVtx += 4;
	}

	//頂点バッファをアンロックする
	g_pVtxBuffMachine->Unlock();
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawMachine(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	MACHINE *pMachine;
	pMachine = &g_aMachine[0];

	//デバイスの取得
	pDevice = GetDevice();			

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffMachine, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (int nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++, pMachine++)
	{
		if (pMachine->bUse == true)
		{
			//テクスチャの設定
			pDevice->SetTexture(0, g_apTextureMachine);

			//ポリゴンの描画
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMachine * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// 子機の頂点座標設定
//-----------------------------------------------------------------------------
void SetVertexMachine(int nIdx)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x - MACHINE_SIZE, g_aMachine[nIdx].pos.y + MACHINE_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x - MACHINE_SIZE, g_aMachine[nIdx].pos.y - MACHINE_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x + MACHINE_SIZE, g_aMachine[nIdx].pos.y + MACHINE_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x + MACHINE_SIZE, g_aMachine[nIdx].pos.y - MACHINE_SIZE, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffMachine->Unlock();

}

//-----------------------------------------------------------------------------
// 子機の設定
//-----------------------------------------------------------------------------
void SetMachine(D3DXVECTOR3 pos)
{
	MACHINE *pMachine;
	pMachine = &g_aMachine[0];

	int nCntMachine;

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++, pMachine++)
	{
		if (pMachine->bUse == false)
		{
			//位置
			pMachine->pos = pos;

			pMachine->State = MACHINESTATE_APPEAR;

			//頂点座標
			SetVertexMachine(nCntMachine);

			//使っている状態に
			pMachine->bUse = true;

			break;
		}
		pVtx += 4;
	}

	g_pVtxBuffMachine->Unlock(); //アンロック

}

//-----------------------------------------------------------------------------
// 子機の場所設定
//-----------------------------------------------------------------------------
void SetPosMachine(int nIdx, D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//g_aMachine[nIdx].pos = D3DXVECTOR3(500, -100, 0.0f);

	//頂点座標
	g_aMachine[nIdx].posDest = pos;

	pVtx[0].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x - MACHINE_SIZE, g_aMachine[nIdx].pos.y + MACHINE_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x - MACHINE_SIZE, g_aMachine[nIdx].pos.y - MACHINE_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x + MACHINE_SIZE, g_aMachine[nIdx].pos.y + MACHINE_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x + MACHINE_SIZE, g_aMachine[nIdx].pos.y - MACHINE_SIZE, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffMachine->Unlock();

}

//-----------------------------------------------------------------------------
// 子機の弾
//-----------------------------------------------------------------------------
void SetBulletMachine(int nIdx)
{
	SetBullet(g_aMachine[nIdx].pos, D3DXVECTOR3(0.0f, -11.5f, 0.0f), BULLETTYPE_MACHINE , BULLETTYPE_MACHINE);
}

MACHINE *GetMachine(void)
{
	return &g_aMachine[0];
}

