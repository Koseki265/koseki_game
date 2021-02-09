//-----------------------------------------------------------------------------
//
// �u���b�N�̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#include "block.h"
#include "Player.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBlock = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureBlock = NULL;			//�e�N�X�`��
BLOCK g_aBlock[MAX_BLOCK];

//-----------------------------------------------------------------------------
//����������
//-----------------------------------------------------------------------------
HRESULT InitBlock(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/Block000.jpg", &g_pTextureBlock);
	
	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BLOCK, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBlock, NULL)))
	{
		return E_FAIL;
	}

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		g_aBlock[nCntBlock].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//�ʒu
		g_aBlock[nCntBlock].move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ���
		g_aBlock[nCntBlock].tex = D3DXVECTOR2(0.0f, 0.0f);			//�e�N�X�`��
		g_aBlock[nCntBlock].fWidth = 0;								//��
		g_aBlock[nCntBlock].fHeight = 0;							//����
		g_aBlock[nCntBlock].bUse = false;							//�g�p���Ă邩�ǂ���

	}

	VERTEX_2D *pVtx;

	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{

		SetVertexBlock(nCntBlock);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
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
// �X�V����
//-----------------------------------------------------------------------------
void UpdateBlock(void)
{

	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
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

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawBlock(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBlock, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureBlock);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++)
	{
		if (g_aBlock[nCntBlock].bUse == true)
		{	
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBlock * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// �u���b�N�̐ݒ�
//-----------------------------------------------------------------------------
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float fWidth, float fHeight)
{
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++,pBlock++)
	{
		if (pBlock->bUse == false)
		{
			//�ʒu
			pBlock->pos = pos;

			//�ړ�
			pBlock->move = move;

			//��
			pBlock->fWidth = fWidth;

			//����
			pBlock->fHeight = fHeight;

			//���_���W
			SetVertexBlock(nCntBlock);

			//�e�N�X�`����
			if (pBlock->fWidth >= 200 && pBlock->fWidth <= 500)
			{
				//���_�̏��̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(5.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(5.0f, 0.0f);
			}

			if (pBlock->fWidth >= 1650)
			{
				//���_�̏��̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(30.0f, 1.0f);
				pVtx[3].tex = D3DXVECTOR2(30.0f, 0.0f);
			}

			if (pBlock->fHeight >= 600 && pBlock->fHeight <= 900)
			{
				//���_�̏��̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 12.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 12.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			}
			if (pBlock->fHeight >= 1000)
			{
				//���_�̏��̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 20.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 20.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			}

			if (pBlock->fHeight >= 300 && pBlock->fHeight <= 600)
			{
				//���_�̏��̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 5.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 5.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			}
			if (pBlock->fHeight >= 100 && pBlock->fHeight <= 250)
			{
				//���_�̏��̐ݒ�
				pVtx[0].tex = D3DXVECTOR2(0.0f, 3.0f);
				pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
				pVtx[2].tex = D3DXVECTOR2(1.0f, 3.0f);
				pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
			}
			//�g���Ă��Ԃ�
			pBlock->bUse = true;

			break;
		}
		pVtx += 4;
	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();

}

//���_���W
void SetVertexBlock(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBlock->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nIdx * 4);

	pVtx[0].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0);
	pVtx[1].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x, g_aBlock[nIdx].pos.y , 0);
	pVtx[2].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y + g_aBlock[nIdx].fHeight, 0);
	pVtx[3].pos = D3DXVECTOR3(g_aBlock[nIdx].pos.x + g_aBlock[nIdx].fWidth, g_aBlock[nIdx].pos.y, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffBlock->Unlock();
}

//-----------------------------------------------------------------------------
// �u���b�N�̓����蔻��
//-----------------------------------------------------------------------------
bool ColisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight,TOUCHING_BULOCK nType)
{
	BLOCK *pBlock;
	pBlock = &g_aBlock[0];

	bool bLand = true;

	//�����蔻��
	for (int nCntBlock = 0; nCntBlock < MAX_BLOCK; nCntBlock++, pBlock++)
	{
		if (pBlock->bUse == true)
		{//�v���C���[�G�̏㉺�̓����蔻��
			if (pBlock->pos.x <= pPos->x + (fWidth) && (pBlock->pos.x + pBlock->fWidth) >= pPos->x - (fWidth))
			{
				//�u���b�N��̓����蔻��
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
				//�ړ���
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
				//�u���b�N���̓����蔻��
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
				//�u���b�N���̓����蔻��
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
				//�ړ��� (��)
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
				
				//�u���b�N�E�̓����蔻��
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
				//�ړ���(�E)
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

//�u���b�N�̏��
BLOCK *GetBlock(void)
{
	return &g_aBlock[0];
}