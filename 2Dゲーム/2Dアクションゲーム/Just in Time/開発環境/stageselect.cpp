//-----------------------------------------------------------------------------
//
// �^�C�g����ʂ̏���
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------
#if 1
#include "stageselect.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//�}�N����`
#define MAX_STAGE (6)			//�^�C�g���̉摜�̐�
#define TITLE_BG_SIZE_X (960)	//�^�C�g����ʂ̉���
#define TITLE_BG_SIZE_Y (540)	//�^�C�g����ʂ̗���
#define STAGE_TEX_SIZE (300)		//�v���X�G���^�[�̉���

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffStage = NULL;		//���_���
LPDIRECT3DTEXTURE9 g_pTextureStage[MAX_STAGE] = {};	//�e�N�X�`��
STAGESELECT g_aStage[MAX_STAGE];

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitStage(void)
{
	//�T�E���h�X�^�[�g
	PlaySound(SOUND_LABEL_BGM001);

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/StageSelect000.png", &g_pTextureStage[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/stage000.png", &g_pTextureStage[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/stage001.png" ,&g_pTextureStage[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/StageSelect000.png", &g_pTextureStage[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/StageSelect001.png", &g_pTextureStage[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/StageSelect002.png", &g_pTextureStage[5]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_STAGE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffStage, NULL)))
	{
		return E_FAIL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_STAGE; nCntTitle++)
	{
		g_aStage[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntStage = 0; nCntStage < MAX_STAGE; nCntStage++, pVtx += 4)
	{

		SetVertexStage(nCntStage);

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

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffStage->Unlock();

	}
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitStage(void)
{
	if (g_pVtxBuffStage != NULL)
	{
		g_pVtxBuffStage->Release();
		g_pVtxBuffStage = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_STAGE; nCntTitle++)
	{
		if (g_pTextureStage[nCntTitle] != NULL)
		{
			g_pTextureStage[nCntTitle]->Release();
			g_pTextureStage[nCntTitle] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateStage(void)
{
	FADE *pFade;
	pFade = GetFade();

	GAME *pGame;
	pGame = GetGame();

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);

	if (*pFade != FADE_OUT)
	{
		if (GetKeyboardTrigger(DIK_A) == true)
		{
			pGame->stage = STAGE_1;

			PlaySound(SOUND_LABEL_SE_SELECT);
		}

		if (GetKeyboardTrigger(DIK_D) == true)
		{
			pGame->stage = STAGE_2;

			PlaySound(SOUND_LABEL_SE_SELECT);
		}

		switch (pGame->stage)
		{
		case STAGE_1:

			g_aStage[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			g_aStage[2].col = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
			break;

		case STAGE_2:

			g_aStage[1].col = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

			g_aStage[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;

		}
		for (int nCntStage = 0; nCntStage < MAX_STAGE; nCntStage++)
		{

			//���_�̃J���[�ݒ�
			pVtx[0].col = g_aStage[nCntStage].col;
			pVtx[1].col = g_aStage[nCntStage].col;
			pVtx[2].col = g_aStage[nCntStage].col;
			pVtx[3].col = g_aStage[nCntStage].col;

			pVtx += 4;

		}

		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			//�T�E���h�X�g�b�v
			StopSound();

			SetFade(FADE_OUT, MODE_GAME);

			PlaySound(SOUND_LABEL_SE_DESICION);
		}
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStage->Unlock();

}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawStage(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffStage, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntStage = 0; nCntStage < MAX_STAGE; nCntStage++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureStage[nCntStage]);

		
		//�|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntStage * 4, 2);
	}

}

//-----------------------------------------------------------------------------
// �^�C�g���̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexStage(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffStage->Lock(0, 0, (void**)&pVtx, 0);


	pVtx += nIdx * 4;


	if (nIdx == 0)
	{
		g_aStage[nIdx].pos = D3DXVECTOR3(960.0f, 540.0f, 0.0f);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - TITLE_BG_SIZE_X, g_aStage[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - TITLE_BG_SIZE_X, g_aStage[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + TITLE_BG_SIZE_X, g_aStage[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + TITLE_BG_SIZE_X, g_aStage[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);

		//���_�̃J���[�ݒ�
		g_aStage[nIdx].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (nIdx == 1)
	{
		g_aStage[nIdx].pos = D3DXVECTOR3(580, 700, 0);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - STAGE_TEX_SIZE, g_aStage[nIdx].pos.y + STAGE_TEX_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - STAGE_TEX_SIZE, g_aStage[nIdx].pos.y - STAGE_TEX_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + STAGE_TEX_SIZE, g_aStage[nIdx].pos.y + STAGE_TEX_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + STAGE_TEX_SIZE, g_aStage[nIdx].pos.y - STAGE_TEX_SIZE, 0.0f);

		//���_�̃J���[�ݒ�
		g_aStage[nIdx].col = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
	}
	else if (nIdx == 2)
	{
		g_aStage[nIdx].pos = D3DXVECTOR3(1300, 700, 0.0f);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - STAGE_TEX_SIZE, g_aStage[nIdx].pos.y + STAGE_TEX_SIZE, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - STAGE_TEX_SIZE, g_aStage[nIdx].pos.y - STAGE_TEX_SIZE, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + STAGE_TEX_SIZE, g_aStage[nIdx].pos.y + STAGE_TEX_SIZE, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + STAGE_TEX_SIZE, g_aStage[nIdx].pos.y - STAGE_TEX_SIZE, 0.0f);

		//���_�̃J���[�ݒ�
		g_aStage[nIdx].col = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);
	}

	else if (nIdx == 3)
	{
		g_aStage[nIdx].pos = D3DXVECTOR3(960, 125, 0.0f);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - 600, g_aStage[nIdx].pos.y + 100, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - 600, g_aStage[nIdx].pos.y - 100, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + 600, g_aStage[nIdx].pos.y + 100, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + 600, g_aStage[nIdx].pos.y - 100, 0.0f);

		//���_�̃J���[�ݒ�
		g_aStage[nIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}
	else if (nIdx == 4)
	{
		g_aStage[nIdx].pos = D3DXVECTOR3(580, 320, 0.0f);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - 300, g_aStage[nIdx].pos.y + 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - 300, g_aStage[nIdx].pos.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + 300, g_aStage[nIdx].pos.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + 300, g_aStage[nIdx].pos.y - 50, 0.0f);

		//���_�̃J���[�ݒ�
		g_aStage[nIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	else if (nIdx == 5)
	{
		g_aStage[nIdx].pos = D3DXVECTOR3(1300, 320, 0.0f);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - 300, g_aStage[nIdx].pos.y + 50, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x - 300, g_aStage[nIdx].pos.y - 50, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + 300, g_aStage[nIdx].pos.y + 50, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aStage[nIdx].pos.x + 300, g_aStage[nIdx].pos.y - 50, 0.0f);

		//���_�̃J���[�ݒ�
		g_aStage[nIdx].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffStage->Unlock();

}
#endif
