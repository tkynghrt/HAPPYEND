#include "countblock.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

COUNTBLOCK countblock[MAX_COUNTBLOCK];
static PLAYER* player = GetPlayer();
static BALL* Ball = GetBall();


void InitCountBlock(void)
{
	//回数で壊れるブロック
	
	countblock[0].pos.x = 800.0f;
	countblock[0].pos.y = 480.0f;
	countblock[0].Texture = LoadTexture("data/TEXTURE/block.png");
	countblock[0].size.x = 60.0f;
	countblock[0].size.y = 60.0f;
	countblock[0].rot = 0.0f;
	countblock[0].HitCount = 10;
	countblock[0].Use = true;
	

}

void UninitCountBlock(void)
{
}

void UpdateCountBlock(void)
{


	if (countblock[1].Use)
	{
		//ボールが当たった時
		if (CollisionBB(Ball->pos, countblock[0].pos, D3DXVECTOR2(Ball->size.x, Ball->size.y), D3DXVECTOR2(countblock[0].size.x, countblock[0].size.y)))
		{
			Ball->move *= -1;

			if (countblock[0].HitCount <= 0)
			{
				countblock[0].Use = false;
			}

			countblock[0].HitCount--;
		}
	}
}

void DrawCountBlock(void)
{
	D3DXCOLOR CountBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if (countblock[0].Use)
	{
		//for (int i = 0; i < MAX_COUNTBLOCK; i++)
		//{
			DrawSpriteColorRotate(countblock[0].Texture, countblock[0].pos.x, countblock[0].pos.y,
			countblock[0].size.x, countblock[0].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			CountBlockCol, countblock[1].rot);
		//}
	}
}


void setCountBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity)
{
	for (int i = 0; i < MAX_COUNTBLOCK; i++)
	{
		if (!countblock[i].Use)
		{
			countblock[i].pos = pos;
			countblock[i].size = size;
			countblock[i].Use = true;
			break;
		}
	}
}

COUNTBLOCK* GetCountBlock(void)
{
	return &countblock[0];
}
