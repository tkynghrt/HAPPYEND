#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_TARGET_COUNT 100


//�񐔂ŉ���^�[�Q�b�g�̍\����
struct TARGET_COUNT 
{
	int				Tex;
	int				Count;
	bool			use;
	float			rot;
	D3DXVECTOR2		pos;
	D3DXVECTOR2		old_pos;
	D3DXVECTOR2		size;
	D3DXVECTOR2		vel;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTarget_Count(void);
void UninitTarget_Count(void);
void UpdateTarget_Count(void);
void DrawTarget_Count(void);

TARGET_COUNT* GetTarget_Count(void);
