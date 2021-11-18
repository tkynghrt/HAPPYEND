#include "countblock.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

COUNTBLOCK countblock[10];


void InitCountBlock(void)
{
	//‰ñ”‚Å‰ó‚ê‚éƒuƒƒbƒN
	
	countblock[1].pos.x = 800.0f;
	countblock[1].pos.y = 400.0f;
	for (int i = 0; 0 < 10; i++)
	{
		countblock[i].Texture = LoadTexture("data/TEXTURE/block.png");
		countblock[i].size.x = 30.0f;
		countblock[i].size.y = 30.0f;
		countblock[i].velocity.x = 3.0f;
		countblock[i].velocity.y = 0.0f;
		countblock[i].rot = 0.0f;
		countblock[i].HitCount = 3;
	}

}

void UninitCountBlock(void)
{
}

void UpdateCountBlock(void)
{
	if (countblock[1].Use)
	{
		if (CollisionBB(BallPos.x, BallPos.y, BallSize.x, BallSize.y,
			countblock[1].pos.x, countblock[1].pos.y, countblock[1].size.x, countblock[1].size.y))
			//SetHitFlag();
	}
}

void DrawCountBlock(void)
{
}


void setCountBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity)
{
	for (int i = 0; i < 10; i++)
	{
		if (!countblock[i].Use)
		{
			countblock[i].pos = pos;
			countblock[i].size = size;
			countblock[i].velocity = velocity;
			countblock[i].Use = true;
			break;
		}
	}
}