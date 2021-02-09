//-----------------------------------------------------------------------------
//
// �^�C�g���̏���
//Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#ifndef _STAGESELECT_H_
#define _STAGESELECT_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;
	D3DXCOLOR col;
}STAGESELECT;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

HRESULT InitStage(void);
void UninitStage(void);
void UpdateStage(void);
void DrawStage(void);
void SetVertexStage(int nIdx);

#endif _STAGESELECT_H_
