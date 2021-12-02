#pragma once
#include "main.h"
#include "ground.h"

static GROUND* ground = GetGround();

HRESULT InitAllGimmickPos(void);

//マクロ定義
//各ブロック総数
#define MAX_GIMMICK	100

// 移動するブロック関連
//表示する総数(x軸)
#define MAX_MOVE_BLOCK_X	5
//表示する総数(y軸)
#define MAX_MOVE_BLOCK_Y	1

//回数で壊れるブロック関連
//表示する総数
#define MAX_COUNT_BLOCK	1

//特定の速度で壊れるブロック関連
//表示する総数
#define MAX_ACCELE_BLOCK	1
//速度レベル
#define	LEVEL_1		0
#define	LEVEL_2		1
#define	LEVEL_3		2
#define	LEVEL_4		3
#define	LEVEL_5		4


//普通のターゲットの総数
#define TARGET_MAX		1

//回数で壊れるターゲットの総数
#define MAX_TARGET_COUNT	1

//表示するコイン総数
#define MAX_COIN	1


//回数で壊れるブロックの構造体
struct GIMMICK_POS {
	//移動するブロック(x軸)
	D3DXVECTOR2 move_block_pos_x;
	//移動するブロック(y軸)
	D3DXVECTOR2 move_block_pos_y;

	//回数で壊れるブロック
	D3DXVECTOR2 count_block_pos;
	int			count_block_hit_count;

	//スピードレベルで壊れるブロック
	D3DXVECTOR2 accele_block_pos;
	int			accele_level;

	//普通のターゲット
	D3DXVECTOR2 normal_target_pos;

	//回数で壊れるターゲット
	D3DXVECTOR2 count_target_pos;

	//コイン
	D3DXVECTOR2 coin;	
};

//移動するブロック(x軸)
GIMMICK_POS* GetMove_Block_X(void);
//移動するブロック(y軸)
GIMMICK_POS* GetMove_Block_X(void);

//回数で壊れるブロック
GIMMICK_POS* GetCount_Block(void);

//スピードレベルで壊れるブロック
GIMMICK_POS* GetAccele_Block(void);

//普通のターゲット
GIMMICK_POS* GetNormal_Target(void);

//回数で壊れるターゲット
GIMMICK_POS* GetCount_Target(void);

//コイン
GIMMICK_POS* GetCoin_(void);
