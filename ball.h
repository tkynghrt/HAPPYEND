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
	float					rot;					// �o���b�g�̉�]��
	D3DXVECTOR2				move;					// �o���b�g�̈ړ���
	int						BallTexture;
	int						ShadowTexture;
};

//�{�[���̃X�s�[�h���x��
typedef enum {
	level_1,
	level_2,
	level_3,
	level_4,
	level_5,

}SPEED_LEVEL;

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

SPEED_LEVEL Speed_Level(D3DXVECTOR2 ball_move);



