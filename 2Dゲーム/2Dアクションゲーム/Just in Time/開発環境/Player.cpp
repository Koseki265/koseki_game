//-----------------------------------------------------------------------------
//
//プレイヤーの処理
//Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#include "Player.h"
#include "game.h"
#include "input.h"
#include "block.h"
#include "score.h"
#include "fade.h"

//-----------------------------------------------------------------------------
// グローバル変数
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPlayer = NULL;	//頂点情報
LPDIRECT3DTEXTURE9 g_pTexturePlayer = NULL;			//テクスチャ
int g_CounterAnim;									//アニメーションカウンター
int g_AnimCounter;
int g_JampCounter;
int g_nPatternAnimU;								//アニメーションパターンU.No.
int g_nPatternAnimV;								//アニメーションパターンV.No.
D3DXVECTOR3 g_rotPlayer;							//
PLAYER g_Player;
int g_nPlayertStateCounter;
int g_nDispCounter;
int g_nTriggerButton;
int g_nPlayertStateAppearCounter;

//-----------------------------------------------------------------------------
// プレイヤーの初期化処理
//-----------------------------------------------------------------------------
HRESULT InitPlayer(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player000.png", &g_pTexturePlayer);

	//構造体初期化
	g_Player.move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_Player.State = PLAYERSTATE_NORMAL;
	g_Player.fWidth = PLAYER_SIZEX;
	g_Player.fHeight = PLAYER_SIZEY;
	g_Player.bDisp = true;
	g_Player.bJump = false;

	g_CounterAnim = 0;
	g_nPatternAnimU = 0;
	g_nPatternAnimV = 0;
	g_nPlayertStateCounter = 0;
	g_nDispCounter = 0;

	//頂点バッファの生成 
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffPlayer, NULL)))
	{
		return E_FAIL;
	}

	GAME *pGame;
	pGame = GetGame();

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点ポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	if (pGame->stage == STAGE_1)
	{
		g_Player.pos = D3DXVECTOR3(50, 130, 0.0f);
	}

	if (pGame->stage == STAGE_2)
	{
		g_Player.pos = D3DXVECTOR3(100, 1030, 0.0f);
	}


	SetVertexPlayer();

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
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.5f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.25, 0.5f);
	pVtx[3].tex = D3DXVECTOR2(0.25, 0.0f);

	//頂点バッファをアンロックする
	g_pVtxBuffPlayer->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// プレイヤーの終了処理
//-----------------------------------------------------------------------------
void UninitPlayer(void)
{
	//バッファの開放
	if (g_pVtxBuffPlayer != NULL)
	{
		g_pVtxBuffPlayer->Release();
		g_pVtxBuffPlayer = NULL;
	}

	//テクスチャの開放
	if (g_pTexturePlayer != NULL)
	{
		g_pTexturePlayer->Release();
		g_pTexturePlayer = NULL;
	}
}

//-----------------------------------------------------------------------------
// プレイヤーの更新処理
//-----------------------------------------------------------------------------
void UpdatePlayer(void)
{
	GAME *pGame;
	pGame = GetGame();

	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点ポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//前回の位置保存
	
	g_Player.posOld = g_Player.pos;
	
	//アニメーション
	g_nPatternAnimU = (g_nPatternAnimU) % 4;

	switch (g_Player.State)
	{//プレイヤーの状態
//ノーマル
	case PLAYERSTATE_NORMAL:

		g_nDispCounter = 0;

		g_nPlayertStateCounter = 0;
		if (g_Player.bDisp == false)
		{
			g_Player.bDisp = true;
		}

		if (GetKeyboardPress(DIK_A) == true)
		{
			if (g_Player.bJump == false)
			{
				g_CounterAnim++;
				if ((g_CounterAnim % ANIM_SPEED) == 0)
				{
					g_nPatternAnimU++;
				}
			}
			g_nPatternAnimV = 1;

			g_Player.move.x += -MOVE_SPEED;

		}

		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (g_Player.bJump == false)
			{
				g_CounterAnim++;
				if ((g_CounterAnim % ANIM_SPEED) == 0)
				{
					g_nPatternAnimU++;
				}
			}
			g_nPatternAnimV = 0;

			g_Player.move.x += MOVE_SPEED;
		}

		if (GetKeyboardRelease(DIK_A) == true)
		{
			g_nPatternAnimU = 0;
		}

		if (GetKeyboardRelease(DIK_D) == true)
		{
			g_nPatternAnimU = 0;
		}
		//ジャンプ
		if (g_Player.bJump == false)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bJump == false)
			{
				g_Player.move.y = -JAMP;
				g_Player.bJump = true;
			}
		}	

		break;

