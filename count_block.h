#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_COUNT_BLOCK 100

HRESULT InitCountBlock(void);
void UninitCountBlock(void);
void UpdateCountBlock(void);
void DrawCountBlock(void);

void SetCountBlock(D3DXVECTOR2 pos,int count);

//回数で壊れるブロックの構造体
struct COUNT_BLOCK {
	int Texture{};
	int HitCount{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 old_pos{};
	D3DXVECTOR2 size{};
	bool		use{};
	float		rot{};
};

COUNT_BLOCK* GetCountBlock(void);

