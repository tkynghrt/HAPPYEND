#pragma once
#include "main.h"
#include "renderer.h"

void InitMoveBlock(void);
void UninitMoveBlock(void);
void UpdateMoveBlock(void);
void DrawMoveBlock(void);

//移動ブロック総数
#define MAX_MOVE_BLOCK	10

void setMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity);

//移動するブロックの構造体
struct MOVE_BLOCK {
	int Texture;
	D3DXVECTOR2 pos;
	D3DXVECTOR2 old_pos;
	D3DXVECTOR2 size;
	D3DXVECTOR2 velocity;
	bool		Use;
	bool		RidingPlayer;
	float		rot;
};

typedef enum {
	level_1,
	level_2,
	level_3,
	level_4,
	level_5,
	
}SPEED_LEVEL;

MOVE_BLOCK* GetMoveBlock(void);


