#pragma once
#include "main.h"
#include "renderer.h"

void InitGround(void);
void UninitGround(void);
void UpdateGround(void);
void DrawGround(void);

//è∞ÇÃç\ë¢ëÃ
struct GROUND {
	int Texture;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
};

GROUND* GetGround(void);


