//-----------------------------------------------------------------------------
//
// �G�̏���
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "main.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MAX_ENEMY_TYPE (3)
#define ENEMY_SIZE_TYPE0 (D3DXVECTOR3(50 , 60 , 0.0f))
#define ENEMY_SIZE_TYPE1 (D3DXVECTOR3(40 , 60 , 0.0f))
#define ENEMY_SIZE_TYPE2 (D3DXVECTOR3(40 , 90 , 0.0f))
#define ENEMY_SPEED (3)
#define MAX_ENEMY (256)			//�G�̏��
#define PLAYER_HITAREA (5)
#define ENEMY_COUNT (45)
#define RIGHT (0)				//����
#define LEFT (1)				//����
#define	UP (2)					//����
#define UNBER (3)				//����
#define BULLETFIRING (100)

//-----------------------------------------------------------------------------
// ���
//-----------------------------------------------------------------------------
typedef enum
{
	ENEMYSTATE_NORMAL = 0,
	ENEMYSTATE_DAMAGE,
}ENEMYSTATE;

//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	D3DXVECTOR3 move;	//�������x
	float fWidth;		//��
	float fHeight;		//����
	int nType;			//���
	ENEMYSTATE State;	//���
	int nCounterState;	//��ԃJ�E���^�[
	int nLife;			//�̗�
	int g_nPatternAnimEnemyV;	
	D3DXCOLOR col;		//�F
	bool bUse;			//�g�p���
}ENEMY;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitEnemy(void);
void UninitEnemy(void);
void UpdateEnemy(void);
void DrawEnemy(void);
void SetEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 move, int nType, D3DXCOLOR col, int nPatternAnimEnemyV);
void SetVertexEnemy(int nIdx);
bool HitEnemy(int nIdx, int nDamage);
ENEMY*GetEnemy(void);

#endif _ENEMY_H_
