#pragma once
#include "main.h"
#include "renderer.h"

HRESULT InitMoveBlock_X(void);
void UninitMoveBlock_X(void);
void UpdateMoveBlock_X(void);
void DrawMoveBlock_X(void);


void setMoveBlock_X(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity);

//移動するブロックの構造体
struct MOVE_BLOCK_X {
	int Texture{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 old_pos{};
	D3DXVECTOR2 size{};
	D3DXVECTOR2 velocity{};
	int MoveCount{};
	bool		Use{};
	float		rot{};
};



MOVE_BLOCK_X* GetMoveBlock_X(void);


