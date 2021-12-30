#pragma once

#include "main.h"
#include "renderer.h"

#define MAX_WARP 4

HRESULT InitWarp(void);
void UninitWarp(void);
void UpdateWarp(void);
void DrawWarp(void);

void SetWarp(D3DXVECTOR2 pos);

//�񐔂ŉ���u���b�N�̍\����
struct WARP {
	int Texture{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 size{};
	bool		use{};
};

WARP* GetWarp(void);