#include "countblock.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

COUNTBLOCK countblock[MAX_COUNTBLOCK];


void InitCountBlock(void)
{
	//âÒêîÇ≈âÛÇÍÇÈÉuÉçÉbÉN
	
	countblock[1].pos.x = 800.0f;
	countblock[1].pos.y = 400.0f;
	
		countblock[1].Texture = LoadTexture("data/TEXTURE/block.png");
		countblock[1].size.x = 30.0f;
		countblock[1].size.y = 30.0f;
		countblock[1].velocity.x = 3.0f;
		countblock[1].velocity.y = 0.0f;
		countblock[1].rot = 0.0f;
		countblock[1].HitCount = 3;
	

}

void UninitCountBlock(void)
{
}

void UpdateCountBlock(void)
{
	
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