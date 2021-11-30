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
#define BALL_SPEED	(4.0f)		// �{�[���̈ړ��X�s�[�h
#define BALL_SPEED_MAX	(52.0f)

// �{�[���\����
struct BALL
{
	int						mode;					// �{�[���̏��
	D3DXVECTOR2				size;					// ���ƍ���
	D3DXVECTOR2				pos;					// �o���b�g�̍��W
	D3DXVECTOR2				old_pos;					// �o���b�g�̍��W
	float					rot;					// �o���b�g�̉�]��
	D3DXVECTOR2				move;					// �o���b�g�̈ړ���
	float					move_angle;
	int						BallTexture;
	int						ShadowTexture;
	int						Speed_Level;
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

D3DXVECTOR2* GetBallPos();
D3DXVECTOR2* GetBallSize();



