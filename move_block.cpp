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
		move_block[i].Texture = LoadTexture("data/TEXTURE/move_block.png");
		move_block[i].old_pos = move_block[i].pos;
		move_block[i].size = D3DXVECTOR2(60.0f,60.0f);
		move_block[i].velocity.x = 3.0f;
		move_block[i].velocity.y = 3.0f;
		move_block[i].rot = PI / 2;
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

		//�u���b�N�̉����i���ԂŌv���Ă�j
		move_block[i].pos.x += move_block[i].velocity.x;
		move_block[i].MoveCount++;
		if (move_block[i].MoveCount >= 90)
		{
			move_block[i].velocity.x *= -1;
			move_block[i].MoveCount = 0;
			move_block[i].rot *= -1;
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
			DrawSpriteColorRotate(move_block[i].Texture, move_block[i].pos.x, move_block[i].pos.y,
				move_block[i].size.x, move_block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
				MoveBlockCol, move_block[i].rot);
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
		//�܂��\������Ă��Ȃ��ꏊ��T��
		if (!move_block[i].use)
		{
			move_block[i].pos = pos;
			move_block[i].use = true;
			break;
		}
	}
}