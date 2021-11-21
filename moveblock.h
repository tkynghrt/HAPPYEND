#pragma once
#include "main.h"
#include "renderer.h"

void InitMoveBlock(void);
void UninitMoveBlock(void);
void UpdateMoveBlock(void);
void DrawMoveBlock(void);

//�ړ��u���b�N����
#define MAX_MOVEBLOCK	10

void setMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity);

//�ړ�����u���b�N�̍\����
struct MOVEBLOCK {
	int Texture;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 old_pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 velocity;
	bool		Use;
	bool		RidingPlayer;
	float		rot;
};

MOVEBLOCK* GetMoveBlock(void);


