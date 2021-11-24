#include "count_block.h"
#include "collision.h"
#include "All_Gimmick_Pos.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

COUNT_BLOCK count_block[MAX_COUNT_BLOCK];
static PLAYER* player = GetPlayer();
static BALL* ball = GetBall();
static GIMMICK_POS* All_Gimmick_Pos = GetGimmick_Pos();

HRESULT InitCountBlock(void)
{
	//‰ñ”‚Å‰ó‚ê‚éƒuƒƒbƒN
	
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		count_block[i].Use = true;
		count_block[i].Texture = LoadTexture("data/TEXTURE/block.png");
		count_block[i].size.x = 60.0f;
		count_block[i].size.y = 60.0f;
		count_block[i].pos = All_Gimmick_Pos[i].count_block_pos;
		count_block[i].old_pos = count_block[i].pos;
		count_block[i].rot = 0.0f;
		count_block[i].HitCount = 10;
	}
	return S_OK;
}

void UninitCountBlock(void)
{
}

void UpdateCountBlock(void)
{
	count_block[0].old_pos = count_block[0].pos;
	
	

}

void DrawCountBlock(void)
{
	D3DXCOLOR CountBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if (count_block[0].Use)
	{
		for (int i = 0; i < MAX_COUNT_BLOCK; i++)
		{
			DrawSpriteColorRotate(count_block[i].Texture, count_block[i].pos.x, count_block[i].pos.y,
			count_block[i].size.x, count_block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			CountBlockCol, count_block[i].rot);
		}
	}
}


void setCountBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity)
{
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		if (!count_block[i].Use)
		{
			count_block[i].pos = pos;
			count_block[i].size = size;
			count_block[i].Use = true;
			break;
		}
	}
}

COUNT_BLOCK* GetCountBlock(void)
{
	return &count_block[0];
}
