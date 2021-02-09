//-----------------------------------------------------------------------------
//
// �A�C�e���̏���
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#include "item.h"
#include "Player.h"
#include "score.h"
#include "time.h"
#include "sound.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureItem[MAX_ITEM_TYPE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffItem = NULL;
ITEM g_aItem[MAX_ITEM];								//�A�C�e���̏��
int g_nCounterAnimItem;
int g_nPattenAnimItem;

//-----------------------------------------------------------------------------
// �A�C�e���̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexItem(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	if (g_aItem[nIdx].nType == ITEM_SCORE)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y, 0);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y, 0);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_SIZEX, g_aItem[nIdx].pos.y - ITEM_SIZEY, 0);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f + (g_nPattenAnimItem * 0.25f), 1.0);
		pVtx[1].tex = D3DXVECTOR2(0.0f + (g_nPattenAnimItem * 0.25f), 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.25f + (g_nPattenAnimItem * 0.25f), 1.0);
		pVtx[3].tex = D3DXVECTOR2(0.25f + (g_nPattenAnimItem * 0.25f), 0.0f);

	}

	else if (g_aItem[nIdx].nType == ITEM_TIME)
	{
		//���_���W
		pVtx[0].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_TIME_SIZEX, g_aItem[nIdx].pos.y, 0);
		pVtx[1].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x - ITEM_TIME_SIZEX, g_aItem[nIdx].pos.y - ITEM_TIME_SIZEY, 0);
		pVtx[2].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_TIME_SIZEX, g_aItem[nIdx].pos.y, 0);
		pVtx[3].pos = D3DXVECTOR3(g_aItem[nIdx].pos.x + ITEM_TIME_SIZEX, g_aItem[nIdx].pos.y - ITEM_TIME_SIZEY, 0);

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitItem(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\coin000.png", &g_apTextureItem[ITEM_SCORE]);
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\item.001.png", &g_apTextureItem[ITEM_TIME]);

	//�\���̏�����
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++)
	{
		g_aItem[nCntItem].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		
		g_aItem[nCntItem].nType = 0;
		g_aItem[nCntItem].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		g_aItem[nCntItem].bUse = false;
	}

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_ITEM, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffItem, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pVtx += 4)
	{
		//���_���W
		SetVertexItem(nCntItem);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�̃J���[�ݒ�
		pVtx[0].col = g_aItem[nCntItem].col;
		pVtx[1].col = g_aItem[nCntItem].col;
		pVtx[2].col = g_aItem[nCntItem].col;		
		pVtx[3].col = g_aItem[nCntItem].col;

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffItem->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitItem(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffItem != NULL)
	{
		g_pVtxBuffItem->Release();
		g_pVtxBuffItem = NULL;
	}
	//�e�N�X�`���̊J��
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
// �X�V����
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

	//�A�C�e���̌���
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		if (pItem->bUse == true)
		{//�����蔻��
			if (pItem->pos.y - ITEM_SIZEY < pPlayer->pos.y && pItem->pos.y > pPlayer->pos.y - pPlayer->fHeight &&
				pItem->pos.x < pPlayer->pos.x + pPlayer->fWidth && pItem->pos.x > pPlayer->pos.x - pPlayer->fWidth)
			{
				//�X�R�A�A�b�v�A�C�e����������
				if (pItem->nType == ITEM_SCORE)
				{
					PlaySound(SOUND_LABEL_SE_COIN);
					AddScore(100);
				}
				//���ԉ����A�C�e����������
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

		//���_���W
		SetVertexItem(nCntItem);

	}

}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawItem(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	ITEM *pItem;
	pItem = &g_aItem[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffItem, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��
	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++, pItem++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_apTextureItem[pItem->nType]);

		if (pItem->bUse == true)
		{
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntItem * 4, 2);
		}
	}
}
//-----------------------------------------------------------------------------
// �A�C�e���̐ݒ�
//-----------------------------------------------------------------------------
void SetItem(D3DXVECTOR3 pos, int nType,D3DXCOLOR col)
{

	ITEM *pItem;
	pItem = &g_aItem[0];

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffItem->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntItem = 0; nCntItem < MAX_ITEM; nCntItem++ , pItem++)
	{
		if (pItem->bUse == false)
		{

			//�ʒu
			pItem->pos = pos;

			//���_���W
			SetVertexItem(nCntItem);

			//�^�C�v
			pItem->nType = nType;

			//�F
			pItem->col = col;
			pVtx[0].col = pItem->col;
			pVtx[1].col = pItem->col;
			pVtx[2].col = pItem->col;
			pVtx[3].col = pItem->col;

			//�g���Ă����Ԃ�
			pItem->bUse = true;

			break;
		}
		pVtx += 4;
	}
	g_pVtxBuffItem->Unlock(); //�A�����b�N
}
