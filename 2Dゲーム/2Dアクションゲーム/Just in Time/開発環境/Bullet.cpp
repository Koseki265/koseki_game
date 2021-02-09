#include "Bullet.h"
#include "enemy.h"
#include "Player.h"
#include "game.h"
#include "sound.h"
//#include "Effect.h"
#include "block.h"

//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	int nLife;			//����
	int nType;			//�e�̎��
	float fWidht;
	float fHeight;
	bool bUse;			//�e�̎g�p��
}BULLET;


//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureBullet[2] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBullet = NULL;		
BULLET g_aBullet[MAX_BULLET];							//�e�̏��
int g_LifeCounter;

//-----------------------------------------------------------------------------
// �e�̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexBullet(int nIdx)
{
	GAME *pGame;
	pGame = GetGame();

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE, g_aBullet[nIdx].pos.y + BULLET_SIZE, 0);
	pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE, g_aBullet[nIdx].pos.y - BULLET_SIZE, 0);
	pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE, g_aBullet[nIdx].pos.y + BULLET_SIZE, 0);
	pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE, g_aBullet[nIdx].pos.y - BULLET_SIZE, 0);

	//���_�̃J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(100, 100, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(100, 100, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(100, 100, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(100, 100, 255, 255);

	if (g_aBullet[nIdx].nType == ENEMY_BULLET_1)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE_TYPE1, g_aBullet[nIdx].pos.y + BULLET_SIZE_TYPE1, 0);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE_TYPE1, g_aBullet[nIdx].pos.y - BULLET_SIZE_TYPE1, 0);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE_TYPE1, g_aBullet[nIdx].pos.y + BULLET_SIZE_TYPE1, 0);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE_TYPE1, g_aBullet[nIdx].pos.y - BULLET_SIZE_TYPE1, 0);

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 255, 0, 255);

	}

	if (pGame->stage == STAGE_2)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE_TYPE1, g_aBullet[nIdx].pos.y + BULLET_SIZE_TYPE1, 0);
		pVtx[1].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x - BULLET_SIZE_TYPE1, g_aBullet[nIdx].pos.y - BULLET_SIZE_TYPE1, 0);
		pVtx[2].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE_TYPE1, g_aBullet[nIdx].pos.y + BULLET_SIZE_TYPE1, 0);
		pVtx[3].pos = D3DXVECTOR3(g_aBullet[nIdx].pos.x + BULLET_SIZE_TYPE1, g_aBullet[nIdx].pos.y - BULLET_SIZE_TYPE1, 0);

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBullet->Unlock();
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitBullet(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet001.png", &g_pTextureBullet[0]); 
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\bullet000.png", &g_pTextureBullet[1]);


	//�\���̏�����
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		g_aBullet[nCntBullet].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aBullet[nCntBullet].nType = 0;
		g_aBullet[nCntBullet].bUse = false;
	}
	g_LifeCounter = 0;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BULLET, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBullet, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBullet->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//���_���W
		SetVertexBullet(nCntBullet);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	g_pVtxBuffBullet->Unlock(); //�A�����b�N

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitBullet(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffBullet != NULL)
	{
		g_pVtxBuffBullet->Release();
		g_pVtxBuffBullet = NULL;
	}
	//�e�N�X�`���̊J��
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET_TYPE; nCntBullet++)
	{
		if (g_pTextureBullet[nCntBullet] != NULL)
		{
			g_pTextureBullet[nCntBullet]->Release();
			g_pTextureBullet[nCntBullet] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateBullet(void)
{
	BULLET *pBullet;
	pBullet = &g_aBullet[0];

	//�G�̏��
	ENEMY *pEnemy;
	pEnemy = GetEnemy();

	//���@�̏��
	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	g_LifeCounter++;

	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{

		if (pBullet->bUse == true)
		{
			pBullet->posOld = pBullet->pos;

			//�ʒu�̍X�V
			pBullet->pos.x += pBullet->move.x;
			pBullet->pos.y += pBullet->move.y;

			//���_���W
			SetVertexBullet(nCntBullet);

			//�����`�F�b�N
			if ((g_LifeCounter % 60) == 0)
			{
				pBullet->nLife--;
			}
			if (pBullet->nLife == 0)
			{
				//SetExplosion(pBullet->pos,D3DXCOLOR(1.0f,0.0f,0.0f,1.0f));
				pBullet->bUse = false;
			}

			//��ʊO�`�F�b�N
			if (pBullet->pos.y < 0)
			{
				pBullet->bUse = false;
			}
			if (pBullet->pos.y > SCREEN_HEIGHT)
			{
				pBullet->bUse = false;
			}

			if (pBullet->pos.x > SCREEN_WIDTH)
			{
				pBullet->bUse = false;
			}

			if (pBullet->pos.x < 0)
			{
				pBullet->bUse = false;
			}

			pBullet->bUse = ColisionBlock(&pBullet->pos, &pBullet->posOld, &pBullet->move, BULLET_SIZE, BULLET_SIZE, TOUCHING_BULLET);

			if (pPlayer->State == PLAYERSTATE_NORMAL)
			{//���@�ƒe�̓����蔻��
				if (pBullet->pos.y + BULLET_SIZE > pPlayer->pos.y - pPlayer->fHeight && pBullet->pos.y - BULLET_SIZE < pPlayer->pos.y &&
					pBullet->pos.x + BULLET_SIZE > pPlayer->pos.x - pPlayer->fWidth && pBullet->pos.x - BULLET_SIZE < pPlayer->pos.x + pPlayer->fWidth)
				{
					//HitPlayer(1);
					if (pBullet->nType == ENEMY_BULLET_0)
					{
						//�q�b�g��
						PlaySound(SOUND_LABEL_SE_HIT);
						pPlayer->State = PLAYERSTATE_FREEZE;
					}
					if (pBullet->nType == ENEMY_BULLET_1)
					{
						//�q�b�g��
						PlaySound(SOUND_LABEL_SE_HIT);
						pPlayer->State = PLAYERSTATE_SLOW;
					}

					pBullet->bUse = false;
				}
			}
		}
	}
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawBullet(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBullet, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBullet[g_aBullet[nCntBullet].nType]);

		if (g_aBullet[nCntBullet].bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBullet * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// �e�̐ݒ�
//-----------------------------------------------------------------------------
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, int nType)
{
	BULLET *pBullet;
	pBullet = &g_aBullet[0];
	
	for (int nCntBullet = 0; nCntBullet < MAX_BULLET; nCntBullet++, pBullet++)
	{
		if (pBullet->bUse == false)
		{
			//�ʒu
			pBullet->pos = pos;

			//���_���W
			SetVertexBullet(nCntBullet);
		
			//�ړ���
			pBullet->move.x = move.x;
			pBullet->move.y = move.y;

			pBullet->nType = nType;

			//����
			pBullet->nLife = nLife;

			pBullet->bUse = true;
			break;
		}
	}
}


