#pragma once
#include "main.h"
#include "renderer.h"

void InitCountBlock(void);
void UninitCountBlock(void);
void UpdateCountBlock(void);
void DrawCountBlock(void);

void setCountBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity);

//�ړ�����u���b�N�̍\����
struct COUNTBLOCK {
	int Texture;
	int HitCount;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 velocity;
	bool		Use;
	float		rot;
};


