#pragma once
#include "main.h"
#include "renderer.h"

#define MAX_BLOCK 1

HRESULT InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);




//�ړ�����u���b�N�̍\����
struct BLOCK {
	int			Texture{};
	D3DXVECTOR2 pos{};
	D3DXVECTOR2 old_pos{};
	D3DXVECTOR2 size{};
	D3DXVECTOR2 velocity{};
	int			MoveCount{};
	bool		Use{};
	float		rot{};
};



BLOCK* GetBlock(void);
void SetBlock_1(D3DXVECTOR2 pos);

