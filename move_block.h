#pragma once
#include "main.h"
#include "renderer.h"

HRESULT InitMoveBlock(void);
void UninitMoveBlock(void);
void UpdateMoveBlock(void);
void DrawMoveBlock(void);


void setMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity);

//移動するブロックの構造体
struct MOVE_BLOCK {
	int Texture{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 old_pos{};
	D3DXVECTOR2 size{};
	D3DXVECTOR2 velocity{};
	bool		Use{};
	float		rot{};
};



MOVE_BLOCK* GetMoveBlock(void);


