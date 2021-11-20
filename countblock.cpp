#include "countblock.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"

COUNTBLOCK countblock[MAX_COUNTBLOCK];
static PLAYER* player = GetPlayer();



void InitCountBlock(void)
{
	//回数で壊れるブロック
	
	countblock[1].pos.x = 800.0f;
	countblock[1].pos.y = 480.0f;
	
	countblock[1].Texture = LoadTexture("data/TEXTURE/block.png");
	countblock[1].size.x = 60.0f;
	countblock[1].size.y = 60.0f;
	countblock[1].rot = 0.0f;
	countblock[1].HitCount = 3;
	countblock[1].Use = true;
	

}

void UninitCountBlock(void)
{
}

void UpdateCountBlock(void)
{



	//回数で壊れるブロックの判定

	if (CollisionBB(player->pos, countblock[1].pos, D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(countblock[1].size.x, countblock[1].size.y)))
	{

		player->move.x = 0.0f;

	}
	
}

void DrawCountBlock(void)
{
	D3DXCOLOR CountBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//for (int i = 0; i < MAX_COUNTBLOCK; i++)
	//{
		DrawSpriteColorRotate(countblock[1].Texture, countblock[1].pos.x, countblock[1].pos.y,
			countblock[1].size.x, countblock[1].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			CountBlockCol, countblock[1].rot);
	//}
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
	return &countblock[1];
}
