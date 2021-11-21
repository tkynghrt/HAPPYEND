#include "moveblock.h"
#include "ball.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "collision.h"




static MOVEBLOCK moveblock[MAX_MOVEBLOCK];
static PLAYER* player = GetPlayer();
static BALL* ball = GetBall();
int MoveCount = 0;

void InitMoveBlock(void)
{
		//�ړ��u���b�N����1
		moveblock[0].Texture = LoadTexture("data/TEXTURE/green.png");
		moveblock[0].pos.x = 300.0f;
		moveblock[0].pos.y = 400.0f;
		moveblock[0].old_pos = moveblock[0].pos;
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
	moveblock[0].old_pos = moveblock[0].pos;

	//�u���b�N�̉����i���ԂŌv���Ă�j
	moveblock[0].pos.x += moveblock[0].velocity.x;
	MoveCount++;
	if (MoveCount >= 90)
	{
		moveblock[0].velocity.x *= -1;
		MoveCount = 0;
	}



	//�{�[���Ɠ����u���b�N�̓����蔻��
	if (CollisionBB(ball->pos, moveblock[0].pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(moveblock[0].size.x, moveblock[0].size.y)))
	{
		//�{�[�����u���b�N�ɓ���������
		if (CollisionBB(ball->pos, moveblock[0].pos, D3DXVECTOR2(ball->size.x, ball->size.y), D3DXVECTOR2(moveblock[0].size.x, moveblock[0].size.y)))
		{

			//�u���b�N�̏�ɓ��������ꍇ
			if (ball->pos.y + (ball->size.y / 2) > moveblock[0].pos.y - (moveblock[0].size.y / 2))
			{
				ball->move.y *= -1;
			}

			//�u���b�N�̉��ɓ��������ꍇ
			if (ball->pos.y + (ball->size.y / 2) > moveblock[0].pos.y - (moveblock[0].size.y / 2))
			{
				ball->move.y *= -1;
			}

			//�u���b�N�̍��ɓ��������ꍇ
			if (ball->pos.x + (ball->size.x / 2) > moveblock[0].pos.x - (moveblock[0].size.x / 2))
			{
				ball->move.x *= -1;
			}

			//�u���b�N�̉E�ɓ��������ꍇ
			if (ball->pos.x - (ball->size.x / 2) > moveblock[0].pos.x + (moveblock[0].size.x / 2))
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