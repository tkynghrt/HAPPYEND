#include "move_block.h"
#include "All_Gimmick_Pos.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "collision.h"

static MOVE_BLOCK move_block[MAX_MOVE_BLOCK];
static PLAYER* player = GetPlayer();
static GIMMICK_POS* All_Gimmick_Pos = GetGimmick_Pos();
static BALL* ball = GetBall();
int MoveCount = 0;

HRESULT InitMoveBlock(void)
{
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		move_block[i].Texture = LoadTexture("data/TEXTURE/green.png");
		move_block[i].pos = All_Gimmick_Pos[i].move_block_pos;
		move_block[i].old_pos = move_block[i].pos;
		move_block[i].size.x = 100.0f;
		move_block[i].size.y = 30.0f;
		move_block[i].velocity.x = 3.0f;
		move_block[i].velocity.y = 0.0f;
		move_block[i].rot = 0.0f;
		move_block[i].Use = true;
	}
	return S_OK;
}

void UninitMoveBlock(void)
{
	
}

void UpdateMoveBlock(void)
{
	for (int i = 0; i < MAX_ACCELE_BLOCK; i++)
	{
		move_block[i].old_pos = move_block[i].pos;

		//ブロックの往復（時間で計ってる）
		move_block[i].pos.x += move_block[i].velocity.x;
		MoveCount++;
		if (MoveCount >= 90)
		{
			move_block[i].velocity.x *= -1;
			MoveCount = 0;
		}
	}


	
		
		if (CollisionBB(ball->pos, move_block[0].pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[0].size.x, move_block[0].size.y)))
		{

			//ブロックの上に当たった場合
			if (ball->pos.y + (ball->size.y / 2) > move_block[0].pos.y - (move_block[0].size.y / 2))
			{
				ball->move.y *= -1;
			}

			//ブロックの下に当たった場合
			if (ball->pos.y + (ball->size.y / 2) > move_block[0].pos.y - (move_block[0].size.y / 2))
			{
				ball->move.y *= -1;
			}

			//ブロックの左に当たった場合
			if (ball->pos.x + (ball->size.x / 2) > move_block[0].pos.x - (move_block[0].size.x / 2))
			{
				ball->move.x *= -1;
			}

			//ブロックの右に当たった場合
			if (ball->pos.x - (ball->size.x / 2) > move_block[0].pos.x + (move_block[0].size.x / 2))
			{
				ball->move.x *= -1;
			}
		}
	

}

void DrawMoveBlock(void)
{
	D3DXCOLOR MoveBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		
			DrawSpriteColorRotate(move_block[i].Texture, move_block[i].pos.x, move_block[i].pos.y,
				move_block[i].size.x, move_block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
				MoveBlockCol, move_block[i].rot);

			
		
	}
}


void setMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity)
{
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		if (!move_block[i].Use)
		{
			move_block[i].pos = pos;
			move_block[i].size = size;
			move_block[i].velocity = velocity;
			move_block[i].Use = true;
			break;
		}
	}
}


MOVE_BLOCK* GetMoveBlock(void)
{
	return &move_block[0];
}