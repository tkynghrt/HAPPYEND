#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_ACCELE_BLOCK 100

HRESULT InitAcceleBlock(void);
void UninitAcceleBlock(void);
void UpdateAcceleBlock(void);
void DrawAcceleBlock(void);




//回数で壊れるブロックの構造体
struct ACCELE_BLOCK {
	int Texture{};
	int level{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 old_pos{};
	D3DXVECTOR2 size{};
	bool		use{};
	float		rot{};
};

ACCELE_BLOCK* GetAcceleBlock(void);
void SetAcceleBlock(D3DXVECTOR2 pos, int level);