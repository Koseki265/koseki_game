//-----------------------------------------------------------------------------
//
// �X�R�A�̏���
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#include "score.h"
#include "game.h"
#include "Time.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureScore = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffScore = NULL;
SCORE g_aScore[STAGE_SCORE];							//�X�R�A�̈ʒu
D3DXVECTOR3 Scorepos[MAX_SCORE];										//�X�R�A

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitScore(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�\���̏�����
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		Scorepos[MAX_SCORE] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�X�R�A�̈ʒu						
	}
	for (int nCntScore = 0; nCntScore < STAGE_SCORE; nCntScore++)
	{
		g_aScore[nCntScore].nScore = 0;
	}

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureScore);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_SCORE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffScore, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++, pVtx += 4)
	{
		//�|���S���̈ʒu
		Scorepos[nCntScore] = D3DXVECTOR3(1500.0f + nCntScore * 50, 50.0f, 0.0f);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(Scorepos[nCntScore].x - SCORE_SIZEX, Scorepos[nCntScore].y + SCORE_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(Scorepos[nCntScore].x - SCORE_SIZEX, Scorepos[nCntScore].y - SCORE_SIZEY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(Scorepos[nCntScore].x + SCORE_SIZEX, Scorepos[nCntScore].y + SCORE_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(Scorepos[nCntScore].x + SCORE_SIZEX, Scorepos[nCntScore].y - SCORE_SIZEY, 0.0f);

		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 0, 255);

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitScore(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffScore != NULL)
	{
		g_pVtxBuffScore->Release();
		g_pVtxBuffScore = NULL;
	}
	//�e�N�X�`���̊J��
	if (g_apTextureScore != NULL)
	{
		g_apTextureScore->Release();
		g_apTextureScore = NULL;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateScore(void)
{
	
}
//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawScore(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_apTextureScore);

	//�|���S���̕`��
	for (int nCntScore = 0; nCntScore < MAX_SCORE; nCntScore++)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//-----------------------------------------------------------------------------
// �X�R�A���Z
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
				//�e�N�X�`�����W�̐ݒ�
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
				//�e�N�X�`�����W�̐ݒ�
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
// �e�N�X�`�����_���W�̍X�V
//-----------------------------------------------------------------------------
void SetTextureScore(int nIdx, int nNumber)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffScore->Lock(0, 0, (void**)&pVtx, 0);
	
	pVtx += (nIdx * 4);

	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffScore->Unlock();
}

SCORE *GetScore(void)
{
	return &g_aScore[0];
}