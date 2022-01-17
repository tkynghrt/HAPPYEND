#include "move_block.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "collision.h"

static MOVE_BLOCK move_block[MAX_MOVE_BLOCK] = {};
static PLAYER* player = GetPlayer();
static BALL* ball = GetBall();

HRESULT InitMoveBlock(void)
{

	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		move_block[i].Left_Texture = LoadTexture("data/TEXTURE/MoveBlock_Left.png");
		move_block[i].Right_Texture = LoadTexture("data/TEXTURE/MoveBlock_Right.png");
		move_block[i].old_pos = move_block[i].pos;
		move_block[i].size = D3DXVECTOR2(150.0f,60.0f);
		move_block[i].velocity.x = 3.0f;
		move_block[i].velocity.y = 3.0f;
		move_block[i].rot = 0.0f;
		move_block[i].use = false;
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
		if (move_block[i].MoveCount >= 60)
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
		if (move_block[i].use)
		{
			if (move_block[i].velocity.x > 0.0f)
			{
				DrawSpriteColorRotate(move_block[i].Right_Texture, move_block[i].pos.x, move_block[i].pos.y,
					move_block[i].size.x + 60.0f, move_block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
					MoveBlockCol, move_block[i].rot);
			}
			else
			{
				DrawSpriteColorRotate(move_block[i].Left_Texture, move_block[i].pos.x, move_block[i].pos.y,
					move_block[i].size.x + 60.0f, move_block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
					MoveBlockCol, move_block[i].rot);
			}
		}
		else
		{
			break;
		}
	}
}



MOVE_BLOCK* GetMoveBlock(void)
{
		return move_block;
}

void SetMoveBlock(D3DXVECTOR2 pos)
{
	for (int i = 0; i < MAX_MOVE_BLOCK; i++)
	{
		//まだ表示されていない場所を探す
		if (!move_block[i].use)
		{
			move_block[i].pos = pos;
			move_block[i].use = true;
			break;
		}
	}
}