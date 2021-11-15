#pragma once
#include "main.h"
#include "renderer.h"

void InitTarget(void);
void UninitTarget(void);
void UpdateTarget(void);
void DrawTarget(void);

struct TARGET {
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 velocity;
	bool Use;
};