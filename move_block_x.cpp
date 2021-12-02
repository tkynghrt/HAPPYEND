#include "move_block_x.h"
#include "All_Gimmick.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "collision.h"

static MOVE_BLOCK_X move_block_x[MAX_MOVE_BLOCK_X];
static PLAYER* player = GetPlayer();
static GIMMICK_POS* All_Move_Block_X_Pos = GetMove_Block_X();
static BALL* ball = GetBall();


HRESULT InitMoveBlock_X(void)
{
	for (int i = 0; i < MAX_MOVE_BLOCK_X; i++)
	{
		move_block_x[i].Texture = LoadTexture("data/TEXTURE/move_block.png");
		move_block_x[i].pos = All_Move_Block_X_Pos[i].move_block_pos_x;
		move_block_x[i].old_pos = move_block_x[i].pos;
		move_block_x[i].size.x = 60.0f;
		move_block_x[i].size.y = 60.0f;
		move_block_x[i].velocity.x = 3.0f;
		move_block_x[i].velocity.y = 3.0f;
		move_block_x[i].MoveCount = 0;
		move_block_x[i].rot = -PI / 2;
		move_block_x[i].Use = true;
	}
	return S_OK;
}

void UninitMoveBlock_X(void)
{
	
}

void UpdateMoveBlock_X(void)
{
	for (int i = 0; i < MAX_MOVE_BLOCK_X; i++)
	{
		move_block_x[i].old_pos = move_block_x[i].pos;

		//ブロックの往復（時間で計ってる）
		move_block_x[i].pos.x += move_block_x[i].velocity.x;
		move_block_x[i].MoveCount++;
		if (move_block_x[i].MoveCount >= 90)
		{
			move_block_x[i].velocity.x *= -1;
			move_block_x[i].MoveCount = 0;
		}
	}

}

void DrawMoveBlock_X(void)
{
	D3DXCOLOR MoveBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < MAX_MOVE_BLOCK_X; i++)
	{
		DrawSpriteColorRotate(move_block_x[i].Texture, move_block_x[i].pos.x, move_block_x[i].pos.y,
			move_block_x[i].size.x, move_block_x[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
			MoveBlockCol, move_block_x[i].rot);
	}
}


void setMoveBlock_X(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity)
{
	for (int i = 0; i < MAX_MOVE_BLOCK_X; i++)
	{
		if (!move_block_x[i].Use)
		{
			move_block_x[i].pos = pos;
			move_block_x[i].size = size;
			move_block_x[i].velocity = velocity;
			move_block_x[i].Use = true;
			break;
		}
	}
}


MOVE_BLOCK_X* GetMoveBlock_X(void)
{
		return move_block_x;
}