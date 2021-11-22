#pragma once
#include "main.h"
#include "renderer.h"

void InitCountBlock(void);
void UninitCountBlock(void);
void UpdateCountBlock(void);
void DrawCountBlock(void);

//回数で壊れるブロック総数
#define MAX_COUNT_BLOCK	10


void setCountBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity);

//回数で壊れるブロックの構造体
struct COUNT_BLOCK {
	int Texture;
	int HitCount;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 old_pos;
	D3DXVECTOR2 size;
	bool		Use;
	float		rot;
};

COUNT_BLOCK* GetCountBlock(void);

