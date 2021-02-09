//-----------------------------------------------------------------------------
//
// �`���[�g���A���̏���
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------

#ifndef _RANKING_H_
#define _RANKING_H_

#include "main.h"
//
//
//
typedef enum
{
	SELECT_RETRY = 0,		//���g���C
	SELECT_STAGESELECT,		//�X�e�[�W�I�����
	SELECT_QUIT,			//�I��
	SELECT_MAX
}SELECT;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

HRESULT InitHighScore(void);
void UninitHighScore(void);
void UpdateHighScore(void);
void DrawHighScore(void);
void SetVertexHighScore(int nIdx,int nNumber);

#endif _RANKING_H_
