#include "machine.h"
#include "Player.h"
#include "sound.h"
#include "Bullet.h"
#include "input.h"

//-----------------------------------------------------------------------------
// �O���[�o���ϐ�
//-----------------------------------------------------------------------------
LPDIRECT3DTEXTURE9 g_apTextureMachine = NULL;
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffMachine = NULL;
MACHINE g_aMachine[MAX_MACHINE];						//�q�@�̏��
int nMachineCounter;

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
HRESULT InitMachine(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	//�f�o�C�X�̎擾
	pDevice = GetDevice();

	//�e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data\\TEXTURE\\player000.png", &g_apTextureMachine);
	
	//�\���̏�����
	for (int nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++)
	{
		g_aMachine[nCntMachine].pos = D3DXVECTOR3(1920.0f, 0.0f, 0.0f);
		g_aMachine[nCntMachine].move = D3DXVECTOR3(1920.0f, 0.0f, 0.0f);
		g_aMachine[nCntMachine].bUse = false;
		g_aMachine[nCntMachine].State = MACHINESTATE_APPEAR;
	}

	nMachineCounter = 0;

	//���_�o�b�t�@�̐���
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * MAX_MACHINE, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &g_pVtxBuffMachine, NULL)))
	{
		return E_FAIL;
	}

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++, pVtx += 4)
	{
		//���_���W
		SetVertexMachine(nCntMachine);

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
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

	}
	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMachine->Unlock();

	return S_OK;
}

//-----------------------------------------------------------------------------
//�@�I������
//-----------------------------------------------------------------------------
void UninitMachine(void)
{
	//�o�b�t�@�̊J��
	if (g_pVtxBuffMachine != NULL)
	{
		g_pVtxBuffMachine->Release();
		g_pVtxBuffMachine = NULL;
	}
	
	if (g_apTextureMachine != NULL)
	{
		g_apTextureMachine->Release();
		g_apTextureMachine = NULL;
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void UpdateMachine(void)
{
	MACHINE *pMachine;
	pMachine = &g_aMachine[0];

	PLAYER *pPlayer;
	pPlayer = GetPlayer();

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++, pMachine++)
	{
		if (pMachine->bUse == true)
		{
			switch (pMachine->State)
			{
			case MACHINESTATE_APPEAR:
				//�ʒu�̍X�V
				pMachine->pos.y += 5;

				if (pMachine->pos.y > SCREEN_HEIGHT)
				{
					pMachine->State = MACHINESTATE_BREAK;
				}


				break;
			
			case MACHINESTATE_NORMAL:

				//����
				pMachine->pos.x += (pMachine->posDest.x - pMachine->pos.x) * 0.09f;
				pMachine->pos.y += (pMachine->posDest.y - pMachine->pos.y) * 0.09f;

				break;

			case MACHINESTATE_BREAK:

				pMachine->bUse = false;

				break;

			}
			SetVertexMachine(nCntMachine);
		}

		pVtx += 4;
	}

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMachine->Unlock();
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void DrawMachine(void)
{
	//���[�J��
	LPDIRECT3DDEVICE9 pDevice;

	MACHINE *pMachine;
	pMachine = &g_aMachine[0];

	//�f�o�C�X�̎擾
	pDevice = GetDevice();			

	//���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffMachine, 0, sizeof(VERTEX_2D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	
	for (int nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++, pMachine++)
	{
		if (pMachine->bUse == true)
		{
			//�e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, g_apTextureMachine);

			//�|���S���̕`��
			pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntMachine * 4, 2);
		}
	}
}

//-----------------------------------------------------------------------------
// �q�@�̒��_���W�ݒ�
//-----------------------------------------------------------------------------
void SetVertexMachine(int nIdx)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//���_���W
	pVtx[0].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x - MACHINE_SIZE, g_aMachine[nIdx].pos.y + MACHINE_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x - MACHINE_SIZE, g_aMachine[nIdx].pos.y - MACHINE_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x + MACHINE_SIZE, g_aMachine[nIdx].pos.y + MACHINE_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x + MACHINE_SIZE, g_aMachine[nIdx].pos.y - MACHINE_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMachine->Unlock();

}

//-----------------------------------------------------------------------------
// �q�@�̐ݒ�
//-----------------------------------------------------------------------------
void SetMachine(D3DXVECTOR3 pos)
{
	MACHINE *pMachine;
	pMachine = &g_aMachine[0];

	int nCntMachine;

	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntMachine = 0; nCntMachine < MAX_MACHINE; nCntMachine++, pMachine++)
	{
		if (pMachine->bUse == false)
		{
			//�ʒu
			pMachine->pos = pos;

			pMachine->State = MACHINESTATE_APPEAR;

			//���_���W
			SetVertexMachine(nCntMachine);

			//�g���Ă����Ԃ�
			pMachine->bUse = true;

			break;
		}
		pVtx += 4;
	}

	g_pVtxBuffMachine->Unlock(); //�A�����b�N

}

//-----------------------------------------------------------------------------
// �q�@�̏ꏊ�ݒ�
//-----------------------------------------------------------------------------
void SetPosMachine(int nIdx, D3DXVECTOR3 pos)
{
	VERTEX_2D *pVtx;

	//���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffMachine->Lock(0, 0, (void**)&pVtx, 0);

	pVtx += nIdx * 4;

	//g_aMachine[nIdx].pos = D3DXVECTOR3(500, -100, 0.0f);

	//���_���W
	g_aMachine[nIdx].posDest = pos;

	pVtx[0].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x - MACHINE_SIZE, g_aMachine[nIdx].pos.y + MACHINE_SIZE, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x - MACHINE_SIZE, g_aMachine[nIdx].pos.y - MACHINE_SIZE, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x + MACHINE_SIZE, g_aMachine[nIdx].pos.y + MACHINE_SIZE, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(g_aMachine[nIdx].pos.x + MACHINE_SIZE, g_aMachine[nIdx].pos.y - MACHINE_SIZE, 0.0f);

	//���_�o�b�t�@���A�����b�N����
	g_pVtxBuffMachine->Unlock();

}

//-----------------------------------------------------------------------------
// �q�@�̒e
//-----------------------------------------------------------------------------
void SetBulletMachine(int nIdx)
{
	SetBullet(g_aMachine[nIdx].pos, D3DXVECTOR3(0.0f, -11.5f, 0.0f), BULLETTYPE_MACHINE , BULLETTYPE_MACHINE);
}

MACHINE *GetMachine(void)
{
	return &g_aMachine[0];
}

