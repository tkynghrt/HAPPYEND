#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_RAMDOM_SHOT_BLOCK 100

HRESULT InitRamdom_Shot_Block(void);
void UninitRamdom_Shot_Block(void);
void UpdateRamdom_Shot_Block(void);
void DrawRamdom_Shot_Block(void);

void SetRamdom_Shot_Block(D3DXVECTOR2 pos);

//回数で壊れるブロックの構造体
struct RAMDOM_SHOT_BLOCK {
	int Texture{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 size{};
	bool		use{};
	float		rot{};
};

RAMDOM_SHOT_BLOCK* GetRamdom_Shot_Block(void);