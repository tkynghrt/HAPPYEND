//=============================================================================
//
// �o���b�g���� [bullet.h]
// Author : 
//
//=============================================================================
#pragma once

#include "main.h"
#include "renderer.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BULLET_SPEED	(4.0f)		// �{�[���̈ړ��X�s�[�h


// �o���b�g�\����
struct BALL
{
	int						mode;					// �{�[���̏��
	float					w, h;					// ���ƍ���
	D3DXVECTOR2				pos;					// �o���b�g�̍��W
	float					rot;					// �o���b�g�̉�]��
	D3DXVECTOR2				move;					// �o���b�g�̈ړ���
	int						texNo;					// ���Ԗڂ̃e�N�X�`���[���g�p����̂�
	int						texNo2;
	
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);

BALL *GetBall(void);
void SetBall(int mode,D3DXVECTOR2 pos, D3DXVECTOR2 power);


