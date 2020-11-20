//-----------------------------------------------------------------------------
//
// ���U���g��ʂ̏���
// Author:KosekiYuto
//
//-----------------------------------------------------------------------------

#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"

//
typedef enum
{
	RESULT_CLEAR = 0,
	RESULT_GAMEOVER,
	RESULT_MAX
}RESULT_STATE;

//-----------------------------------------------------------------------------
// �v���g�^�C�v�錾
//-----------------------------------------------------------------------------

HRESULT InitResult(void);
void UninitResult(void);
void UpdateResult(void);
void DrawResult(void);
void SetVertexResult(int nIdx);

#endif _RESULT_H_