//無敵
	case PLAYERSTATE_INVINCIBLE:

		g_nPlayertStateAppearCounter = 0;

		//頂点のカラー設定
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		g_nTriggerButton = 0;

		g_nDispCounter++;

		if ((g_nDispCounter % 5) == 0)
		{
			g_Player.bDisp = g_Player.bDisp ? false : true;
		}

		if (GetKeyboardPress(DIK_A) == true)
		{
			if (g_Player.bJump == false)
			{
				g_CounterAnim++;
				if ((g_CounterAnim % ANIM_SPEED) == 0)
				{
					g_nPatternAnimU++;
				}
			}
			g_nPatternAnimV = 1;

			g_Player.move.x += -MOVE_SPEED;

		}

		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (g_Player.bJump == false)
			{
				g_CounterAnim++;
				if ((g_CounterAnim % ANIM_SPEED) == 0)
				{
					g_nPatternAnimU++;
				}
			}
			g_nPatternAnimV = 0;

			g_Player.move.x += MOVE_SPEED;
		}

		if (GetKeyboardRelease(DIK_A) == true)
		{
			g_nPatternAnimU = 0;
		}

		if (GetKeyboardRelease(DIK_D) == true)
		{
			g_nPatternAnimU = 0;
		}
		//ジャンプ
		if (g_Player.bJump == false)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bJump == false)
			{
				g_Player.move.y = -JAMP;
				g_Player.bJump = true;
			}
		}

		g_nPlayertStateCounter++;

		if ((g_nPlayertStateCounter % 150) == 0)
		{
			g_Player.State = PLAYERSTATE_NORMAL;
		}

		break;

//ダメージ
	case PLAYERSTATE_DAMAGE:

		g_nPlayertStateCounter++;
		g_nDispCounter++;

		if ((g_nDispCounter % 5) == 0)
		{
			g_Player.bDisp = g_Player.bDisp ? false: true;
		}

		if ((g_nPlayertStateCounter % 60) == 0)
		{
			g_Player.State = PLAYERSTATE_INVINCIBLE;
		}

		break;
//凍結
	case PLAYERSTATE_FREEZE:
		if (GetKeyboardTrigger(DIK_A) == true || GetKeyboardTrigger(DIK_D) == true)
		{
			g_Player.move.y -= 1.0f;
			g_nTriggerButton++;
		}

		if (g_nTriggerButton == 10)
		{
			g_Player.State = PLAYERSTATE_INVINCIBLE;
		}

		//頂点のカラー設定
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 255, 255);

		break;
