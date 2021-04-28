//-----------------------------------------------------------------------------
//
// �`���[�g���A���̏���
// Author:KosekiYuto
//
//-----------------------------------------------------------------------------

#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 pos;	//�ʒu
	bool bDisp;			//�\��ON/OFF

}TUTORIAL;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

HRESULT InitTutorial(void);
void UninitTutorial(void);
void UpdateTutorial(void);
void DrawTutorial(void);
void SetVertexTutorial(int nIdx);

#endif _TUTORIAL_H_

