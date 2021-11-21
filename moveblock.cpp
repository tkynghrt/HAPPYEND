#include "moveblock.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "collision.h"




static MOVEBLOCK moveblock[MAX_MOVEBLOCK];
static PLAYER* player = GetPlayer();
int MoveCount = 0;

void InitMoveBlock(void)
{
		//移動ブロックその1
		moveblock[0].Texture = LoadTexture("data/TEXTURE/green.png");
		moveblock[0].pos.x = 300.0f;
		moveblock[0].pos.y = 400.0f;
		moveblock[0].size.x = 100.0f;
		moveblock[0].size.y = 30.0f;
		moveblock[0].velocity.x = 3.0f;
		moveblock[0].velocity.y = 0.0f;
		moveblock[0].rot = 0.0f;
		moveblock[0].RidingPlayer = false;
		
}

void UninitMoveBlock(void)
{
	
}

void UpdateMoveBlock(void)
{
	//ブロックの往復（時間で計ってる）
	moveblock[0].pos.x += moveblock[0].velocity.x;
	MoveCount++;
	if (MoveCount >= 90)
	{
		moveblock[0].velocity.x *= -1;
		MoveCount = 0;
	}

	//プレイヤーと動くブロックの当たり判定
	if (CollisionBB(player->pos, moveblock[0].pos, D3DXVECTOR2(player->size.x, player->size.y), D3DXVECTOR2(moveblock[0].size.x, moveblock[0].size.y)))
	{
		//プレイヤーがブロックの上にいるとき
		if (player->pos.y + (player->size.y / 2) > moveblock[0].pos.y - (moveblock[0].size.y / 2)) 
		{
			player->pos.y = moveblock[0].pos.y - ((player->size.y / 2) + (moveblock[0].size.y / 2));
			player->pos.x += moveblock[0].velocity.x;

			//player->player_doingjump = false;
			//moveblock[0].RidingPlayer = true;
		}
		

		




		/*if (moveblock[i].velocity.y > 0.0f)
		{
			player->pos.y += moveblock[i].velocity.y;
		}*/

	}

}

void DrawMoveBlock(void)
{
	D3DXCOLOR MoveBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < 10; i++)
	{
		
			DrawSpriteColorRotate(moveblock[i].Texture, moveblock[i].pos.x, moveblock[i].pos.y,
				moveblock[i].size.x, moveblock[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
				MoveBlockCol, moveblock[i].rot);

			
		
	}
}


void setMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity)
{
	for (int i = 0; i < 10; i++)
	{
		if (!moveblock[i].Use)
		{
			moveblock[i].pos = pos;
			moveblock[i].size = size;
			moveblock[i].velocity = velocity;
			moveblock[i].Use = true;
			break;
		}
	}
}


MOVEBLOCK* GetMoveBlock(void)
{
	return &moveblock[0];
}