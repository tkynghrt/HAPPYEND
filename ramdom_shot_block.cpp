#include "ramdom_shot_block.h"
#include "texture.h"
#include "sprite.h"


RAMDOM_SHOT_BLOCK Ramdom_Shot_Block[MAX_RAMDOM_SHOT_BLOCK];

HRESULT InitRamdom_Shot_Block(void)
{
	for (int i = 0; i < MAX_RAMDOM_SHOT_BLOCK; i++)
	{
		Ramdom_Shot_Block[i].use = false;
		//Ramdom_Shot_Block[i].Texture = warpTexture3;
		Ramdom_Shot_Block[i].size = D3DXVECTOR2(60.0f, 60.0f);
	}
	return S_OK;
}

void UninitRamdom_Shot_Block(void)
{

}

void UpdateRamdom_Shot_Block(void)
{
}

void DrawRamdom_Shot_Block(void)
{
}

void SetRamdom_Shot_Block(D3DXVECTOR2 pos)
{

}

RAMDOM_SHOT_BLOCK* GetRamdom_Shot_Block(void)
{
	return &Ramdom_Shot_Block[0];
}