//スロウ	
	case PLAYERSTATE_SLOW:

		g_nPlayertStateCounter++;

		if ((g_nPlayertStateCounter % 100) == 0)
		{
			g_Player.State = PLAYERSTATE_INVINCIBLE;
		}

		if (GetKeyboardPress(DIK_A) == true)
		{
			if (g_Player.bJump == false)
			{
				g_CounterAnim++;
				if ((g_CounterAnim % ANIM_SLOW_SPEED) == 0)
				{
					g_nPatternAnimU++;
				}
			}
			g_nPatternAnimV = 1;

			g_Player.move.x += -MOVE_SLOW_SPEED;

		}

		else if (GetKeyboardPress(DIK_D) == true)
		{
			if (g_Player.bJump == false)
			{
				g_CounterAnim++;
				if ((g_CounterAnim % ANIM_SLOW_SPEED) == 0)
				{
					g_nPatternAnimU++;
				}
			}
			g_nPatternAnimV = 0;

			g_Player.move.x += MOVE_SLOW_SPEED;
		}

		if (GetKeyboardRelease(DIK_A) == true)
		{
			g_nPatternAnimU = 0;
		}

		if (GetKeyboardRelease(DIK_D) == true)
		{
			g_nPatternAnimU = 0;
		}
		//ジャンプ
		if (g_Player.bJump == false)
		{
			if (GetKeyboardTrigger(DIK_SPACE) == true && g_Player.bJump == false)
			{
				g_Player.move.y = -LOW_JUMP;
				g_Player.bJump = true;
			}
		}

		//頂点のカラー設定
		pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);

		break;

	default:
		break;

	}

	//ジャンプ中のテクスチャ
	if (g_Player.bJump == true)
	{
		g_nPatternAnimU = 1;
	}
	if (g_Player.bJump == false)
	{
		g_Player.Touchi = 0;
	}

	//位置更新
	g_Player.pos.x += g_Player.move.x;
	g_Player.pos.y += g_Player.move.y;
	g_Player.pos.z += g_Player.move.z;

	//重力
	g_Player.move.y += GRAVITY;

	//移動量
	g_Player.move.x += (0 - g_Player.move.x) * 0.5f;
	if (g_Player.bJump == true)
	{
		g_Player.move.x += (0 - g_Player.move.x) * 0.025f;
	}
	g_Player.move.y += (0 - g_Player.move.y) * 0.025f;

	
	//ジャンプしていてるかどうか,プレイヤーとブロックの当たり判定
	g_Player.bJump = ColisionBlock(&g_Player.pos, &g_Player.posOld, &g_Player.move, g_Player.fWidth, g_Player.fHeight, TOUCHING_PLAYER);


	//画面端当たり判定
	if (g_Player.pos.x < 0 + g_Player.fWidth)
	{
		g_Player.pos.x = 0 + g_Player.fWidth;
	}

	if (g_Player.pos.y - g_Player.fHeight > SCREEN_HEIGHT)
	{
		if (pGame->stage == STAGE_1)
		{
			g_Player.pos = D3DXVECTOR3(50, 130, 0.0f);
		}
		else
		{
			SetFade(FADE_OUT, MODE_GAME);
		}

		AddScore(-200);
	}

	//テクスチャ座標
	pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nPatternAnimU * 0.25f), 0.5f + (g_nPatternAnimV * 0.5f));
	pVtx[1].tex = D3DXVECTOR2(0.0f + (g_nPatternAnimU * 0.25f), 0.0f + (g_nPatternAnimV * 0.5f));
	pVtx[2].tex = D3DXVECTOR2(0.25f + (g_nPatternAnimU * 0.25f), 0.5f + (g_nPatternAnimV * 0.5f));
	pVtx[3].tex = D3DXVECTOR2(0.25f + (g_nPatternAnimU * 0.25f), 0.0f + (g_nPatternAnimV * 0.5f));

	SetVertexPlayer();

	g_pVtxBuffPlayer->Unlock(); //アンロック
}

//-----------------------------------------------------------------------------
// プレイヤーの描画処理
//-----------------------------------------------------------------------------
void DrawPlayer(void)
{
	//ローカル変数
	LPDIRECT3DDEVICE9 pDevice;

	//デバイスの取得
	pDevice = GetDevice();

	//頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffPlayer, 0, sizeof(VERTEX_2D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);

	//テクスチャの設定
	pDevice->SetTexture(0,g_pTexturePlayer);
	
	if (g_Player.bDisp == true)
	{
		//ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
	
}

//頂点座標
void SetVertexPlayer(void)
{
	VERTEX_2D *pVtx;

	//頂点バッファをロックし、頂点ポインタを取得
	g_pVtxBuffPlayer->Lock(0, 0, (void**)&pVtx, 0);

	//頂点座標
	pVtx[0].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fWidth, g_Player.pos.y, 0);
	pVtx[1].pos = D3DXVECTOR3(g_Player.pos.x - g_Player.fWidth, g_Player.pos.y - g_Player.fHeight, 0);
	pVtx[2].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fWidth, g_Player.pos.y, 0);
	pVtx[3].pos = D3DXVECTOR3(g_Player.pos.x + g_Player.fWidth, g_Player.pos.y - g_Player.fHeight, 0);
	
	g_pVtxBuffPlayer->Unlock(); //アンロック

}

//-----------------------------------------------------------------------------
//プレイヤー情報
//-----------------------------------------------------------------------------
PLAYER *GetPlayer(void)
{
	return &g_Player;
}

