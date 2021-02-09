//-----------------------------------------------------------------------------
//
// アイテムの処理
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------
#include "goal.h"
#include "Player.h"
#include "fade.h"

//-----------------------------------------------------------------------------
//グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;
GOAL g_nGoal;									//ゴールの情報
int g_nFadeCounterGoal;							//ゴールしてからのフェードに入るまでの時間
int g_nPatternGoalAnim;							//アニメーションパターン
int g_nGoalAnimCounter;							//アニメーションカウンター


//-----------------------------------------------------------------------------
// ゴールのの頂点座標の設定
//-----------------------------------------------------------------------------
void SetVertexGoal(void)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_nGoal.pos.x - GOAL_SIZEX, g_nGoal.pos.y, 0);
	pVtx[1].pos = D3DXVECTOR3(g_nGoal.pos.x - GOAL_SIZEX, g_nGoal.pos.y - GOAL_SIZEY, 0);
	pVtx[2].pos = D3DXVECTOR3(g_nGoal.pos.x + GOAL_SIZEX, g_nGoal.pos.y, 0);
	pVtx[3].pos = D3DXVECTOR3(g_nGoal.pos.x + GOAL_SIZEX, g_nGoal.pos.y - GOAL_SIZEY, 0);

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();
}


//-----------------------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------------------
HRESULT InitGoal(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\goal.png", &g_pTextureGoal);

	//構造体初期化

	g_nGoal.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nGoal.bUse = false;

	g_nFadeCounterGoal = 0;
	g_nPatternGoalAnim = 0;

	//頂点バッファの生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGoal, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	SetVertexGoal();

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
	pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);


	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//　終了処理
//-----------------------------------------------------------------------------
void UninitGoal(void)
{
	//バッファの開放
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
	//テクスチャの開放

	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

}

//-----------------------------------------------------------------------------
// 更新処理
//-----------------------------------------------------------------------------
void UpdateGoal(void)
{
	GOAL *pGoal;
	pGoal = &g_nGoal;

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	VERTEX_2D *pVtx;

	g_nGoalAnimCounter++;

	//頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if ((g_nGoalAnimCounter % 10) == 0)
	{
		g_nPatternGoalAnim = (g_nPatternGoalAnim + 1) % 2;
	}


	//頂点の情報の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f * g_nPatternGoalAnim), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.5f * g_nPatternGoalAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f + (0.5f * g_nPatternGoalAnim), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f * g_nPatternGoalAnim), 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffGoal->Unlock();

	//ゴールしたら
	if (pGoal->bUse == true)
	{//当たり判定
		if (pGoal->pos.y - GOAL_SIZEY < pPlayer->pos.y && pGoal->pos.y > pPlayer->pos.y - pPlayer->fHeight &&
			pGoal->pos.x < pPlayer->pos.x + pPlayer->fWidth && pGoal->pos.x > pPlayer->pos.x - pPlayer->fWidth)
		{
			pPlayer->bDisp = true;
			pGoal->bUse = false;
		}
	}
}

//-----------------------------------------------------------------------------
// 描画処理
//-----------------------------------------------------------------------------
void DrawGoal(void)
{
	//ローカル
	LPDIRECT3DDEVICE9 pDevice;

	GOAL *pItem;
	pItem = &g_nGoal;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//ポリゴンの描画

	//テクスチャの設定
	pDevice->SetTexture(0, g_pTextureGoal);

	if (pItem->bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//-----------------------------------------------------------------------------
// ゴールの設定
//-----------------------------------------------------------------------------
void SetGoal(D3DXVECTOR3 pos)
{

	GOAL *pGoal;
	pGoal = &g_nGoal;

	if (pGoal->bUse == false)
	{
		//位置
		pGoal->pos = pos;

		//頂点座標
		SetVertexGoal();

		//使っている状態に
		pGoal->bUse = true;

	}
}
//
GOAL *GetGoal(void)
{
	return &g_nGoal;
}

