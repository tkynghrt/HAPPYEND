#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_COIN 300


void InitCoin(void);
void UninitCoin(void);
void UpdateCoin(void);
void DrawCoin(void);

void SetCoin(D3DXVECTOR2 pos);

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
