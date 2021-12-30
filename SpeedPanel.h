
#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_Panel 100
#define SPEED_UP   1
#define SPEED_DOWN 2

void InitSpeedPanel(void);
void UninitSpeedPanel(void);
void UpdateSpeedPanel(void);
void DrawSpeedPanel(void);

void SetSpeedPanel(D3DXVECTOR2 pos, int type);

//回数で壊れるブロックの構造体
struct SPEED_PANEL {
	int Texture;
	int type;			//スピードダウンかアップかの判別用
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	bool		use;
	float		rot;
};

SPEED_PANEL* GetSpeedPanel(void);
