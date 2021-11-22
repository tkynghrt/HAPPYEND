#pragma once
#include "main.h"
#include "renderer.h"

void InitAcceleBlock(void);
void UninitAccelBlock(void);
void UpdateAcceleBlock(void);
void DrawAcceleBlock(void);

//����̑��x�ŉ���u���b�N����
#define MAX_ACCELE_BLOCK	10

//�񐔂ŉ���u���b�N�̍\����
struct ACCELE_BLOCK {
	int Texture;
	int HitCount;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 old_pos;
	D3DXVECTOR2 size;
	bool		Use;
	float		rot;
};

ACCELE_BLOCK* GetAcceleBlock(void);