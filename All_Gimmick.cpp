//全ギミックのポジションはここで管理

#include "All_Gimmick.h"

//移動(x軸)するブロックのサイズ
#define MOVE_BLOCK_X		(60.0f)
//移動(Y軸)するブロックのサイズ
#define MOVE_BLOCK_Y		(60.0f)
//回数で壊れるブロックのサイズ
#define COUNT_BLOCK			(60.0f)
//スピードレベルで壊れるブロックのサイズ
#define ACCELE_BLOCK		(60.0f)
//コインのサイズ
#define COIN				(60.0f)

//地面の座標
#define GROUND (SCREEN_HEIGHT - ground->size.y - (60 / 2))

GIMMICK_POS Gimick_Pos[MAX_GIMMICK];

HRESULT InitAllGimmickPos(void)
{
	//移動するブロック(x軸)
	//座標
	Gimick_Pos[0].move_block_pos_x = D3DXVECTOR2(300.0f, 350.0f);
	Gimick_Pos[1].move_block_pos_x = D3DXVECTOR2(300.0f + MOVE_BLOCK_Y, 350.0f);
	Gimick_Pos[2].move_block_pos_x = D3DXVECTOR2(300.0f +(MOVE_BLOCK_Y * 2), 350.0f);
	Gimick_Pos[3].move_block_pos_x = D3DXVECTOR2(300.0f +(MOVE_BLOCK_Y * 3), 350.0f);
	Gimick_Pos[4].move_block_pos_x = D3DXVECTOR2(300.0f +(MOVE_BLOCK_Y * 4), 350.0f);

	//移動するブロック(y軸)
	//座標
	Gimick_Pos[0].move_block_pos_y = D3DXVECTOR2(300.0f, 350.0f);

	//回数で壊れるブロック
	//座標
	Gimick_Pos[0].count_block_pos = D3DXVECTOR2(800.0f, GROUND);
	//回数
	Gimick_Pos[0].count_block_hit_count = 3;

	//スピードレベルで壊れるブロック
	//座標
	Gimick_Pos[0].accele_block_pos = D3DXVECTOR2(100.0f, GROUND);
	//レベル
	Gimick_Pos[0].count_block_hit_count = LEVEL_3;

	//普通のターゲット
	Gimick_Pos[0].normal_target_pos = D3DXVECTOR2(600.0f, GROUND);

	//回数で壊れるターゲット
	Gimick_Pos[0].count_target_pos = D3DXVECTOR2(800.0f, GROUND);

	//コイン
	//座標
	Gimick_Pos[0].coin = D3DXVECTOR2(500.0f, GROUND);

return S_OK;
}
//移動するブロック
GIMMICK_POS* GetMove_Block_X(void)
{
	for (int i = 0; i < MAX_MOVE_BLOCK_X; i++)
	{
		return &Gimick_Pos[i];
	}
}
//回数で壊れるブロック
GIMMICK_POS* GetCount_Block(void)
{
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		return &Gimick_Pos[i];
	}
}
//スピードレベルで壊れるブロック
GIMMICK_POS* GetAccele_Block(void)
{
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		return &Gimick_Pos[i];
	}
}
//普通のターゲット
GIMMICK_POS* GetNormal_Target(void)
{
	for (int i = 0; i < TARGET_MAX; i++)
	{
		return &Gimick_Pos[i];
	}
}
//回数で壊れるターゲット
GIMMICK_POS* GetCount_Target(void)
{
	for (int i = 0; i < MAX_TARGET_COUNT; i++)
	{
		return &Gimick_Pos[i];
	}
}
//コイン
GIMMICK_POS* GetCoin_(void)
{
	for (int i = 0; i < MAX_COIN; i++)
	{
		return &Gimick_Pos[i];
	}
}