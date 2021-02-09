//-----------------------------------------------------------------------------
//
// �A�C�e���̏���
// Author : Yuto Koseki 
//
//-----------------------------------------------------------------------------
#include "goal.h"
#include "Player.h"
#include "fade.h"

//-----------------------------------------------------------------------------
//�O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_pTextureGoal = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffGoal = NULL;
GOAL g_nGoal;									//�S�[���̏��
int g_nFadeCounterGoal;							//�S�[�����Ă���̃t�F�[�h�ɓ���܂ł̎���
int g_nPatternGoalAnim;							//�A�j���[�V�����p�^�[��
int g_nGoalAnimCounter;							//�A�j���[�V�����J�E���^�[


//-----------------------------------------------------------------------------
// �S�[���̂̒��_���W�̐ݒ�
//-----------------------------------------------------------------------------
void SetVertexGoal(void)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_nGoal.pos.x - GOAL_SIZEX, g_nGoal.pos.y, 0);
	pVtx[1].pos = D3DXVECTOR3(g_nGoal.pos.x - GOAL_SIZEX, g_nGoal.pos.y - GOAL_SIZEY, 0);
	pVtx[2].pos = D3DXVECTOR3(g_nGoal.pos.x + GOAL_SIZEX, g_nGoal.pos.y, 0);
	pVtx[3].pos = D3DXVECTOR3(g_nGoal.pos.x + GOAL_SIZEX, g_nGoal.pos.y - GOAL_SIZEY, 0);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();
}


//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitGoal(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\goal.png", &g_pTextureGoal);

	//�\���̏�����

	g_nGoal.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	g_nGoal.bUse = false;

	g_nFadeCounterGoal = 0;
	g_nPatternGoalAnim = 0;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffGoal, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	//���_���W
	SetVertexGoal();

	//rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	//���_�̃J���[�ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, 255);
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, 255);

	//���_�̏��̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f, 0.0f);


	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitGoal(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffGoal != NULL)
	{
		g_pVtxBuffGoal->Release();
		g_pVtxBuffGoal = NULL;
	}
	//�e�N�X�`���̊J��

	if (g_pTextureGoal != NULL)
	{
		g_pTextureGoal->Release();
		g_pTextureGoal = NULL;
	}

}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateGoal(void)
{
	GOAL *pGoal;
	pGoal = &g_nGoal;

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	VERTEX_2D *pVtx;

	g_nGoalAnimCounter++;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffGoal->Lock(0, 0, (void**)&pVtx, 0);

	if ((g_nGoalAnimCounter % 10) == 0)
	{
		g_nPatternGoalAnim = (g_nPatternGoalAnim + 1) % 2;
	}


	//���_�̏��̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f + (0.5f * g_nPatternGoalAnim), 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + (0.5f * g_nPatternGoalAnim), 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.5f + (0.5f * g_nPatternGoalAnim), 1.0f);
	pVtx[3].tex = D3DXVECTOR2(0.5f + (0.5f * g_nPatternGoalAnim), 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffGoal->Unlock();

	//�S�[��������
	if (pGoal->bUse == true)
	{//�����蔻��
		if (pGoal->pos.y - GOAL_SIZEY < pPlayer->pos.y && pGoal->pos.y > pPlayer->pos.y - pPlayer->fHeight &&
			pGoal->pos.x < pPlayer->pos.x + pPlayer->fWidth && pGoal->pos.x > pPlayer->pos.x - pPlayer->fWidth)
		{
			pPlayer->bDisp = true;
			pGoal->bUse = false;
		}
	}
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawGoal(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	GOAL *pItem;
	pItem = &g_nGoal;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffGoal, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	//�|���S���̕`��

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_pTextureGoal);

	if (pItem->bUse == true)
	{
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//-----------------------------------------------------------------------------
// �S�[���̐ݒ�
//-----------------------------------------------------------------------------
void SetGoal(D3DXVECTOR3 pos)
{

	GOAL *pGoal;
	pGoal = &g_nGoal;

	if (pGoal->bUse == false)
	{
		//�ʒu
		pGoal->pos = pos;

		//���_���W
		SetVertexGoal();

		//�g���Ă����Ԃ�
		pGoal->bUse = true;

	}
}
//
GOAL *GetGoal(void)
{
	return &g_nGoal;
}

