//-----------------------------------------------------------------------------
//
// �_�C���N�g���̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#include "game.h"
#include "Player.h"
#include "bg.h"
#include "Bullet.h"
#include "Explosion.h"
#include "enemy.h"
#include "sound.h"
#include "score.h"
#include "fade.h"
#include "input.h"
//#include "Effect.h"
#include "pause.h"
#include "Time.h"
#include "block.h"
#include "item.h"
#include "goal.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
bool g_bPause = false;
GAME g_Game;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitGame(void)
{
	switch (g_Game.stage)
	{
	case STAGE_1:
		//�w�i�̏�����
		InitBg();

		//�v���C���[�̏���������
		InitPlayer();

		//�u���b�N�̏���������
		InitBlock();

		//�A�C�e���̏���������
		InitItem();

		//�S�[���̏�����
		InitGoal();

		//�e�̏���������
		InitBullet();

		//�G�t�F�N�g�̏���������
		//InitEffect();

		//�G�̏���������
		InitEnemy();

		//�X�R�A�̏�����
		InitScore();

		//���Ԃ̏�����
		InitTime();

		//�|�[�Y�̏���������
		InitPause();

		//�T�E���h�X�^�[�g
		//PlaySound(SOUND_LABEL_BGM002);
		Stage1();

		break;

		case STAGE_2:

			//�w�i�̏�����
			InitBg();

			//�v���C���[�̏���������
			InitPlayer();

			//�u���b�N�̏���������
			InitBlock();

			//�A�C�e���̏���������
			InitItem();

			//�S�[���̏�����
			InitGoal();

			//�e�̏���������
			InitBullet();

			//�G�t�F�N�g�̏���������
			//InitEffect();

			//�G�̏���������
			InitEnemy();

			//�X�R�A�̏�����
			InitScore();

			//���Ԃ̏�����
			InitTime();

			//�|�[�Y�̏���������
			InitPause();

			//�T�E���h�X�^�[�g
			//PlaySound(SOUND_LABEL_BGM002);

		Stage2();

		break;

	}

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitGame(void)
{
	switch (g_Game.stage)
	{
	case STAGE_1:
		//�T�E���h�X�g�b�v
		StopSound();

		//�|�[�Y�̏I������
		UninitPause();

		//���Ԃ̏I������
		UninitTime();

		//�G�̏I������
		UninitEnemy();

		//�G�t�F�N�g�̏I������
		//UninitEffect();

		//�e�̏I������
		UninitBullet();

		//�S�[���̏I������
		UninitGoal();

		//�A�C�e���̏I������
		UninitItem();

		//�u���b�N�̏I������
		UninitBlock();

		//�v���C���[�̏I������
		UninitPlayer();

		//�w�i�̏I��
		UninitBg();
		break;

	case STAGE_2:

		//�T�E���h�X�g�b�v
		StopSound();

		//�|�[�Y�̏I������
		UninitPause();

		//���Ԃ̏I������
		UninitTime();

		//�G�̏I������
		UninitEnemy();

		//�G�t�F�N�g�̏I������
		//UninitEffect();

		//�e�̏I������
		UninitBullet();

		//�S�[���̏I������
		UninitGoal();

		//�A�C�e���̏I������
		UninitItem();

		//�u���b�N�̏I������
		UninitBlock();

		//�v���C���[�̏I������
		UninitPlayer();

		//�w�i�̏I��
		UninitBg();

		break;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateGame(void)
{

	FADE *pFade;
	pFade = GetFade();

	GOAL *pGoal;
	pGoal = GetGoal();

	if (GetKeyboardTrigger(DIK_P) == true)
	{
		if (*pFade == FADE_NONE)
		{
			g_bPause = g_bPause ? false : true;
		}
		if (g_bPause == true)
		{
			PlaySound(SOUND_LABEL_SE_MENU);
		}
		else if (g_bPause == false)
		{
			PlaySound(SOUND_LABEL_SE_MENUCLOSE);
		}
	}

	SetPause(g_bPause);

	if (g_bPause == true)
	{
		//�|�[�Y�̍X�V����
		UpdatePause();
	}

	else if (g_bPause == false && *pFade == FADE_NONE)
	{
		switch (g_Game.stage)
		{
		case STAGE_1:
			if (pGoal->bUse == true)
			{

				//�w�i�̍X�V����
				UpdateBg();

				//�v���C���[�̍X�V����
				UpdatePlayer();

				//�u���b�N�̍X�V����
				UpdateBlock();

				//�G�̍X�V����
				UpdateEnemy();

				//�A�C�e���̍X�V����
				UpdateItem();

				//�S�[���̍X�V����
				UpdateGoal();

				//�e�̍X�V����
				UpdateBullet();

				//�G�t�F�N�g�̍X�V����
				//UpdateEffect();

				//�X�R�A�̍X�V����
				UpdateScore();
			}

			//���Ԃ̍X�V����
			UpdateTime();
			break;

		case STAGE_2:
			if (pGoal->bUse == true)
			{

				//�w�i�̍X�V����
				UpdateBg();

				//�v���C���[�̍X�V����
				UpdatePlayer();

				//�u���b�N�̍X�V����
				UpdateBlock();

				//�G�̍X�V����
				UpdateEnemy();

				//�A�C�e���̍X�V����
				UpdateItem();

				//�S�[���̍X�V����
				UpdateGoal();

				//�e�̍X�V����
				UpdateBullet();

				//�G�t�F�N�g�̍X�V����
				//UpdateEffect();

				//�X�R�A�̍X�V����
				UpdateScore();
			}

			//���Ԃ̍X�V����
			UpdateTime();
			break;
		}
	}

	/*if (GetKeyboardTrigger(DIK_L) == true)
	{
		SetFade(FADE_OUT, MODE_RESULT);
	}*/
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawGame(void)
{
	switch (g_Game.stage)
	{
	case STAGE_1:

		//�w�i�̕`��
		DrawBg();

		//�|���S���̕`�揈��
		DrawPlayer();

		//�u���b�N�̕`�揈��
		DrawBlock();

		//�A�C�e���̕`�揈��
		DrawItem();

		//�S�[���̕`�揈��
		DrawGoal();

		//�e�̕`�揈��
		DrawBullet();

		//�G�t�F�N�g�̕`�揈��
		//DrawEffect();

		//�G�̕`�揈��
		DrawEnemy();

		//�X�R�A�̕`�揈��
		DrawScore();

		//���Ԃ̕`�揈��
		DrawTime();

		break;

	case STAGE_2:

		//�w�i�̕`��
		DrawBg();

		//�|���S���̕`�揈��
		DrawPlayer();

		//�u���b�N�̕`�揈��
		DrawBlock();

		//�A�C�e���̕`�揈��
		DrawItem();

		//�S�[���̕`�揈��
		DrawGoal();

		//�e�̕`�揈��
		DrawBullet();

		//�G�t�F�N�g�̕`�揈��
		//DrawEffect();

		//�G�̕`�揈��
		DrawEnemy();

		//�X�R�A�̕`�揈��
		DrawScore();

		//���Ԃ̕`�揈��
		DrawTime();

		break;

	}

	if (g_bPause == true)
	{
		DrawPause();
	}

}

void Stage1(void)
{
	//�T�E���h�X�^�[�g
	PlaySound(SOUND_LABEL_BGM000);

	//�u���b�N�z�u
	//��
	SetBlock(D3DXVECTOR3(0, 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1920, 50);

	//�V��
	SetBlock(D3DXVECTOR3(0, -25, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1920, 50);
#if 1
	//���̃u���b�N

	//��
	SetBlock(D3DXVECTOR3(50, 750, 0), D3DXVECTOR3(0, 0, 0.0f), 300, 50);

	//�^��
	SetBlock(D3DXVECTOR3(225, 450, 0), D3DXVECTOR3(0, 0, 0.0f), 275, 50);

	//��
	SetBlock(D3DXVECTOR3(50, 130, 0), D3DXVECTOR3(0, 0, 0.0f), 275, 50);

#endif
	//�^�񒆂̃u���b�N

	//�G������Ă�u���b�N��
	SetBlock(D3DXVECTOR3(550, 250, 0), D3DXVECTOR3(0, 0, 0.0f), 100, 50);

	//�G������Ă�u���b�N�^��
	SetBlock(D3DXVECTOR3(550, 500, 0), D3DXVECTOR3(0, 0, 0.0f), 100, 50);

	//�G������Ă�u���b�N��
	SetBlock(D3DXVECTOR3(550, 750, 0), D3DXVECTOR3(0, 0, 0.0f), 100, 50);

	//��
	SetBlock(D3DXVECTOR3(1025, 150, 0), D3DXVECTOR3(0, 0, 0.0f), 75, 50);

	//�^��
	SetBlock(D3DXVECTOR3(800, 350, 0), D3DXVECTOR3(0, 0, 0.0f), 75, 50);

	//�^�񒆉�
	SetBlock(D3DXVECTOR3(1050, 600, 0), D3DXVECTOR3(0, 0, 0.0f), 70, 50);

	//��
	SetBlock(D3DXVECTOR3(800, 750, 0), D3DXVECTOR3(0, 0, 0.0f), 75, 50);

	//�E�u���b�N
	//��
	SetBlock(D3DXVECTOR3(1150, 150, 0), D3DXVECTOR3(0, 0, 0.0f), 450, 50);

	//�^��
	SetBlock(D3DXVECTOR3(1420, 400, 0), D3DXVECTOR3(0, 0, 0.0f), 500, 50);

	//��
	SetBlock(D3DXVECTOR3(1150, 650, 0), D3DXVECTOR3(0, 0, 0.0f), 500, 50);

#if 1
	//��
	//���[
	SetBlock(D3DXVECTOR3(0, 130, 0), D3DXVECTOR3(0, 0, 0.0f), 50, 900);

	//�^�񒆍�
	SetBlock(D3DXVECTOR3(500, 25, 0), D3DXVECTOR3(0, 0, 0.0f), 50, 900);

	//�^�񒆉E
	SetBlock(D3DXVECTOR3(1100, 150, 0), D3DXVECTOR3(0, 0, 0.0f), 50, 900);

	//�E�[
	SetBlock(D3DXVECTOR3(1870, 25, 0), D3DXVECTOR3(0, 0, 0.0f), 50, 1005);

#endif
	//�G�̔z�u
	//���̃u���b�N
	//��̓G
	SetEnemy(D3DXVECTOR3(440, 400, 0.0f), D3DXVECTOR3(ENEMY_SPEED, 0, 0.0f), 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//���̓G
	SetEnemy(D3DXVECTOR3(300, 750, 0.0f), D3DXVECTOR3(ENEMY_SPEED, 0, 0.0f), 0, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//�^�񒆃u���b�N
	//���̓G
	SetEnemy(D3DXVECTOR3(600, 750, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//�^�񒆂̓G
	SetEnemy(D3DXVECTOR3(600, 500, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//��̓G
	SetEnemy(D3DXVECTOR3(600, 250, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), NULL);

	//�E�̃u���b�N
	//�G
	SetEnemy(D3DXVECTOR3(1300, 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), RIGHT);

	//SetEnemy(D3DXVECTOR3(600, 900, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�A�C�e��
	//�R�C��
	//����
	for (int nCount = 0; nCount < 5; nCount++)
	{
		SetItem(D3DXVECTOR3(80 + (nCount * 60.0f), 1030, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(80 + (nCount * 60.0f), 980, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(80 + (nCount * 60.0f), 930, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(80 + (nCount * 60.0f), 880, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	//�^��
	//�΂߃R�C��
	for (int nCount = 0; nCount < 4; nCount++)
	{
		SetItem(D3DXVECTOR3(700 + (nCount * 20.0f), 1030 - (nCount * 80.0f), 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(880 + (nCount * 30.0f), 710 - (nCount * 50.0f), 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(1000 - (nCount * 30.0f), 510 - (nCount * 50.0f), 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(880 + (nCount * 30.0f), 310 - (nCount * 40.0f), 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}
	for (int nCount = 0; nCount < 8; nCount++)
	{
		SetItem(D3DXVECTOR3(1150 + (nCount * 80.0f), 150, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(1290 + (nCount * 75.0f), 390, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		SetItem(D3DXVECTOR3(1175 + (nCount * 80.0f), 650, 0.0f), ITEM_SCORE, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
	}

	//���ԉ����A�C�e��
	SetItem(D3DXVECTOR3(525, 1030, 0.0f), ITEM_TIME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	SetItem(D3DXVECTOR3(1050, 150, 0.0f), ITEM_TIME, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	//�S�[���̈ʒu
	SetGoal(D3DXVECTOR3(1200, 1030, 0.0f));
}

void Stage2(void)
{

	//�T�E���h�X�^�[�g
	PlaySound(SOUND_LABEL_BGM002);

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	//�u���b�N�z�u
	
	//�V��
	SetBlock(D3DXVECTOR3(0, -25, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1920, 50);

	//��
	SetBlock(D3DXVECTOR3(1870, 0, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 1080);
	
	//��
	SetBlock(D3DXVECTOR3(220, 780, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 80, 400);

	//��
	SetBlock(D3DXVECTOR3(220, 490, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 80, 155);

	//��
	SetBlock(D3DXVECTOR3(220, 150, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 80, 250);

	//��
	SetBlock(D3DXVECTOR3(300, 150, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 20, 1000);

	//��
	SetBlock(D3DXVECTOR3(960, 25, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 800);

	//���X�^�[�g
	SetBlock(D3DXVECTOR3(70, 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);

	//��
	SetBlock(D3DXVECTOR3(70, 780, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 60, 50);
	
	//��
	SetBlock(D3DXVECTOR3(70, 490, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	
	//��
	SetBlock(D3DXVECTOR3(70, 200, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);

	//��
	SetBlock(D3DXVECTOR3(70, 200, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);

	//��
	SetBlock(D3DXVECTOR3(320, 250, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 500, 50);

	//��
	SetBlock(D3DXVECTOR3(460, 600, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 500, 50);

	//��
	SetBlock(D3DXVECTOR3(320, 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 100, 50);

	for (int nCount = 0; nCount < 4; nCount++)
	{	
		SetBlock(D3DXVECTOR3(640 + (nCount * 320), 1030, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	}

	//��
	SetBlock(D3DXVECTOR3(1800, 750, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//��
	SetBlock(D3DXVECTOR3(1800, 470, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//��
	SetBlock(D3DXVECTOR3(1010, 660, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//��
	SetBlock(D3DXVECTOR3(1010, 360, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//��
	SetBlock(D3DXVECTOR3(1700, 190, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);
	//��
	SetBlock(D3DXVECTOR3(1500, 360, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);

	SetBlock(D3DXVECTOR3(1250, 190, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 50, 50);


	//�G
	SetEnemy(D3DXVECTOR3(260, 690, 0.0f), D3DXVECTOR3(0, 0, 0.0f),2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LEFT);

	//�G
	SetEnemy(D3DXVECTOR3(260, 390, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 2, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LEFT);

	//�G
	SetEnemy(D3DXVECTOR3(365, 250, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), RIGHT);

	//�G
	SetEnemy(D3DXVECTOR3(920, 350, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), LEFT);

	//�G
	SetEnemy(D3DXVECTOR3(1040, 590, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), RIGHT);

	//�G
	SetEnemy(D3DXVECTOR3(1040, 200, 0.0f), D3DXVECTOR3(0, 0, 0.0f), 1, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), RIGHT);

	//�S�[���̈ʒu
	SetGoal(D3DXVECTOR3(1100, 100, 0.0f));
}


GAME *GetGame(void)
{
	return &g_Game;
}

void SetPause(bool bpause)
{
	g_bPause = bpause;
}