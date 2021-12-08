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
#define BALL_SPEED	(2.0f)		// �{�[���̈ړ��X�s�[�h
#define BALL_SPEED_MAX	(52.0f)

// �{�[���\����
struct BALL
{
	D3DXVECTOR2				size;					// ���ƍ���
	D3DXVECTOR2				pos;					// �o���b�g�̍��W
	D3DXVECTOR2				old_pos;				//�ߋ��� �o���b�g�̍��W
	float					rot;					// �o���b�g�̉�]��
	D3DXVECTOR2				velocity;					// �o���b�g�̈ړ���
	float					speed;
	int						BallTexture;
	int						Speed_Level;
	bool					Use;
	int						Judgment;
	int						judgment_time;
};



//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitBall(void);
void UninitBall(void);
void UpdateBall(void);
void DrawBall(void);

BALL *GetBall(void);



