//-----------------------------------------------------------------------------
//
// �w�i�̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#ifndef _BG_H_
#define _BG_H_

#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MOVE_BG (2)		//�w�i�̈ړ���
#define MAX_BG (2)		//�w�i�̖���

//-----------------------------------------------------------------------------
//�\����
//-----------------------------------------------------------------------------

typedef struct
{
	int nType;
}BG;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitBg(void);
void UninitBg(void);
void UpdateBg(void);
void DrawBg(void);
void SetVertexBg(int nIdx);

#endif
