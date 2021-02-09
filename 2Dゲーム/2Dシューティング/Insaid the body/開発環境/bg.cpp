//-----------------------------------------------------------------------------
//
// �_�C���N�g���̏���
//Author:KosekiYuto
//
//-----------------------------------------------------------------------------
#include "bg.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffBg = NULL;	//���_���
LPDIRECT3DTEXTURE9 g_pTextureBg[MAX_BG] = {};			//�e�N�X�`��
BG g_aBg[MAX_BG];
int g_nCounterAnimBg;									//�A�j���[�V�����J�E���^�[
int g_nPatternAnimBg;									//�A�j���[�V�����p�^�[��No.

//-----------------------------------------------------------------------------
// �w�i�̏���������
//-----------------------------------------------------------------------------
HRESULT InitBg(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg003.jpg", &g_pTextureBg[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg101.png", &g_pTextureBg[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/bg102.png", &g_pTextureBg[2]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_BG, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffBg, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		g_aBg[nCntBg].pos = D3DXVECTOR3(960, 540, 0);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aBg[nCntBg].pos.x - 960, g_aBg[nCntBg].pos.y + 540, 0);
		pVtx[1].pos = D3DXVECTOR3(g_aBg[nCntBg].pos.x - 960, g_aBg[nCntBg].pos.y - 540, 0);
		pVtx[2].pos = D3DXVECTOR3(g_aBg[nCntBg].pos.x + 960, g_aBg[nCntBg].pos.y + 540, 0);
		pVtx[3].pos = D3DXVECTOR3(g_aBg[nCntBg].pos.x + 960, g_aBg[nCntBg].pos.y - 540, 0);

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
	g_pVtxBuffBg->Unlock();

	return S_OK;
}
//-----------------------------------------------------------------------------
// �w�i�̏I������
//-----------------------------------------------------------------------------
void UninitBg(void)
{
	if (g_pVtxBuffBg != NULL)
	{
		g_pVtxBuffBg->Release();
		g_pVtxBuffBg = NULL;
	}
	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		if (g_pTextureBg[nCntBg] != NULL)
		{
			g_pTextureBg[nCntBg]->Release();
			g_pTextureBg[nCntBg] = NULL;
		}
	}
}
//-----------------------------------------------------------------------------
// �w�i�̍X�V����
//-----------------------------------------------------------------------------
void UpdateBg(void)
{
	//VERTEX_2D *pVtx;

	////���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	//g_pVtxBuffBg->Lock(0, 0, (void**)&pVtx, 0);

	////�ړ���
	//g_aBg[1].pos.y += MOVE_BG;

	////���_�̍��W
	//pVtx[0].pos = D3DXVECTOR3(g_aBg[1].pos.x - 960, g_aBg[1].pos.y + 540, 0);
	//pVtx[1].pos = D3DXVECTOR3(g_aBg[1].pos.x - 960, g_aBg[1].pos.y - 540, 0);
	//pVtx[2].pos = D3DXVECTOR3(g_aBg[1].pos.x + 960, g_aBg[1].pos.y + 540, 0);
	//pVtx[3].pos = D3DXVECTOR3(g_aBg[1].pos.x + 960, g_aBg[1].pos.y - 540, 0);

	//
	////���_�o�b�t�@���A�����b�N����
	//g_pVtxBuffBg->Unlock();
}

//-----------------------------------------------------------------------------
// �w�i�̕`�揈��
//-----------------------------------------------------------------------------
void DrawBg(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffBg, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	for (int nCntBg = 0; nCntBg < MAX_BG; nCntBg++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureBg[nCntBg]);

		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntBg * 4, 2);
	}
}