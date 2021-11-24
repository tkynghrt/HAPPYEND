#pragma once
#include "main.h"
#include "renderer.h"

void InitCoin(void);
void UninitCoin(void);
void UpdateCoin(void);
void DrawCoin(void);




void setCoin(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity);

//回数で壊れるブロックの構造体
struct COIN {
	int Texture;
	int point;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	bool		Use;
	float		rot;
};

COIN* GetCoin(void);
