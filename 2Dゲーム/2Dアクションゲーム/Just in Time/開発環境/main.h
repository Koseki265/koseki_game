//-----------------------------------------------------------------------------
//
// �_�C���N�g���̏���
// Author : Yuto Koseki
//
//-----------------------------------------------------------------------------

#ifndef _MAIN_H_
#define _MAIN_H_

#pragma once
#define DIRECTINPUT_VERSION (0x800)
#include "dinput.h"										//���͏����ɕK�v
#include <windows.h>
#include "d3dx9.h"
#include "xaudio2.h"									//�T�E���h�Đ��ɕK�v			

#pragma comment(lib,"dinput8.lib")						//���͏����ɕK�v
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"winmm.lib")

//�}�N����`
#define CLASS_NAME "WindowClass"						//�E�C���h�E�N���X�̖��O
#define WINDOW_NAME "justintime"				//�E�C���h�E�̖��O
#define SCREEN_WIDTH (1920)								//�X�N���[���̕�
#define SCREEN_HEIGHT (1080)							//�X�N���[���̍���
#define FVF_VERTEX_2D (D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1)

//�\����
typedef struct
{
	D3DXVECTOR3 pos;
	float rhw;
	D3DCOLOR col;
	D3DXVECTOR2 tex;
}VERTEX_2D;

//���[�h�̎��
typedef enum
{
	MODE_TITLE = 0,		//�^�C�g�����
	MODE_TUTORIAL,		//�`���[�g���A�����
	MODE_STAGESELECT,	//�X�e�[�W�I�����
	MODE_GAME,			//�Q�[�����
	MODE_RESULT,		//���U���g���
	MODE_HIGHSCORE,		//�n�C�X�R�A���
	MODE_MAX
}MODE;

//�O���[�o���ϐ�

//�v���g�^�C�v�錾
LPDIRECT3DDEVICE9 GetDevice(void);
void SetMode(MODE mode);
MODE GetMode(void);

#endif