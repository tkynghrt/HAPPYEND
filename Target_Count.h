#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_TARGET_COUNT 100


//回数で壊れるターゲットの構造体
struct TARGET_COUNT 
{
	int				Tex;
	int				Count;
	bool			use;
	float			rot;
	D3DXVECTOR2		pos;
	D3DXVECTOR2		old_pos;
	D3DXVECTOR2		size;
	D3DXVECTOR2		vel;
};

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitTarget_Count(void);
void UninitTarget_Count(void);
void UpdateTarget_Count(void);
void DrawTarget_Count(void);

TARGET_COUNT* GetTarget_Count(void);
