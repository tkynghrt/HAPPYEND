#include "ground.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

GROUND ground[MAX_GROUND] = {};
static PLAYER* player = GetPlayer();
static BALL* ball = GetBall();


void InitGround(void)
{
	//回数で壊れるブロック
	for (int i = 0; i < MAX_GROUND; i++)
	{
		ground[i].pos = D3DXVECTOR2(0.0f, 0.0f);
		ground[i].Texture = LoadTexture("data/TEXTURE/ground.jpeg");
		ground[i].size = D3DXVECTOR2(60.0f, 60.0f);
		ground[i].use = false;
	}
}

void UninitGround(void)
{
}

void UpdateGround(void)
{
	
}

void DrawGround(void)
{
	D3DXCOLOR CountBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	
	for (int i = 0; i < MAX_GROUND; i++)
	{
		if (ground[i].use)
		{
			DrawSpriteColorRotate(ground[i].Texture, ground[i].pos.x, ground[i].pos.y,
				ground[i].size.x, ground[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
				CountBlockCol, 0.0f);
		}
		else
		{
			break;
		}
	}
}

GROUND* GetGround(void)
{
	return &ground[0];
}

void SetGround(D3DXVECTOR2 pos)
{
	for (int i = 0; i < MAX_GROUND; i++)
	{
		//まだ表示されていない場所を探す
		if (!ground[i].use)
		{
			ground[i].pos = pos;
			ground[i].use = true;
			break;
		}
	}
}