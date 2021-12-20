#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_MOVE_BLOCK 100

HRESULT InitMoveBlock(void);
void UninitMoveBlock(void);
void UpdateMoveBlock(void);
void DrawMoveBlock(void);

//移動するブロックの構造体
struct MOVE_BLOCK {
	int Texture{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 old_pos{};
	D3DXVECTOR2 size{};
	D3DXVECTOR2 velocity{};
	int			MoveCount{};
	bool		use{};
	float		rot{};
};



MOVE_BLOCK* GetMoveBlock(void);

void SetMoveBlock(D3DXVECTOR2 pos);