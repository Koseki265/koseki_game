
#ifndef _BULLET_H_
#define _BULLET_H_

#pragma once
#include "main.h"


//-----------------------------------------------------------------------------
// �}�N����`
//---------------------------------------------------------------------------
#define MOVE_BULLET (5)				//�e�̑��x
#define BULLET_SIZE (10)			//�e�̑傫��
#define MAX_BULLET (256)			//�e�̏��
#define MAX_BULLET_TYPE (2)			//�e�̎��
#define PLAYER_BULLET (1)			//�v���C���[�̒e�̃e�N�X�`��
#define ENEMY_BULLET (0)			//�G�̒e�̃e�N�X�`��
//�e�̏��
typedef enum
{
	BULLETTYPE_PLAYER = 0,	//�v���C���[�̒e
	BULLETTYPE_ENEMY,		//�G�̒e
	BULLETTYPE_MACHINE,		//�q�@�̒e
	BULLETTYPE_MAX,
}BULLETTYPE;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitBullet(void);
void UninitBullet(void);
void UpdateBullet(void);
void DrawBullet(void);
void SetBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nLife, BULLETTYPE Type);
void SetVertexBullet(int nIdx);

#endif _BULLET_H_