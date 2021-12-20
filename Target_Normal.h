#pragma once
#include "main.h"
#include "renderer.h"

#define TARGET_MAX 100

// ���ʂ̃^�[�Q�b�g�\����
struct TARGET_NORMAL
{
	int				Tex;
	int				Bom;
	bool			use;
	float			rot;
	int				flame;
	int				normal_target_count;
	D3DXVECTOR2		pos;
	D3DXVECTOR2		old_pos;
	D3DXVECTOR2		size;
	D3DXVECTOR2		vel;
};

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitTarget_Normal(void);
void UninitTarget_Normal(void);
void UpdateTarget_Normal(void);
void DrawTarget_Normal(void);

TARGET_NORMAL* GetTarget_Normal(void);