#pragma once
#include "main.h"
#include "renderer.h"

void InitCountBlock(void);
void UninitCountBlock(void);
void UpdateCountBlock(void);
void DrawCountBlock(void);

//�񐔂ŉ���u���b�N����
#define MAX_COUNTBLOCK	10


void setCountBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity);

//�񐔂ŉ���u���b�N�̍\����
struct COUNTBLOCK {
	int Texture;
	int HitCount;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	bool		Use;
	float		rot;
};

COUNTBLOCK* GetCountBlock(void);

