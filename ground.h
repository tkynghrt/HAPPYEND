#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_GROUND 100

void InitGround(void);
void UninitGround(void);
void UpdateGround(void);
void DrawGround(void);

//è∞ÇÃç\ë¢ëÃ
struct GROUND {
	int Texture{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 size{};
	int num;
	bool use{};
};

GROUND* GetGround(void);
void SetGround(D3DXVECTOR2 pos);


