#include "move_block.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "collision.h"




static MOVE_BLOCK move_block[MAX_MOVE_BLOCK];
static PLAYER* player = GetPlayer();
static BALL* ball = GetBall();
int MoveCount = 0;

void InitMoveBlock(void)
{
		//�ړ��u���b�N����1
		move_block[0].Texture = LoadTexture("data/TEXTURE/green.png");
		move_block[0].pos.x = 300.0f;
		move_block[0].pos.y = 400.0f;
		move_block[0].old_pos = move_block[0].pos;
		move_block[0].size.x = 100.0f;
		move_block[0].size.y = 30.0f;
		move_block[0].velocity.x = 3.0f;
		move_block[0].velocity.y = 0.0f;
		move_block[0].rot = 0.0f;
		move_block[0].RidingPlayer = false;
		
}

void UninitMoveBlock(void)
{
	
}

void UpdateMoveBlock(void)
{
	move_block[0].old_pos = move_block[0].pos;

	//�u���b�N�̉����i���ԂŌv���Ă�j
	move_block[0].pos.x += move_block[0].velocity.x;
	MoveCount++;
	if (MoveCount >= 90)
	{
		move_block[0].velocity.x *= -1;
		MoveCount = 0;
	}



	//�{�[���Ɠ����u���b�N�̓����蔻��
	if (CollisionBB(ball->pos, move_block[0].pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[0].size.x, move_block[0].size.y)))
	{
		//�{�[�����u���b�N�ɓ���������
		if (CollisionBB(ball->pos, move_block[0].pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(move_block[0].size.x, move_block[0].size.y)))
		{

			//�u���b�N�̏�ɓ��������ꍇ
			if (ball->pos.y + (ball->size.y / 2) > move_block[0].pos.y - (move_block[0].size.y / 2))
			{
				ball->move.y *= -1;
			}

			//�u���b�N�̉��ɓ��������ꍇ
			if (ball->pos.y + (ball->size.y / 2) > move_block[0].pos.y - (move_block[0].size.y / 2))
			{
				ball->move.y *= -1;
			}

			//�u���b�N�̍��ɓ��������ꍇ
			if (ball->pos.x + (ball->size.x / 2) > move_block[0].pos.x - (move_block[0].size.x / 2))
			{
				ball->move.x *= -1;
			}

			//�u���b�N�̉E�ɓ��������ꍇ
			if (ball->pos.x - (ball->size.x / 2) > move_block[0].pos.x + (move_block[0].size.x / 2))
			{
				ball->move.x *= -1;
			}
		}
	}

}

void DrawMoveBlock(void)
{
	D3DXCOLOR MoveBlockCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = 0; i < 10; i++)
	{
		
			DrawSpriteColorRotate(move_block[i].Texture, move_block[i].pos.x, move_block[i].pos.y,
				move_block[i].size.x, move_block[i].size.y, 0.0f, 0.0f, 1.0f, 1.0f,
				MoveBlockCol, move_block[i].rot);

			
		
	}
}


void setMoveBlock(D3DXVECTOR2 pos, D3DXVECTOR2 size, D3DXVECTOR2 velocity)
{
	for (int i = 0; i < 10; i++)
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