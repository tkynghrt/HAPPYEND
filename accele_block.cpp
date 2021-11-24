#include "accele_block.h"
#include "collision.h"
#include "All_Gimmick_Pos.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

ACCELE_BLOCK accele_block[MAX_ACCELE_BLOCK];


static GIMMICK_POS* All_Gimmick_Pos = GetGimmick_Pos();

HRESULT InitAcceleBlock(void)
{
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		accele_block[i].Texture = LoadTexture("data/TEXTURE/pink.png");
		accele_block[i].size.x = 60.0f;
		accele_block[i].size.y = 60.0f;
		accele_block[i].pos = All_Gimmick_Pos[i].accele_block_pos;
		accele_block[i].rot = 0.0f;
		accele_block[i].HitCount = 10;
		accele_block[i].Use = true;
		accele_block[i].level = 3;
	}
	return S_OK;
}

void UninitAcceleBlock(void)
{
}

void UpdateAcceleBlock(void)
{
}

void DrawAcceleBlock(void)
{
	D3DXCOLOR CountBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if (accele_block[0].Use)
	{
		//for (int i = 0; i < MAX_COUNTBLOCK; i++)
		//{
		DrawSpriteColorRotate(accele_block[0].Texture, accele_block[0].pos.x, accele_block[0].pos.y,
			accele_block[0].size.x, accele_block[0].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			CountBlockCol, accele_block[0].rot);
		//}
	}
}

ACCELE_BLOCK* GetAcceleBlock(void)
{
	return &accele_block[0];
}
