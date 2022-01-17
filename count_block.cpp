#include "count_block.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

COUNT_BLOCK count_block[MAX_COUNT_BLOCK];
static PLAYER* player = GetPlayer();
static BALL* ball = GetBall();

HRESULT InitCountBlock(void)
{
	count_block[0].Texture_Number = LoadTexture("data/TEXTURE/CountBlock1.png");
	count_block[1].Texture_Number = LoadTexture("data/TEXTURE/CountBlock2.png");
	count_block[2].Texture_Number = LoadTexture("data/TEXTURE/CountBlock3.png");

	//回数で壊れるブロック
	
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		count_block[i].use = false;
		count_block[i].Texture = count_block[3].Texture_Number;
		count_block[i].size = D3DXVECTOR2(60.0f, 60.0f);
	}
	return S_OK;
}

void UninitCountBlock(void)
{
}

void UpdateCountBlock(void)
{
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		if(count_block[i].use)
		{
			count_block[i].old_pos = count_block[i].pos;
			count_block[i].Texture = count_block[count_block[i].HitCount].Texture_Number;
		}
	}
}

void DrawCountBlock(void)
{
	D3DXCOLOR CountBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		if (count_block[i].use)
		{
		DrawSpriteColorRotate(count_block[i].Texture, count_block[i].pos.x, count_block[i].pos.y,
		count_block[i].size.x, count_block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
		CountBlockCol, count_block[i].rot);
		}
	}
}


void SetCountBlock(D3DXVECTOR2 pos, int count)
{
	for (int i = 0; i < MAX_COUNT_BLOCK; i++)
	{
		//まだ表示されていない場所を探す
		if (!count_block[i].use)
		{
			count_block[i].pos = pos;
			count_block[i].HitCount = count;
			count_block[i].use = true;
			break;
		}
	}
}

COUNT_BLOCK* GetCountBlock(void)
{
	return count_block;
}