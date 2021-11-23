#include "count_block.h"
#include "collision.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "ground.h"

COUNT_BLOCK count_block[MAX_COUNT_BLOCK];
static PLAYER* player = GetPlayer();
static GROUND* ground = GetGround();
static BALL* ball = GetBall();


void InitCountBlock(void)
{
	//回数で壊れるブロック
	
	
	count_block[0].old_pos = count_block[0].pos;
	count_block[0].Texture = LoadTexture("data/TEXTURE/block.png");
	count_block[0].size.x = 60.0f;
	count_block[0].size.y = 60.0f;
	count_block[0].pos.x = 800.0f;
	count_block[0].pos.y = SCREEN_HEIGHT - ground->size.y - (count_block[0].size.y / 2);
	count_block[0].rot = 0.0f;
	count_block[0].HitCount = 10;
	count_block[0].Use = true;
	

}

void UninitCountBlock(void)
{
}

void UpdateCountBlock(void)
{
	count_block[0].old_pos = count_block[0].pos;
	//ボール使用中
	if (count_block[0].Use)
	{
		//ブロックにボールが当たった時
		if (CollisionBB(ball->pos, count_block[0].pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(count_block[0].size.x, count_block[0].size.y)))
		{
			ball->move *= -1;
			if (count_block[0].HitCount <= 0)
			{
				count_block[0].Use = false;
			}
			count_block[0].HitCount--;
		}

		

		//if (CollisionBB(player->pos, count_block[0].pos, D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(count_block[0].size.x, count_block[0].size.y)))
		//{
		//	
		//	//プレイヤーがブロックの上にいるとき
		//	if (player->pos.y + (player->size.y / 2) > count_block[0].pos.y - (count_block[0].size.y / 2))
		//	{
		//		player->pos.y = count_block[0].pos.y - ((player->size.y / 2) + (count_block[0].size.y / 2));
		//		//player->move.y = 0.0f;
		//	}

		//	//プレイヤーがブロックの左に当たっているとき
		//	if (player->pos.x + (player->size.x / 2) > count_block[0].pos.x - (count_block[0].size.x / 2))
		//	{
		//		player->move.x = 0.0f;
		//	}

		//	//プレイヤーがブロックの右に当たっているとき
		//	if (player->pos.x - (player->size.x / 2) > count_block[0].pos.x + (count_block[0].size.x / 2))
		//	{
		//		player->move.x = 0.0f;
		//	}
		//}
	}
}

void DrawCountBlock(void)
{
	D3DXCOLOR CountBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	if (count_block[0].Use)
	{
		//for (int i = 0; i < MAX_COUNTBLOCK; i++)
		//{
			DrawSpriteColorRotate(count_block[0].Texture, count_block[0].pos.x, count_block[0].pos.y,
			count_block[0].size.x, count_block[0].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			CountBlockCol, count_block[1].rot);
		//}
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
