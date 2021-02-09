//-----------------------------------------------------------------------------
//
// �X�R�A�̏���
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#include "highscore.h"
#include "score.h"
#include "game.h"
#include "input.h"
#include "fade.h"
#include "sound.h"

//-----------------------------------------------------------------------------
//�}�N����`
//-----------------------------------------------------------------------------
#define MAX (13)						//�|���S���̐�
#define MAX_HISCORE (8)
#define MAX_TEXTURE (6)
#define LETTER_SIZE (D3DXVECTOR3(500,100,0.0f))
#define MIN_LETTER_SIZE (D3DXVECTOR3(200,50,0.0f))
#define SELECT_SIZE (D3DXVECTOR3(200,50,0.0f))
#define HIGHSOCORE_SIZEX (50)						//����
#define HIGHSOCORE_SIZEY (80)						//�c��

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureHighScore[MAX_TEXTURE] = {};
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHighScore = NULL;
D3DXVECTOR3 scorePos[MAX];				//�X�R�A�̈ʒu
D3DXCOLOR scorecol[MAX];
int g_HeghScore[2];
int NewScore;
int g_HightscoreFadeCounter;
int g_Select;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitHighScore(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�\���̏�����
	for (int nCntHighScore = 0; nCntHighScore < MAX; nCntHighScore++)
	{
		scorePos[nCntHighScore] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�X�R�A�̈ʒu						
	}

	g_HightscoreFadeCounter = 0;
	
	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/number000.png", &g_apTextureHighScore[0]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause001.png", &g_apTextureHighScore[1]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause003.png", &g_apTextureHighScore[2]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/pause002.png", &g_apTextureHighScore[3]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/score.png", &g_apTextureHighScore[4]);
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/record.png" , &g_apTextureHighScore[5]);

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffHighScore, NULL)))
	{
		return E_FAIL;
	}

	g_Select = SELECT_RETRY;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntHighScore = 0; nCntHighScore < MAX; nCntHighScore++, pVtx += 4)
	{
		//�|���S���̈ʒu
		scorePos[nCntHighScore] = D3DXVECTOR3(650 + (nCntHighScore * 90.0f), 540.0f, 0.0f);

		//���_���W
		pVtx[0].pos = D3DXVECTOR3(scorePos[nCntHighScore].x - HIGHSOCORE_SIZEX, scorePos[nCntHighScore].y + HIGHSOCORE_SIZEY, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(scorePos[nCntHighScore].x - HIGHSOCORE_SIZEX, scorePos[nCntHighScore].y - HIGHSOCORE_SIZEY, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(scorePos[nCntHighScore].x + HIGHSOCORE_SIZEX, scorePos[nCntHighScore].y + HIGHSOCORE_SIZEY, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(scorePos[nCntHighScore].x + HIGHSOCORE_SIZEX, scorePos[nCntHighScore].y - HIGHSOCORE_SIZEY, 0.0f);

		//���_�̃J���[�ݒ�
		scorecol[nCntHighScore] = D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f);

		//���_�̏��̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.1f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(0.1f, 0.0f);

		if (nCntHighScore >= MAX - 5 && nCntHighScore < MAX - 2)
		{
			//�|���S���̈ʒu
			scorePos[nCntHighScore] = D3DXVECTOR3(525 + ((nCntHighScore - 8.0f) * 400), 900, 0.0f);

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(scorePos[nCntHighScore].x - SELECT_SIZE.x, scorePos[nCntHighScore].y + SELECT_SIZE.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(scorePos[nCntHighScore].x - SELECT_SIZE.x, scorePos[nCntHighScore].y - SELECT_SIZE.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(scorePos[nCntHighScore].x + SELECT_SIZE.x, scorePos[nCntHighScore].y + SELECT_SIZE.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(scorePos[nCntHighScore].x + SELECT_SIZE.x, scorePos[nCntHighScore].y - SELECT_SIZE.y, 0.0f);

			//���_�̃J���[�ݒ�
			scorecol[nCntHighScore] = D3DXCOLOR(0.75f, 0.75f, 0.75f, 1.0f);

			//���_�̏��̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}
		if (nCntHighScore == MAX - 2)
		{
			//�|���S���̈ʒu
			scorePos[nCntHighScore] = D3DXVECTOR3(960, 300, 0.0f);

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(scorePos[nCntHighScore].x - LETTER_SIZE.x, scorePos[nCntHighScore].y + LETTER_SIZE.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(scorePos[nCntHighScore].x - LETTER_SIZE.x, scorePos[nCntHighScore].y - LETTER_SIZE.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(scorePos[nCntHighScore].x + LETTER_SIZE.x, scorePos[nCntHighScore].y + LETTER_SIZE.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(scorePos[nCntHighScore].x + LETTER_SIZE.x, scorePos[nCntHighScore].y - LETTER_SIZE.y, 0.0f);

			//���_�̃J���[�ݒ�
			scorecol[nCntHighScore] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���_�̏��̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
		}
		if (nCntHighScore == MAX - 1)
		{
			//�|���S���̈ʒu
			scorePos[nCntHighScore] = D3DXVECTOR3(1650, 150, 0.0f);

			//���_���W
			pVtx[0].pos = D3DXVECTOR3(scorePos[nCntHighScore].x - MIN_LETTER_SIZE.x, scorePos[nCntHighScore].y + MIN_LETTER_SIZE.y, 0.0f);
			pVtx[1].pos = D3DXVECTOR3(scorePos[nCntHighScore].x - MIN_LETTER_SIZE.x, scorePos[nCntHighScore].y - MIN_LETTER_SIZE.y, 0.0f);
			pVtx[2].pos = D3DXVECTOR3(scorePos[nCntHighScore].x + MIN_LETTER_SIZE.x, scorePos[nCntHighScore].y + MIN_LETTER_SIZE.y, 0.0f);
			pVtx[3].pos = D3DXVECTOR3(scorePos[nCntHighScore].x + MIN_LETTER_SIZE.x, scorePos[nCntHighScore].y - MIN_LETTER_SIZE.y, 0.0f);

			//���_�̃J���[�ݒ�
			scorecol[nCntHighScore] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			//���_�̏��̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		}
		//rhw�̐ݒ�
		pVtx[0].rhw = 1.0f;
		pVtx[1].rhw = 1.0f;
		pVtx[2].rhw = 1.0f;
		pVtx[3].rhw = 1.0f;

		//���_�J���[�̐ݒ�
		pVtx[0].col = scorecol[nCntHighScore];
		pVtx[1].col = scorecol[nCntHighScore];
		pVtx[2].col = scorecol[nCntHighScore];
		pVtx[3].col = scorecol[nCntHighScore];

	}

	int aNumber[MAX];

	SCORE *pScore;
	pScore = GetScore();

	GAME *pGame;
	pGame = GetGame();

	if (pGame->stage == STAGE_1)
	{
		NewScore = pScore->nScore;

		if (g_HeghScore[STAGE_1] <= NewScore)
		{
			g_HeghScore[STAGE_1] = NewScore;

			for (int nCntScore = 0; nCntScore < MAX_HISCORE; nCntScore++)
			{
				aNumber[nCntScore] = g_HeghScore[STAGE_1] / powf(10.0f, 8.0f - (nCntScore + 1.0f));

				//�e�N�X�`�����W�̐ݒ�
				SetVertexHighScore(nCntScore, aNumber[nCntScore]);
			}
		}
		else
		{
			for (int nCntScore = 0; nCntScore < MAX_HISCORE; nCntScore++)
			{
				aNumber[nCntScore] = g_HeghScore[STAGE_1] / powf(10.0f, 8.0f - (nCntScore + 1.0f));

				//�e�N�X�`�����W�̐ݒ�
				SetVertexHighScore(nCntScore, aNumber[nCntScore]);
			}
		}
	}
	if (pGame->stage == STAGE_2)
	{
		pScore++;

		NewScore = pScore->nScore;

		if (g_HeghScore[STAGE_2] <= NewScore)
		{
			g_HeghScore[STAGE_2] = NewScore;

			for (int nCntScore = 0; nCntScore < MAX_HISCORE; nCntScore++)
			{
				aNumber[nCntScore] = g_HeghScore[STAGE_2] / powf(10.0f, 8.0f - (nCntScore + 1.0f));

				//�e�N�X�`�����W�̐ݒ�
				SetVertexHighScore(nCntScore, aNumber[nCntScore]);
			}
		}
		else
		{
			for (int nCntScore = 0; nCntScore < MAX_HISCORE; nCntScore++)
			{
				aNumber[nCntScore] = g_HeghScore[STAGE_2] / powf(10.0f, 8.0f - (nCntScore + 1.0f));

				//�e�N�X�`�����W�̐ݒ�
				SetVertexHighScore(nCntScore, aNumber[nCntScore]);
			}
		}
	}


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHighScore->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitHighScore(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffHighScore != NULL)
	{
		g_pVtxBuffHighScore->Release();
		g_pVtxBuffHighScore = NULL;
	}
	//�e�N�X�`���̊J��
	for (int nCntHighScore = 0; nCntHighScore < MAX_TEXTURE; nCntHighScore++)
	{
		if (g_apTextureHighScore[nCntHighScore] != NULL)
		{
			g_apTextureHighScore[nCntHighScore]->Release();
			g_apTextureHighScore[nCntHighScore] = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateHighScore(void)
{
	FADE *pFade;
	pFade = GetFade();
	
	if (*pFade == FADE_NONE)
	{
		if (GetKeyboardTrigger(DIK_D) == true)
		{
			g_Select++;
			if (g_Select > SELECT_MAX - 1)
			{
				g_Select = 0;
			}
			PlaySound(SOUND_LABEL_SE_SELECT);
		}

		if (GetKeyboardTrigger(DIK_A) == true)
		{
			g_Select--;
			if (g_Select < 0)
			{
				g_Select = SELECT_MAX - 1;
			}
			PlaySound(SOUND_LABEL_SE_SELECT);
		}
		switch (g_Select)
		{
		case SELECT_RETRY:

			scorecol[8] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			scorecol[9] = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			scorecol[10] = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			break;

		case SELECT_STAGESELECT:

			scorecol[8] = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			scorecol[9] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			scorecol[10] = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			break;

		case SELECT_QUIT:

			scorecol[8] = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			scorecol[9] = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);

			scorecol[10] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			break;

		}

		VERTEX_2D *pVtx;

		//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
		g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

		for (int nCount = 0; nCount < MAX; nCount++)
		{
			pVtx[0].col = scorecol[nCount];
			pVtx[1].col = scorecol[nCount];
			pVtx[2].col = scorecol[nCount];
			pVtx[3].col = scorecol[nCount];

			pVtx += 4;
		}

		//���_�o�b�t�@���A�����b�N����
		g_pVtxBuffHighScore->Unlock();

		if (GetKeyboardTrigger(DIK_RETURN) == true)
		{
			if (g_Select == SELECT_RETRY)
			{
				SetFade(FADE_OUT, MODE_GAME);
			}
			else if (g_Select == SELECT_STAGESELECT)
			{
				SetFade(FADE_OUT, MODE_STAGESELECT);
			}
			else if (g_Select == SELECT_QUIT)
			{
				SetFade(FADE_OUT, MODE_TITLE);
			}
			PlaySound(SOUND_LABEL_SE_DESICION);
		}
	}
	if (*pFade == FADE_NONE)
	{
		g_HightscoreFadeCounter++;
		if ((g_HightscoreFadeCounter % 1000) == 0)

		{
			SetFade(FADE_OUT, MODE_TITLE);
		}
	}
}
//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawHighScore(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHighScore, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (int nCntScore = 0; nCntScore < MAX; nCntScore++)
	{
		//�e�N�X�`���̐ݒ�
		if (nCntScore < 8)
		{
			pDevice->SetTexture(0, g_apTextureHighScore[0]);
		}
		else if (nCntScore == 8)
		{
			pDevice->SetTexture(0, g_apTextureHighScore[1]);
		}
		else if (nCntScore == 9)
		{
			pDevice->SetTexture(0, g_apTextureHighScore[2]);
		}

		else if (nCntScore == 10)
		{
			pDevice->SetTexture(0, g_apTextureHighScore[3]);
		}

		else if (nCntScore == 11)
		{
			pDevice->SetTexture(0, g_apTextureHighScore[4]);
		}
		else
		{
			pDevice->SetTexture(0, g_apTextureHighScore[5]);
		}

		//�|���S���̕`��

		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntScore * 4, 2);
	}
}

//-----------------------------------------------------------------------------
// �e�N�X�`�����_���W�̍X�V
//-----------------------------------------------------------------------------
void SetVertexHighScore(int nIdx, int nNumber)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHighScore->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += (nIdx * 4);

	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.1f * nNumber), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.1f + (0.1f * nNumber), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffHighScore->Unlock();
}