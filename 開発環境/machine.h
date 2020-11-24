#ifndef _MACHINE_H_
#define _MACHINE_H_

#pragma once
#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MACHINE_SIZE (20)
#define MOVE_MACHINE (3)
#define MAX_MACHINE (50) //�q�@�̏��

//-----------------------------------------------------------------------------
// ���
//-----------------------------------------------------------------------------
typedef enum
{
	MACHINESTATE_APPEAR = 0,
	MACHINESTATE_NORMAL,
	MACHINESTATE_BREAK,
	MACHINESTATE_MAX
}MACHINESTATE;

//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;		//���݂̈ʒu
	D3DXVECTOR3 posDest;	//�ړI�̈ʒu
	D3DXVECTOR3 move;		//�ړ����x
	bool bUse;
	MACHINESTATE State;
}MACHINE;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitMachine(void);
void UninitMachine(void);
void UpdateMachine(void);
void DrawMachine(void);
MACHINE *GetMachine(void);
void SetPosMachine(int nIdx, D3DXVECTOR3 pos);
void SetBulletMachine(int nIdx);
void SetMachine(D3DXVECTOR3 pos);
void SetVertexMachine(int nIdx);


#endif _MACHINE_H_

