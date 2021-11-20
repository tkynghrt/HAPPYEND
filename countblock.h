#pragma once
#include "main.h"
#include "renderer.h"

void InitCountBlock(void);
void UninitCountBlock(void);
void UpdateCountBlock(void);
void DrawCountBlock(void);

//回数で壊れるブロック総数
#define MAX_COUNTBLOCK	10

void setCountBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity);

//移動するブロックの構造体
struct COUNTBLOCK {
	int Texture;
	int HitCount;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 velocity;
	bool		Use;
	float		rot;
};


