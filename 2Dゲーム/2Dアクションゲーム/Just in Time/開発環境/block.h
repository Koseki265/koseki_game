//-----------------------------------------------------------------------------
//
// �u���b�N�̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MAX_BLOCK (128)
#define MOVE_BLOCK (2)

//----------------------------------------------------------------------------
// 
//-----------------------------------------------------------------------------
typedef enum
{
	TOUCHING_PLAYER = 0,
	TOUCHING_ENEMY,
	TOUCHING_BULLET,
	TOUCHING_BOLOCK_MAX,
}TOUCHING_BULOCK;
//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld; //�O�̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	D3DXVECTOR2 tex;	//�e�N�X�`��
	float fWidth;		//��
	float fHeight;		//����
	bool bUse;			//�g�p���Ă邩�ǂ���
}BLOCK;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);
void SetBlock(D3DXVECTOR3 pos, D3DXVECTOR3 move, float Width, float fHeight);
void SetVertexBlock(int nIdx);
bool ColisionBlock(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, float fWidth, float fHeight, TOUCHING_BULOCK nType);
BLOCK *GetBlock(void);


#endif _BLOCK_H_