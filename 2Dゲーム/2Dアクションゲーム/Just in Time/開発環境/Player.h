//-----------------------------------------------------------------------------
//
//�v���C���[�̏���
//Author : Yuto Koseki
//
//-----------------------------------------------------------------------------
#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "main.h"


//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define MOVE_SPEED (4)			//�ړ����x
#define GRAVITY		(2.6f)		//�d��
#define PLAYER_SIZEX (35)		//�v���C���[�̕�
#define PLAYER_SIZEY (75)		//�v���C���[�̍���
#define JAMP (42)				//�W�����v��
#define ANIM_SPEED (5)			//�A�j���[�V�����X�s�[�h
#define ANIM_SLOW_SPEED (20)	//�x���A�j���[�V�����X�s�[�h
#define LOW_JUMP (30)			//�Ⴂ�W�����v
#define MOVE_SLOW_SPEED (1)		//�x���ړ����x


//-----------------------------------------------------------------------------
//�v���C���[�̏��
//-----------------------------------------------------------------------------
typedef enum
{
	PLAYERSTATE_NORMAL = 0,		//�ʏ�
	PLAYERSTATE_DAMAGE,			//�_���[�W
	PLAYERSTATE_INVINCIBLE,		//���G
	PLAYERSTATE_FREEZE,			//����
	PLAYERSTATE_SLOW,			//�X���E
	PLAYERSTATE_MAX,			
}PLAYERSTATE;

//-----------------------------------------------------------------------------
// �\����
//-----------------------------------------------------------------------------
typedef struct
{
	D3DXVECTOR3 pos;	//���݂̈ʒu
	D3DXVECTOR3 posOld;	//�O��̈ʒu
	D3DXVECTOR3 move;	//�ړ���
	PLAYERSTATE State;	//�v���C���[�̏��
	float fWidth;		//��
	float fHeight;		//����
	int Touchi;			//�n�ʂɂ������ǂ���
	bool bDisp;			//�\�����Ă邩�ǂ���
	bool bJump;			//�W�����v���Ă邩�ǂ���
}PLAYER;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------
HRESULT InitPlayer(void);
void UninitPlayer(void);
void UpdatePlayer(void);
void DrawPlayer(void);
PLAYER *GetPlayer(void);
bool HitPlayer(int nDamage);
void SetVertexPlayer(void);


#endif
