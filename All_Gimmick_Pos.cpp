//全ギミックのポジションはここで管理

#include "All_Gimmick_Pos.h"


//地面の座標
#define GROUND (SCREEN_HEIGHT - ground->size.y - (60 / 2))

GIMMICK_POS Gimick_Pos[MAX_GIMMICK];

HRESULT InitAllGimmickPos(void)
{

	//移動するブロックの座標
	Gimick_Pos[0].move_block_pos = D3DXVECTOR2(300.0f, 350.0f);

	//回数で壊れるブロックの座標
	Gimick_Pos[0].count_block_pos = D3DXVECTOR2(800.0f, GROUND);

	//スピードレベルで壊れるブロックの座標
	Gimick_Pos[0].accele_block_pos = D3DXVECTOR2(100.0f, GROUND);

	//コインの座標
	Gimick_Pos[0].coin = D3DXVECTOR2(500.0f, GROUND);

return S_OK;
}

GIMMICK_POS* GetGimmick_Pos(void)
{
	for (int i = 0; i < 1; i++)
	{
		return &Gimick_Pos[i];
	}
}