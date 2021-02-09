//-----------------------------------------------------------------------------
//
// �_�C���N�g���̏���
//Author:KosekiYuto
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
#include "Effect.h"
#include "Machine.h"
#include "pause.h"
#include "Time.h"
#include "EnemyCounter.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
bool g_bPause = false;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitGame(void)
{
	//�w�i�̏�����
	InitBg();

	//�|���S���̏���������
	InitPlayer();

	//�q�@�̏���������
	InitMachine();

	//�e�̏���������
	InitBullet();

	//�G�t�F�N�g�̏���������
	InitEffect();

	//�G�̏���������
	InitEnemy();
	
	//�����̏�����
	InitExplosion();

	//�X�R�A�̏�����
	InitScore();

	//���Ԃ̏�����
	InitTime();

	//�G�̃J�E���^�[�̏�����
	InitEnemyCounter();

	//�|�[�Y�̏���������
	InitPause();

	//�T�E���h�X�^�[�g
	PlaySound(SOUND_LABEL_BGM002);

	return S_OK;
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void UninitGame(void)
{
	//�T�E���h�X�g�b�v
	StopSound();

	//�|�[�Y�̏I������
	UninitPause();

	//�X�R�A�̏I������
	UninitScore();

	//���Ԃ̏I������
	UninitTime();

	//�G�̃J�E���^�[�̏I������
	UninitEnemyCounter();

	//���j�̏I������
	UninitExplosion();

	//�G�̏I������
	UninitEnemy();

	//�G�t�F�N�g�̏I������
	UninitEffect();

	//�e�̏I������
	UninitBullet();

	//�q�@�̏I������
	UninitMachine();

	//�v���C���[�̏I������
	UninitPlayer();
	
	//�w�i�̏I��
	UninitBg();
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateGame(void)
{

	FADE *pFade;
	pFade = GetFade();

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
		//�w�i�̍X�V����
		UpdateBg();

		//�|���S���̍X�V����
		UpdatePlayer();

		//�q�@�̍X�V����
		UpdateMachine();

		//�e�̍X�V����
		UpdateBullet();

		//�G�t�F�N�g�̍X�V����
		UpdateEffect();

		//�G�̍X�V����
		UpdateEnemy();

		//�G�̍X�V����
		UpdateExplosion();

		//�X�R�A�̍X�V����
		UpdateScore();

		//���Ԃ̍X�V����
		UpdateTime();

		//�G�̃J�E���^�[�̍X�V����
		UpdateEnemyCounter();
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
	//�w�i�̕`��
	DrawBg();

	//�|���S���̕`�揈��
	DrawPlayer();

	//�q�@�̕`�揈��
	DrawMachine();

	//�e�̕`�揈��
	DrawBullet();

	//�G�t�F�N�g�̕`�揈��
	DrawEffect();

	//�G�̕`�揈��
	DrawEnemy();

	//�����̕`�揈��
	DrawExplosion();

	//�X�R�A�̕`�揈��
	DrawScore();

	//���Ԃ̕`�揈��
	DrawTime();

	//�G�̃J�E���^�[�̕`�揈��
	DrawEnemyCounter();

	if (g_bPause == true)
	{
		DrawPause();
	}

}

void SetPause(bool bpause)
{
	g_bPause = bpause;
}