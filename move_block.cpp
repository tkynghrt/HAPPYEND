#include "move_block.h"
#include "All_Gimmick.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "collision.h"

static MOVE_BLOCK move_block[MAX_MOVE_BLOCK];
static PLAYER* player = GetPlayer();
static GIMMICK_POS* All_Move_Block_Pos = GetMove_Block();
static BALL* ball = GetBall();


HRESULT InitMoveBlock(void)
{
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		move_block[i].Texture = LoadTexture("data/TEXTURE/move_block.png");
		move_block[i].pos = All_Move_Block_Pos[i].move_block_pos;
		move_block[i].old_pos = move_block[i].pos;
		move_block[i].size.x = 60.0f;
		move_block[i].size.y = 60.0f;
		move_block[i].velocity.x = 0.3f;
		move_block[i].velocity.y = 0.3f;
		move_block[i].MoveCount = 0;
		move_block[i].rot = -PI / 2;
		move_block[i].Use = true;
	}
	return S_OK;
}

void UninitMoveBlock(void)
{
	
}

void UpdateMoveBlock(void)
{
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		move_block[i].old_pos = move_block[i].pos;

		//ブロックの往復（時間で計ってる）
		move_block[i].pos.x += move_block[i].velocity.x;
		move_block[i].MoveCount++;
		if (move_block[i].MoveCount >= 900)
		{
			move_block[i].velocity.x *= -1;
			move_block[i].MoveCount = 0;
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
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		return &move_block[i];
	}
}