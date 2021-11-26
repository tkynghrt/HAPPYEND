#pragma once
#include "main.h"
#include "renderer.h"

HRESULT InitAcceleBlock(void);
void UninitAcceleBlock(void);
void UpdateAcceleBlock(void);
void DrawAcceleBlock(void);




//�񐔂ŉ���u���b�N�̍\����
struct ACCELE_BLOCK {
	int Texture{};
	int level{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 old_pos{};
	D3DXVECTOR2 size{};
	bool		Use{};
	float		rot{};
};

ACCELE_BLOCK* GetAcceleBlock(void);