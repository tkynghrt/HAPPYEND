#pragma once
#include "main.h"
#include "renderer.h"

void InitAcceleBlock(void);
void UninitAccelBlock(void);
void UpdateAcceleBlock(void);
void DrawAcceleBlock(void);

//特定の速度で壊れるブロック総数
#define MAX_ACCELE_BLOCK	10

//回数で壊れるブロックの構造体
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