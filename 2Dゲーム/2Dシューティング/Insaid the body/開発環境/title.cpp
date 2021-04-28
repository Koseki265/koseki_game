//-----------------------------------------------------------------------------
//
// �^�C�g����ʂ̏���
// Author:KosekiYuto
//
//-----------------------------------------------------------------------------
#include "title.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//�}�N����`
#define MAX_TITLE (3)				//�^�C�g���̉摜�̐�
#define TITLE_BG_SIZE_X (960)		//�^�C�g����ʂ̉���
#define TITLE_BG_SIZE_Y (540)		//�^�C�g����ʂ̗���
#define GAME_TITLE_SIZE_X (700)		//�^�C�g���̉���
#define GAME_TITLE_SIZE_Y (100)		//�^�C�g���̗���
#define ENTER_SIZE_X (400)			//�v���X�G���^�[�̉���
#define ENTER_SIZE_Y (75)			//�v���X�G���^�[�̗���
#define MOVE_TITLE (5)				//�^�C�g���̈ړ����x

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTitle = NULL;		//���_���
LPDIRECT3DTEXTURE9 g_pTextureTitle[MAX_TITLE] = {};	//�e�N�X�`��
TITLE g_aTitle[MAX_TITLE];
int g_nCounterTitle;
int g_FadeCounter;
int g_nCounter;
bool g_bEnter;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitTitle(void)
{
	//�T�E���h�X�^�[�g
	PlaySound(SOUND_LABEL_BGM003);

	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, NULL, &g_pTextureTitle[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/game_title000.png", &g_pTextureTitle[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/press_enter.png", &g_pTextureTitle[2]);

	g_bEnter = false;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_TITLE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffTitle, NULL)))
	{
		return E_FAIL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		g_aTitle[nCntTitle].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		g_aTitle[nCntTitle].bDisp = true;
	}

	g_FadeCounter = 0;
	g_nCounterTitle = 30;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++, pVtx += 4)
	{

		SetVertexTitle(nCntTitle);

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
		g_pVtxBuffTitle->Unlock();

	}
	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitTitle(void)
{
	if (g_pVtxBuffTitle != NULL)
	{
		g_pVtxBuffTitle->Release();
		g_pVtxBuffTitle = NULL;
	}

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		if (g_pTextureTitle[nCntTitle] != NULL)
		{
			g_pTextureTitle[nCntTitle]->Release();
			g_pTextureTitle[nCntTitle] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateTitle(void)
{
	FADE *pFade;
	pFade = GetFade();

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += 4;

	g_nCounter++;		//�\���J�E���^�[

	if (g_aTitle[1].pos.y <= 300)
	{
		g_aTitle[1].pos.y += MOVE_TITLE;	//�^�C�g���ړ�
	}
	
	if ((g_nCounter % g_nCounterTitle) == 0)
	{
		g_aTitle[2].bDisp = g_aTitle[2].bDisp ? false : true;	//�v���X�G���^�[�̓_��
	}

	if (GetKeyboardTrigger(DIK_RETURN) == true && *pFade == FADE_NONE)
	{

		if (g_aTitle[1].pos.y < 300)
		{
			g_aTitle[1].pos.y = 300;
		}

		else if (g_aTitle[1].pos.y >= 300 && g_bEnter == false)
		{
			g_nCounterTitle -= 25;
			PlaySound(SOUND_LABEL_SE_DESICION);

			g_bEnter = true;
		}
	}

	if (g_bEnter == true)
	{
		if ((g_nCounter % 2) == 0)
		{
			
			g_FadeCounter++;

		}
	}
	if (g_FadeCounter == 30)
	{
		//�T�E���h�X�g�b�v
		//StopSound();

		SetFade(FADE_OUT, MODE_TUTORIAL);
	}

	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(g_aTitle[1].pos.x - GAME_TITLE_SIZE_X, g_aTitle[1].pos.y + GAME_TITLE_SIZE_Y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aTitle[1].pos.x - GAME_TITLE_SIZE_X, g_aTitle[1].pos.y - GAME_TITLE_SIZE_Y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aTitle[1].pos.x + GAME_TITLE_SIZE_X, g_aTitle[1].pos.y + GAME_TITLE_SIZE_Y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aTitle[1].pos.x + GAME_TITLE_SIZE_X, g_aTitle[1].pos.y - GAME_TITLE_SIZE_Y, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawTitle(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffTitle, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	for (int nCntTitle = 0; nCntTitle < MAX_TITLE; nCntTitle++)
	{
		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, g_pTextureTitle[nCntTitle]);

		if (g_aTitle[nCntTitle].bDisp == true)
		{
			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntTitle * 4, 2);
		}
	}

}

//-----------------------------------------------------------------------------
// �^�C�g���̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------

void SetVertexTitle(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffTitle->Lock(0, 0, (void**)&pVtx, 0);


	pVtx += nIdx * 4;

	
	if (nIdx == 0)
	{
		g_aTitle[nIdx].pos = D3DXVECTOR3(960.0f, 540.0f, 0.0f);

		g_aTitle[nIdx].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y + TITLE_BG_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + TITLE_BG_SIZE_X, g_aTitle[nIdx].pos.y - TITLE_BG_SIZE_Y, 0.0f);

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[1].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[2].col = D3DCOLOR_RGBA(0, 0, 0, 255);
		pVtx[3].col = D3DCOLOR_RGBA(0, 0, 0, 255);

	}
	else if (nIdx == 1)
	{
		g_aTitle[1].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, -300, 0);

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - GAME_TITLE_SIZE_X, g_aTitle[nIdx].pos.y + GAME_TITLE_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - GAME_TITLE_SIZE_X, g_aTitle[nIdx].pos.y - GAME_TITLE_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + GAME_TITLE_SIZE_X, g_aTitle[nIdx].pos.y + GAME_TITLE_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + GAME_TITLE_SIZE_X, g_aTitle[nIdx].pos.y - GAME_TITLE_SIZE_Y, 0.0f);

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}
	else if (nIdx == 2)
	{
		g_aTitle[nIdx].pos = D3DXVECTOR3(SCREEN_WIDTH / 2, 900.0f, 0.0f);
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - ENTER_SIZE_X, g_aTitle[nIdx].pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x - ENTER_SIZE_X, g_aTitle[nIdx].pos.y - ENTER_SIZE_Y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + ENTER_SIZE_X, g_aTitle[nIdx].pos.y + ENTER_SIZE_Y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(g_aTitle[nIdx].pos.x + ENTER_SIZE_X, g_aTitle[nIdx].pos.y - ENTER_SIZE_Y, 0.0f);

		//���_�̃J���[�ݒ�
		pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
		pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffTitle->Unlock();

}
