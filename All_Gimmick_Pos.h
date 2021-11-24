#pragma once
#include "main.h"
#include "ground.h"

static GROUND* ground = GetGround();

HRESULT InitAllGimmickPos(void);


//各ブロック総数
#define MAX_GIMMICK	100

//表示する回数で壊れるブロック総数
#define MAX_COUNT_BLOCK	1
//表示する特定の速度で壊れるブロック総数
#define MAX_ACCELE_BLOCK	1
//表示する移動ブロック総数
#define MAX_MOVE_BLOCK	1
//表示するコイン総数
#define MAX_COIN	1

//回数で壊れるブロックの構造体
struct GIMMICK_POS {
	D3DXVECTOR2 count_block_pos;	//回数で壊れるブロック
	D3DXVECTOR2 move_block_pos;		//移動するブロック
	D3DXVECTOR2 accele_block_pos;	//スピードレベルで壊れるブロック
	D3DXVECTOR2 coin;	//コイン
};

GIMMICK_POS* GetGimmick_Pos(void);

