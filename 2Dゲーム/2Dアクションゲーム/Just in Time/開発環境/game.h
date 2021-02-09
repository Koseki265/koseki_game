//-----------------------------------------------------------------------------
//
// �_�C���N�g���̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//-----------------------------------------------------------------------------
// �I��
//-----------------------------------------------------------------------------
typedef enum
{
	STAGE_1 = 0,
	STAGE_2,
	STAGE_MAX,
}STAGE;

//�\����
typedef struct
{
	STAGE stage;
}GAME;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

HRESULT InitGame(void);
void UninitGame(void);
void UpdateGame(void);
void DrawGame(void);
void Stage1(void);
void Stage2(void);
GAME *GetGame(void);
void SetPause(bool bPause);

#endif
